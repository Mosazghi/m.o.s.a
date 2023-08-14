#include "WiFiS3.h"
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>
#include <string.h>

// Motorpinner --------------------
// LEFT
int enA = 9;
int l1 = 8;
int l2 = 7;
int l3 = 11;
int l4 = 10;
// RIGHT
int enB = 3;
int r1 = 6;
int r2 = 5;
int r3 = 13;
int r4 = 12;

#define midPin A4
#define rightPin A5
#define leftPin A3

// WiFi & MQTT --------------------
char ssid[] = "Weini2.4G";    // your network SSID (name)
char pass[] = "20052009";    // your network password 

const char broker[] = "10.0.0.13";
int        port     = 1884;
const char subscribe_topic[]  = "shoplist";
const char publish_topic[]  = "shoplist";

// Motor variabler --------------------
int M1_Speed = 50;  

int MID_SENSOR = 0;
int LEFT_SENSOR = 0;
int RIGHT_SENSOR = 0 ;

unsigned lineCount = 0;  //ikke i bruk 

int countTurns = 0;

 
// millis delay variabler
unsigned long previousMillis = 0;   
const long interval = 1500;   

// flagger
bool reachedStation = true; 
bool reachedDelivery = false; 
bool reachedBase = false;
bool turningFinished = true; 
bool test = false;

int dropSted;
int prevDropSted = 0;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Setup --------------------
void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; 
  }

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);

  pinMode(midPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);

// Connect to WiFi
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker.");

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");

  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(subscribe_topic);

  mqttClient.subscribe(subscribe_topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(subscribe_topic);

  // Serial.println("TESTING!");
  // forward();
  // delay(10000);
  // backward();
  // delay(10000);
  // stop();
  // right();
  // delay(10000);
  // left();
  // delay(10000);
}

void loop() {
  //  if (!mqttClient.connected()) {
  //    Reconnect til MQTT hvis tilkobling er brutt
  //   if (mqttClient.connect("ArduinoClient")) {
  //     mqttClient.subscribe("shoplist");   
  //   }
  // }
  mqttClient.poll(); // holde MQTT tilkobling i live

  // IR sensorer
  MID_SENSOR = digitalRead(midPin);
  LEFT_SENSOR = digitalRead(leftPin);
  RIGHT_SENSOR = digitalRead(rightPin);

  // // TESTING (DROPSTED 2)
  // if(!reachedStation) {
  //   baseTilStasjon();
  // } 
  // else if (reachedStation && !reachedDelivery && !turningFinished) {
  //   stopAndTurnAround();
  //   countTurns = 0;
  // } 
  // else if(reachedStation && !reachedDelivery && turningFinished) {
  //   stasjonTilD2();
  // }
  // else if(reachedStation && reachedDelivery && !reachedBase){
  //   D2tilBase();
  // }
  // else if(reachedBase) {
  //   stop();
  // }

  
  // TESTING DROPSTED 1
  if(!reachedStation) {
    baseTilStasjon();
  } 
  else if (reachedStation && !turningFinished && !reachedDelivery) {
    stopAndTurnAround();
    countTurns = 0;
  } 
  else if(reachedStation && !reachedDelivery && turningFinished) {
    stasjonTilD1();
  }
  else if(reachedStation && reachedDelivery && !reachedBase){
    D1tilBase();
  }
  else if(reachedBase) {
    stop();
  }



  unsigned long currentMillis = millis();
  // DEBUGGING --------------------
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    MID_SENSOR ? Serial.println("m_1") : Serial.println("m_0");
    LEFT_SENSOR ? Serial.println("l_1") : Serial.println("l_0");
    RIGHT_SENSOR ? Serial.println("r_1") : Serial.println("r_0");
    Serial.println("-----------------");  
		// digitalRead(in1) ? Serial.println("in1_1") : Serial.println("in1_0");
		// digitalRead(in2) ? Serial.println("in2_1") : Serial.println("in2_0");
		// digitalRead(in3) ? Serial.println("in3_1") : Serial.println("in3_0");
		// digitalRead(in4) ? Serial.println("in4_1") : Serial.println("in4_0");
		// Serial.println(analogRead(enA));
		Serial.println(reachedStation);
  	Serial.println(reachedDelivery);
		Serial.println(turningFinished);
    Serial.println(reachedBase);
    Serial.println(countTurns);
		// Serial.println("-----------------");  
  }

  // ---- MAIN ----
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  //   if(getDropSted() != -1) {
  //     // Vår hovedfunksjoner skal være inne her (ny bestilling):
  //     baseTilStasjon();
  //     if(dropSted == 1 && reachedStation) {
  //       stasjonTilD1();
  //       D1tilBase();
  //     }
  //     else if (dropSted == 2 && reachedStation){
  //       stasjonTilD2();
  //       D2tilBase();
  //     }
  //   }
  //   else {
  //     Serial.println("ingen ny dropsted!");
  //     Serial.println(prevDropSted);
  //   } 
  // }
}


// Hjelpe funksjoner --------------------

/**
 * @brief Kjører roboten fremover og tar venstre svinger
 * @see forward()
 * @see left()
 * @see keepStraightLine()
*/
void turnLeft() {
  // FORWARD
  if(MID_SENSOR && !LEFT_SENSOR && !RIGHT_SENSOR) {
    // Serial.println("HER_1");
    forward();
  }
  // IF LEFT LINE DETECTED, TURN LEFT
  else if(LEFT_SENSOR && MID_SENSOR && !RIGHT_SENSOR) {
    // Serial.println("HER_2");
    left();
    delay(2000);
    countTurns++;
  }
  // IF OUT OF LINE, STRAIGHTEN SELF 
  else {
    keepStraightLine();
    // Serial.println("HER_3");
  }
}


/**
 * @brief Kjører roboten fremover og tar høyre svinger
 * @see forward()
 * @see right()
 * @see keepStraightLine()
*/
void turnRight(){
  if(MID_SENSOR && !LEFT_SENSOR && !RIGHT_SENSOR){
    forward();
  }
  else if(RIGHT_SENSOR && MID_SENSOR && !LEFT_SENSOR) {
    right();
    countTurns++;
  }
  else {
    keepStraightLine();
  }
}


/**
 * @brief Korigerer roboten til å holde seg på en rett linje (fremover)
 * @see left()
 * @see right()
*/
void keepStraightLine() {
  if(LEFT_SENSOR && !RIGHT_SENSOR && !MID_SENSOR) {
    Serial.println("KEEP RIGHT!");
    left();
  }
  else if(RIGHT_SENSOR && !LEFT_SENSOR && !MID_SENSOR) {
    Serial.println("KEEP LEFT!");
    right();
  }
}


/**
 * @brief Stopper og snur roboten 180 grader
 * @see right()
 * @see stop()
 * @see turningFinished
*/
void stopAndTurnAround() {                                       
  Serial.println("TURNING");
  turnAroundRight();
  if(!LEFT_SENSOR && MID_SENSOR && !RIGHT_SENSOR) {
    // stop(); 
    // delay(2000);
    Serial.println("TURNING FINISHED!");
    turningFinished = true; 
  }
}


// Ved oppstart (hente komponenter)--------------------------------
/**
 * @brief Kjører fra basen til komponentstasjonen
 * @see turnLeft()
 * @see reachedStation
*/
void baseTilStasjon() {
  Serial.println("STASJONEN");
  // Serial.println("Kjører til stasjonen!");
  turnLeft();
  
  // IF ARRIVED BASE, STOP AND TURN AROUND (LEFT/RIGHT) 
  if (!LEFT_SENSOR && !MID_SENSOR && !RIGHT_SENSOR) {
    reachedStation = true; 
  }
}


// Ved levering (droppe komponenter)--------------------------------

/**
 * @brief Kjører fra komponentstasjonen til dropsted 1
 * @see forward()
 * @see right()
 * @see stopAndTurnAround()
*/
void stasjonTilD1() {
  if(!countTurns) {
    Serial.println("her!");
    turnRight();
  }
  else if(countTurns) {
    Serial.println("her!!!");
    turnLeft();
  }
  if (LEFT_SENSOR && !MID_SENSOR && RIGHT_SENSOR) {
    stop();
    Serial.println("ARRIVED AT D1!");
    reachedDelivery = true;
  }
}  


/**
 * @brief Kjører fra komponentstasjonen til dropsted 2
 * @see forward()
 * @see stop()
 * @see keepStraightLine()
 * @see reachedDelivery
*/
void stasjonTilD2() {
  Serial.println("DRIVING TO D2");D1 tilbake til basen
  if(!LEFT_SENSOR && MID_SENSOR && !RIGHT_SENSOR) {
    Serial.println("D2");
    forward();
  }
  else if(!LEFT_SENSOR && MID_SENSOR && RIGHT_SENSOR) { //Ingnorer ekstra teip
    // Serial.println("HER_2");
    forward();
  }
  else if (LEFT_SENSOR && !MID_SENSOR && RIGHT_SENSOR) {
    stop();
    delay(2000);
    Serial.println("ARRIVED AT D2!");
    reachedDelivery = true;
  }
  else {
    keepStraightLine();
  }
}


// Ved kjøring tilbake til basen --------------------------------
/**
 * @brief Kjører fra D1 tilbake til basen
 * @see stopAndTurnAround()
*/
void D1TilBase(){
}


/**
 * @brief Kjører fra D2 tilbake til basen
 * @see stopAndTurnArond()
*/
void D2tilBase(){
  // byttet turningFinished -> test
  if(LEFT_SENSOR && RIGHT_SENSOR && !MID_SENSOR && !test){
    Serial.println("Rygger");
    backward();
  }

  else if(!test){
    Serial.println("Snur");
    turnAroundRight();
    delay(500); 
    if(MID_SENSOR && !LEFT_SENSOR && !RIGHT_SENSOR){
      test = true;
    }
  }
  else if(test){
    if(!countTurns){
      Serial.println("V");
      turnLeft();
    }
    else if(countTurns){
      Serial.println("H");
      turnRight();
    }
  }
  else if (!MID_SENSOR && !LEFT_SENSOR && !RIGHT_SENSOR) {
    reachedBase = true;
    countTurns = 0;
    Serial.println("Nådd basen");
  }
} 


// Manuvers funksjoner --------------------------------

/**
 * @brief Kjører fram 
*/
void forward() {
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, HIGH);

  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  digitalWrite(r4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M1_Speed);
}


/**
 * @brief Kjører baklengs
*/
void backward() {
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, LOW);

  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M1_Speed);
}


/**
 * @brief Svinger til venstre
*/
void left() {
  // Serial.println("LEFT!");
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, LOW);

  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  digitalWrite(r4, HIGH);

  // analogWrite(enA, 60);
  // analogWrite(enB, 100);
  analogWrite(enA, 60);
  analogWrite(enB, 80);
}


/**
 * @brief Svinger til høyre
*/
void right() {
  // Serial.println("RIGHT!");
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, HIGH);

  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, LOW);

  analogWrite(enA, 80);
  analogWrite(enB, 60);
}

void turnAroundRight() {
  // Serial.println("RIGHT!");
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, HIGH);

  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, LOW);

  analogWrite(enA, 140);
  analogWrite(enB, 120);
}

/**
 * @brief Stopper roboten
*/
void stop() {
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);

  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  // Serial.println("Stopper!");
}


// Andre funksjoner --------------------------------
/**
 * @brief Når det blir mottatt en melding fra MQTT broker (nettsiden)
*/
void onMqttMessage(int messageSize) {
  Serial.print("Ny melding i topic: '");
  Serial.println(mqttClient.messageTopic());

  StaticJsonDocument<16> filter;
  filter["dropSted"] = true;

  StaticJsonDocument<64> doc;
  DeserializationError error = deserializeJson(doc, mqttClient, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  dropSted = doc["dropSted"];  
}


/**
 * @brief Setter dropSted til å være det samme som prevDropSted
 * @return dropSted (om det er endret)
*/
int getDropSted() {
  if (dropSted != prevDropSted) {
    prevDropSted = dropSted; 
    return dropSted;
  }
  else {
    return -1; 
  }
}