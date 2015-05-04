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

#define _XTAL_FREQ 8000000

void main(void) {

    /* Initialisation and start sequence */
    init();
    initBlinky(3);

    selectLevel(1);
    // First test, just one byte
    sendByte(0x01, 1);
    for (uint8_t j = 1; j < 90; j++)
                __delay_ms(20);
    sendByte(0x03, 1);
    for (uint8_t j = 1; j < 90; j++)
                __delay_ms(20);
    sendByte(0x07, 1);
    for (uint8_t j = 1; j < 90; j++)
                __delay_ms(20);
    sendByte(0x0F, 1);
    for (uint8_t j = 1; j < 90; j++)
                __delay_ms(20);
    sendByte(0x1F, 1);
    for (uint8_t j = 1; j < 90; j++)
                __delay_ms(20);
    // Test whole level
    //enableLevels();
    //disableLevels();
    //LEV3 = 1;

    while(1)
    {
        for (int i = 1; i < 8; i++)
        {
            selectLevel(1);
            sendByte(0x01, 1);
            for (uint8_t j = 1; j < 90; j++)
                        __delay_ms(20);
            sendByte(0x03, 1);
            for (uint8_t j = 1; j < 90; j++)
                        __delay_ms(20);
            sendByte(0x07, 1);
            for (uint8_t j = 1; j < 90; j++)
                        __delay_ms(20);
            sendByte(0x0F, 1);
            for (uint8_t j = 1; j < 90; j++)
                        __delay_ms(20);
            sendByte(0x1F, 1);
            for (uint8_t j = 1; j < 90; j++)
                        __delay_ms(20);
            if(8 == i)
                i = 1;
        }
        /*
        for (uint8_t i = 1; i < 8; i++)
        {
            selectLevel(i);

            // Delay
            for (uint8_t j = 1; j < 9; j++)
                __delay_ms(20);

            // Loop
            if (8 == i)
            {
                sendByte(0xAA, 1);
                i = 1;
            }
        }*/
    }

    

    // Test marine :
    /*    init();
        Delay100TCYx (120*1);
        clearCube(); 

        while ( 1 ){    

            cube_block_wipe();

            Delay100TCYx (120*100);
            Delay100TCYx (120*100);

            cubes_4();
    */


}
