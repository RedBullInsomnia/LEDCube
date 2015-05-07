#include "functions.h"
#include "user.h"
#include <stdint.h>
#include <spi.h>

#define _XTAL_FREQ 8000000

void init()
{
    initSpi();

    // Output enable on tlc 5916
    TRISDbits.RD2 = 0;
    OE = 0; //active low

    // Latch enable
    TRISDbits.RD3 = 0;
    LE = 0;

    // Blinky on RD5 as output
    TRISDbits.RD5 = 0;
    blinky = 0; // 0 at beginning

    // Disable A/D on port A
    ADCON1 = 0x0F;

    // Disable comparator on port A
    CMCON = 0x07;

     // Initialize Level selectors
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;

    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    
    disableLevels();

    // Clear the cube
    clearCube();
}

void initSpi()
{
    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
}

void blink()
{
    blinky = 1;
    for(uint8_t i = 0; i < 50; i++)
        __delay_ms(50);
    blinky = 0;
    for(uint8_t i = 0; i < 50; i++)
        __delay_ms(50);
}

void initBlinky(uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
        blink();
}

void clearCube()
{
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            cube[i][j] = 0;
}

void fullCube()
{
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            cube[i][j] = 0xFF;
}

void disableLevels()
{
    LATA &= 0b11000000;
    LATE &= 0b1100;
}

void enableLevels()
{
    LATA |= 0b11111111;
    LATE |= 0b1111;
}

void sendByte(uint8_t byte, uint8_t single)
{
    LE = 0; // LE low

    WriteSPI(byte);

    if(single > 0)
    {
        LE = 1; // LE high
        //__delay_ms(10);
        LE = 0; // LE low; to activate latch
    }
}

void selectLevel(uint8_t level)
{
    // First disable all levels
    disableLevels();

    // Then, activate the one you want
    switch(level)
    {
        case 0 :
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

void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level)
{
    disableLevels();
    sendByte(byte, single);
    selectLevel(level);
}

void sendLevel(uint8_t byte[8], uint8_t level)
{
    //disableLevels();

    for (uint8_t i = 0; i < 8; i++)
        sendByte(byte[i], 0); //send 8 bytes 8 times

    // Latch and activate
    selectLevel(level);
    LE = 1; // LE high
    LE = 0; // LE low; to activate latch
    //OE = 0; // enable output
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
