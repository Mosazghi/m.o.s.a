#include "Lager.h"
#include <WiFi.h>
#include <pwmWrite.h>

/**
*   Default constructor.
*   @param char* ssid, passord - nettverk navn og passord
*/
Lager::Lager(const char* nettverkNavn, const char* nettPassord, int SPin){
  ssid = nettverkNavn;
  passord = nettPassord;
  sensorPin = SPin;
}

/**
*   constructor + kobler opp til nettverket
*
*   @see bool Lager::isConnected
*/
void Lager::begin(){
    WiFi.begin(ssid, passord);
    Serial.println("Connecting");
    while(!Lager::isConnected()) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

/*
*   Sjekker om esp32'en er i nettet.
*
*   @return true/false
*/
bool Lager::isConnected(){
    return (WiFi.status() == WL_CONNECTED ? true : false);
}

/**
*   Sender en melding om lyssensoren er dekket. 
*
*   @return 1 eller 0 
*/
int Lager::count() {
    int sensorData, midNumber;
    midNumber = 500; // analogsignalets midpunkt
    sensorData = analogRead(sensorPin); // analogsignalet
   
    return (sensorData <= midNumber ? 1 : 0); 
}

/**
*   Plokker ut varene som blir bestilit og gjør dem klar til å leveres.
* 
*   @param int servo, in1, in2, en, antall - pin for motor og servo + antall varer
*/
void Lager::prepare(int servo, int in1, int in2, int en, int antall) {
    Pwm pwm = Pwm();
    pinMode(en, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    int runde = 0; // hjelpe variabel 

    while(runde < antall){
        if(!Lager::count()){ // hvis der er lyst kjører motoren
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(en, 150);
        }else{ // servoen drar av motstanden når lyset blir dekket
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(en, 0);
            runde++;

            // sweep bevegelse
            pwm.writeServo(servo, 180);
            delay(1000);
            pwm.writeServo(servo, 0); // nullstiller posisjonen 
        }

        delay(5000);
        Serial.println(runde);
    }

    // slår av motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
    Serial.println("Preperasjon status: 100%");
}