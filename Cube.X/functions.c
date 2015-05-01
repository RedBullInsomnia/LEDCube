#include "functions.h"
#include <spi.h>

void init()
{
    initSpi();

    // Output enable on tlc 5916
    TRISDbits.RD2 = 0;
    LATDbits.LATD2 = 1; //active low

    // Latch enable
    TRISDbits.RD3 = 0;
    LATDbits.LATD3 = 0;

    // Blinky on RD5 as output
    TRISDbits.RD5 = 0;
    LATDbits.LATD5 = 0; // 0 at beginning

    // Disable A/D
    ADCON1 = 0x0F;

    // Disable comparator
    CMCON = 0x07;

     // Level selectors
    TRISA = 0;
    LATA = 0;
    TRISE = 0;
    LATE = 0;
}

void initSpi()
{
    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
}

void clearCube()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            cube[i][j] = 0;
        }
    }
}

void sendByte(unsigned char byte, unsigned char single)
{
    LATDbits.LATD2 = 1; // disable output
    LATDbits.LATD3 = 0; // LE low

    WriteSPI(byte);

    if(single)
    {
        LATDbits.LATD3 = 1; // LE high
        LATDbits.LATD3 = 0; // LE low; to activate latch
        LATDbits.LATD2 = 0; // enable output
    }
}

void sendByteL(unsigned char byte, unsigned char single, unsigned int level)
{
    PORTD = 0;
    sendByte(byte, single);
    selectLevel(level);
}

void sendLevel(unsigned char byte[8], unsigned int level)
{
    PORTD = 0x0; //disable all levels

    for (int i = 0; i < 8; i++)
        sendByte(byte[i], 0); //send 8 bytes

    // Latch and activate
    selectLevel(level);
    PORTEbits.RE1 = 1; // LE high
    PORTEbits.RE1 = 0; // LE low; to activate latch
    PORTEbits.RE0 = 0; // enable output
}

void sendFrame(unsigned char byte[8][8])
{
    unsigned int level = 1;
    for (int i = 0; i < 8; i++)
    {
        sendLevel(byte[i], level);
        level = level*2;
    }
}

void selectLevel(unsigned int level)
{
    switch(level)
    {
        case 1 : LATA &= 0b00000100; // RA2
        break;

        case 2 : LATA &= 0b00001000; // RA3
        break;

        case 3 : LATA &= 0b00010000; // RA4
        break;

        case 4 : LATA &= 0b00100000; // RA5
        break;

        case 5 : LATA &= 0b00000010; // RA1
        break;

        case 6 : LATA &= 0b00000001; // RA0
        break;

        case 7 : LATE &= 0b0010; // RE1
        break;

        case 8 : LATE &= 0b0001; // RE0
        break;
    }
}
