#include "smart_pir.h"
#include "sys_time.h"
//DEBUG
/*
#include "config.h"
#include "mcc_generated_files/delay.h"
*/

void set_pir_status(smart_pir_t *pir, bool status)
{
	pir->status = status;
	pir->status_changed = true;
	pir->last_update = sys_time_get_ms();
}

void smart_pir_device_monitor(smart_pir_t *pir)
{
	if (pir->status_changed)
	{
		//text_display_t *display = get_text_display();
		if (pir->status == true)
		{
			/*display_home(display);
			display_print_text(display, "PIR HIGH");*/
			if (pir->device_status == false)
			{
				pir->enable_device_fn();
				pir->device_status = true;
				pir->status_changed = false;
			}
		}
		else
		{
			/*display_home(display);
			display_print_text(display, "PIR LOW");*/
			if (sys_time_get_ms() - pir->last_update > pir->inactive_time)
			{
				pir->disable_device_fn();
				pir->device_status = false;
				pir->status_changed = false;
			}
		}
	}
	//DELAY_milliseconds(1000);
}

