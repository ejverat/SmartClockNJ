#include <stdbool.h>

#include "config.h"
#include "mcp23s17.h"
#include "text_display.h"
#if defined (USE_DS3231)
#include "ds3231.h"
#elif  defined (USE_DS1307)
#include "ds1307.h"
#include "i2c_bus_config.h"
#endif
#include "motor.h"
#include "smart_pir.h"
#include "io_manager.h"
#include "sys_time.h"
#include "motor_alarm.h"
#include "dual_alarm_utils.h"
#include "motor_utils.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/i2c2_master.h"
#include "mcc_generated_files/pin_manager.h"

#define LCD_RS 		0b10000000
#define LCD_ENABLE 	0b01000000

#define DEFAULT_TIME_TO_SPIN_MS  2000

static mcp23s17_t io_expander;
static text_display_t display;
#if defined (USE_DS3231)
static ds3231_t rtc;
#elif defined (USE_DS1307)
static ds1307_t rtc;
static i2c_bus_t i2c_bus;
#endif
static motor_t motor;
static smart_pir_t spir;
static dual_day_alarm_t dualday_alarms[7];

static mode_t current_mode;
static uint32_t time_to_spin;


static void config_sys_timer();
static void config_io_expander();
static void config_display();
static void config_rtc();
static void config_motor();
static void motor_spin_to_left();
static void motor_spin_to_right();
static void config_pir();
static void pir_handler();
static void lcd_write(uint8_t byte);
static void lcd_rs_high();
static void lcd_rs_low();
static void lcd_enable_high();
static void lcd_enable_low();
#if defined (USE_DS3231)
static void i2c2_start(uint8_t address);
static void i2c2_stop();
static void i2c2_read(uint8_t* buff, size_t size);
static void i2c2_write(uint8_t* buff, size_t size);
#endif

void config_devices()
{
	config_sys_timer();
	config_io_expander();
	config_display();
	config_rtc();
	config_motor();
	config_pir();
	current_mode = PIR_MODE;
	time_to_spin = DEFAULT_TIME_TO_SPIN_MS;

	uint8_t idx;

	for (idx = 0; idx < 7; idx++)
	{
		set_dual_alarm_to_defaults(&dualday_alarms[idx]);
		dualday_alarms[idx].day = idx+1;
	}
}

text_display_t *get_text_display()
{
	return &display;
}

#if defined (USE_DS3231)
ds3231_t *get_ds3231()
{
	return &rtc;
}
#elif defined (USE_DS1307)
ds1307_t *get_ds1307()
{
	return &rtc;
}
#endif

motor_t *get_motor()
{
	return &motor;
}

smart_pir_t *get_pir()
{
	return &spir;
}

dual_day_alarm_t *get_dualday_alarms()
{
	return &dualday_alarms[0];
}

mode_t get_mode()
{
	return current_mode;
}

void set_mode(mode_t mode)
{
	current_mode = mode;
}
uint32_t get_time_to_spin()
{
	return time_to_spin;
}

void set_time_to_spin(uint32_t time_ms)
{
	time_to_spin = time_ms;
}

static void config_sys_timer()
{
    sys_time_reset();
    TMR0_SetInterruptHandler(sys_time_handler);
}

static void config_io_expander()
{
    io_expander.address = 0x00;
    io_expander.disable = spi_cs_high;
    io_expander.enable = spi_cs_low;
    io_expander.read_fn = SPI1_ReadByte;
    io_expander.write_fn = SPI1_ExchangeBlock;
    io_expander.porta_value = 0x00;
    io_expander.portb_value = 0x00;

    uint32_t start_time = sys_time_get_ms();
    while (sys_time_get_ms() - start_time <1000);
    
    SPI1_Open(SPI1_DEFAULT);
    mcp23s17_port_dir(&io_expander, mcp23s17_porta, 0b00000000);
    mcp23s17_port_dir(&io_expander, mcp23s17_portb, 0b00000000);

}

static void config_display()
{
    display.height = 2;
    display.width = 16;
    display.font = font_5x8;
    display.bus_size = lcd_8bit;
    display.write_fn = lcd_write;
    display.rs_high_fn = lcd_rs_high;
    display.rs_low_fn = lcd_rs_low;
    display.enable_high_fn = lcd_enable_high;
    display.enable_low_fn = lcd_enable_low;

    display_begin(&display);
}

static void config_rtc()
{
#if defined (USE_DS3231)
    rtc.start_fn = i2c2_start;
    rtc.stop_fn = i2c2_stop;
    rtc.read_fn = i2c2_read;
    rtc.write_fn = i2c2_write;

    ds3231_read_all(&rtc);
    // we change to am_pm format
    if (rtc.data.hours.f12_24 == 0)
    {
	    uint8_t hours = ds3231_get_hours(&rtc);
	    if ( hours > 12)
	    {
		    ds3231_set_hours_f12(&rtc, hours%12, true);
	    }
	    else if(hours == 12)
	    {
		    ds3231_set_hours_f12(&rtc, 12, true);
	    }
	    else if(hours == 0)
	    {
		    ds3231_set_hours_f12(&rtc, 12, false);
	    }
	    else
	    {
		    ds3231_set_hours_f12(&rtc, hours, false);
	    }
    }
#elif defined(USE_DS1307)
    i2c_bus_config(&i2c_bus);
    rtc.bus = &i2c_bus;
    ds1307_read_all(&rtc);

    // we change to am_pm format
    if (rtc.data.hours.f12_24 == 0 || rtc.data.seconds.ch == 1)
    {
	    uint8_t hours = ds1307_get_hours(&rtc);
	    if ( hours > 12)
	    {
		    ds1307_set_hours_f12(&rtc, hours%12, true);
	    }
	    else if(hours == 12)
	    {
		    ds1307_set_hours_f12(&rtc, 12, true);
	    }
	    else if(hours == 0)
	    {
		    ds1307_set_hours_f12(&rtc, 12, false);
	    }
	    else
	    {
		    ds1307_set_hours_f12(&rtc, hours, false);
	    }
	    ds1307_set_seconds(&rtc, 0);
    }
#endif
}

static void config_motor()
{
	motor.pin_dir1_high_fn = set_motor1_O1_high;
	motor.pin_dir1_low_fn = set_motor1_O1_low;
	motor.pin_dir2_high_fn = set_motor1_O2_high;
	motor.pin_dir2_low_fn = set_motor1_O2_low;
	set_motor_direction(&motor, off);
}
static void motor_spin_to_left()
{
	spin_motor_left(&motor);
}
static void motor_spin_to_right()
{
	spin_motor_right(&motor);
}

static void config_pir()
{
	spir.last_update=0;
	spir.status = false;
	spir.status_changed = false;
	spir.pir.pin_status_fn = get_PIR1;
	spir.device_status = false;
	spir.inactive_time =  (uint32_t)PIR_MINIMUM_INACTIVE_TIME;
	spir.disable_device_fn = motor_spin_to_left;
	spir.enable_device_fn = motor_spin_to_right;
	spir.pir.handler_fn = pir_handler;
	IOCCF6_SetInterruptHandler(spir.pir.handler_fn);
}
static void pir_handler()
{
	if (spir.pir.pin_status_fn() == HIGH)
	{
		set_pir_status(&spir,true);
	}
	else
	{
		set_pir_status(&spir,false);
	}
}
static void lcd_write(uint8_t byte)
{
	io_expander.portb_value = byte;
	mcp23s17_write_port(&io_expander, mcp23s17_portb);
}

static void lcd_rs_high()
{
	io_expander.porta_value |= LCD_RS;
	mcp23s17_write_port(&io_expander, mcp23s17_porta);
}


static void lcd_rs_low()
{
	io_expander.porta_value  &= ~LCD_RS;
	mcp23s17_write_port(&io_expander, mcp23s17_porta);
}

static void lcd_enable_high()
{
	io_expander.porta_value  |= LCD_ENABLE;
	mcp23s17_write_port(&io_expander, mcp23s17_porta);
}


static void lcd_enable_low()
{
	io_expander.porta_value  &= ~LCD_ENABLE;
	mcp23s17_write_port(&io_expander, mcp23s17_porta);
}

static void i2c2_start(uint8_t address)
{

	i2c2_error_t status;
	do
	{
		status = I2C2_Open(address);
	}while(I2C2_BUSY == status);
}

static void i2c2_stop()
{
	i2c2_error_t status;
	do
	{
		status = I2C2_Close();
	}while(I2C2_BUSY == status);
}

static void i2c2_read(uint8_t* buff, size_t size)
{
	I2C2_SetBuffer(buff, size);
	i2c2_error_t status;
	do
	{
		status = I2C2_MasterOperation(true);
	}while(I2C2_BUSY == status);
}

static void i2c2_write(uint8_t* buff, size_t size)
{
	I2C2_SetBuffer(buff, size);
	i2c2_error_t status;
	do
	{
		status = I2C2_MasterOperation(false);
	}while(I2C2_BUSY == status);
}
