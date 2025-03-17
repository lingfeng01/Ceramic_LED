#include "LED.h"

bool djs_flag = 1;
uint8_t Code_table1[12] = {
    0x40, // 0
    0x4F, // 1
    0x22, // 2
    0x06, // 3
    0x0D, // 4
    0x14, // 5
    0x10, // 6
    0x4E, // 7
    0x00, // 8
    0x04, // 9
    0xFF, // null
    0x3F, // -
};
uint8_t Code_table2[12] = {
    0x40, // 0
    0x4F, // 1
    0x12, // 2
    0x06, // 3
    0x0D, // 4
    0x24, // 5
    0x20, // 6
    0x4E, // 7
    0x00, // 8
    0x04, // 9
    0xFF, // null
    0x3F, // -
};

uint8_t lingfeng[9] = {
    0x71,
    0x77,
    0x38,
    0x3E,
};

uint8_t Hex_to_cx(uint8_t hex, int i)
{
    uint8_t temp = 0;
    temp = (hex >> i) & 0x01;
    if (temp == 1)
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}
void LED_Clear()
{
    delay(10);
    LED_Set_num(1, 10);
    delay(10);
    LED_Set_num(2, 10);
    delay(10);
    LED_Set_num(3, 10);
    delay(10);
    LED_Set_num(4, 10);
    delay(10);
}

void LED_LF()
{
    int i = 0;
    for (i = 7; i >= 0; i--)
    {
        digitalWrite(LED_DS, Hex_to_cx(lingfeng[0], i));
        R1_CP();
    }
    for (i = 7; i >= 0; i--)
    {
        digitalWrite(LED_DS, Hex_to_cx(lingfeng[1], i));
        R2_CP();
    }
    for (i = 7; i >= 0; i--)
    {
        digitalWrite(LED_DS, Hex_to_cx(lingfeng[2], i));
        L1_CP();
    }
    for (i = 7; i >= 0; i--)
    {
        digitalWrite(LED_DS, Hex_to_cx(lingfeng[3], i));
        L2_CP();
    }
    display();
}

void LED_Set_num(int x, int num)
{
    int i = 0;
    if (x == 2 || x == 4)
    {
        for (i = 7; i >= 0; i--)
        {
            digitalWrite(LED_DS, Hex_to_cx(Code_table2[num], i));

            if (x == 1)
            {
                R1_CP();
            }
            else if (x == 2)
            {
                R2_CP();
            }
            else if (x == 3)
            {
                L1_CP();
            }
            else if (x == 4)
            {
                L2_CP();
            }
        }
    }
    else
    {
        for (i = 7; i >= 0; i--)
        {
            digitalWrite(LED_DS, Hex_to_cx(Code_table1[num], i));

            if (x == 1)
            {
                R1_CP();
            }
            else if (x == 2)
            {
                R2_CP();
            }
            else if (x == 3)
            {
                L1_CP();
            }
            else if (x == 4)
            {
                L2_CP();
            }
        }
    }

    display();
}

void loin(int x)
{
}

void countdown(int second)
{

    if (second != 0)
    {
        djs_flag = 1;
        for (int i = second; i >= 0; i--)
        {
            int minutes = i / 60;
            int secs = i % 60;

            // 显示分钟的十位数和个位数

            if (minutes / 10 == 0)
            {
                LED_Set_num(1, 10); // 高位为0时显示为10
            }
            else
            {
                LED_Set_num(1, minutes / 10);
            }

            if (minutes % 10 == 0 && minutes / 10 == 0)
            {
                LED_Set_num(2, 10); // 高位为0时显示为10
            }
            else
            {
                LED_Set_num(2, minutes % 10);
            }

            // 显示秒的十位数和个位数

            if (secs / 10 == 0)
            {
                LED_Set_num(3, 10); // 高位为0时显示为10
            }
            else
            {
                LED_Set_num(3, secs / 10);
            }

            if (secs % 10 == 0 && secs / 10 == 0)
            {
                LED_Set_num(4, 10); // 高位为0时显示为10
            }
            else
            {
                LED_Set_num(4, secs % 10);
            }

            esp_delay(1000); // 延迟1秒
        }
        Serial.println("倒计时结束");
        for (int j = 0; j < 5; j++)
        {
            LED_Set_num(1, 11);
            LED_Set_num(2, 11);
            LED_Set_num(3, 11);
            LED_Set_num(4, 11);
            esp_delay(500);
            LED_Set_num(1, 10);
            LED_Set_num(2, 10);
            LED_Set_num(3, 10);
            LED_Set_num(4, 10);
            esp_delay(500);
        }
        djs_flag = 0;
    }
    else
    {
        djs_flag = 1;
        LED_Set_num(1, 10);
        LED_Set_num(2, 10);
        LED_Set_num(3, 10);
        LED_Set_num(4, 10);
    }
}

void L1_CP()
{
    digitalWrite(LED_L1_CP, HIGH);
    delay(1);
    digitalWrite(LED_L1_CP, LOW);
}
void L2_CP()
{
    digitalWrite(LED_L2_CP, HIGH);
    delay(1);
    digitalWrite(LED_L2_CP, LOW);
}
void R1_CP()
{
    digitalWrite(LED_R1_CP, HIGH);
    delay(1);
    digitalWrite(LED_R1_CP, LOW);
}
void R2_CP()
{
    digitalWrite(LED_R2_CP, HIGH);
    delay(1);
    digitalWrite(LED_R2_CP, LOW);
}

void display()
{
    digitalWrite(LED_Dis, HIGH);
    delay(1);
    digitalWrite(LED_Dis, LOW);
}