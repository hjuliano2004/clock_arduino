#include "Tick.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

static volatile unsigned long overflow_count = 0;
static uint8_t timer_initialized = 0;

void timerInit() {
    TCCR1A = 0;           // modo normal
    TCCR1B = (1 << CS11); // prescaler = 8
    TCNT1 = 0;            // zera contador

    TIMSK1 = (1 << TOIE1); // habilita interupção de overflow
    sei();                 // habilita interrupções globais
}

ISR(TIMER1_OVF_vect) {
    overflow_count++; // cada vez que transborda soma 1
}

unsigned long micros() {

    if (!timer_initialized) {
        timerInit();
        timer_initialized = 1;
    }

    unsigned long ovf;
    uint16_t cnt;
    cli();
    ovf = overflow_count;
    cnt = TCNT1;
    sei();

    return (((ovf << 16) | cnt) >> 1);
}
