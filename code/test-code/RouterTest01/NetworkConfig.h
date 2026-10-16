#pragma once

#include <Arduino.h>
#include <WiFi.h>

namespace NetConfig {

constexpr char WIFI_SSID[] = "LaserTagGame";
constexpr char WIFI_PASSWORD[] = "password1234";

constexpr uint16_t GUN_PORT = 4211;
constexpr uint16_t VEST_PORT = 4212;
constexpr uint16_t LCD_PORT = 4213;

inline IPAddress routerIp() {
  return IPAddress(192, 168, 4, 1);
}

inline IPAddress gunIp() {
  return IPAddress(192, 168, 4, 2);
}

inline IPAddress vestIp() {
  return IPAddress(192, 168, 4, 3);
}

inline IPAddress lcdIp() {
  return IPAddress(192, 168, 4, 4);
}

inline IPAddress subnetMask() {
  return IPAddress(255, 255, 255, 0);
}

}