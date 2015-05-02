#include "debug.h"
#include "delays.h"
#include <xc.h>
#include "functions.h"

#define _XTAL_FREQ 8000000

void startSequence(uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
        blink();
}

void blink()
{
    PORTDbits.RD5 = 1;
    for(uint8_t i = 0; i <100; i++)
        __delay_ms(50);
    PORTDbits.RD5 = 0;
    for(uint8_t i = 0; i <100; i++)
        __delay_ms(50);
}

void testMsg()
{
    uint8_t msg = 0x55;
    uint8_t single = 0xFF; // Yes, it is a single message

    sendByte(msg, single);
}

void testLevel()
{
    uint8_t msg = 0x55;
    uint8_t level = 3;
    sendLevel(msg, level);
}
