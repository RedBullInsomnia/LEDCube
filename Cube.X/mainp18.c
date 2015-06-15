/*
 * File:   mainp18.c
 * Author: Hwk
 *
 * Created on 17 février 2015, 18:30
 */

#include <xc.h>
#include "functions.h"
#include "animations.h"

#define _XTAL_FREQ 30000000

void main(void) {

    /* Initialisation and start sequence */
    init();

    uint8_t rand_anim = 0;

    buttonPressed = 0;
    while(buttonPressed == 0);
    buttonPressed = 0;
    countdown();

    while(1)
    {
        if (1 == buttonPressed)
        {
            buttonPressed = 0;
            rand_anim = (rand_anim + 1);
            if (rand_anim > 5)
                rand_anim = 0;
        }

        switch(rand_anim) {
            case 0: snow();
                    delay_10ms(4);
                    break;
            case 1: resetCube();
                    edges();
                    delay_10ms(2);
                    break;
            case 2: resetCube();
                    cube_string_to_front("abcdefghijklmnopqrstuvwxyz", 26);
                    delay_10ms(2);
                    break;
            case 3: resetCube();
                    cube_char('c', 255);
                    rotate_90();
                    delay_10ms(2);
                    rotate_90();
                    delay_10ms(2);
                    rotate_90();
                    delay_10ms(2);
                    rotate_90();
                    if(buttonPressed == 1)
                        break;
                    else
                        delay_10ms(50);
                    break;
            case 4: setCube();
                    break;
            case 5: moving_cube(5);
                    break;

        }
    }
}