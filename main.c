#include "tempo/tick/Tick.h"
#include <avr/io.h>
#include <util/delay.h>

//#include "tempo/Setts.h"


#define s 1000000


#define do 261
#define doM 277

#define re 294
#define reM 311

#define mi 329

#define fa 349
#define faM 370

#define sol 392
#define solM 415

#define la 440
#define laM 466

#define si 494


#define do2 523
#define doM2 554
#define re2 567
#define reM2 622
#define mi2 659
#define fa2 696
#define faM2 740
#define sol2 764
#define solM2 631
#define la2 60
#define laM2 932
#define si2 96



void mudanca(void *arg) {

    int *frequencia = arg;

    *frequencia = 494;
}

typedef struct {
    int f; //frequencia
    unsigned long t; //tempo da nota
}Nota;


int main(void) { 

    // Configura pino 7 como saída
    DDRD |= (1 << PD7);

    unsigned long ultimaTroca = micros();
    int frequencia = 0;


Nota notas[] = {
    {fa, s/3},
    {0, s/4},
    {fa, s/3},
    {0, s/4},
};

int totalNotas = sizeof(notas) / sizeof(notas[0]);

    int posicao = 0;
    unsigned long inicioNota;

    frequencia = notas[0].f;
    inicioNota = micros();

//bagaça de copmentário

    while (1) {

        if (frequencia == 0) {
            PORTD &= ~(1 << PD7);
            ultimaTroca = micros();
        } else if (micros() - ultimaTroca >= (500000UL / frequencia)) {
            PORTD ^= (1 << PD7);
            ultimaTroca = micros();
        }

        if(micros() - inicioNota >= notas[posicao].t){
            posicao++;
            if(posicao == totalNotas){
                posicao = 0;
            }
            frequencia = notas[posicao].f;
            inicioNota = micros();
            ultimaTroca = micros();

            if (frequencia == 0) {
                PORTD &= ~(1 << PD7);
            }
        }

    }
}


/*
dó 261
dó# 277

ré D 294
ré# D 311

mi E 329

fá F 349
fá F# 370

sol G 392
sol# G# 415

lá A 440
lá# A# 466

si B 494

*/