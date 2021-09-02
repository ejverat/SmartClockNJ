#include "io_manager.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/spi1.h"

void set_motor1_O1_high()
{
	MOTOR1_O1_SetHigh();
}
void set_motor1_O1_low()
{
	MOTOR1_O1_SetLow();
}
void set_motor1_O2_high()
{
	MOTOR1_O2_SetHigh();
}
void set_motor1_O2_low()
{
	MOTOR1_O2_SetLow();
}

unsigned get_button0_status()
{
	return BUTTON0_GetValue();
}
unsigned get_button1_status()
{
	return BUTTON1_GetValue();
}
unsigned get_button2_status()
{
	return BUTTON2_GetValue();
}

unsigned get_PIR1()
{
    return PIR1_GetValue();
}
void spi_cs_low()
{
	IOEXP_NCS_SetLow();
}

void spi_cs_high()
{
	IOEXP_NCS_SetHigh();
}

void spi_write_bytes(uint8_t *bytes, unsigned int nbytes)
{
	while(nbytes)
	{
		SPI1_WriteByte(*bytes);
        while(!PIR3bits.SSP1IF);
	    PIR3bits.SSP1IF = 0;
		bytes++;
		nbytes--;
	}
}

