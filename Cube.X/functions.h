/* 
 * File:   functions.h
 * Author: Hwk
 *
 * Created on 23 mars 2015, 10:47
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <stdint.h> // Defines uint8_t

#define _XTAL_FREQ 20000000

/* OE, LE */
#define OE LATDbits.LATD2
#define LE LATDbits.LATD3

/* Level selectors */
#define LEV1 LATAbits.LATA2
#define LEV2 LATAbits.LATA3
#define LEV3 LATAbits.LATA4
#define LEV4 LATAbits.LATA5
#define LEV5 LATAbits.LATA1
#define LEV6 LATAbits.LATA0
#define LEV7 LATEbits.LATE1
#define LEV8 LATEbits.LATE0

uint8_t cube[8][8];

void init();

void initSpi();

void clearCube();

void disableLevels();

void enableLevels();

void sendByte(uint8_t byte, uint8_t single);

void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level);

void sendLevel(uint8_t byte[8], uint8_t level);

void sendFrame(uint8_t byte[8][8]);

void selectLevel(uint8_t level);

#endif	/* FUNCTIONS_H */
