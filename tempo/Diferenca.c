#include "Diferenca.h"
#include <stdbool.h>
#include "tick/Tick.h"

unsigned long decorrido(unsigned long inicio) {
    return micros() - inicio; // diferença em ciclos de clock
}

bool espera(unsigned long espera,  unsigned long *inicio) {

    unsigned long esperei = micros() - *inicio;

    if (esperei >= espera) {
        *inicio = micros();
        return true;
    }

    return false;
}