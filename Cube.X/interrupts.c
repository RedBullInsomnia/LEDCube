/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>     /* For uint8_t definition */
#include <stdbool.h>    /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
//void interrupt high_isr(void)
//{
//
//      /* This code stub shows general interrupt handling.  Note that these
//      conditional statements are not handled within 3 seperate if blocks.
//      Do not use a seperate if block for each interrupt flag to avoid run
//      tvoid interrupt Timer0_ISR()
//{
//    if (TMR0IE && TMR0IF) //are TMR0 interrupts enabled and is the TMR0 interrupt flag set?
//    {
//        resetTimer();
//        blinky = 1;
//
//    }
//}me errors. */
//
//#if 0
//
//      /* TODO Add High Priority interrupt routine code here. */
//
//      /* Determine which flag generated the interrupt */
//      if(<Interrupt Flag 1>)
//      {
//          <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
//      }
//      else if (<Interrupt Flag 2>)
//      {
//          <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
//      }
//      else
//      {
//          /* Unhandled interrupts */
//      }
//
//#endif
//}
//
///* Low-priority interrupt routine */
//void low_priority interrupt low_isr(void)
//{
//      /* This code stub shows general interrupt handling.  Note that these
//      conditional statements are not handled within 3 seperate if blocks.
//      Do not use a seperate if block for each interrupt flag to avoid run
//      time errors. */
//
//#if 0
//
//      /* TODO Add Low Priority interrupt routine code here. */
//
//      /* Determine which flag generated the interrupt */
//      if(<Interrupt Flag 1>)
//      {
//          <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
//      }
//      else if (<Interrupt Flag 2>)
//      {
//          <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
//      }
//      else
//      {
//          /* Unhandled interrupts */
//      }
//
//#endif
//}
