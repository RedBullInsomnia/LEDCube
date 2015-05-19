#include "functions.h"
#include <stdint.h>
#include <spi.h>
#include <stdlib.h>
#include <stdio.h>

#define _XTAL_FREQ 30000000

void init() {

    // Initiate the SPI
    initSpi();

    // Init random numbers
    srand(TMR0L);

    // Output enable on tlc 5916
    TRISDbits.RD2 = 0;
    OE = 1; //active low, so disabled by default

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

    // By default, all levels are disabled
    disableLevels();

    // Init global variables
    resetCube();
    currentLevel = 0;

     // Define interrupt priority
    IPEN = 1; // Interrupt priority bit
    GIE = 1; //enable Global interrupts (high priority as IPEN = 1)
    GIEL = 1; //enable low priority interrupts

    // Configure timer 0 for display interrupt
    T0CON = 0b10011000; //activate the timer0 with the right parameters
    TMR0IE = 1; //enable TMR0 overflow interrupts (INTCON PDF pg. 113)
    TMR0IP = 1; // TMRO is a high priority interrupt ( bit 2 de INTCON 2)
    resetTimer();

    // Configure external interrupt for the button
    INT2IE = 1;
    INT2IP = 0;
    INTEDG2 = 0; // Interrupt on a falling edge ( bit 4 de INTCON 2)
    INT2IF = 0;

    // Configure INT2 has an input
    TRISBbits.RB2 = 1;
    // Configure PIN RB3 as VDD and RB4 as GND for the button usage
    TRISBbits.RB3 = 0; LATBbits.LATB3 = 1;
    TRISBbits.RB4 = 0; LATBbits.LATB4 = 0;

}

void initSpi() {
    CloseSPI();
    OpenSPI(SPI_FOSC_4, MODE_00, SMPMID);
}

void resetTimer() {
    TMR0L = 0x23;
    TMR0H = 0xCD;
    TMR0IF = 0; //TMR0 interrupt flag must be cleared in software to allow subsequent interrupts increment the counter variable by 1
}

void blink() {
    blinky = 1;
    delay_10ms(255);
    blinky = 0;
    delay_10ms(255);
}

void blink_nb_times(uint8_t nb) {
    for (uint8_t i = 0; i < nb; i++)
        blink();
}

void resetCube() {
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            cube[i][j] = 0;
}

void setCube() {
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            cube[i][j] = 0xFF;
}

void disableLevels() {
    LATA &= 0b11000000;
    LATE &= 0b1100;
}

void sendByte(uint8_t byte, uint8_t latch) {
    LE = 0; // LE low
    WriteSPI(byte);
    if (latch > 0) {
        LE = 1; // LE high
        Nop();
        Nop();
        LE = 0; // LE low; to activate latch
    }
}

void selectLevel(uint8_t level) {
    // First disable all levels
    disableLevels();

    // Wait a few cycles for the MOST to close
    Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop();

    // Then, activate the one you want
    switch (level) {
        case 0: LEV1 = 1;
            break;

        case 1: LEV2 = 1;
            break;

        case 2: LEV3 = 1;
            break;

        case 3: LEV4 = 1;
            break;

        case 4: LEV5 = 1;
            break;

        case 5: LEV6 = 1;
            break;

        case 6: LEV7 = 1;
            break;

        case 7: LEV8 = 1;
            break;
    }
}

void sendByteAndLevel(uint8_t byte, uint8_t latch, uint8_t level) {
    disableLevels();
    sendByte(byte, latch);
    selectLevel(level);
}

void sendLevel(uint8_t byte[8], uint8_t level) {
    // disable the current sinks
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
    Nop(); Nop();
    LE = 0; // LE low; to activate latch
    OE = 0; // enable output
}

void delay_10ms(int multiplier)
{
    for(int i=0; i<multiplier ; i++)
        __delay_ms(10);
}

void interrupt high_priority Timer0_ISR() {
    if (TMR0IE && TMR0IF) {
        resetTimer();
        //blinky = 1;

        sendLevel(cube[currentLevel], currentLevel);

        if (currentLevel == 7)
            currentLevel = 0;
        else
            currentLevel++;

        //blinky = 0;
    }
}


void interrupt low_priority pressedOnButton() {
    if (INT2IE && INT2IF) {
        blinky = 1;
        buttonPressed = 1;
        blinky = 0;
        INT2IF = 0;
    }
}