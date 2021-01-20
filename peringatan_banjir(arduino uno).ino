 /************************************
 * Program : Sistem peringatan banjir
 * Input   : Sensor Ultrasonic HC-SR04
 * Output  : LCD 2x16 
 * ***********************************/
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String data;
char c;

#define MAX_DISTANCE 200
#define trigPin 8
#define echoPin 7
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x3F,16,2);
String inString="";

void setup() {
//  Serial.begin(9600);
  mySerial.begin(9600);
//  Serial.print("Tes Koneksi...");
  lcd.begin();
  lcd.print("Tes Koneksi...");
  delay(1000);  
  do{
  }
  while(inString == "OK");
  lcd.clear();
  lcd.print(" Koneksi OK ");
  delay(1000);    
  lcd.clear();
  lcd.print("Early Warning");
  lcd.setCursor(0,1);
  lcd.print("System banjir"); 
  delay(2000);

}

void loop() {
  int jarak;
  unsigned int uS = sonar.ping();
  jarak=uS / US_ROUNDTRIP_CM;
  
  while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }  
  if (data.length()>0) {
    Serial.println(data);
    if (data == "STATUS"){
      if (jarak > 50) {
        mySerial.print("Jarak Air : "); 
        mySerial.print(jarak);
        mySerial.print(" cm, Status AMAN");
        delay(500);
      }
      else if ((jarak > 30)&&(jarak <= 50)){
        mySerial.print("Jarak Air : "); 
        mySerial.print(jarak);
        mySerial.print(" cm, Status WASPADA");
        delay(500);
      }
      else if ((jarak > 10)&&(jarak <= 30)){
        mySerial.print("Jarak Air : "); 
        mySerial.print(jarak);
        mySerial.print(" cm, Status AWAS");
        delay(500);
      }       
      else if (jarak <= 10 && jarak != 0){
//        mySerial.print("Jarak Air : "+jarak+" cm\nStatus : Bahaya");
        mySerial.print("Jarak Air : "); 
        mySerial.print(jarak);
        mySerial.print(" cm, Status BAHAYA");
        delay(500);
      }
      else{
        mySerial.print("Ulangi Lagi");
        delay(100);
      }
    }
    data = "";
  }
  
//   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Jarak air: ");  
   lcd.setCursor(0,1);
   lcd.print("Status: ");  
   lcd.setCursor(11,0);
   lcd.print(jarak);
   lcd.print("cm  ");
  if (jarak > 50) {
    delay(100);
     lcd.setCursor(8,1);
     lcd.print("Aman    ");
  }
  else if ((jarak > 30)&&(jarak <= 50)){
    delay(100);
     lcd.setCursor(8,1);
     lcd.print("Waspada ");
  }
  else if ((jarak > 10)&&(jarak <= 30)){
    delay(100);
     lcd.setCursor(8,1);
     lcd.print("Awas!   ");  
     mySerial.print("AWAS");
     delay(3000);
  }       
  else if (jarak <= 10 && jarak != 0){
    delay(100);
     lcd.setCursor(8,1);
     lcd.print("Bahaya!");
     mySerial.print("BAHAYA");
     delay(3000);
  }
  else {
    delay(100);
     lcd.setCursor(8,1);
     lcd.print("Mencari");
  }
  delay(1000);
}
