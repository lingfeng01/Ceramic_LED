#include <main.h>

WiFiUDP ntpudp;

int32_t timeZone = 8 * 3600;
const PROGMEM char *ntpServer = "ntp1.aliyun.com";
NTPClient timeClient(ntpudp, ntpServer, timeZone, 60000);

volatile uint32_t LED_pool_neg_time = 0;
volatile uint32_t countdown_pool_neg_time = 0;
int display_count = 0;

uint8_t Dismode = 1;
char str[64];
String rxbuff;

int Hour;
int Minute;
int Second;

int countdown_time = 0;
int login = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println("Hello World\r\n");
  systick_Init();
  GPIO_Init();
  LED_Clear();
  Wifi_Inti();
  time_Inti();
}

void loop()
{
  // put your main code here, to run repeatedly :
  rxbuff = Serial.readString();
  if (rxbuff == "mode=1")
  {
    Dismode = 1;
  }
  else if (rxbuff == "mode=2")
  {
    Dismode = 2;
  }
  else if (rxbuff == "mode=3")
  {
    djs_flag = 1;
    Dismode = 3;
  }
  else if (Dismode == 3)
  {
    if (atoi(rxbuff.c_str()) != 0)
    {
      djs_flag = 1;
      countdown_time = atoi(rxbuff.c_str());
    }
  }

  if (LED_pool_neg_time + 200 < get_time_tick())
  {
    if (Dismode == 1)
    {
      LED_Set_Time();
      Serial.println("Mode = 1");
    }
    if (Dismode == 2)
    {
      LED_Set_Time2();
      Serial.println("Mode = 2");
    }
    if (Dismode == 3)
    {
      if (djs_flag == 1)
      {
        Serial.println("Mode = 3");
        Serial.println("请输入倒计时时间");
        countdown(countdown_time);
        countdown_time = 0;
        countdown_pool_neg_time = get_time_tick();
      }
      if (djs_flag == 0)
      {
        if (countdown_pool_neg_time + 5000 < get_time_tick())
        {
          Dismode = 1;
          countdown_pool_neg_time = get_time_tick();
        }
      }
    }
    if (Dismode != 3)
    {
      display_count++;
      Serial.println(display_count);
    }
    if (display_count >= 60)
    {
      if (Dismode == 1)
      {
        Dismode = 2;
        display_count = 0;
      }
      else
      {
        Dismode = 1;
        display_count = 0;
      }
    }

    LED_pool_neg_time = get_time_tick();
  }
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

void LED_Set_Time2()
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

  LED_Set_num(1, m1);
  LED_Set_num(2, m2);
  LED_Set_num(3, s1);
  LED_Set_num(4, s2);
  Serial.print("Time:");
  Serial.print(Hour);
  Serial.print(":");
  Serial.print(Minute);
  Serial.print(":");
  Serial.println(Second);
}