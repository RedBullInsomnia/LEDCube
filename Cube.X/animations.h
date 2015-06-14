/* 
 * File:   animations.h
 * Author: 
 *
 * Created on 3 may 2015
 */

#ifndef ANIMATIONS_H
#define	ANIMATIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

void go_front(uint8_t n);
void go_back(uint8_t n);
void go_right(uint8_t n);
void go_left(uint8_t n);
void go_up(uint8_t n);
void go_down(uint8_t n);

void moving_cube(uint8_t n);
void flash();

void snow();
void edges();
void rotate_90();
void cube_string_to_front(char *string, int size);
void cube_char(char ch, uint8_t z );


#endif	/* ANIMATIONS_H */
