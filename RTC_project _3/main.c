#include "TM4C123.h"                    // Device header
#include "delay.h"
#include "LCD_display.h"
#include "SPI_init.h"
#include <stdio.h>
//macro to deffine clock Register addresses
#define WR_CREG  0x8E /*control register write*/
#define RD_CREG  0x8F /*control register read*/
#define WR_TCR   0x90 /*trickle charger write register*/
#define RD_TCR   0x91 /*trickle charge register read*/
#define WR_BURST 0xBE /*burst write */
#define RD_BURST 0xBF /*burst read */

#define WR_SEC    0x80 /*Seconds write */
#define RD_SEC    0x81 /*Seconds read */



/*pins to be used in ss0
CLK = pA2
DATA =
RESET = 

ssi0clk =pA2= clk
ssi0Fss =pA3= CE /RST
ssi0Tx  =pA5 = data line
*/





int main(void)
{
	uint8_t Read_sec =0;  //keep track of the seconds 
	char result[20];/*string buffer to store the read  */
	
	LCD_init();
	LCD_CMD(0x01); /*clear screen */
	LCD_CMD(0x80);/*set cursor to line 1 beginning */
	delay_ms(500);
	string_data("REAL TIME CLOCK");
	delay_ms(1000);
 
	
	SPI_Init(); //ninitialize SPI
	
	
	//LCD_CMD(0x01); /*clear screen */
	LCD_CMD(0xC0);/*set cursor to line 1 beginning */
	string_data(" Sec ");
	delay_ms(500);
/*send control bits , start by sending bit 7 of control register as 0 and also
	force the rest to 0this to enable write operation to the rest of the registers*/	
   SPI_Write(WR_CREG);//go to control register 
	 SPI_Write(0x00);//disable write protect
	// SPI_READ(RD_CREG);
	 //SPI_Write(WR_TCR); //go to trickle charge register
	 //SPI_Write(0xAB); //enable charger , 2 diodes , 8Kohm
	/*write to seconds register  
     set bit 7 to 0 to start the the clock 	*/
	SPI_Write(WR_SEC); //goto seconds control register
	SPI_Write(00); //set as 00 seconds
	Read_sec = SPI_READ(RD_SEC);
	
	//display on LCD
	sprintf(result ,"%d",Read_sec);
	LCD_CMD(0x01); /*clear screen */
	LCD_CMD(0x80);/*set cursor to line 1 beginning */
	delay_ms(500);
	string_data(result);
	
	/* we want to display the time on the LCD  thus we use the */
	 
	
	while(1)
	{
		
	}
	
}

