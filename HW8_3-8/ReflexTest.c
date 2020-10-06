#include <pic18.h>
#include <stdlib.h> 
#include <stdio.h> 

// Global Variables
unsigned int TIME;
unsigned int TEMP2,TEMP;
unsigned char RUN;
const unsigned char MSG0[21] = "ReflexTest.C        "; 
const unsigned char MSG1[21] = "RB1:start RB0:test  ";   

// Subroutines
#include "LCD_PortD.C"
void interrupt IntServe(void)
{
	 if (TMR2IF) {
 	 	RC0 = !RC0; // Allows you to measure the interrupt time
 	 	if (TEMP2==1) RUN = 1;
 	    if (TEMP2==2) RUN = 0;
 		if (RB2) TIME = 0;
 		if (RUN) TIME += 1;
 		TMR2IF = 0;
 	}
 }

void LCD_Out(unsigned int DATA, unsigned int N)
{
 unsigned char A[5], i;
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

   LCD_Init();                  // initialize the LCD
   LCD_Move(0,0);  for (int i=0; i<20; i++) LCD_Write(MSG0[i]);
   Wait_ms(5000);
   LCD_Inst(1);




 // initialize Timer2 for 1ms (10,000 clocks)
 PR2 = 249;
 T2CON = 0xFF;
 TMR2IE = 1;
 PEIE = 1;
 TMR2IP = 1;
 TIME = 0;
 RUN = 0;
 GIE = 1;

 while(1) {
 	RA1 = !RA1; // allows you to measure the main loop
	if(RB1){   //RB1 starts the game
		TEMP=1;
		TEMP2=0;
		Wait_ms((rand() % 7001) + 1);
		while(TEMP){
			PORTD = 0xFF;
			TEMP2 = 1;
			if(RB0) {
				PORTD = 0x00;
				LCD_Move(1, 0);
				LCD_Out(TIME,4);
				TEMP=0;
				TEMP2=0;
				TIME=0;
			}
		}
	}	
 	}
 }