/* 
 * File:   debug.h
 * Author: Hwk
 *
 * Created on 28 avril 2015, 18:10
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <stdint.h> // Defines uint8_t

void startSequence(uint8_t length);

void blink();

void testLevelControl();

void sendTestMsg();

#endif	/* DEBUG_H */

