// Bibliotker --------------------

//#include <WiFi.h>   
//#include <PubSubClient.h>
//#include <HTTPClient.h>
//#include <ArduinoJson.h>
//#include <Wire.h>

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

const char * ssid = "Weini2.4G";
const char * password = "20052009";

const char* mqttBroker = "10.0.0.13";
const int mqttPort = 1884;   

//WiFiClient wifiClient;
//PubSubClient mqttClient(wifiClient);

// Motor variabler --------------------

int M1_Speed = 50;  


int MID_SENSOR = 0;
int LEFT_SENSOR = 0;
int RIGHT_SENSOR = 0 ;

unsigned lineCount = 0;
int stajsonNr = 0;

int dropSted;
int prevDropSted = 0;

// millis delay ---------------------
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1500;  // interval at which to blink (milliseconds)
bool reachedStation = false; 
bool reachedDelivery = false; 

// Setup --------------------
void setup() {
  Serial.begin(9600);

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


	
	// Turn off motors - Initial state
 

  pinMode(midPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);

  // // WiFi tilkobling
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // // Tilbkopling til MQTT
  // mqttClient.setServer(mqttBroker, mqttPort);
  // mqttClient.setCallback(mqttCallback);
  // mqttClient.subscribe("shoplist");

  // while (!mqttClient.connected()) {
  //   if (mqttClient.connect("ArduinoClient")) {
  //     mqttClient.subscribe("shoplist");  
  //     Serial.println("Tilkoblet MQTT!");
  //   } else {
  //     Serial.println("MQTT timeout, prøver igjen...");
  //     delay(5000);
  //   }
  // }

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
  //   // Reconnect til MQTT hvis tilkobling er brutt
  //   if (mqttClient.connect("ArduinoClient")) {
  //     mqttClient.subscribe("shoplist");   
  //   }
  // }
  // mqttClient.loop();

  // IR sensorer
  MID_SENSOR = digitalRead(midPin);
  LEFT_SENSOR = digitalRead(leftPin);
  RIGHT_SENSOR = digitalRead(rightPin);
  // if(!reachedStation) {
  //   baseTilStasjon();
  // } else {
  //   stasjonTilD2();
  //   if(reachedDelivery) {
  //     stop();
  //     D2tilBase();
  //   }
  // }
 
  unsigned long currentMillis = millis();

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
		// Serial.println("-----------------");  
  }

  //---- MAIN ----
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

// Test funksjoner --------------------

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
  }
  // IF OUT OF LINE, STRAIGHTEN SELF 
  else {
    keepStraightLine();
    // Serial.println("HER_3");
  }
}

void keepStraightLine() {
  if(LEFT_SENSOR && !RIGHT_SENSOR && !MID_SENSOR) {
    // Serial.println("KEEP RIGHT!");
    left();
  }
  else if(RIGHT_SENSOR && !LEFT_SENSOR && !MID_SENSOR) {
    // // Serial.println("KEEP LEFT!");
    right();
  }
 
}

// Enten den ene eller andre 
// Ved oppstart (hente komponenter)--------------------------------
void baseTilStasjon() {
  Serial.println("STASJONEN");
  // Serial.println("Kjører til stasjonen!");
  turnLeft();
  
  // IF ARRIVED BASE, STOP AND TURN AROUND (LEFT/RIGHT) 
  if (!LEFT_SENSOR && !MID_SENSOR && !RIGHT_SENSOR) {
    stopAndTurnAround();
    delay(2000);
    reachedStation = true; 
  }
}


void stopAndTurnAround() {
  forward();
  delay(1000);
  stop();
  delay(2000);
  right();
  if(!LEFT_SENSOR && MID_SENSOR && !RIGHT_SENSOR) {
    stop();
    delay(3000);;
    Serial.println("TURNING FINISHED!");
  }
}

// // Ved levering (lever komponenter)--------------------------------
// void stasjonTilD1() {
//   Serial.println("Kjører til D1!");
//   forward(); // Kjører frem til kryss
//   if (!digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
//     right(); // Svinger til høyre og kjører til dropsted 1 
//     delay(2000);
//     forward();
//     Serial.println("Svinger venstre & kjører forward");
//     if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
//       stopAndTurnAround();
//       Serial.println("Stoppet, framme ved dropsted 1");
//     }
//   }
// }

void stasjonTilD2() {
  if(!LEFT_SENSOR && MID_SENSOR && !RIGHT_SENSOR) {
    Serial.println("D2");
    forward();
  }
  else if (LEFT_SENSOR && !MID_SENSOR && !RIGHT_SENSOR) {
    stop();
    delay(2000);
    Serial.println("ARRIVED AT D2!");
    reachedDelivery = true;
  }
  else {
    keepStraightLine();
  }
}

// // Tilbake tvoid D1tilBaseil basen--------------------------------
// () {
//   if(!digitalRead(LEFT_SENSOR) && !digitalRead(RIGHT_SENSOR) && digitalRead(MID_SENSOR) && !digitalRead(FRONT_SENSOR) && !digitalRead(BACK_SENSOR)) {
//     forward();
//     Serial.println("kjører til basen!");
//   }
//   if (digitalRead(LEFT_SENSOR) && digitalRead(RIGHT_SENSOR) && !digitalRead(MID_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
//     stopAndTurnAround();
//     Serial.println("Stoppet, framme ved ladestasjon");
//   }
// }

void D2tilBase() {
  stopAndTurnAround();
}

// // Andre funksjoner --------------------------------

// void intersectionDetected() {
//   static long lastDetected = 0;
//   if (millis() - lastDetected < 2000) {
//     return;
//   }
//   lastDetected = millis(); //Sist sjekket linje */
//   lineCount++;
// }

 


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

  analogWrite(enA, 55);
  analogWrite(enB, 75);
}

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

  analogWrite(enA, 75);
  analogWrite(enB, 55);
}


 


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
// void mqttCallback(const char* topic, byte* payload, unsigned int length) {
//   String jsonPayload;
//   for (int i = 0; i < length; i++) {
//     jsonPayload += (char)payload[i];
//   }

//   StaticJsonDocument<16> filter;
//   filter["dropSted"] = true;

//   StaticJsonDocument<64> doc;

//   DeserializationError error = deserializeJson(doc, jsonPayload, DeserializationOption::Filter(filter));

//   if (error) {
//     Serial.print("deserializeJson() failed: ");
//     Serial.println(error.c_str());
//     return;
//   }

//   dropSted = doc["dropSted"];  
// }

int getDropSted() {
  if (dropSted != prevDropSted) {
    prevDropSted = dropSted; 
    return dropSted;
  }
  else {
    return -1; 
  }
}


