#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include "drive/LED.h"
#include "systick.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

void GPIO_Init();
void Wifi_Inti();
void time_Inti();
void LED_Set_Time();
void LED_Set_Time2();

#endif // __MAIN_H__