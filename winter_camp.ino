#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9  	// RST接到9
#define NSS_PIN  10 	// NSS接到10
MFRC522 mfrc522 (NSS_PIN,RST_PIN);


void setup() {
  
  Serial.begin(9600); 		// 通訊 baud 值
  SPI.begin();
  mfrc522.PCD_Init(); 	// 初始化 MFRC522 讀卡機模組
  Serial.print(F("Reader ")); // 印出文字
  Serial.print(F(": ")); 		// 印出文字
  mfrc522.PCD_DumpVersionToSerial(); // 顯示讀卡設備的版本 
}

void loop() {

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) { 
    // 檢查是否讀到卡片
    // 顯示卡片內容 
    Serial.print(F("Card UID:")); // 印出'Card UID:'
    
    byte *id = mfrc522.uid.uidByte; // 取得卡片的UID
    byte idSize = mfrc522.uid.size; // 取得UID的長度
    Serial.println();


    // 印出卡片UID
    for (byte i = 0; i < idSize; i++){
       Serial.print(id[i]); 
       Serial.print(" "); 
    }
    
    Serial.println(); // 換行
    byte Card[4] = {82,244,212,26}; // 正確的卡片UID

    for (byte i = 0; i < 4; i++){
      if (id[i] != Card[i]){ // 判斷卡片UID符合
        Serial.print("Access Denied!"); // 拒絕進入
        break;
      }

      if (i == 3){
        Serial.print("Access Granted!"); // 歡迎回來
      }

    }
    mfrc522.PICC_HaltA(); // 讓卡片進入停止模式
  }
}

