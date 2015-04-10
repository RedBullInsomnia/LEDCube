// Frequence crystal
#define _XTAL_FREQ 20000000

#include <xc.h>
#include <p18f4550.h>
#include <delays.h>
#include <stdlib.h>
#include <stdint.h> // Permet d'utiliser le vecteur de 8 bits : uint8_t
#include "functions.h"

void cube_string_belt(char *string);
void set_char_to_belt(char character, char *belt);
void move_belt_left(char *belt);
#define SHOW_BELT_DELAY 5 /* seems to be the best */
void show_belt(char *belt);
void cube_string_to_front(char *string);
void cube_fixed_string( void );


int main(void)
{
	init(); // Fonction init => Hub (function.c) 
	_delay_ms(100);
	_delay_ms(100);
	clearCube(); /* never forget this */

	while ( 1 ){	

		// Letters show
		cube_string_belt("  fornax led cube demo");
		cube_explosion();
 }
 
 
 
 
 /****************/
/* Letters show */
/****************/

/* moving chars on a belt
 * a cute function to display larger strings.
 * we need to define an own layer for the chars
 * which is then transformed to the cube array 
 */

void cube_string_belt( char *string )
{
	/* 2D 
	 * bits are Y, 0 is bottom, 7 is top
	 * 0 is the right end where the chars come in
	 * 20 visible lines, 5 are added to the "beginning"
	 * outside the cube so the chars can move in
	 */
	char cube_belt[25];
	for (uint8_t i = 0; i < 25; i++) { cube_belt[i] = 0; }

	string++;
	string++;
	while(*string){
		set_char_to_belt(*string, cube_belt);
		for (uint8_t i = 0; i < 6; i++){
			show_belt(cube_belt);
			move_belt_left(cube_belt);
		}
		string++;
	}
	/* move the rest out */
	for (uint8_t i = 0; i < 18; i++){
		show_belt(cube_belt);
		move_belt_left(cube_belt);
	}
}

void move_belt_left( char *belt )
{
	for (uint8_t i = 25; i > 1; i--){
		belt[i-1] = belt[i-2];
	}
	belt[0] = 0;
}
/*
 * set a char to the cube array, then transform this char to
 * the first 5 elements of the belt array 
 */
void set_char_to_belt( char character, char *belt )
{	
	cube_clear();
	cli();
	PORTC = 0x00;
	cube_char(character, 1);
	for (uint8_t layer = 0; layer < 8; layer++) {
		for (uint8_t i = 1; i < 6; i++){
			if (cube[layer][i] & 0x01) 
				belt[5-i] |= (1 << layer);
		}
	}
	cube_clear();
	sei();
}

/* this function passes the given array to the cube array */
void show_belt( char *belt )
{
	cube_clear();
	/* right side */
	for (uint8_t i = 5; i <= 11; i++){
		for (uint8_t j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][7] |= (1 << (12-i));
		}
	}
	/* front side */
	for (uint8_t i = 12; i <= 17; i++){
		for (uint8_t j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][18-i] |= (1 << 0);
		}
	}
	/* left side */
	for (uint8_t i = 18; i <= 24; i++){
		for (uint8_t j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][0] |= (1 << (i-17));
		}
	}
	cube_show_loop(SHOW_BELT_DELAY);
}

/* 2 fixed chars rotating */
void cube_fixed_string( void )
{
	cube_clear();
	cube_clear();
	cube_char('3', 2);
	rotate_90_deg();
	rotate_90_deg();
	cube_char('d', 2);
	rotate_90_deg();

	rotate_90_auto(8);
}


/* back to front moving */
void cube_string_to_front( char *string )
{
	while(*string) {	
		for (uint8_t i = 8; i > 0; i--){
			cube_clear();
			cube_char(*string, (1 << (i-1)));
			cube_show_loop(3);
		}
		string++;
	}

}

/* automated text display, takes a string and adds
 * some effects. Usable for short strings.
 */
void cube_string( char *string )
{
	while(*string){
		cube_clear();
		cli();
		PORTC = 0x00;
		cube_char(*string, 16);
		string++;
		rotate_90_deg();
		rotate_90_deg();
		rotate_90_deg();
		move_x_rev(1,0,6,7);
		move_x_rev(1,0,6,7);
		move_x_rev(1,0,6,7);
		sei();
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		rotate_90_auto(1);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		cube_flash(5);
		cube_explosion();
	}
	cube_explosion();
	cube_explosion();
}

void cube_outline( void )
{
	cube_clear();
	cube_show_loop(OUTLINE_DELAY);
	for (uint8_t i = 0; i < 8; i++) {
		cube[0][0] |= (1 << i);
		cube[i][0] |= 1;
		cube[0][i] |= 1;
		cube_show_loop(OUTLINE_DELAY);
	}
	for (uint8_t i = 1; i < 8; i++) {
		cube[7][0] |= (1 << i);
		cube[7][i] |= 1;
		cube[i][0] |= 128;
		cube[0][i] |= 128;
		cube[0][7] |= (1 << i);
		cube[i][7] |= 1;
		cube_show_loop(OUTLINE_DELAY);
	}
	for (uint8_t i = 1; i < 8; i++) {
		cube[7][i] |= 128;
		cube[7][7] |= (1 << i);
		cube[i][7] |= 128;
		cube_show_loop(OUTLINE_DELAY);
	}
	cube_show_loop(20);
	/* shrink */
	cube_clear();
	cube[1][1] = 0b01111110;
	cube[1][6] = 0b01111110;
	cube[6][1] = 0b01111110;
	cube[6][6] = 0b01111110;
	for (uint8_t i=2; i< 6; i++) {
		cube[1][i] = 0b01000010;
		cube[6][i] = 0b01000010;
		cube[i][1] = 0b01000010;
		cube[i][6] = 0b01000010;
	}
	cube_show_loop(30);
	rotate_90_auto( 8 );
 
}
 
 
 
 
