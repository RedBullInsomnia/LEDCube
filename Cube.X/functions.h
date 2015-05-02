/* 
 * File:   functions.h
 * Author: Hwk
 *
 * Created on 23 mars 2015, 10:47
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <stdint.h>

uint8_t cube[8][8];

void init();

void initSpi();

void blinky();

void initBlinky(uint8_t length);

void clearCube();

void disableLevels();

void enableLevels();

void sendByte(uint8_t byte, uint8_t single);

void selectLevel(uint8_t level);

void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level);

void sendLevel(uint8_t byte[8], uint8_t level);

void sendFrame(uint8_t byte[8][8]);

#endif	/* FUNCTIONS_H */
