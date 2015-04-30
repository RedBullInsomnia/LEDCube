#include "debug.h"
#include "delays.h"
#include <xc.h>

#define _XTAL_FREQ 8000000

void startSequence(uint8_t length)
{
    uint8_t i;
    blink();
    for (i = 0; i < length; i++)
    {
        blink();
    }
}

void blink()
{
    PORTDbits.RD5 = 1;
    for(int i = 0; i <100; i++)
        __delay_ms(50);
    PORTDbits.RD5 = 0;
    for(int i = 0; i <100; i++)
        __delay_ms(50);
}

void testLevelControl()
{

}