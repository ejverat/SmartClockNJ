#include "text_display.h"
#include "sys_time.h"
#include "mcc_generated_files/delay.h"

static void pulse_enable(text_display_t *display)
{
	display->enable_low_fn();
	DELAY_microseconds(10);
	display->enable_high_fn();
	DELAY_microseconds(10);
	display->enable_low_fn();
	DELAY_microseconds(100);
}

static void write_byte(text_display_t *display, uint8_t byte)
{
	if (display->bus_size == lcd_8bit)
	{
		display->write_fn(byte);
		pulse_enable(display);
	}
	else
	{
		display->write_fn(byte >> 4);
		pulse_enable(display);
		display->write_fn(byte&0x0f);
		pulse_enable(display);
	}
}

static void write_command(text_display_t *display, uint8_t value)
{
	display->rs_low_fn();
	write_byte(display, value);
}

static void write_data(text_display_t *display, uint8_t value)
{
	display->rs_high_fn();
	write_byte(display, value);
}

void display_begin(text_display_t* display)
{
	//wait for 50ms
	DELAY_milliseconds(50);
	
	//default pin status
	display->enable_low_fn();
	display->rs_low_fn();

	//create function command
	uint8_t disp_function = display->bus_size;
	disp_function |= display->font;
	if(display->height > 1)
	{
		disp_function |= LCD_2LINE;
	}
	if(display->bus_size == lcd_4bit)
	{
		//try to change to 4 bit
		display->write_fn(0x03);
		pulse_enable(display);
		//wait for min 4.1 ms
		DELAY_milliseconds(5);

		//try to change to 4 bit
		display->write_fn(0x03);
		pulse_enable(display);
		//wait for min 4.1 ms
		DELAY_milliseconds(5);

		//try to change to 4 bit
		display->write_fn(0x03);
		pulse_enable(display);
		//wait for min 4.1 ms
		DELAY_microseconds(200);

		//set 4 bit interface
		display->write_fn(0x02);
		pulse_enable(display);
	}
	else
	{
		//function set command sequence
		write_command(display, LCD_FUNCTIONSET | disp_function);
		DELAY_milliseconds(5);

		//function set command sequence
		write_command(display, LCD_FUNCTIONSET | disp_function);
		DELAY_microseconds(200);

		//last time
		write_command(display, LCD_FUNCTIONSET | disp_function);
	}

	write_command(display, LCD_FUNCTIONSET | disp_function);
	display->control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;

	display_on(display);
	display_clear(display);

	display->mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	write_command(display, LCD_ENTRYMODESET | display->mode);
}

void display_clear(text_display_t *display)
{
	write_command(display, LCD_CLEARDISPLAY);
	uint32_t start_time = sys_time_get_ms();
	while(sys_time_get_ms() - start_time < 2);
}

void display_home(text_display_t *display)
{
	write_command(display, LCD_RETURNHOME);
	uint32_t start_time = sys_time_get_ms();
	while(sys_time_get_ms() - start_time < 2);
}

void display_set_cursor(text_display_t *display, uint8_t col, uint8_t row)
{
	if (row >= 4)
	{
		row = 3;
	}
	if (row >= display->height)
	{
		row = display->height - 1;
	}

	uint8_t row_offsets[] = {0x00,0x40,display->width,display->width + 0x40};
	write_command(display, LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void display_on(text_display_t *display)
{
	display->control |= LCD_DISPLAYON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_off(text_display_t *display)
{
	display->control &= ~LCD_DISPLAYON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_cursor_on(text_display_t *display)
{
	display->control |= LCD_CURSORON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_cursor_off(text_display_t *display)
{
	display->control &= ~LCD_CURSORON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_blink_on(text_display_t *display)
{
	display->control |= LCD_BLINKON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_blink_off(text_display_t *display)
{
	display->control &= ~LCD_BLINKON;
	write_command(display, LCD_DISPLAYCONTROL | display->control);
}

void display_scroll_left(text_display_t *display)
{
	write_command(display,LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void display_scroll_right(text_display_t *display)
{
	write_command(display,LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void display_left_to_right(text_display_t *display)
{
	display->mode |= LCD_ENTRYLEFT;
	write_command(display, LCD_ENTRYMODESET | display->mode);
}

void display_right_to_left(text_display_t *display)
{
	display->mode &= ~LCD_ENTRYLEFT;
	write_command(display, LCD_ENTRYMODESET | display->mode);
}

void display_autoscroll_on(text_display_t *display)
{
	display->mode |= LCD_ENTRYSHIFTINCREMENT;
	write_command(display, LCD_ENTRYMODESET | display->mode);
}

void display_autoscroll_off(text_display_t *display)
{
	display->mode &= ~LCD_ENTRYSHIFTINCREMENT;
	write_command(display, LCD_ENTRYMODESET | display->mode);
}

void display_create_char(text_display_t *display, uint8_t location, uint8_t charmap[])
{
	location &= 0x7;
	write_command(display, LCD_SETCGRAMADDR | (location << 3));
	uint8_t i = 0;

	for(i = 0; i < 8; i++)
	{
		write_data(display, charmap[i]);
	}
}

void display_print_text(text_display_t *display, const char text[])
{
	while(*text != '\0')
	{
		write_data(display, *text);
        text++;
	}
}
