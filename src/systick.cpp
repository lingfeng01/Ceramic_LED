#include "systick.h"
Ticker ticker;

volatile uint32_t time_tick_count = 0;

void time_tick()
{
    time_tick_count++;
}
void systick_Init()
{

    ticker.attach_ms(1, time_tick);
}

volatile uint32_t get_time_tick()
{
    return time_tick_count;
}