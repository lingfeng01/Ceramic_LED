#include <main.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpudp;

int8_t timeZone = 8 * 60 * 60;
const PROGMEM char *ntpServer = "ntp1.aliyun.com";
NTPClient timeClient(ntpudp, ntpServer, timeZone * 3600, 60000);
int Hour;
int Minute;
int Second;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println("Hello World\r\n");

  GPIO_Init();
  LED_Clear();
  Wifi_Inti();
  time_Inti();
}

void loop()
{
  int i = 0;
  int j = 0;
  // put your main code here, to run repeatedly :
  for (j = 1; j < 5; j++)
  {
    for (i = 0; i < 10; i++)
    {
      LED_Set_num(j, i);
      delay(1000);
    }
    LED_Set_num(j, 10);
  }

  // for (i = 0; i < 25; i++)
  // {
  //   if (i == 0 || i == 1 || i == 18 || i == 19 || i == 20 || i == 21 || i == 22 || i == 23)
  //   {
  //     loin(1, i);
  //   }
  //   else if (i == 2 || i == 3 || i == 17 || i == 18)
  //   {
  //     loin(2, i);
  //   }
  //   else if (i == 4 || i == 5 || i == 14 || i == 15)
  //   {
  //     loin(3, i);
  //   }

  //   else if (i == 6 || i == 7 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12 || i == 13)
  //   {
  //     loin(4, i);
  //   }
  //   delay(1000);
  // }
  // loin(3, 1);
}

void GPIO_Init()
{
  pinMode(LED_Dis, OUTPUT);
  pinMode(LED_DS, OUTPUT);
  pinMode(LED_L1_CP, OUTPUT);
  pinMode(LED_L2_CP, OUTPUT);
  pinMode(LED_R1_CP, OUTPUT);
  pinMode(LED_R2_CP, OUTPUT);
}
void Wifi_Inti()
{
  WiFi.begin("ZNCXZX.", ":zncxzx1234567890");

  while (WiFi.status() != WL_CONNECTED)
  {
    LED_LF();
    delay(500);
    LED_Clear();
    delay(100);
    Serial.print(".");
  }
  Serial.println("Local IP:");
  Serial.print(WiFi.localIP());
}

void time_Inti()
{
  timeClient.begin();
  timeClient.update();
  Hour = timeClient.getHours();
  Minute = timeClient.getMinutes();
  Second = timeClient.getSeconds();
  Serial.print("Time:");
  Serial.print(Hour);
  Serial.print(":");
  Serial.print(Minute);
  Serial.print(":");
  Serial.println(Second);
}