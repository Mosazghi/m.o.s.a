#include <Lager.h>
#include <Vare.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Lager lager("Abdi", "zxqp2111", D1);

Vare vare;

void setup() {
  Serial.begin(115200);
  lager.begin();
}

void loop() {
  getData("http://192.168.2.182:4000/dashboard/api/bestilling");
  lager.prepare(D0, D3, D2, D5, vare.hentAntall());
  
  /*
  lager.waitOnCar();
  lager.give()
  lager.delete() 
  millis(10000);
  Serial.println(test);
  */
}

/**
*   Sender en GET request og mottar en Vare objekt som inneholder den eldste bestillingen.
*
*   @param String link - nettside adresse
*   @see bool Lager::isConnected()
*/
void getData(String link){
    if(lager.isConnected()){
        HTTPClient http;
        http.begin(link.c_str()); // legger inn link'en
        int result = http.GET(); // get request

        if(result > 0) {
            int i = 0; // runde int 
            String rawJson = http.getString();
            StaticJsonDocument<256> doc;
            DeserializationError error = deserializeJson(doc, rawJson);

            if(error){
            Serial.print("JSON ERROR: ");
            Serial.println(error.c_str());
            }

            const char* komponentNavn = doc["komponenter"][0]["Komponent"]; // "motstand 2k"
            const char* komponentAntall = doc["komponenter"][0]["Antall"]; // "4"

            vare.insert(komponentNavn, komponentAntall);
            Serial.println("Varen er mottat!");
        }else{
          Serial.print("Error code: ");
          Serial.println(result);
        }
        http.end();
    }
  delay(2000);
}