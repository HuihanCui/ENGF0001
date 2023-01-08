#include <stdio.h>
#include <time.h>
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"

void setup() 
{
  Serial.begin(115200);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 0, 4);
  // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Time will be shown in 5 seconds\n");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
  struct timespec tout;
  struct tm *tmp;
  char buf[64];
  clock_gettime(CLOCK_REALTIME, &tout);
  tmp = localtime(&tout.tv_sec);
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tmp);
  Serial.println("current time is");
  Serial.println(buf);
  delay(5000);
}
