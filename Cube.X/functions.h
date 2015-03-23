/* 
 * File:   functions.h
 * Author: Hwk
 *
 * Created on 23 mars 2015, 10:47
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

void init();

void initSpi();

void sendByte(unsigned char byte, unsigned char single);

void sendByteL(unsigned char byte, unsigned char single, unsigned int level);

void sendLevel(unsigned char byte[8], unsigned int level);

void sendFrame(unsigned char byte[8][8]);

void selectLevel(unsigned int level);


#endif	/* FUNCTIONS_H */

