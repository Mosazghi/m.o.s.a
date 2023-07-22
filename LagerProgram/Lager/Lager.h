/**
*   Lager.h - programmet lager et lager som kan hente data fra en valgt nettside via GET request
*   også velge riktig komponent basert på JSON dataen den får tak i.
*
*   @author Abdirahman Ahmed Yusuf - Sommerprojeket 2023
*/
#ifndef __LAGER_H
#define __LAGER_H

#include "Arduino.h" // trengs for å bruke arduino (f.eks. PinMode)
#include "Vare.h"

class Lager {
    private:
    const char* ssid; // nettverk navn
    const char* passord; // nettverk passord
    int sensorPin;
    enum {
        motstand,
        kondesator,
        spoler,
        kabel
    };

    public:
    Lager(const char* nettverkNavn, const char* netPassord, int SPin); // default constructor
    void begin(); // kobler direkte til nett
    //void connectMqtt(const char* broker, uint16_t port);
    bool isConnected();
    int count();
    void prepare(int servo, int in1, int in2, int en, int antall);
};

#endif
