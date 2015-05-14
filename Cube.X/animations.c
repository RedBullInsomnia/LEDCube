#include "animations.h"
#include "functions.h"
#define _XTAL_FREQ 30000000
//
//void cube_block_wipe( void )
//{
//    ;
//}
//void move_x_fwd(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
//{
//    ;
//}
//void cube_show_loop(uint8_t cycle)
//{
//    ;
//}
//void cubes_4( void )
//{
//    ;
//}
//
//// Translation :
//void move_z_fwd ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}
//void move_z_rev ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}
//void move_y_fwd( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}
//void move_y_rev( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}
//void move_x_fwd( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}
//void move_x_rev( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
//{
//    ;
//}

/* Snow */
void snow()
{

    int rnd[4];

    for(uint8_t i = 0; i < 4 ; i++)
    {
        rnd[i] = rand();
        rnd[i] = rnd[i]%8;
    }

    // Go down
    for(uint8_t i = 1; i<8; i++)
        for(uint8_t j =0; j<8; j++)
            cube[i-1][j] = cube[i][j];

    // Generate new level
    for(uint8_t j =0; j<8; j++)
        cube[7][j] = 0;

    for(uint8_t i = 0; i < 4 ; i=1+2)
        cube[7][rnd[i]] = 1 << rnd[i+1];
}


/* front to back moving */
void cube_string_to_front(char *string, int size) {
    for (uint8_t i = 0; i < size; i++) {
        for (uint8_t i = 8; i > 0; i--) {
            resetCube();
            cube_char(*string, (1 << (i - 1)));
            for (uint8_t j = 1; j < 7; j++)
                __delay_ms(10);
        }
        string++;
    }
}

void cube_char(char ch, uint8_t z) {
    switch (ch) {
        case ' ':
            resetCube();
            break;
        case '0':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][2] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][3] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][4] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '1':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][3] |= z;
            cube[2][3] |= z;
            cube[3][3] |= z;
            cube[4][3] |= z;
            cube[5][2] |= z;
            cube[5][3] |= z;
            cube[6][3] |= z;
            break;
        case '2':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[0][5] |= z;
            cube[1][2] |= z;
            cube[2][3] |= z;
            cube[3][4] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '3':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][5] |= z;
            cube[3][4] |= z;
            cube[4][3] |= z;
            cube[5][4] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case '4':
            cube[0][4] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][2] |= z;
            cube[2][3] |= z;
            cube[2][4] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][4] |= z;
            cube[4][2] |= z;
            cube[4][4] |= z;
            cube[5][3] |= z;
            cube[5][4] |= z;
            cube[6][4] |= z;
            break;
        case '5':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][5] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][2] |= z;
            cube[4][3] |= z;
            cube[4][4] |= z;
            cube[5][1] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case '6':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[5][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '7':
            cube[0][2] |= z;
            cube[1][2] |= z;
            cube[2][2] |= z;
            cube[3][3] |= z;
            cube[4][4] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case '8':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '9':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[1][4] |= z;
            cube[2][5] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '!':
            cube[0][3] |= z;
            cube[3][3] |= z;
            cube[4][3] |= z;
            cube[5][2] |= z;
            cube[5][3] |= z;
            cube[5][4] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case ':':
            cube[1][2] |= z;
            cube[1][3] |= z;
            cube[2][2] |= z;
            cube[2][3] |= z;
            cube[4][2] |= z;
            cube[4][3] |= z;
            cube[5][2] |= z;
            cube[5][3] |= z;
            break;
        case '.':
            cube[1][2] |= z;
            cube[1][3] |= z;
            cube[2][2] |= z;
            cube[2][3] |= z;
            break;
        case '?':
            cube[0][3] |= z;
            cube[2][3] |= z;
            cube[3][4] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case '&':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][3] |= z;
            cube[2][5] |= z;
            cube[3][2] |= z;
            cube[4][1] |= z;
            cube[4][3] |= z;
            cube[5][1] |= z;
            cube[5][4] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            break;
        case 'a':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][2] |= z;
            cube[2][3] |= z;
            cube[2][4] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'b':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'c':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][5] |= z;
            cube[1][1] |= z;
            cube[2][1] |= z;
            cube[3][1] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[5][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'd':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][4] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            break;
        case 'e':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[2][1] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case 'f':
            cube[0][1] |= z;
            cube[1][1] |= z;
            cube[2][1] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case 'g':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'h':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'i':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][3] |= z;
            cube[2][3] |= z;
            cube[3][3] |= z;
            cube[4][3] |= z;
            cube[5][3] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'j':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][4] |= z;
            cube[3][4] |= z;
            cube[4][4] |= z;
            cube[5][4] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case 'k':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][3] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[4][1] |= z;
            cube[4][3] |= z;
            cube[5][1] |= z;
            cube[5][4] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'l':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[2][1] |= z;
            cube[3][1] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[6][1] |= z;
            break;
        case 'm':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][3] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][3] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][2] |= z;
            cube[5][4] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'n':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][4] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][3] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][2] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'o':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'p':
            cube[0][1] |= z;
            cube[1][1] |= z;
            cube[2][1] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'q':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][3] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 'r':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][3] |= z;
            cube[3][1] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            break;
        case 's':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][5] |= z;
            cube[2][5] |= z;
            cube[3][2] |= z;
            cube[3][3] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[5][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case 't':
            cube[0][3] |= z;
            cube[1][3] |= z;
            cube[2][3] |= z;
            cube[3][3] |= z;
            cube[4][3] |= z;
            cube[5][3] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        case 'u':
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'v':
            cube[0][3] |= z;
            cube[1][2] |= z;
            cube[1][4] |= z;
            cube[2][1] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'w':
            cube[0][2] |= z;
            cube[0][4] |= z;
            cube[1][1] |= z;
            cube[1][3] |= z;
            cube[1][5] |= z;
            cube[2][1] |= z;
            cube[2][3] |= z;
            cube[2][5] |= z;
            cube[3][1] |= z;
            cube[3][3] |= z;
            cube[3][5] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'x':
            cube[0][1] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[1][5] |= z;
            cube[2][2] |= z;
            cube[2][4] |= z;
            cube[3][3] |= z;
            cube[4][2] |= z;
            cube[4][4] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'y':
            cube[0][3] |= z;
            cube[1][3] |= z;
            cube[2][3] |= z;
            cube[3][2] |= z;
            cube[3][4] |= z;
            cube[4][1] |= z;
            cube[4][5] |= z;
            cube[5][1] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][5] |= z;
            break;
        case 'z':
            cube[0][1] |= z;
            cube[0][2] |= z;
            cube[0][3] |= z;
            cube[0][4] |= z;
            cube[0][5] |= z;
            cube[1][1] |= z;
            cube[2][2] |= z;
            cube[3][3] |= z;
            cube[4][4] |= z;
            cube[5][5] |= z;
            cube[6][1] |= z;
            cube[6][2] |= z;
            cube[6][3] |= z;
            cube[6][4] |= z;
            cube[6][5] |= z;
            break;
        default:
            break;
    }
}
