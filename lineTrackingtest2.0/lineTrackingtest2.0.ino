#include <WiFi.h>

#include <HTTPClient.h>

#include <ArduinoJson.h>


#include <Wire.h>

#define in1 4
#define in2 13
#define in3 23
#define in4 18
#define enA 2
#define enB 19

#define frontPin 25
#define midPin 26
#define leftPin 27
#define rightPin 32
#define backPin 33

char auth[] = " ";
const char* ssid = "Abdi";
const char* password = "zxqp2111";

int M1_Speed = 50; // speed of motor 1
int M2_Speed = 50; // speed of motor 2
int LeftRotationSpeed = 250; // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed

unsigned lineCount = 0;

int stajsonNr = 0;

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

  // // Connect to Wi-Fi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // Input fra bruker (serial monitor)
  // Serial.println(" ");
  // Serial.println("Hvilken stasjon skal M.O.S.A til 1 eller 2?: ");
  // while (Serial.available() == 0) {}

  // stajsonNr = Serial.parseInt();
  // delay(2000);

  // stajsonNr;
  // forward();
  // delay(5000);
  // backward();
  // delay(5000);
  // left();
  // delay(5000);
  // right();
  // delay(5000);
  // Stop();
}

int FRONT_SENSOR = digitalRead(frontPin);
int MID_SENSOR = digitalRead(midPin);
int LEFT_SENSOR = digitalRead(leftPin);
int RIGHT_SENSOR = digitalRead(rightPin);
int BACK_SENSOR = digitalRead(backPin);

void loop() {

  // HTTPClient http;

  // while (true) {
  //   http.begin("http://192.168.218.179:4000/dashboard/api/bestilling");
  //   int httpResponseCode = http.GET();
  //   String payload = http.getString();

  //   StaticJsonDocument<384> doc;
  //   Serial.print("payload:");
  //   Serial.println(payload);
  //   DeserializationError error = deserializeJson(doc, payload);

  //   if (error) {
  //     Serial.print("deserializeJson() failed: ");
  //     Serial.println(error.c_str());
  //     http.end();
  //     continue;
  //   }

  //   const char* id = doc["_id"]; // "64a5bc8d247ec5276ebc856e"
  //   const char* bruker = doc["bruker"]; // "mos"
  //   int dropSted = doc["dropSted"]; // 4

  //   for (JsonObject komponenter_item : doc["komponenter"].as<JsonArray>()) {
  //     const char* komponenter_item_Komponent = komponenter_item["Komponent"]; // "Bryter", "LED", ...
  //     const char* komponenter_item_Antall = komponenter_item["Antall"]; // "3", "2", "3"
  //   }

  //   int v = doc["__v"]; // 0

  //   if (httpResponseCode == 200 && payload.length() > 0) {
  //     // Process the JSON data
  //   } else {
  //     // No new JSON data available
  //   }

  //   http.end();

  //   delay(60000);
  // }

  // if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0 && MID_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) {
  //   forward(); //FORWARD
  //   Serial.println("Fremover");
  // } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) {
  //   right(); //Move Right
  //   Serial.println("HÃ¸yre");
  // } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) {
  //   left(); //Move Left
  //   Serial.println("Venstre");
  // } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1 && MID_SENSOR == 0 && BACK_SENSOR == 0 && FRONT_SENSOR == 0) {
  //   right(); //Move Right
  //   Serial.println("Høyre");
  // } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1 && MID_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 0) {
  //   Stop(); //STOP
  //   Serial.println("Stopper");
  // } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1 && MID_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) { //Kryss
  //   intersectionDetected();
  //   Serial.println("Ved krysset: ");
  //   Serial.print(lineCount);
  //   Serial.println(" ");

  //   if (stajsonNr == lineCount && stajsonNr == 1) {
  //     Serial.println("Tar svingen til stasjon ");
  //     Serial.print(stajsonNr);
  //     right(); // Tar svingen til høyre
  //     delay(2000);
  //     forward();
  //   } else if (stajsonNr == lineCount && stajsonNr == 2) {
  //     Serial.println("Tar svingen til stasjon ");
  //     Serial.print(stajsonNr);
  //     left(); // Tar svingen til venstre
  //     delay(2000);
  //     forward();
  //   } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1 && MID_SENSOR == 0 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) {
  //     Serial.println("Ved drop steddet");
  //     dropSpot();
  //   } else {
  //     forward();
  //   }

  // }
}



//Ikke ferdig mangler funskjoner som vektsensor osv...
void dropSpot() {
  Stop();
  turnAround();
  delay(2000); //Få på last 
  forward();
}

// void returnStart() {
//   lineCount = 0;

//   turnAround();
//   forward(); // Til den møter stopskilt (T)
// }

// // Ikke ferdig
// void goToDropSpot() {
//   lineCount = 0;
//   turnAround();
//   forward();
//   if (stajsonNr == 1 && lineCount == 1) {
//     right();
//     delay(2000);
//     forward();
//   } else if (stajsonNr == 2 && lineCount == 1) {
//     left();
//     delay(2000);
//     forward();
//   } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 0) {
//     Stop(); //STOP
//     Serial.println("Stopper");
//   } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1 && BACK_SENSOR == 1 && FRONT_SENSOR == 1) { //Kryss
//     int stajsonNr = 2; //Hardkodet 
//     intersectionDetected();
//     Serial.println("Ved krysset: ");
//     Serial.print(lineCount);
//     Serial.println(" ");
//     if (lineCount == stajsonNr) {
//       Serial.println("Tar svingen til stasjon 2");
//     } else {
//       forward();
//     }
//   }
// }
//--------manuvere-funksjoner---------

// Ved oppstart (hente komponenter)--------------------------------
void baseTilS1() {
  if (!digitalRead(LEFT_SENSOR) && !digitalRead(RIGHT_SENSOR) && digitalRead(FRONT_SENSOR) && digitalRead(BACK_SENSOR)) {
    forward();
    Serial.println("Fremover");
    delay(2000);
    turnLeft();
  }
}
void baseTilS2() {

}

// Ved levering (lever komponenter)--------------------------------
void S1tilD1() {

}

void S1tilD2() {

}

void S2tilD1() {

}

void S2tilD2() {

}

// Tilbake til basen--------------------------------

void D1tilBase() {

}

void D2tilBase() {

}

// Andre funksjoner --------------------------------
void turnAround() {}

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

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
  Serial.println("kjører frem!");
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
  Serial.println("kjører bak!");

}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
  Serial.println("kjører høyre!");

}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
  Serial.println("kjører venstre!");

}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.println("stopper!");

}