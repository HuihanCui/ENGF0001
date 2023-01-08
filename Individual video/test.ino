#include <ESP32Time.h>
#include <TFT_eSPI.h>
#include <stdio.h>
#include <time.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();
ESP32Time rtc(0);  // offset in seconds GMT+1

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Time will be shown in 5 seconds\n");
  rtc.setTime(0, 40, 13, 19, 10, 2022);  // 17th Jan 2021 15:24:30
  delay(5000);
}

void loop() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  Serial.println(rtc.getTime("%B %d %Y %H:%M:%S")); 
  struct tm timeinfo = rtc.getTimeStruct();
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println(rtc.getTime("%B %d %Y %H:%M:%S"));
  delay(1000);
}

