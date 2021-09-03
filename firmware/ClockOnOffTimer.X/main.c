/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18877
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <string.h>

#include "mcc_generated_files/mcc.h"
#include "config.h"
#include "sys_time.h"
#include "text_display.h"
#include "clock.h"
#include "time_day.h"
#include "display_utils.h"
#include "motor_alarm.h"
#include "alarm_utils.h"
#include "motor_utils.h"
#include "dual_alarm_utils.h"
#include "menu.h"
#include "button.h"
//pir
#include "smart_pir.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    config_devices();
    load_motor_alarms_default();
    init_menus();
    set_mode(PIR_MODE);

    button_t button;
    uint32_t time_menu_last_event = sys_time_get_ms();
    uint32_t time_last_button_event = sys_time_get_ms();
    menu_t *current_menu;
    while (1)
    {
        // Add your application code
	// monitor the time when the motor should be off
	motor_spin_time_monitor(get_motor(), get_time_to_spin());
	current_menu = get_current_menu();
	// is timeout menu?
	if (sys_time_get_ms() - time_menu_last_event > current_menu->timeout_ms )
	{
		time_menu_last_event = sys_time_get_ms();
		current_menu->on_timeout();
	}
	button = get_user_input();
	if(button == button_ok)
	{
		time_menu_last_event = sys_time_get_ms();
		time_last_button_event = time_menu_last_event;
		current_menu->on_ok();
	}
	else if(button == button_dec)
	{
		time_menu_last_event = sys_time_get_ms();
		time_last_button_event = time_menu_last_event;
		current_menu->on_dec();
	}
	else if(button == button_inc)
	{
		time_menu_last_event = sys_time_get_ms();
		time_last_button_event = time_menu_last_event;
		current_menu->on_inc();
	}
	//is time to sleep?
	if (sys_time_get_ms() - time_last_button_event > SLEEP_TIMEOUT_MS )
	{
		menu_sleep();
	}
	//mode validation
	if (get_mode() == ALARM_MODE)
	{
		/*uint8_t count = count_motor_alarms();
		uint8_t idx;
		motor_alarms_index_backup();
		motor_alarm_t *alarm = get_first_motor_alarm();
		if (alarm != NULL)
		{
			time_day_t *current_time = get_rtc_timeday();
			for (idx = 0; idx < count; idx++)
			{
				if (is_alarm_time(&alarm->alarm, current_time))
				{
					alarm->alarm.callback_fn();
				}
				alarm = get_next_motor_alarm();
			}
		}
		motor_alarms_index_restore();*/

		uint8_t idx;
		time_day_t *current_time = get_rtc_timeday();
		dual_day_alarm_t *alarms = get_dualday_alarms();
		for (idx = 0; idx < 7; idx++)
		{
			if (current_time->day_of_week == alarms->day)
			{
				if (alarms->alarm1.callback_fn != NULL &&
						alarms->alarm1.time.pm == current_time->pm &&
						alarms->alarm1.time.hour == current_time->hour &&
						alarms->alarm1.time.minute == current_time->minute && 
						alarms->alarm1.time.second == current_time->second)
				{
					alarms->alarm1.callback_fn();
				}

				if (alarms->alarm2.callback_fn != NULL &&
						alarms->alarm2.time.pm == current_time->pm &&
						alarms->alarm2.time.hour == current_time->hour &&
						alarms->alarm2.time.minute == current_time->minute && 
						alarms->alarm2.time.second == current_time->second)
				{
					alarms->alarm2.callback_fn();
				}
			}
			alarms++;
		}
	}
	else if (get_mode() == PIR_MODE)
	{
		smart_pir_t *pir = get_pir();
		smart_pir_device_monitor(pir);
	}
	else if (get_mode() == MANUAL_MODE)
	{

	}
    }
}

/**
 End of File
*/
