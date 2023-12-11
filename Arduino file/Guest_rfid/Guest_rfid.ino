#include <SPI.h>
#include <MFRC522.h>

 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int Red = 8;
int Green = 7;
int buzzer = 6; 

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() 
{
  digitalWrite(Red, HIGH);
  digitalWrite(Green,LOW);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  digitalWrite(Red, LOW);
  digitalWrite(Green,HIGH);
  tone(buzzer,500,500);
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  delay(1500);
} 
