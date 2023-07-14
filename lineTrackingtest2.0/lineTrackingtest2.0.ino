// Bibliotker --------------------

#include <WiFi.h>   
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>

// Motorpinner --------------------

#define in1 22
#define in2 21
#define in3 19
#define in4 18
#define enA 23
#define enB 4

#define frontPin 25
#define midPin 26
#define leftPin 14
#define rightPin 32
#define backPin 33

// WiFi & MQTT --------------------

const char * ssid = "Weini2.4G";
const char * password = "20052009";

const char* mqttBroker = "10.0.0.13";
const int mqttPort = 1884;   

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Motor variabler --------------------

int M1_Speed = 80;  
int M2_Speed = 80;  
int LeftRotationSpeed = 80;  
int RightRotationSpeed = 80;  

int FRONT_SENSOR = 0;
int MID_SENSOR = 0;
int LEFT_SENSOR = 0;
int RIGHT_SENSOR = 0;
int BACK_SENSOR = 0;

unsigned lineCount = 0;
int stajsonNr = 0;

int dropSted;

// millis delay ---------------------
unsigned long previousMillis = 0;  // 

const long interval = 2000;  

// Setup --------------------
void setup() {
  Serial.begin(115200);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(frontPin, INPUT);
  pinMode(midPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(backPin, INPUT);

  // WiFi tilkobling
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Tilbkopling til MQTT
  mqttClient.setServer(mqttBroker, mqttPort);
  mqttClient.setCallback(mqttCallback);
  mqttClient.subscribe("shoplist");

  while (!mqttClient.connected()) {
    if (mqttClient.connect("ArduinoClient")) {
      mqttClient.subscribe("shoplist");  
      Serial.println("Tilkoblet MQTT!");
    } else {
      Serial.println("MQTT timeout, prøver igjen...");
      delay(5000);
    }
  }

  //// Testing av robot
  // forward();
  // delay(10000);
  // backward();
  // delay(10000);
  // left();
  // delay(10000);
  // right();
  // delay(10000);
}

int prevDropSted = 0;
void loop() {
   if (!mqttClient.connected()) {
    // Reconnect til MQTT hvis tilkobling er brutt
    if (mqttClient.connect("ArduinoClient")) {
      mqttClient.subscribe("shoplist");   
    }
  }
  mqttClient.loop();

  // IR sensorer
  FRONT_SENSOR = digitalRead(frontPin);
  MID_SENSOR = digitalRead(midPin);
  LEFT_SENSOR = digitalRead(leftPin);
  RIGHT_SENSOR = digitalRead(rightPin);
  BACK_SENSOR = digitalRead(backPin);

  // if (FRONT_SENSOR && !BACK_SENSOR && LEFT_SENSOR && RIGHT_SENSOR && MID_SENSOR) {
  //   forward(); //FORWARD
  //   Serial.println("kjører forward!!");
  // } else {
  //   stopAndTurnAround();
  //   Serial.println("Stopper!!");
  // }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if(getDropSted() != -1) {
      // Vår hovedfunksjoner skal være inne her (ny bestilling):
      baseTilStasjon();
      if(dropSted == 1) {
        stasjonTilD1();
        D1tilBase();
      }
      else {
        stasjonTilD2();
        D2tilBase();
      }
    }
    else {
      Serial.println("ingen ny dropsted!");
      Serial.println(prevDropSted);
    }
  }
}


//--------Manvuere funksjoner---------

// Enten den ene eller andre 

// Ved oppstart (hente komponenter)--------------------------------
void baseTilStasjon() {
  Serial.println("Kjører til stasjonen!");
  forward(); // Kjøre forward til kryss 
  if (digitalRead(LEFT_SENSOR) && !digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    left(); // Svinger til venstre kryss og kjører forward kryss
    delay(2000);
    forward();
    Serial.println("Svinger venstre & kjører forward");
    if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && !digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
      left(); // Svinger til venstre kryss og kjører mot komponent
      delay(2000);
      forward();
      Serial.println("Svinger venstre & kjører forward");
      if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
        stopAndTurnAround();
        Serial.println("Stoppet, framme ved statsjonen");
      }
    }
  }
}

// Ved levering (lever komponenter)--------------------------------
void stasjonTilD1() {
  Serial.println("Kjører til D1!");
  forward(); // Kjører frem til kryss
  if (!digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    right(); // Svinger til høyre og kjører til dropsted 1 
    delay(2000);
    forward();
    Serial.println("Svinger venstre & kjører forward");
    if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
      stopAndTurnAround();
      Serial.println("Stoppet, framme ved dropsted 1");
    }
  }
}

void stasjonTilD2() {
  Serial.println("Kjører til D2!");
  forward();
  if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    stopAndTurnAround();
    Serial.println("Stoppet, framme ved dropsted 2");
  }
}

// Tilbake til basen--------------------------------
void D1tilBase() {
  Serial.println("kjører til basen!");
  forward();
  if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    stopAndTurnAround();
    Serial.println("Stoppet, framme ved ladestasjon");
  }
}

void D2tilBase() {
  Serial.println("kjører til basen!");
  forward();
  if (digitalRead(LEFT_SENSOR) && !digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    left(); // Svinger til venstre og kjører forward til kryss 
    delay(2000);
    forward();
    Serial.println("Svinger venstre & kjører forward");
    if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && !digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
      right(); // Svinger til venstre og kjører forward
      delay(2000);
      forward();
      if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
        stopAndTurnAround();
        Serial.println("Stoppet, framme ved ladestasjon");
      }
    }
  }
}

// Andre funksjoner --------------------------------

void intersectionDetected() {
  static long lastDetected = 0;
  if (millis() - lastDetected < 2000) {
    return;
  }
  lastDetected = millis(); //Sist sjekket linje */
  lineCount++;
}

void turnLeft() {
  left();
  delay(2000);
}

void forward() {
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M1_Speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("frem");
}

void backward() {
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M1_Speed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("bak");
}

void right() {
  analogWrite(enA, 55);
  analogWrite(enB, 65);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("høyre");
}

void left() {

  analogWrite(enA, 65);
  analogWrite(enB, 55);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("venstre");
}

void stopAndTurnAround() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  delay(500);   

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  delay(1000);   
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}



void mqttCallback(const char* topic, byte* payload, unsigned int length) {
  String jsonPayload;
  for (int i = 0; i < length; i++) {
    jsonPayload += (char)payload[i];
  }

  StaticJsonDocument<16> filter;
  filter["dropSted"] = true;

  StaticJsonDocument<64> doc;

  DeserializationError error = deserializeJson(doc, jsonPayload, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  dropSted = doc["dropSted"];  
}

int getDropSted() {
  if (dropSted != prevDropSted) {
    prevDropSted = dropSted; 
    return dropSted;
  }
  else {
    return -1; 
  }
}


