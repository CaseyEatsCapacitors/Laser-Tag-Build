#include <Arduino.h>
#include <WiFi.h>

#include "NetworkConfig.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(NetConfig::routerIp(),
                    NetConfig::routerIp(),
                    NetConfig::subnetMask());

  bool started = WiFi.softAP(NetConfig::WIFI_SSID,
                             NetConfig::WIFI_PASSWORD);

  if (!started) {
    Serial.println("SoftAP failed to start");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("Dedicated laser-tag SoftAP started");
  Serial.print("SSID: ");
  Serial.println(NetConfig::WIFI_SSID);
  Serial.print("Router IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  delay(1000);
}
