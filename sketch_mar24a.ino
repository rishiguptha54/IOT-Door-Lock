 #include <SoftwareSerial.h>
#include <PN532_SWHSU.h>
#include <PN532.h>
SoftwareSerial SWSerial( 6, 7 ); // RX, TX
PN532_SWHSU pn532swhsu( SWSerial );
PN532 nfc( pn532swhsu );
String tagId = "None", dispTag = "None";
byte nuidPICC[4];
#include <LiquidCrystal.h>
int buz =2;
int lock=3;
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup(void) {

  Serial.begin(9600);
  Serial.println("welcome");
  delay(500);
  nfc.begin();
 
  
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {

   
  
  Serial.println("fail");
  delay(1000);

  }
 //Serial.print("Found chip PN5");

   lcd.begin(16,2);
  lcd.print("  WELCOME");
  pinMode(lock,OUTPUT);
  pinMode(buz,OUTPUT);
  digitalWrite(lock,1);
 
  // Got valid data, print it out!

 
  // Configure board to read RFID tags

  nfc.SAMConfig();
delay(1000);
  

}

void loop(void) {

  lcd.clear();
  lcd.print("SCAN CARD..");

  boolean success;

  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID

  uint8_t uidLength;                       // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {

 
String content="";
    for (uint8_t i=0; i < uidLength; i++)

    {

      //Serial.print(" 0x");Serial.print(uid[i], HEX);
     content.concat(String(uid[i] < 0x10 ? " 0" : " "));
     content.concat(String(uid[i], HEX));
    }

    Serial.println(content.substring(1));

    if(String(content.substring(1))=="89 7d 15 53")
    {
      Serial.println("USER-1");
      lcd.clear();
      lcd.print("USER-1");
      digitalWrite(lock,0);
      delay(5000);
       digitalWrite(lock,1);
      
      
    }
    
    if(String(content.substring(1))=="89 7d 15 53")
    {
      Serial.println("USER-3");
      lcd.clear();
      lcd.print("USER-3");
      digitalWrite(lock,0);
      delay(5000);
       digitalWrite(lock,1);
      
      
    }


    else if(String(content.substring(1))=="2d 0e 1e 85")
    {
      Serial.println("USER-2");
       lcd.clear();
      lcd.print("USER-2");
            digitalWrite(lock,0);
      delay(5000);
       digitalWrite(lock,1);
      
    }
    else
    {
       lcd.clear();
      lcd.print("Unauthorized");
      Serial.println("UnAuthorized");
            digitalWrite(buz,1);
      delay(1000);
       digitalWrite(buz,0);
    }
  

    delay(2000);

  }
  delay(100);

  if(Serial.available())
  {
    int x=Serial.read();
    if(x=='1')
    {
        lcd.clear();
      lcd.print("ACCESS OK");
      digitalWrite(lock,0);
      delay(5000);
       digitalWrite(lock,1);
    }
    else if(x=='2')
    {
         lcd.clear();
      lcd.print("REJECTED");
      digitalWrite(buz,1);
      delay(1000);
       digitalWrite(buz,0);
    }
  }
}
