//
// This sketch repreatedly scans wifi access points until it sees one called
// eduroam, and it them attempts to connect to it. If the rssi (= received signal
// strength indication) number in brackets is very negative then the signal is very
// weak and the device may see eduroam in a scan and then fail to connect.
//
// To make this work, you need to change the EAP_IDENTITY and EAP_PASSWORD
// to match your login
//
// Adapted from https://github.com/martinius96/ESP32-eduroam to work at UCL
//

#include <WiFi.h>
#include <stdio.h>
#include <time.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "esp_wpa2.h"   // wpa2 for connection to enterprise networks

#define EAP_IDENTITY "zcabhcu@ucl.ac.uk"                
#define EAP_PASSWORD "LaniceZhasnow0206"

#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"

const char* essid = "eduroam";


void setup() {
  bool eduroamFound = false;
  
  Serial.begin(115200);
  delay(10);

  ////////////////////////////////////////////////////////////////////////////////
  //
  // Scan available WiFi networks until eduroam is seen
  //
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Repeatedly scan until we see eduroam
  //
  while (!eduroamFound) {
    Serial.println("scan start");
    int n = WiFi.scanNetworks(); // WiFi.scanNetworks returns the number of networks found
    Serial.println("scan done");
    
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        
        for (int i = 0; i < n; ++i) {
            String ssid = WiFi.SSID(i);
            int    rssi = WiFi.RSSI(i);
          
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(ssid);
            Serial.print(" (");
            Serial.print(rssi);
            Serial.print(")");
            Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            
            ssid.trim();
            if (ssid == essid) {
              Serial.print(" <==== eduroam found");
              eduroamFound = true;
            }
            Serial.println("");
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    if (!eduroamFound)
      delay(5000);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // If we come here, we've successfully found eduroam. Try to connect to it.
  //
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(essid);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // This is where the wpa2 magic happens to allow us to connect to eduroam
  //
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  
  WiFi.begin(essid);       //connect to eduroam
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi is connected to ");
  Serial.println(essid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //print LAN IP
}


void loop() {
  // put your main code here, to run repeatedly:
  configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
}
