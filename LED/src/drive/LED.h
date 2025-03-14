#ifndef __LED_H__
#define __LED_H__

#include <Arduino.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define LED_Dis D2
#define LED_DS D1
#define LED_L1_CP D0
#define LED_L2_CP D5
#define LED_R1_CP D6
#define LED_R2_CP D7

    void display();
    void LED_Clear();
    void LED_LF();
    void LED_Set_num(int x, int num);
    void loin(int x, int num);
    uint8_t Hex_to_cx(uint8_t hex, int i);
    void L1_CP();
    void L2_CP();
    void R1_CP();
    void R2_CP();

#ifdef __cplusplus
}
#endif

#endif // __LED_H__