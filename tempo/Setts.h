#ifndef SETTS_H
#define SETTS_H

#include "Diferenca.h"
#include <stdbool.h>


typedef struct {
    int id;                       // identificador único
    void (*callback)(void *arg);
    void *arg;
    unsigned long inicio;
    unsigned long intervalo;
    bool repete;
} SetTimer;


typedef struct{
    SetTimer** list;
    int length;
    int size;

}TimerList;

extern TimerList *temporizadores;

TimerList *timerList();

SetTimer *setInterval(void (*callback)(void *arg), void *arg, unsigned long intervalo);

SetTimer *setTimeOut(void (*callback)(void *arg), void *arg, unsigned long intervalo);
void clearAllIntervals();

TimerList *addTimer(TimerList *list, SetTimer *setTimer);

void rodar();

void repetidor(SetTimer *timer);

void clearInterval(SetTimer* setTimer);

#endif