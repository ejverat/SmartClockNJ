/* 
 * File:   text_display.h
 * Author: evera
 *
 * Created on July 5, 2021, 4:17 AM
 */

#ifndef TEXT_DISPLAY_H
#define	TEXT_DISPLAY_H

#include <inttypes.h>

#ifdef	__cplusplus
extern "C" {
#endif
	// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

	// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

	// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

	// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

	// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

	typedef enum {lcd_8bit = LCD_8BITMODE, lcd_4bit = LCD_4BITMODE} display_bus_size_t;
	typedef enum {font_5x8 = LCD_5x8DOTS, font_5x10 = LCD_5x10DOTS} display_font_t;
	typedef struct
	{
		unsigned int width;
		unsigned int height;
		display_bus_size_t bus_size;
		display_font_t font;
		uint8_t mode;
		uint8_t control;
		void (*write_fn)(uint8_t);
		void (*rs_low_fn)(void);
		void (*rs_high_fn)(void);
		void (*enable_low_fn)(void);
		void (*enable_high_fn)(void);
	} text_display_t;
	
	void display_begin(text_display_t *display);
	void display_clear(text_display_t *display);
	void display_home(text_display_t *display);
	void display_set_cursor(text_display_t *display, uint8_t col, uint8_t row);
	void display_on(text_display_t *display);
	void display_off(text_display_t *display);
	void display_cursor_on(text_display_t *display);
	void display_cursor_off(text_display_t *display);
	void display_blink_on(text_display_t *display);
	void display_blink_off(text_display_t *display);
	void display_scroll_left(text_display_t *display);
	void display_scroll_right(text_display_t *display);
	void display_left_to_right(text_display_t *display);
	void display_right_to_left(text_display_t *display);
	void display_autoscroll_on(text_display_t *display);
	void display_autoscroll_off(text_display_t *display);
	void display_create_char(text_display_t *display, uint8_t location, uint8_t charmap[]);
	void display_print_text(text_display_t *display, const char text[]);



#ifdef	__cplusplus
}
#endif

#endif	/* TEXT_DISPLAY_H */

