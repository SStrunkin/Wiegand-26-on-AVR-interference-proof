# Wiegand 26-on-AVR
Firmware for AVR ATmega168 microcontroller

A device with a Wiegand  interface is connected to the microcontroller via pins INT0 (Data0) and INT1 (Data1).
//**************************************************************************************************************

If you want change Wiegand type at 26 to another, you may change some variables in code:

uint32_t w26_data = 0;
uint8_t w26_receive_data_length = 26;

int32_t w26_recieve_data;													   ///< Wiegand 26 data, all bits from low abstract level
uint8_t w26_facility;														     ///< Divide w26_recieve_data, first byte	
uint8_t w26_middle_byte;													   ///< Divide w26_recieve_data, middle byte	
uint8_t w26_last_byte;                               ///< Divide w26_recieve_data, last byte

//**************************************************************************************************************


