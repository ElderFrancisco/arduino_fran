#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>


#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x3f,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Lector RFID listo.");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lector RFID");
  lcd.setCursor(0, 1);
  lcd.print("Listo");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
     Serial.println("tarjeta");
    if (mfrc522.PICC_ReadCardSerial()) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tarjeta UID:");
      
          String uidString = ""; // Variable para almacenar el UID como una cadena

      
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidString += (mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        uidString += String(mfrc522.uid.uidByte[i], HEX);
      }

      lcd.setCursor(0, 1);
      lcd.print(uidString);
      
      mfrc522.PICC_HaltA();
      delay(5000); // Muestra el UID durante 10 segundos antes de borrar la pantalla
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lector RFID");
      lcd.setCursor(0, 1);
      lcd.print("Listo");
    }
  }
}

