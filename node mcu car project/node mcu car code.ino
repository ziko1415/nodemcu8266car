#define enA   14              //GPIO14(D5)
#define enB   12              //GPIO12(D6)
#define in1  15               //GPIO15(D8)
#define in2  13               //GPIO13(D7)
#define in3  2                //GPIO2(D4)
#define in4  0                //GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>

String command;        //String to store app command state.
Servo cam;
int speedCar = 800;   // 400 - 1023.
int i=0;



const char* ssid = "CamBot";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);  
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT); 
 cam.attach(4);        // Servo on D2
 cam.write(90);
 delay(1000);
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goForward(){ 

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, speedCar);

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, speedCar);
  }

void goBack(){ 

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, speedCar);

      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, speedCar);
  }

void goRight(){ 

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, speedCar);

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, speedCar);
  }

void goLeft(){

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, speedCar);

      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, speedCar);
  }

void oneThreeFive(){
     i=0;
    cam.write(135);
    delay(1000);  
 
   }

void nintyAndHalf(){
    i=i+1;  
    if( i==1)
    { cam.write(45);
      delay(1000);
    }
    if(i==2)
    { i=0;
      cam.write(90);
      delay(1000);
    }
  }

void oneEightZero(){ 
    i=0;
    cam.write(180);
    delay(1000);
 
  }

void zero(){ 
    i=0;
   cam.write(0);
   delay(1000); 
  }

void stopRobot(){  

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goForward();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") oneThreeFive();
      else if (command == "G") nintyAndHalf();
      else if (command == "J") oneEightZero();
      else if (command == "H") zero();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
