#include <main.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpudp;

int32_t timeZone = 8 * 3600;
const PROGMEM char *ntpServer = "ntp1.aliyun.com";
NTPClient timeClient(ntpudp, ntpServer, timeZone, 60000);

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
  // put your main code here, to run repeatedly :
  // int i = 0;
  // int j = 0;
  //
  // for (j = 1; j < 5; j++)
  // {
  //   for (i = 0; i < 10; i++)
  //   {
  //     LED_Set_num(j, i);
  //     delay(1000);
  //   }
  //   LED_Set_num(j, 10);
  // }
  LED_Set_Time();
  delay(1000);
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

void LED_Set_Time()
{
  Hour = timeClient.getHours();
  Minute = timeClient.getMinutes();
  Second = timeClient.getSeconds();
  int h1 = Hour / 10;
  int h2 = Hour % 10;
  int m1 = Minute / 10;
  int m2 = Minute % 10;
  int s1 = Second / 10;
  int s2 = Second % 10;
  if (h1 == 0)
  {
    h1 = 10;
  }
  if (m1 == 0)
  {
    m1 = 10;
  }
  if (s1 == 0)
  {
    s1 = 10;
  }

  LED_Set_num(1, h1);
  LED_Set_num(2, h2);
  LED_Set_num(3, m1);
  LED_Set_num(4, m2);
  Serial.print("Time:");
  Serial.print(Hour);
  Serial.print(":");
  Serial.print(Minute);
  Serial.print(":");
  Serial.println(Second);
}