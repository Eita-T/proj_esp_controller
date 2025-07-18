#include "PS4Controller.h"

// コールバック関数の定義
void onConnect() {
  Serial.println("PS4 controller connected!");
}

void onDisconnect() {
  Serial.println("PS4 controller disconnected!");
}

void setup() {
  Serial.begin(115200);
  
  Serial.println("ESP32 PS4 Controller Test");
  Serial.println("=========================");
  Serial.println();
  
  // コールバック関数を設定
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisconnect);
  
  // PS4 Controller の初期化
  // 実際のESP32のMACアドレスに変更してください
  // get_mac_address.inoで取得したMACアドレスを使用
  PS4.begin("DC:9B:BB:96:F6:FE"); // ここを実際のMACアドレスに変更
  
  Serial.println("PS4 Controller initialized successfully!");
  Serial.println("ESP32 MAC Address: DC:9B:BB:96:F6:FE");
  Serial.println();
  Serial.println("=== PAIRING INSTRUCTIONS ===");
  Serial.println("1. Turn OFF your PS4 console completely");
  Serial.println("2. Hold PS + Share buttons on controller for 3-5 seconds");
  Serial.println("3. Controller light should flash rapidly (pairing mode)");
  Serial.println("4. Wait for connection...");
  Serial.println();
  Serial.println("If connection fails:");
  Serial.println("- Make sure controller is not paired with PS4");
  Serial.println("- Try resetting controller (small button on back)");
  Serial.println("- Check MAC address is correct");
  Serial.println("=============================");
  Serial.println();
}

void loop() {
  // PS4コントローラが接続されているかチェック
  if (PS4.isConnected()) {
    
    static bool firstConnection = true;
    if (firstConnection) {
      Serial.println("🎮 CONTROLLER CONNECTED SUCCESSFULLY! 🎮");
      Serial.println("All inputs will be shown below:");
      Serial.println("=====================================");
      firstConnection = false;
    }
    
    // アナログスティック（左）
    int leftX = PS4.LStickX();
    int leftY = PS4.LStickY();
    if (leftX != 0 || leftY != 0) {
      Serial.printf("Left Stick - X: %d, Y: %d\n", leftX, leftY);
    }
    
    // アナログスティック（右）
    int rightX = PS4.RStickX();
    int rightY = PS4.RStickY();
    if (rightX != 0 || rightY != 0) {
      Serial.printf("Right Stick - X: %d, Y: %d\n", rightX, rightY);
    }
    
    // トリガー（L2/R2）
    int l2 = PS4.L2Value();
    int r2 = PS4.R2Value();
    if (l2 > 0) {
      Serial.printf("L2 Trigger: %d\n", l2);
    }
    if (r2 > 0) {
      Serial.printf("R2 Trigger: %d\n", r2);
    }
    
    // ボタンの状態をチェック
    if (PS4.Cross()) Serial.println("❌ Cross button pressed");
    if (PS4.Circle()) Serial.println("⭕ Circle button pressed");
    if (PS4.Triangle()) Serial.println("🔺 Triangle button pressed");
    if (PS4.Square()) Serial.println("⬜ Square button pressed");
    
    if (PS4.L1()) Serial.println("L1 button pressed");
    if (PS4.R1()) Serial.println("R1 button pressed");
    if (PS4.L2()) Serial.println("L2 button pressed");
    if (PS4.R2()) Serial.println("R2 button pressed");
    
    if (PS4.Share()) Serial.println("Share button pressed");
    if (PS4.Options()) Serial.println("Options button pressed");
    if (PS4.PSButton()) Serial.println("🏠 PS button pressed");
    if (PS4.Touchpad()) Serial.println("📱 Touchpad pressed");
    
    if (PS4.L3()) Serial.println("L3 (Left stick) pressed");
    if (PS4.R3()) Serial.println("R3 (Right stick) pressed");
    
    // 方向パッド
    if (PS4.Up()) Serial.println("⬆️ Up button pressed");
    if (PS4.Down()) Serial.println("⬇️ Down button pressed");
    if (PS4.Left()) Serial.println("⬅️ Left button pressed");
    if (PS4.Right()) Serial.println("➡️ Right button pressed");
    
    // バッテリーレベル（利用可能な場合）
    static unsigned long lastBatteryCheck = 0;
    if (millis() - lastBatteryCheck > 10000) { // 10秒ごとにバッテリーチェック
      int battery = PS4.Battery();
      if (battery >= 0) {
        Serial.printf("🔋 Battery Level: %d%%\n", battery);
      }
      lastBatteryCheck = millis();
    }
    
  } else {
    // 接続状態を詳しく表示
    static unsigned long lastPrint = 0;
    static int connectionAttempts = 0;
    
    if (millis() - lastPrint > 3000) { // 3秒ごとに表示
      connectionAttempts++;
      Serial.printf("⏳ Attempt %d: PS4 controller not connected\n", connectionAttempts);
      
      if (connectionAttempts % 5 == 0) {
        Serial.println("🔄 Troubleshooting tips:");
        Serial.println("   1. Make sure PS4 console is OFF");
        Serial.println("   2. Reset controller (button on back)");
        Serial.println("   3. Hold PS + Share for 5+ seconds");
        Serial.println("   4. Controller light should flash rapidly");
        Serial.println("   5. Check MAC address matches ESP32");
        Serial.println();
      } else {
        Serial.println("   Put controller in pairing mode: Hold PS + Share buttons");
      }
      
      lastPrint = millis();
    }
  }
  
  delay(50); // CPUの負荷を軽減
}
