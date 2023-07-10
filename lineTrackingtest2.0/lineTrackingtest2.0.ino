#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


#include <Wire.h>
#include <WiFi.h>


#define in1 4
#define in2 5
#define in3 15
#define in4 18
#define enA 2
#define enB 19

#define frontPin 25
#define midPin 26
#define leftPin 27
#define rightPin 32
#define backPin 33

char auth[] = " ";
char ssid[] = "TP-Link_E710_5G";
char pass[] = "41359754";

 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 80; // speed of motor 2
 int LeftRotationSpeed = 250;  // Left Rotation Speed
 int RightRotationSpeed = 250; // Right Rotation Speed

 unsigned lineCount = 0;
 int stajsonNr = 0;


 void setup() {
  Serial.begin(9600);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);

  pinMode(frontPin, INPUT);
  pinMode(midPin, INPUT); 
  pinMode(leftPin, INPUT); 
  pinMode(rightPin, INPUT);
  pinMode(backPin, INPUT);

  Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  // Input fra bruker (serial monitor)
  Serial.println(" ");
  Serial.println("Hvilken stasjon skal M.O.S.A til 1 eller 2?: ");
  while(Serial.available() == 0){
  }

  stajsonNr = Serial.parseInt();
  delay(2000); 

  stajsonNr;
}

void loop() {
  int FRONT_SENSOR = digitalRead(frontPin);
  int MID_SENSOR = digitalRead(midPin); 
  int LEFT_SENSOR = digitalRead(leftPin);
  int RIGHT_SENSOR = digitalRead(rightPin);
  int BACK_SENSOR = digitalRead(backPin);

  HTTPClient http;
  http.begin("http://10.161.2.15:4000/dashboard/api/bestilling");
  int httpResponseCode = http.GET();
  String payload = http.getString();

  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("eserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  int dropSted = doc["dropSted"]; // 121
  char* bruker = doc["bruker"];
  String komponenter = doc["komponenter"];

  Serial.print("bruker: ");
  Serial.print(bruker);
  Serial.print("dropSted: ");
  Serial.println(dropSted);
  Serial.print("komponenter: ");
  Serial.println(komponenter);

  delay(5000); 


if(RIGHT_SENSOR==0 && LEFT_SENSOR==0 && MID_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==1) {
    forward(); //FORWARD
    Serial.println("Fremover");
}

else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0 && MID_SENSOR==0  && BACK_SENSOR==0 && FRONT_SENSOR==0) {
    left(); //Move Left
    Serial.println("Venstre");
 }

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1 && MID_SENSOR==0  && BACK_SENSOR==0 && FRONT_SENSOR==0) {
    right(); //Move Right
    Serial.println("Høyre");
}

else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && MID_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==0) {
    Stop();  //STOP
    Serial.println("Stopper");
 } 


else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && MID_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==1){   //Kryss
  intersectionDetected();
  Serial.println("Ved krysset: ");
  Serial.print(lineCount);
  Serial.println(" ");

  if(stajsonNr == lineCount && stajsonNr == 1){
    Serial.println("Tar svingen til stasjon ");
    Serial.print(stajsonNr);
    right();  // Tar svingen til høyre
    delay(2000);
    forward();
  }
  else if (stajsonNr == lineCount && stajsonNr == 2){
    Serial.println("Tar svingen til stasjon ");
    Serial.print(stajsonNr);
    left();  // Tar svingen til venstre
    delay(2000);
    forward();
  } 
  else
    forward();
 }

 else if (RIGHT_SENSOR==1 && LEFT_SENSOR==1 && MID_SENSOR==0 && BACK_SENSOR==1 && FRONT_SENSOR==1){
   Serial.println("Ved drop steddet");
   dropSpot();
 }

}



void intersectionDetected(){
  static long lastDetected = 0;
  if(millis() - lastDetected < 2000){ 
    return;
  }
  lastDetected = millis(); //Sist sjekket linje */
  lineCount++;
} 

void forward(){

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward(){
    digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);


  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//Ikke ferdig mangler funskjoner som vektsensor osv...
void dropSpot(){
  Stop();
  turnAround();
  delay(2000); //Få på last 
  forward();
}

void returnStart(){
  lineCount = 0;

  turnAround();
  forward(); // Til den møter stopskilt (T)
}

// Ikke ferdig
void goToDropSpot(){
  lineCount = 0;
  turnAround();
  forward();
  if(stajsonNr==1 && lineCount ==1){
    right();
    delay(2000);
    forward();
  }
  else if(stajsonNr==2 && lineCount ==1){
    left();
    delay(2000);
    forward();
  }

}

// Ikke ferdig 
void turnAround(){}