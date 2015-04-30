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
#include "functions.h"
#include "debug.h"

#define _XTAL_FREQ 8000000

#define LED1 LATEbits.LATE0

volatile uint8_t start = 1;

void main(void) {
   
    init();
    startSequence(3);

    sendTestMsg();
    //LATAbits.LATA2 = 1; //Level 1
    //for(int i = 0; i <500; i++)
    //    __delay_ms(50);
    LATEbits.LATE2 = 1;
    LATEbits.LATE1 = 1;
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 1;
    LATAbits.LATA4 = 1;
    LATAbits.LATA5 = 1;
    /*
    PORTEbits.RE0 = 1;
    PORTEbits.RE1 = 1;
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
    */
    while(1)
    {
        
    }
}
