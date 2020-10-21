/************************************
 * Program : Sistem peringatan banjir
 * Input   : Sensor Ultrasonic HC-SR04
 * Output  : LCD 2x16
 * ***********************************/
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

#define MAX_DISTANCE 200
#define trigPin 8
#define echoPin 7
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27,16,2);
String inString="";
char f1,f2,f3;
unsigned int Status;

void setup() {
  Serial.begin(9600);
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
  lcd.setCursor(0,0);
  lcd.print("Jarak air:");  
  lcd.setCursor(0,1);
  lcd.print("Status=");  
  lcd.setCursor(10,0);
  lcd.print(jarak);
  lcd.print("cm  ");
  if (jarak > 100) {
     lcd.setCursor(7,1);
     lcd.print("Aman    ");
     Status=1;
     if (f1==1){
       f1=0;
       f2=0;
       f3=0;
     }
  }
  else if ((jarak < 90) && (jarak > 75)){
  lcd.setCursor(7,1);
  lcd.print("Waspada ");
    if (f1==0){
      Status=2;

    }
  f1=1;  
  f2=0;
  f3=0;
  }
  else if ((jarak < 65) && (jarak > 50)){
  lcd.setCursor(7,1);
  lcd.print("Awas!   ");  
    if (f2==0){
      Status=3;
    }
  f1=0;
  f2=1;
  f3=0;
  }       
  else if (jarak < 40){
  lcd.setCursor(7,1);
  lcd.print("Bahaya!!");  
    if (f3==0){
      Status=4;
    } 
  f1=0;
  f2=0;
  f3=1;
  }
  delay(4000);
}
