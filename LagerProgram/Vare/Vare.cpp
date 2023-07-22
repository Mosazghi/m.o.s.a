#include "Vare.h"
#include <stdlib.h>     /* atoi */


/**
*   Default construcor.
*/
Vare::Vare(){}

/**
*   Fyller privat data.
*   @param Const char* komponentNavn, komponentAntall (navnet og antallet til varen)
*/
void Vare::insert(const char* komponentNavn, const char* komponentAntall) {
    navn =  komponentNavn;
    antall = komponentAntall;
}

/**
*   Sender navnet til den bestilte varen.
*
*   @return navn - navnet it varen 
*/
const char* Vare::hentNavn() {
    return navn;
}

/**
*   Sender antallet varer som bestilles.
*
*   @return int converted - antallet av bestillingen 
*/
int Vare::hentAntall() {
    int converted;
    converted = atoi(antall);
    return converted;
}