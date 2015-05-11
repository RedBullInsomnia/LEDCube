/*
 * File:   mainp18.c
 * Author: Hwk
 *
 * Created on 17 février 2015, 18:30
 */

#include <p18cxxx.h>
#include <delays.h>
#include <xc.h>
#include "functions.h"
#include "animations.h"

#define _XTAL_FREQ 30000000

void main(void) {

    /* Initialisation and start sequence */
    init();
    //initBlinky(3);

    resetCube();

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
//        snow();
//        for (uint8_t j = 1; j < 10; j++)
//            __delay_ms(10);

        //setCube();
        // Caroline text
        char text[] = "wingardium leviosaaaa";
        cube_string_to_front(text, 21);

        // Drivers
//        for(uint8_t j = 8; j > 0; j--)
//        {
//            // Levels
//            for(uint8_t i = 0; i < 8; i++)
//            {
//
//                for(uint8_t k = 0; k < 8; k++)
//                {
//                    cube[i][j-1] = cube[i][j-1]*2+1;
//                    for (uint8_t j = 1; j < 5; j++)
//                        __delay_ms(10);
//                }
//            }
//        }

        //        //selectLevel(1);
//        uint8_t tab[8];
//        tab[0] = 0x01;
//        sendLevel(tab,1);
//        sendLevel(tab,5);
//        for (uint8_t j = 1; j < 500; j++)
//            __delay_ms(20);
//
//        tab[0] = 0x03;
//        sendLevel(tab,1);
//        //for (uint8_t j = 1; j < 50; j++)
//        //    __delay_ms(20);
//        sendLevel(tab,5);
//        for (uint8_t j = 1; j < 500; j++)
//            __delay_ms(20);

        // First test, just one byte
//        sendByte(0x01, 1);
//        for (uint8_t j = 1; j < 50; j++)
//                    __delay_ms(20);
//        sendByte(0x03, 1);
//        for (uint8_t j = 1; j < 50; j++)
//                    __delay_ms(20);
//        sendByte(0x07, 1);
//        for (uint8_t j = 1; j < 50; j++)
//                    __delay_ms(20);
//        sendByte(0x0F, 1);
//        for (uint8_t j = 1; j < 50; j++)
//                    __delay_ms(20);
//
//        sendByte(0x00, 1);
//        for (uint8_t j = 1; j < 50; j++)
//                    __delay_ms(20);
        //sendByte(0x1F, 1);

      //  sendByte(0x01, 0);
//        for (uint8_t i = 0; i < 8; i++)
//        {
//            if(i==1 || i==2 || i==3 || i==5 ||i==6)
//                continue;
//
//            for (uint8_t k = 0; k < 8; k++)
//            {
//
//                cube[i][k] = 0x01;
//                sendFrame(cube);
//                for (uint8_t j = 0; j < 50; j++)
//                   __delay_ms(20);
//                //Delay100TCYx(120000);
//
//                cube[i][k] = 0x03;
//                sendFrame(cube);
//                for (uint8_t j = 0; j < 50; j++)
//                   __delay_ms(20);
//                //Delay100TCYx(120000);
//
//                cube[i][k] = 0x07;
//                sendFrame(cube);
//                for (uint8_t j = 0; j < 50; j++)
//                   __delay_ms(20);
//                //Delay100TCYx(120000);
//
//                cube[i][k] = 0x0F;
//                sendFrame(cube);
//                for (uint8_t j = 0; j < 50; j++)
//                   __delay_ms(20);
//                //Delay100TCYx(120000);
//
//            }
//        }
        //for (uint8_t j = 0; j < 250; j++)
                   //__delay_ms(20);
        //clearCube();
//        for (uint8_t j = 1; j < 100; j++)
//                    __delay_ms(20);
       // sendByte(0x55, 0);
       // sendByte(0xFF, 0);
       // sendByte(0x55, 0);
       // sendByte(0xFF, 1);
        
    }
}
