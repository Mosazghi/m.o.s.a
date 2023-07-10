#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5

#define A1 5
#define A2 5




 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 80; // speed of motor 2
 int LeftRotationSpeed = 250;  // Left Rotation Speed
 int RightRotationSpeed = 250; // Right Rotation Speed
  
 unsigned  lineCount = 0;


const char* SSID = "Weini2.4G";      
const char* PASSWORD = "20052009";  

 void setup() {
  Serial.begin(115200);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT); // initialize Left sensor as an input
  pinMode(A3, INPUT); // initialize Right sensor as an input
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int FRONT_SENSOR = digitalRead(A0);
  int MID_SENSOR = digitalRead(A1); // Ikke i bruk 
  int LEFT_SENSOR = digitalRead(A2);
  int RIGHT_SENSOR = digitalRead(A3);
  int BACK_SENSOR = digitalRead(A4);

  HTTPClient http;
  http.begin("http://10.0.0.13:4000/dashboard/api/bestilling");
  int httpResponseCode = http.GET();
  String input = http.getString();

  StaticJsonDocument<384> doc;

  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.println("eserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  Serial.println(httpResponseCode);
  const char* id = doc["_id"]; // "64a5bc8d247ec5276ebc856e"
  const char* bruker = doc["bruker"]; // "mos"
  int dropSted = doc["dropSted"]; // 4

  for (JsonObject komponenter_item : doc["komponenter"].as<JsonArray>()) {

    const char* komponenter_item_Komponent = komponenter_item["Komponent"]; // "Bryter", "LED", ...
    const char* komponenter_item_Antall = komponenter_item["Antall"]; // "3", "2", "3"

  }

  delay(5000);  

if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) {
    forward(); //FORWARD
    Serial.println("Fremover");
}

    else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1  && BACK_SENSOR==1 && FRONT_SENSOR==1) {
      right(); //Move Right
      Serial.println("Høyre");
  }

    else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0 && BACK_SENSOR==1 && FRONT_SENSOR==1) {
      left(); //Move Left
      Serial.println("Venstre");
  }

    else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==0) {
      Stop();  //STOP
      Serial.println("Stopper");
  } 

 else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==1){   //Kryss
  int stajsonNr = 2; //Hardkodet 
  intersectionDetected();
  Serial.println("Ved krysset: ");
  Serial.print(lineCount);
  Serial.println(" ");
  if(lineCount == stajsonNr){
    Serial.println("Tar svingen til stasjon 2");
  }
  else
    forward();
 } 
}




//Ikke ferdig
void dropSpot(){
  Stop();
  delay(2000);
  turnLeft();
  forward();
}


void intersectionDetected(){
  static long lastDetected = 0;
  if(millis() - lastDetected < 2000){ 
    return;
  }
  lastDetected = millis(); //Sist sjekket linje */
  lineCount++;
} 

void turnLeft(){
  left();
  delay(2000);
}

void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
