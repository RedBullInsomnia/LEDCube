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

/* Button */


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

/*
 * Blinks the debug LED on the board one time
 */
void blink();

/*
 * Blinks the debug Led on the board 'nb' times
 */
void blink_nb_times(uint8_t nb);

/*
 * Reset the whole cube (all bits to 0)
 */
void resetCube();

/*
 * Set the whole cube (all bits to 1)
 */
void setCube();

/*
 * Disable all the levels
 */
void disableLevels();

/*
 * Send 1 byte over the SPI, 'single' is used to configure the latch
 */
void sendByte(uint8_t byte, uint8_t single);

/*
 * Disable all the levels (by security) and select the desired level
 */
void selectLevel(uint8_t level);

/*
 * Send one byte over the SPI, intended for a particular level
 */
void sendByteAndLevel(uint8_t byte, uint8_t single, uint8_t level);

/*
 * Send the whole level to be display over the SPI
 */
void sendLevel(uint8_t byte[8], uint8_t level);

/*
 * Creates a delay of about ('multiplier' x 10ms)
 */
void delay_10ms(int multiplier);

/*
 * Routine for the high priority interrupt
 */
void interrupt high_priority Timer0_ISR();

/*
 * Routine for the low priority interrupt
 */
void interrupt low_priority pressedOnButton();
#endif	/* FUNCTIONS_H */