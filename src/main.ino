#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9   // kabel kuning
#define SDA_PIN 10  // kabel hijau
#define RELAY 8
#define LED_red 7   // kabel abu-abu
#define LED_green 6 // kabel hijau
// SCK  : kabel biru    : 13
// MOSI : kabel ungu    : 11
// MISO : kabel abu-abu : 12

String tagID = "";

MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(RELAY, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  digitalWrite(RELAY, HIGH);
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_green, LOW);
  Serial.print("letakkan kartu :");
}

void loop() 
{
  while (getID()) 
  {
    Serial.print(" ID : ");
    Serial.println(tagID);
    if (tagID == "C7F8103C") 
    { 
      Serial.println(" Akses diizinkan");
      digitalWrite(RELAY, LOW);
      digitalWrite(LED_green, HIGH);
      delay(3000);
      digitalWrite(RELAY, HIGH);
      digitalWrite(LED_green, LOW);
    }
    else
    {
      Serial.println(" Akses ditolak !");
      digitalWrite(LED_red, HIGH);
      delay(1000);
      digitalWrite(LED_red, LOW);
    }
    
    Serial.print("letakkan kartu :");
  }
  
}

//membaca kartu yang terdeteksi
boolean getID() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  tagID = "";
  for ( byte i = 0; i < mfrc522.uid.size; i++) {
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // berhenti membaca
  return true;
}
