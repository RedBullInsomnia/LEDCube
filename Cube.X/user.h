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

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

//void InitApp(void);         /* I/O and Peripheral Initialization */