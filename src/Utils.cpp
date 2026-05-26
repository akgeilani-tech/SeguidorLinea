#include "Utils.h"

void setupFastPWM()
{
    // TIMER0
    TCCR0B =
        TCCR0B & 0b11111000 | 0x01;

    // TIMER1
    TCCR1B =
        TCCR1B & 0b11111000 | 0x01;

    // TIMER2
    TCCR2B =
        TCCR2B & 0b11111000 | 0x01;
}