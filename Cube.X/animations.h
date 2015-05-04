/* 
 * File:   animations.h
 * Author: 
 *
 * Created on 3 mai 2015
 */

#ifndef ANIMATIONS_H
#define	ANIMATIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <spi.h>
#include <delays.h> //Delay100TCYx (120); = 1ms

#define BLOCK_WIPE_DELAY 5
 void cube_block_wipe( void );
 void move_x_fwd( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );

 void cube_show_loop( uint8_t cycle );


 #define CUBES4_DELAY 5
void cubes_4( void );


// Translation :
void move_z_fwd ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );
void move_z_rev ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );
void move_y_fwd( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );
void move_y_rev( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );
void move_x_fwd( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );
void move_x_rev( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 );




#endif	/* ANIMATIONS_H */
