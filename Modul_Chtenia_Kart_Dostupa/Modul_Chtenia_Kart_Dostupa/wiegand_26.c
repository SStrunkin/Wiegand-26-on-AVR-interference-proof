/*
 * Interrupts.c
 *
 * Created: 05.03.2017 9:06:16
 *  Author: stepan
 */ 
#include "wiegand_26.h"



extern uint8_t programm_status_byte;								           ///< "extern" All program status byte	
extern uint32_t w26_recieve_data;									           ///< "extern" Put data received on Wieagand26 in this variable for higher processing \n(w26_data -> w26_recieve_data)

#define EXPECT_RISING	1											           ///< Expect rising front flag
#define EXPECT_FALLING	0											           ///< Expect falling front flag
#define STATUS_ACTIVE   1											           ///< Active line means, next front will be in this line
#define STATUS_PASSIVE  0											           ///< Passive line means, next front will be in other line

char d0_expect_rising_falling = EXPECT_FALLING;						           ///< Next front on D0 line
char d1_expect_rising_falling = EXPECT_FALLING;						           ///< Next front on D1 line
	
char d0_status;														           ///< Wiegand 26 lines status, can be STATUS_ACTIVE or STATUS_PASSIVE	
char d1_status;														           ///< Wiegand 26 lines status, can be STATUS_ACTIVE or STATUS_PASSIVE		

uint32_t w26_data = 0;												           ///< Wiegand 26 receive data, use first 26 bit
uint8_t w26_receive_bit_counter = 0;								           ///< Count to w26_recive_data_length
uint8_t w26_receive_data_length = 26;								           ///< Length of Weigand26 receive data
uint8_t w26_LOW_phase = 0;// 4;										           ///< Disable D0 and D1 interrupts, on time, when lines D0 and D1 must be stable
uint8_t w26_HIGH_phase = 0;// 59;									           ///< Disable D0 and D1 interrupts, on time, when lines D0 and D1 must be stable

/************************************************************************/
/* Define D0 D1 lines                                                                     */
/************************************************************************/
#define D0_INT_ENABLE           EIMSK |= (1 << INT0)						   ///< Enable interrupt on line D0 Wiegand 26	
#define D0_INT_DISABLE	        EIMSK &= ~(1 << INT0)						   ///< Disable interrupt on line D0 Wiegand 26	

#define D1_INT_ENABLE           EIMSK |= (1 << INT1)						   ///< Enable interrupt on line D1 Wiegand 26	
#define D1_INT_DISABLE	        EIMSK &= ~(1 << INT1)                          ///< Disable interrupt on line D1 Wiegand 26

#define D0_INT_RISING           EICRA |= (1 << ISC01)|(1 << ISC00)			   ///< Weigand 26 D0 interrupt rising front
#define D0_INT_FALLING          EICRA &= ~(1 << ISC00)					       ///< Weigand 26 D0 interrupt falling front

#define D1_INT_RISING	        EICRA |= (1 << ISC11)|(1 << ISC10)			   ///< Weigand26 D1 interrupt to rising front
#define D1_INT_FALLING	        EICRA &= ~(1 << ISC10)		            	   ///< Weigand26 D1 interrupt to falling front
#define D0_D1_INT_FALLING	    EICRA |= (1 << ISC11)|(1 << ISC01)             ///< Weigand26 D0 and D1 interrupt to falling front

#define D0_D1_INT_ENABLE		EIMSK |= (1 << INT0)|(1 << INT1)			   ///< Enable interrupts on line D0 and D1 Wiegand 26
#define D0_D1_INT_DISABLE		EIMSK &= ~(1 << INT0) & ~(1 << INT1)           ///< Disable interrupts on line D0 and D1 Wiegand 26
#define D0_D1_INT_FLAG_CLEAR	EIFR |= (1 << INTF1)|(1 << INTF0)	           ///< Clear Wiegand 26 on line D0 and D1 interrupts flags

/************************************************************************/
/* Define Timer0                                                                     */
/************************************************************************/

#define CLEAR_TO_COUNTER		TCNT0 = 0									   ///< Clear Timer0 counter 
#define CLEAR_T0_COMP_INT_FLAG	TIFR0 |= (1 << OCF0A)                          ///< Clear Timer0 compare interrupt flag

#define WAIT_W26_LOW_PHASE		OCR0A = w26_LOW_phase						   ///< Set compare value for time when Wigand 26 line in zero state 	
#define WAIT_W26_HIGH_PHASE		OCR0A = w26_HIGH_phase					       ///< Set compare value for time when Wigand 26 line in high state

#define TO_COMP_INT_ENABLE		TIMSK0 |= (1 << OCIE0A)						   ///< Enable Timer0 compare interrupt
#define TO_COMP_INT_DISABLE		TIMSK0 &= ~(1 << OCIE0A)					   ///< Disable Timer0 compare interrupt

#define  T0_OV_INT_ENABLE		TIMSK0 |= (1 << TOIE0);						   ///< Enable Timer0 overflow interrupt
#define  T0_OV_INT_DISABLE		TIMSK0 &= ~(1 << TOIE0);					   ///< Disable Timer0 overflow interrupt

#define  CLEAR_T0_OV_INT_FLAG	TIFR0 |= (1 << TOV0);                          ///< Clear Timer0 overflow interrupt flag

/************************************************************************/
/* Functions                                                                     */
/************************************************************************/

/**
@brief Wiegand 26 start initialization.
*/
void Weigand_26_ini()
{
    Weigand_26_D0_D1_int_ini();
    Weigand_26_TIMER0_ini();
}


/**
@brief Interrupts on Wiegand26 lines D0 and D1 expect falling fronts.\n
Reset w26_data and w26_receive_bit_counter. \n
Set Wiegand26 D0 and D1 lines STATUS_PASSIVE, we dont know which bit (0 or 1) will be first. \n
Set w26_LOW_phase and w26_HIGH_phase.
*/
void Weigand_26_D0_D1_int_ini()
{	
	d0_expect_rising_falling = EXPECT_FALLING;
	d1_expect_rising_falling = EXPECT_FALLING;	
	
	w26_data = 0;
	w26_receive_bit_counter = 0;
	
	d1_status = STATUS_PASSIVE;
	d0_status = STATUS_PASSIVE;        
    
    //EEPROM_write_byte(w26_HIGH_phase_eep_addr, 59);    
    w26_LOW_phase = get_w26_LOW_phase();
    w26_HIGH_phase = get_w26_HIGH_phase();
                
    USART_Transmit(w26_LOW_phase);
    USART_Transmit(w26_HIGH_phase);
	
	D0_D1_INT_FALLING;								 
	D0_D1_INT_FLAG_CLEAR;
	D0_D1_INT_ENABLE;
	
}

/**
@brief In interrupt vector: \n
we disable D0 and D1 line during \n
smaller then bit send time (line D0 or D1 in low state). \n
Enable Timer0 compare interrupt, where we enable \n
D0 or D1 lines to receive next front.
*/
void Weigand_26_low_phase_ini()
{
	DEBUG_LED_ON;
	
	D0_INT_DISABLE;
	D1_INT_DISABLE;
	D0_D1_INT_FLAG_CLEAR;
	
	CLEAR_TO_COUNTER;
	CLEAR_T0_COMP_INT_FLAG;
	WAIT_W26_LOW_PHASE;
	TO_COMP_INT_ENABLE;
	
	CLEAR_T0_OV_INT_FLAG;
	T0_OV_INT_ENABLE;
}

/**
@brief In interrupt vector: \n
we disable D0 and D1 line during \n
smaller then bit send time (line D0 or D1 in high state). \n
Enable Timer0 compare interrupt, where we enable \n
D0 or D1 lines to receive next front.
*/
void Weigand_26_high_phase_ini()
{
	DEBUG_LED_ON;
	
	D0_INT_DISABLE;
	D1_INT_DISABLE;
	D0_D1_INT_FLAG_CLEAR;
	
	CLEAR_TO_COUNTER;
	CLEAR_T0_COMP_INT_FLAG;
	WAIT_W26_HIGH_PHASE;
	TO_COMP_INT_ENABLE;
	
	CLEAR_T0_OV_INT_FLAG;
	T0_OV_INT_ENABLE;
}

/**
@brief Timer divider. \n
We need overflow time little bigger then Wiegand 26 one bit send time.
*/
void Weigand_26_TIMER0_ini()
{
	TCCR0B |= (1 << CS02);											           /// F_CPU / 256		
}


/**
@brief Set up and enable interrupt, depending on which front will be next. \n
Fill out w26_data.
*/
ISR(INT1_vect)
{														    
	if (d1_expect_rising_falling == EXPECT_FALLING)
	{
		D1_INT_RISING;
		d1_expect_rising_falling = EXPECT_RISING;
		d1_status = STATUS_ACTIVE;
		d0_status = STATUS_PASSIVE;
			
		w26_data <<= 1;
		w26_data += 1;						
						
		Weigand_26_low_phase_ini();		
	}
	else if (d1_expect_rising_falling == EXPECT_RISING)
	{
		D1_INT_FALLING;
		d1_expect_rising_falling = EXPECT_FALLING;	
		d1_status = STATUS_PASSIVE;
		d0_status = STATUS_PASSIVE;	
			
		w26_receive_bit_counter++;
		if (w26_receive_bit_counter < w26_receive_data_length)
		{
			TCNT0 = 0;
		}
		
		Weigand_26_high_phase_ini();		
	}		
}
//send b100011111110010100000111 = 9430279 = 0x8FE507 = 143_58631 (8bit + 16bit);
/**
@brief Set up and enable interrupt, depending on which front will be next. \n
Fill out w26_data.
*/
ISR(INT0_vect)
{														   // 
	if (d0_expect_rising_falling == EXPECT_FALLING)
	{
		D0_INT_RISING;
		d0_expect_rising_falling = EXPECT_RISING;
		d0_status = STATUS_ACTIVE;
		d1_status = STATUS_PASSIVE;
						
		w26_data <<= 1;					
				
		Weigand_26_low_phase_ini();									
	}
	else if (d0_expect_rising_falling == EXPECT_RISING)
	{
		D0_INT_FALLING;
		d0_expect_rising_falling = EXPECT_FALLING;
		d1_status = STATUS_PASSIVE;
		d0_status = STATUS_PASSIVE;
					
		w26_receive_bit_counter++;	
		if (w26_receive_bit_counter < w26_receive_data_length)
		{
			TCNT0 = 0;
		}
		
		Weigand_26_high_phase_ini();		
	}
}



/**
@brief Depending what front and on what line will be next \n
we enable interrupts.
*/
ISR (TIMER0_COMPA_vect)
{
	if ((d0_status == STATUS_ACTIVE) & (d1_status == STATUS_PASSIVE))
	{
		if (d0_expect_rising_falling == EXPECT_RISING)
		{
			D0_D1_INT_FLAG_CLEAR;
			D0_INT_ENABLE;
			TO_COMP_INT_DISABLE;
			DEBUG_LED_OFF;
		} 		
	} 
	else if ((d0_status == STATUS_PASSIVE) & (d1_status == STATUS_ACTIVE))
	{
		if (d1_expect_rising_falling == EXPECT_RISING)
		{
			D0_D1_INT_FLAG_CLEAR;
			D1_INT_ENABLE;			
			TO_COMP_INT_DISABLE;
			DEBUG_LED_OFF;
		} 		
	}
	else if ((d0_status == STATUS_PASSIVE) & (d1_status == STATUS_PASSIVE))
	{
		D0_D1_INT_FLAG_CLEAR;
		D0_INT_ENABLE;
		D1_INT_ENABLE;
		TO_COMP_INT_DISABLE;
		DEBUG_LED_OFF;
	}
	
	
	
}

/**
@brief In this interrupt we see:
1) If we receive all bytes in message, push message higher.
2) If we receive not all bytes in message (we receive noise), reset \n
w26_receive_bit_counter and w26_data.
*/
ISR (TIMER0_OVF_vect)
{		
	
	if (w26_receive_bit_counter == w26_receive_data_length)
	{
		w26_receive_bit_counter = 0;
		w26_recieve_data = w26_data;						
		w26_data = 0;		
		
		SET_W26_MESSAGE_READY_BIT;
	}
	else 
	{
		w26_receive_bit_counter = 0;
		w26_data = 0;
	}
		
	DEBUG_LED_ON;		
	DEBUG_LED_OFF;
	T0_OV_INT_DISABLE;	

}


