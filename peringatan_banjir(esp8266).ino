#include "CTBot.h";
CTBot myBot;

String ssid = "NAMA SSID WIFI";
String pass = "PASSWORD WIFI";
String token = "TOKEN BOT TELEGRAM";

String data;
char c;

void setup() {
	Serial.begin(9600);
 delay(1000);
  Serial.println("Mulai");
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);
	if (myBot.testConnection())
		Serial.println("\nKoneksi OK");
	else
		Serial.println("\nKoneksi Gagal");

}

void loop() {
	TBMessage msg;

	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("/start")) {              
			myBot.sendMessage(msg.sender.id, "Memulai Program..\nSistem Peringatan Banjir");
		}
    else if (msg.text.equalsIgnoreCase("/status")) {
      Serial.print("STATUS");
    }
		else {                                                    
			// membalas pesan selain kode diatas
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Maaf Keyword Salah.";
			myBot.sendMessage(msg.sender.id, reply);         
		}
	}
   
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length()>0) {
    if (data == "AWAS"){
      myBot.sendMessage(msg.sender.id, "STATUS AWAS!"); 
      delay(5000);    
    }
    else if (data == "BAHAYA"){
      myBot.sendMessage(msg.sender.id, "STATUS BAHAYA!!"); 
      delay(5000);    
    }
    else{
      myBot.sendMessage(msg.sender.id, data); 
    }
    delay(10);
    data = "";
  }

	delay(500);
}
