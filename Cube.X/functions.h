/* 
 * File:   functions.h
 * Author: Hwk
 *
 * Created on 23 mars 2015, 10:47
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <stdint.h> // Permet d'utiliser le vecteur de 8 bits : uint8_t
uint8_t cube[8][8];

void init();

void initSpi();

void clearCube();

void sendByte(unsigned char byte, unsigned char single);

void sendByteL(unsigned char byte, unsigned char single, unsigned int level);

void sendLevel(unsigned char byte[8], unsigned int level);

void sendFrame(unsigned char byte[8][8]);

void selectLevel(unsigned int level);


#endif	/* FUNCTIONS_H */

