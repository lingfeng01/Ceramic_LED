#ifndef __systick_H__
#define __systick_H__

#include <Arduino.h>
#include <Ticker.h>

void systick_Init();
volatile uint32_t get_time_tick();

#endif // __systick_H__