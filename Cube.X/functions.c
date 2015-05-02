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

     // Init Level selectors
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
        for (uint8_t j = 0; j < 8; j++)
            cube[i][j] = 0;
}

void disableLevels()
{
    LATA &= 0b11100000;
    LATE &= 0b1100;
}

void enableLevels()
{
    LATA |= 0b11111111;
    LATE |= 0b1111;
}

void sendByte(uint8_t byte, uint8_t single)
{
    OE = 1; // disable output
    LE = 0; // LE low

    WriteSPI(byte);

    if(single)
    {
        LE = 1; // LE high
        LE = 0; // LE low; to activate latch
        OE = 0; // enable output
    }
}

void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level)
{
    disableLevels();
    sendByte(byte, single);
    selectLevel(level);
}

void sendLevel(uint8_t byte[8], uint8_t level)
{
    disableLevels();

    for (int i = 0; i < 8; i++)
        sendByte(byte[i], 0); //send 8 bytes

    // Latch and activate
    selectLevel(level);
    LE = 1; // LE high
    LE = 0; // LE low; to activate latch
    OE = 0; // enable output
}

void sendFrame(uint8_t byte[8][8])
{
    uint8_t level = 1;
    for (uint8_t i = 0; i < 8; i++)
    {
        sendLevel(byte[i], level);
        level++;
    }
}

void selectLevel(uint8_t level)
{
    // First disable all levels
    disableLevels();
    
    switch(level)
    {
        case 1 : LEV1 = 1;
                 break;

        case 2 : LEV2 = 1;
                 break;

        case 3 : LEV3 = 1;
                 break;

        case 4 : LEV4 = 1;
                 break;

        case 5 : LEV5 = 1;
                 break;

        case 6 : LEV6 = 1;
                 break;

        case 7 : LEV7 = 1;
                 break;

        case 8 : LEV8 = 1;
                 break;
    }
}


