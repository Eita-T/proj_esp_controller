#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  
  Serial.println();
  Serial.println("ESP32 MAC Address Information");
  Serial.println("=============================");
  
  String macAddress = WiFi.macAddress();
  Serial.print("ESP32 MAC Address: ");
  Serial.println(macAddress);
  
  Serial.println();
  Serial.println("Copy this MAC address and paste it into your PS4 controller code:");
  Serial.printf("String macAddress = \"%s\";\n", macAddress.c_str());
  
  Serial.println();
  Serial.println("Next steps:");
  Serial.println("1. Copy the MAC address above");
  Serial.println("2. Replace 'AA:BB:CC:DD:EE:FF' in esp32_ps4_controller.ino");
  Serial.println("3. Use a tool like SixAxisPairTool to pair your PS4 controller");
  Serial.println("4. Set PS4 controller's target MAC to this ESP32's MAC");
}

void loop() {
  // 何もしない
}
