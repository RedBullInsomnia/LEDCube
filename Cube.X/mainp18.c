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

    
    //cube_char('g',4);
    

    while(1)
    {
        if(buttonPressed == 0){
            blinky = 0;
            edges();
        }
        else{
            //blinky = 1;
            setCube();
            delay_10ms(500);
            buttonPressed = 0;
        }
        
        //snow();
        
//        delay_10ms(10);
//        char text[] = "wingardium leviosaaaa";
//        cube_string_to_front(text, 21);

//        // Levels
//        for(uint8_t l = 0; l < 8; l++)
//        {
//            // drivers
//            for(uint8_t d = 0; d < 4; d++)
//            {
//                cube[l][d] = 0xFF;
//            }
//        }

    }
}
