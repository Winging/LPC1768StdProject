#include "clock-arch.h"
#include "LPC17xx.h"
#include "ucos_ii.h"
__IO clock_time_t Ticks;

#define LED_PIN 	(1<<6)


/* Timer init */
void clock_init(void)
{
	Ticks = OSTimeGet();

	// NXP: Initialize System tick timer
	// Generate interrupt each SYSTICK_PERIOD microsecond
	if (SysTick_Config((SystemCoreClock/CLOCK_CONF_SECOND))){
		// Capture error
		while (1);
	}
}

/* returned The current clock time, measured in system ticks */
clock_time_t clock_time(void)
{
  return OSTimeGet() -(Ticks);
}
