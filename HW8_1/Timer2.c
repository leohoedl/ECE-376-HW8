#include <pic18.h>

// Global Variables
unsigned int TIME;
unsigned char RUN;

// Subroutines
#include "LCD_PortD.C"
void interrupt IntServe(void)
{
	 if (TMR2IF) {
 	 	RC0 = !RC0; // Allows you to measure the interrupt time
 	 	if (RB0) RUN = 1;
 	    if (RB1) RUN = 0;
 		if (RB2) TIME = 0;
 		if (RUN) TIME += 1;
 		TMR2IF = 0;
 	}
 }

// LCD output time
void LCD_Out(unsigned int DATA, unsigned int N)
{
	 unsigned char A[6], i;
 	for (i=0; i<5; i++) {
 		A[i] = DATA % 10;
 		DATA = DATA / 10;
 	}
 	for (i=5; i>0; i--) {
 		if (i == N) LCD_Write('.');
 		LCD_Write(A[i-1] + 48);
 		}
 }

// main routine
void main(void)
{
 TRISA = 0;
 TRISB = 0xFF;
 TRISC = 0;
 TRISD = 0;
 ADCON1 = 15;
LCD_Init();

 // initialize Timer2 for 1ms (10,000 clocks)
 PR2 = 249;
 T2CON = 0x4D;
 TMR2IE = 1;
 PEIE = 1;
 TMR2IP = 1;
 TIME = 0;
 RUN = 0;
 GIE = 1;

 while(1) {
 	RA1 = !RA1; // allows you to measure the main loop
 	LCD_Move(1,0);
 	LCD_Out(TIME, 3);
 	}
 }