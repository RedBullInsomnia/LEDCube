/*
 * File:   mainp18.c
 * Author: Hwk
 *
 * Created on 17 février 2015, 18:30
 */

#include <p18cxxx.h>
#include <spi.h>
#include <delays.h>
#include <xc.h>

#define _XTAL_FREQ 20000000

unsigned char portValue;

void interrupt blinky()
{
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        portValue++;
        INTCONbits.TMR0IF = 0; // clear this interrupt condition
    }
}

void sendByte(unsigned char byte)
{
    PORTEbits.RE0 = 1; // disable output
    PORTEbits.RE1 = 0; // LE low

    WriteSPI(byte);

    PORTEbits.RE1 = 1; // LE high
    PORTEbits.RE1 = 0; // LE low; to activate latch
    PORTEbits.RE0 = 0; // enable output
}

void main(void) {
    TRISDbits.RD1 = 0; //blinky

    TRISEbits.RE0 = 0; //oe tlc5916
    PORTEbits.RE0 = 1; //active low
    TRISEbits.RE1 = 0; //le tlc5916

    //WDTCONbits.ADSHR = 1; // enable alternate access to MEMCON
    //MEMCONbits.EBEIS = 1; // turn off external memory bus

    T0CON = 0b10001000; // enable the timer as 16 bit...
    // internal clock, no prescaler
    INTCONbits.TMR0IE = 1; // enable interrupts for timer 0
    ei(); // enable all interrupts

    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);

    sendByte(0xB7);
    Delay100TCYx(0x60);
    sendByte(0xB7);


    while(1)
    {
        LATEbits.LATE0 = portValue;

        /*sendByte(0xFF);
        sendByte(0x00);
        Delay100TCYx(0x60);*/
    }
    return;
}



