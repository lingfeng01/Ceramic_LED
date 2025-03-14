#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include "drive/LED.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

void GPIO_Init();
void Wifi_Inti();
void time_Inti();

#endif // __MAIN_H__