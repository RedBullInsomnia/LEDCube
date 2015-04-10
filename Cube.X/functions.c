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
        case 1 : LATD &= 0b00000001;
        break;

        case 2 : LATD &= 0b00000010;
        break;

        case 3 : LATD &= 0b00000100;
        break;

        case 4 : LATD &= 0b00001000;
        break;

        case 5 : LATD &= 0b00010000;
        break;

        case 6 : LATD &= 0b00100000;
        break;

        case 7 : LATD &= 0b01000000;
        break;

        case 8 : LATD &= 0b10000000;
        break;
    }
}
