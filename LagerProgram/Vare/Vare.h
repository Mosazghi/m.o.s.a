/**
*   Vare.h - programmet definer hva en "vare" skal hete, og antallet bestilt.
*
*   @author Abdirahman Ahmed Yusuf - Sommerprojektet 2023
*/
#ifndef __VARE_H
#define __VARE_H

#include "Arduino.h"

class Vare {
    private: 
    const char* navn; // komponent navnet 
    const char* antall; // antallet bestillt

    public:
    Vare();
    void insert(const char* komponentNavn, const char* komponentAntall);
    const char* hentNavn();
    int hentAntall();

};

#endif