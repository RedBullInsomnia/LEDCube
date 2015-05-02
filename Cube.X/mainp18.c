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

/* Level selectors */
#define LEV1 LATAbits.LATA2
#define LEV2 LATAbits.LATA3
#define LEV3 LATAbits.LATA4
#define LEV4 LATAbits.LATA5
#define LEV5 LATAbits.LATA1
#define LEV6 LATAbits.LATA0
#define LEV7 LATEbits.LATE1
#define LEV8 LATEbits.LATE0

/* OE, LE */
#define OE LATDbits.LATD2
#define LE LATDbits.LATD3

void main(void) {

    /* Initialisation and start sequence */
    init();
    startSequence(3);

    // First test, just one byte
    testMsg();

    // Test whole level
    //enableLevels();
    //disableLevels();
    //LEV3 = 1;

    while(1)
    {
        for (uint8_t i = 1; i < 8; i++)
        {
            selectLevel(i);
            if (8 == i)
                i = 1;
        }
    }
}
