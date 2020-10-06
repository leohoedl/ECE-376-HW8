// Global Variables
const unsigned int B3 = 128;

// Subroutine Declarations
#include <pic18.h>
#include "lcd_portd.c"
void interrupt IntServe(void)
{
 if (TMR2IF) {
 if(PORTB) RC0 = !RC0;
 else RC0 = 0;
 TMR2IF = 0;
 }
 }

void Play(unsigned char NOTE)
{
 PR2 = NOTE;
 TMR2ON = 1;
 Wait_ms(450);
 TMR2ON = 0;
 Wait_ms(50);
 }
// Main Routine
void main(void)
{
 unsigned char i, j;
 TRISA = 0;
 TRISB = 0xFF;
 TRISC = 0;
 TRISD = 0;
 TRISE = 0;
 ADCON1 = 15;

// Timer2 Initialize
 TMR2ON = 1;
 TMR2IE = 1;
 PEIE = 1;
 T2CON = 0x7F; // A=16, C=16 0 1111 1 11
 PR2 = 49;
 GIE = 1;

 while(1) {
 	if (RB0) PR2 = B3;
 };

 }