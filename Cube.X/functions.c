#include "functions.h"
#include "user.h"
#include <stdint.h>
#include <spi.h>

#define _XTAL_FREQ 30000000

void init()
{
    initSpi();

    // configure the timer 0
    T0CON = 0b10011000; // activate the timer0 with the right parameters
    TMR0IE = 1; //enable TMR0 overflow interrupts (voir INTCON PDF page 113)
    GIE = 1; //enable Global interrupts
    resetTimer();

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

    currentLevel = 0;
    irCount = 0;
}

void initSpi()
{
    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
}

void resetTimer()
{
//    TMR0L = 0x61;
//    TMR0H = 0xDB;
      TMR0L = 0xAD;
      TMR0H = 0xF8;
    TMR0IF = 0;//TMR0 interrupt flag must be cleared in software to allow subsequent interrupts increment the counter variable by 1
}

void blink()
{
    blinky = 1;
    for(uint8_t i = 0; i < 255; i++)
        __delay_ms(10);
    blinky = 0;
    for(uint8_t i = 0; i < 255; i++)
        __delay_ms(10);
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

void sendByte(uint8_t byte, uint8_t latch)
{
    LE = 0; // LE low

    WriteSPI(byte);

    if(latch > 0)
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
    Nop();   //!!!!!!!!!!!!!!
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();

    // Then, activate the one you want
    switch(level)
    {
        case 0 : LEV1 = 1;
                 break;

        case 1 : LEV2 = 1;
                 break;

        case 2 : LEV3 = 1;
                 break;

        case 3 : LEV4 = 1;
                 break;

        case 4 : LEV5 = 1;
                 break;

        case 5 : LEV6 = 1;
                 break;

        case 6 : LEV7 = 1;
                 break;

        case 7 : LEV8 = 1;
                 break;
    }
}

void sendByteAndLevel(uint8_t byte, uint8_t latch, uint8_t level)
{
    disableLevels();
    sendByte(byte, latch);
    selectLevel(level);
}

void sendLevel(uint8_t byte[8], uint8_t level)
{
    //disableLevels();
    OE = 1;
    sendByte(byte[7], 0); //send 8 bytes - driver 
    sendByte(byte[6], 0); //send 8 bytes - driver 
    sendByte(byte[3], 0); //send 8 bytes - driver 
    sendByte(byte[2], 0); //send 8 bytes - driver 
    sendByte(byte[5], 0); //send 8 bytes - driver 
    sendByte(byte[4], 0); //send 8 bytes - driver 
    sendByte(byte[1], 0); //send 8 bytes - driver 
    sendByte(byte[0], 0); //send 8 bytes - driver 

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

void interrupt Timer0_ISR()
{
    if (TMR0IE && TMR0IF)
    {
        resetTimer();
        if (irCount == 4) //are TMR0 interrupts enabled and is the TMR0 interrupt flag set?
        {
            blinky = 1;
            //resetTimer();
            
            sendLevel(cube[currentLevel], currentLevel);
            //sendLevel(cube[currentLevel], 0);
            if(currentLevel == 7)
                currentLevel = 0;
            else
                currentLevel++;

            blinky = 0;
        }
        else if (irCount == 3) //are TMR0 interrupts enabled and is the TMR0 interrupt flag set?
        {
            disableLevels();
        }

        if(irCount == 4)
            irCount = 0;
        else
            irCount++;
        
    }

}