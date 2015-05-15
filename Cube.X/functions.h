/* 
 * File:   functions.h
 * Author: Hwk
 *
 * Created on 23 mars 2015, 10:47
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <stdint.h>

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* Level selectors */
#define LEV1 LATAbits.LATA2
#define LEV2 LATAbits.LATA3
#define LEV3 LATAbits.LATA4
#define LEV4 LATAbits.LATA5
#define LEV5 LATAbits.LATA1
#define LEV6 LATAbits.LATA0
#define LEV7 LATEbits.LATE1
#define LEV8 LATEbits.LATE0

/* OE, LE */
#define OE LATDbits.LATD2
#define LE LATDbits.LATD3

/* Blinky */
#define blinky LATDbits.LATD5


/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

uint8_t cube[8][8];
uint8_t currentLevel;

uint8_t buttonPressed = 0;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/

/*
 * Initializes the outputs : LEV1 -> LEV8, blinky and timer0
 */
void init();

/*
 * Inits the SPI ports
 */
void initSpi();

/*
 * Resets the timer after an interrupt has
 */
void resetTimer();

void blink();

void initBlinky(uint8_t length);

void resetCube();

void setCube();

void disableLevels();

void enableLevels();

void sendByte(uint8_t byte, uint8_t single);

void selectLevel(uint8_t level);

void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level);

void sendLevel(uint8_t byte[8], uint8_t level);

void sendFrame(uint8_t byte[8][8]);

void delay_10ms(int multiplier);

void interrupt Timer0_ISR();

void interrupt pressedOnButton();
#endif	/* FUNCTIONS_H */