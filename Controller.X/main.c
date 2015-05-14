/* 
 * File:   main.c
 * Author: Greg
 *
 * Created on 23 février 2015, 13:06
 */
#include <stdio.h>
#include <stdlib.h>

#include <p18F2620.h>        // Include Header for PIC18F2620
#include <htc.h>
#include "pwm.h"
#define USE_OR_MASKS


/* ******COMPILER DIRECTIVES FOR CHIP CONFIGURATION BITS *** */
/*
#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
#pragma config BORV = 3
#pragma config WDT = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
*/

/* COMPILER DIRECTIVES FOR CHIP CONFIGURATION BITS*/

#define _XTAL_FREQ 20000000
#pragma config OSC      = HS   // Internal oscillator block, digital I/O on RA6 and RA7
//#pragma config OSC      = INTIO67   // Internal oscillator block, digital I/O on RA6 and RA7
#pragma config MCLRE    = ON      // Disable the reset function --------------------------------------------------------------------
#pragma config FCMEN    = OFF       // Fail-Safe Clock Monitor Enable bit
#pragma config IESO     = OFF       // Internal/External Oscillator Switchover bit
#pragma config PWRT     = ON        // Power-up Timer Enable bit
#pragma config BOREN    = OFF       // Brown-out Reset Enable bits
#pragma config BORV     = 3         // Brown-out Voltage bits
#pragma config LPT1OSC  = OFF       // Timer1 configured for higher power operation
#pragma config PBADEN   = OFF       // PORTB <4:0> pins are configured as digital I/O on Reset
#pragma config CCP2MX   = PORTC     // CCP2 input/output is multiplexed with RC1
#pragma config STVREN   = ON        // Stack Full/Underflow Reset Enable bit
#pragma config LVP      = OFF       // Single-Supply ICSP Enable bit         <---- pour avoir RB5 en digital IO
#pragma config XINST    = OFF       // Extended Instruction Set Enable bit
#pragma config DEBUG    = OFF       // Background Debugger Enable bit
#pragma config CP0      = OFF       // Code Protection bit Block 0
#pragma config CP1      = OFF       // Code Protection bit Block 1
#pragma config CP2      = OFF       // Code Protection bit Block 2
#pragma config CP3      = OFF       // Code Protection bit Block 3
#pragma config CPB      = OFF       // Boot Block Code Protection bit
#pragma config CPD      = OFF       // Data EEPROM Code Protection bit
#pragma config WRT0     = OFF       // Write Protection bit Block 0
#pragma config WRT1     = OFF       // Write Protection bit Block 1
#pragma config WRT2     = OFF       // Write Protection bit Block 2
#pragma config WRT3     = OFF       // Write Protection bit Block 3
#pragma config WRTB     = OFF       // Boot Block Write Protection bit
#pragma config WRTC     = OFF       // Configuration Register Write Protection bit
#pragma config WRTD     = OFF       // Data EEPROM Write Protection bit
#pragma config EBTR0    = OFF       // Table Read Protection bit Block 0
#pragma config EBTR1    = OFF       // Table Read Protection bit Block 1
#pragma config EBTR2    = OFF       // Table Read Protection bit Block 2
#pragma config EBTR3    = OFF       // Table Read Protection bit Block 3
#pragma config EBTRB    = OFF       // Boot Block Table Read Protection
#pragma config WDT      = OFF       // Watchdog Timer Enable bit
#pragma config WDTPS    = 1


/* Functions declaration */
void setDuty(float duty);
void reset_controller(void);
void interrupt Timer0_ISR(void);

void delayzz();
void setLight(int number);
void clearLight(int number);


/* ************* Global variables because in interrupt ************* */
unsigned int cnt_update_duty =0; // Mettre cette variable comme variable globale car interrupt ne prend pas d'argument
// Variables for PI
float measured_voltage = 0;
float previous_output = 0;
float previous_error = 0;
float error = 0;
float integral = 0;
float reference = 0;     // Referenve voltage (after sensor gain)
//float dt = 0.001008;         // Sampling period: 20ms
float dt = 0.000756;
float output;
//float kp = 0.1819,ki = 10;//10.3902;
float kp = 0.05,ki = 10;//10.3902; // OK après tuning 
float kiDtDemi = 0;
float Ts = 0.000332;

/* ******************************* MAIN ************************************* */
void main(void)
{
    reference = 3.72 * 1024.0 /5.0;
    kiDtDemi = ki*dt*0.5;

    // PORT C Setting: Set pin 4 in port C to Output
    TRISC = 0b11101111 ;

    // Step 1: Configure the A/D module
    ADCON1 = 0b00001110; // Pour Vref+ = VDD et Vref_ = VSS et pour configurer uniquement AN0 en analogique. Les autres restent I/O digital.
    ADCON0 = 0b00000000; // Pour activer le channel 0
    ADCON2 = 0b10010101; // Acquisition time = 4Tad; Conversion clock = Fosc / 16
    ADCON0 = 0b00000001; // Conversion module is enabled

    // Config for PWM
    // 1st step - configure the frequency 
    PR2 = 166;  // PR2 = 166 for PWM frequency 30kHz

    // 2nd step - Configure duty cycle
    CCPR2L = 0b01010011;             // High bits
    CCP2CON = CCP2CON & 0b11011111; // Low bit
    CCP2CON = CCP2CON | 0b00010000; // Low low bit

    // 3rd step - Setting the output
    TRISC = TRISC & 0b11111101;

    // 4th step - Activate timer2 and define prescaler
    TMR2ON = 1;     // Acvitvate Timer2
    T2CKPS1 = 0;    // Prescaler value - High bit
    T2CKPS0 = 0;    // Prescaler value - Low bit

    // 5th step - CCPM module for PWM operation
    CCP2M3 = 1;
    CCP2M2 = 1;
    CCP2M1 = 0;
    CCP2M0 = 0;

    // Start the cube by progresivly increasing the duty cyle
    //reset_controller();

    // configure the timer 0
    T0CON = 0b10011000; // activate the timer0 with the right parameters
    TMR0L = 0x4E;
    TMR0H = 0xEC;
    TMR0IE = 1; //enable TMR0 overflow interrupts (voir INTCON PDF page 113)
    GIE = 1; //enable Global interrupts
    TMR0IF = 0; // clear the interrupt flag at the begining


    while(1)
    {
        /*
        // MCLR == 1 if we put the MCLR pin to GND
        // !!! Not forget to put a pull up resistor with pin MCLR !!!
        if(MCLR == 0b0){
            reset_controller();
        }
        */
        
        // Step 4: Start conversion
        ADCON0 = 0b00000011; // Go

        // Step 5: Wait for A/D conversion to complete
        while(ADCON0 & 0b00000010);

        // Step 6: Read A/D result registers
        measured_voltage = (float)ADRESL + (float)ADRESH * 256.0;
        //measured_voltage = measured_voltage * 5.0 / 1024.0;
    }
}


void setDuty(float duty)
{
    //float freq_duty;
    int cpp;

    if(duty<16.6)
    {
        duty = 16.6;
        //clearLight(1);
    }
    else if(duty>116)
    {
        duty = 116;
        //clearLight(1);
    }
    //else
        //setLight(1);

    //duty = 0.54; // <--------------------------------------------------------------------------------------- HERE !!!!

    //freq_duty = (1/duty) * 30000;
    //cpp = (int)//(_XTAL_FREQ / freq_duty);
    
    cpp = (int)duty;
    CCPR2L = cpp;

    /*
    CCPR2L = cpp >> 2;                  // High bits


    if (cpp & 1) // Faut-il mettre 0b1 ou pas car si on met 1 cmt il sait que c'est un seul bit ?????????????????????????????????????
        CCP2CON = CCP2CON & 0b11101111; // Low low bit
    else
        CCP2CON = CCP2CON | 0b00010000; // Low low bit

    if ((cpp>>1) & 1) .// Idem ?????????????????????????????????????????????????????????????????????????????????????????????????
        CCP2CON = CCP2CON | 0b00100000; // Low bit
    else
        CCP2CON = CCP2CON & 0b11011111; // Low bit
        */
    
}

/** Function who resets the controller*/
void reset_controller(){
    // Start the cube by progresivly increasing the duty cyle
    setDuty(20);
    delayzz();
    setDuty(50);
    delayzz();
    setDuty(80);
    delayzz();

    // Switch on the diode during 3 seconds to see that the PWM is at 54%
    setLight(1);
    delayzz();
    delayzz();
    delayzz();
    clearLight(1);
}

void interrupt Timer0_ISR() 
{
    if (TMR0IE && TMR0IF) //are TMR0 interrupts enabled and is the TMR0 interrupt flag set?
    {
        setLight(1);
        //TMR0L = 0x4E;
        //TMR0H = 0xEC;
        TMR0L = 0x3B;
        TMR0H = 0xF1;
        TMR0IF=0; //TMR0 interrupt flag must be cleared in software to allow subsequent interrupts increment the counter variable by 1

   
    //++cnt_update_duty;
    //if (cnt_update_duty == 7) // On a fait 7 interruption (commence à 0)
    //{
        
        //setLight(1);
        //PORTCbits.RC4 =~ PORTCbits.RC4;

        //On prend la dernière valeur de l'AD de la v_out et on calcule le nouveau D
        // Controller PI A changer ici
        // Regarder le bit GO/DONE
        error = reference - measured_voltage;
        output = kp*(error - previous_error) + kiDtDemi*(error + previous_error) + previous_output;
        if(output > 116){ // Output est le duty or duty max est PR2 = 166 alors ne sert à rien d'aller trop loin de cette valeur
            output = 116;
            //setLight(1);
        }
        else if(output <= 16.6){ // Idem output est duty or duty min est PR2 alors ne sert à rien d'aller trop en dessous
            output = 16.6;
            //setLight(1);
        }
        else{
            //clearLight(1);
        }
        

        previous_error = error;
        previous_output = output;
        
        
        //integral = integral + error*dt;
        //if(integral >= 757760 || integral <= -757760) //  = 3.7*1000*1024/5
        //{
            //integral = integral - error*dt;
            //setLight(1);
        //}
        //else
            //clearLight(1);
        
        //output = kp*(error) + ki*integral;
        

        setDuty(output);///5.0);
        
        // cnt_update_duty = 0;
        
        clearLight(1);
        //PORTCbits.RC4 =~ PORTCbits.RC4;
    //}

    }

}


// ---------------------------------------------------------------------------

void delayzz()
{
    for(int i=0; i<100 ; ++i)
        __delay_ms(10);
}

void setLight(int number)
{
    if(number==1)
        PORTCbits.RC4 = 1;   // RC-4 to High
}

void clearLight(int number)
{
    if(number==1)
        PORTCbits.RC4 = 0;   // RC-4 to Low
}