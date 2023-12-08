#include "delay.h"
 #include "TM4C123.h"                    // Device header

void delay_ms(int time)
{
	int i;
	SYSCTL->RCGCTIMER |= 0x01;/*clock for timer 0*/
	TIMER0->CTL &= ~0x01;  /*diable timer */
	TIMER0->CFG = 0x04;  /*i6-bit configurration mode*/
  TIMER0->TAMR |= 0x02 ;/*configure TA as periodic*/
	TIMER0->TAILR |= 16000 -1;/*set load . delay = load *(1/16M) = 16000* (1/16M) = 0.001 sec*/
	TIMER0->ICR |= 0x01;/*clear prior interrupts*/
	TIMER0->CTL |= 0x01; /*enable timer*/
	
	/*polling for loop*/
	
	for (i = 0; i < time ; i++)
	{
		while((TIMER0->RIS & 0x01 ) == 0 ){}  /*wait for time out*/
			TIMER0->ICR |= 0x01; /*clear interrupt */
		}
	}
	