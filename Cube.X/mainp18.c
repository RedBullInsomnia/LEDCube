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


    
    while(1)
    {

//        snow();
//        delay_10ms(10);
//
//        setCube();
//        
//        char text[] = "wingardium leviosaaaa";
//        cube_string_to_front(text, 21);

        cube_char('t', 4);
//        // Drivers
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


    }
}
