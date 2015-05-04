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
#include "user.h"

#define _XTAL_FREQ 8000000

void main(void) {

    /* Initialisation and start sequence */
    init();
    initBlinky(3);

    /*selectLevel(1);
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
                __delay_ms(20);*/
    //sendByte(0x1F, 1);
    //for (uint8_t j = 1; j < 90; j++)
      //          __delay_ms(20);
    // Test whole level
    //enableLevels();
    //disableLevels();
    //LEV3 = 1;

    // End of init
    

    clearCube();

//    selectLevel(6);
//    sendByte(0x01, 0);
//    sendByte(0x03, 0);
//    sendByte(0x07, 0);
//    sendByte(0x0F, 0);
//    sendByte(0x1F, 0);
//    sendByte(0x3F, 0);
//    sendByte(0x7F, 0);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);
//    sendByte(0x00, 1);
//    for (uint8_t j = 1; j < 150; j++)
//        __delay_ms(20);

    //sendByte(0x02, 1);
    
    while(1)
    {
      //  sendByte(0x01, 0);
        for (uint8_t i = 0; i < 8; i++)
        {
            for (uint8_t k = 0; k < 6; k++)
            {
                cube[i][k] = 0xFF;
                sendFrame(cube);
                //for (uint8_t j = 1; j < 20; j++)
                  //          __delay_ms(20);
            }
        }
       // sendByte(0x55, 0);
       // sendByte(0xFF, 0);
       // sendByte(0x55, 0);
       // sendByte(0xFF, 1);
        
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
