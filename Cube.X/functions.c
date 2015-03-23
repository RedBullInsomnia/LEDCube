#include "functions.h"
#include <spi.h>


void init()
{
    initSpi();

    // Output enable on tlc 5916
    TRISEbits.RE0 = 0;
    PORTEbits.RE0 = 1; //active low

    // Latch enable
    TRISEbits.RE1 = 0;

    // Port D as output
    TRISD = 0;
    PORTD = 0; // 0 at beginning
}

void initSpi()
{
    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
}

void sendByte(unsigned char byte, unsigned char single)
{
    PORTEbits.RE0 = 1; // disable output
    PORTEbits.RE1 = 0; // LE low

    WriteSPI(byte);

    if(single)
    {
        PORTEbits.RE1 = 1; // LE high
        PORTEbits.RE1 = 0; // LE low; to activate latch
        PORTEbits.RE0 = 0; // enable output
    }
}

void sendByteL(unsigned char byte, unsigned char single, unsigned char level)
{
    PORTD = 0;
    sendByte(byte, single);
    PORTD = level;
}

void sendLevel(unsigned char byte[], unsigned char level)
{
    PORTD = 0; //disable all levels

    for (int i = 0; i < 8; i++)
        sendByte(byte[i], 0) //send 8 bytes

    // Latch and activate
    PORTD = level;
    PORTEbits.RE1 = 1; // LE high
    PORTEbits.RE1 = 0; // LE low; to activate latch
    PORTEbits.RE0 = 0; // enable output
}

void sendFrame(unsigned char byte[][])
{
    unsigned char level = 0x00000001;
    for (int i = 0; i < 8; i++)
    {
        sendLevel(byte[i], level)
        level *= 2;
    }
}
