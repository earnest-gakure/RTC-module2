#include "delay.h"
#include "LCD_display.h"
#include "TM4C123.h"                    // Device header
/*
GPIO PINs used 
PA5,PA6,PA7
PA5 -> RS  change to pin 4 PA4
PA6 ->Rw
PA7 ->E
PB1 0->7
*/
#define RS 0x10
#define RW 0x40
#define E 0x80
void LCD_init(void)
{
	SYSCTL->RCGCGPIO = 0x02; /*clock for port B*/
	SYSCTL->RCGCGPIO |= 0x01;//enablock for GPIO port
	/*control pins enable */
	GPIOA->DIR |= 0xD0;//set GPIO pins as output pins
	GPIOA->DEN |= 0xD0;//enable the pins
	/*Data pins enable */
	GPIOB->DIR |= 0xFF; /*output pins */
	GPIOB->DEN |= 0xFF;
	//LCD_init
  LCD_CMD(0x038);	//function set command 0x38->8bit ,2lines display 5x7 font
	LCD_CMD(0x06);//Entry mode set command 0x06 ->increment automatically
  LCD_CMD(0x0F);	//display control 0x0F ->turn on display,cursor blinking
  LCD_CMD(0x01);	//display control 0x01->clear display
	 
}
void LCD_CMD(unsigned char command)
{
	GPIOA->DATA = 0x00;/*select command register pA4->RS=0*/
  GPIOB->DATA = command;/*write the command*/
	GPIOA->DATA = E;/*secure command->E= 1 PA7*/
	delay_ms(0);/*delay micro*/
	GPIOA->DATA = 0x00; /*disable E*/
	if (command < 4 )
		delay_ms(2);/*delay 2ms*/
	else 
		delay_ms(700);/*delay 37 Us*/
	
}

void LCD_DATA(unsigned char data )
{
   GPIOA->DATA = RS;/*select data register->RS= 1*/
   GPIOB->DATA = data ;/*write data*/
   GPIOA->DATA |= E;/*secure command->E= 1 PA7*/
	 delay_ms(0);/*delay 0 us*/
	 GPIOA->DATA = 0x00;/*disable E*/
	 delay_ms(0);/*delay 0 us*/
	
}

void string_data(char *ptr)
{
	while(*ptr)
	{
		LCD_DATA(*ptr);
		delay_ms(1);
		ptr++;
	}
}
