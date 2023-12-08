#include "TM4C123.h"                    // Device header
#include "SPI_init.h"
#include "delay.h"
#include <stdint.h>
/*function that initialize spi protocol */
/*pins to be used in ss0

ssi0clk =pA2= clk
ssi0Fss =pA3= CE /RST
ssi0Tx  =pA5 = data line
*/
#define CLK 2
#define RST 3
#define TX 5
void SPI_Init(void)
{
	SYSCTL->RCGCSSI |= 0x01; /*clock for SSI0 */
	SYSCTL->RCGCGPIO |= 0x01; /*clock for port A */
	
	GPIOA->AFSEL |= 0x2C ;    /*pA 2,3,5 Alternate function */
	GPIOA->PCTL |= 0x00202200 ; /* assign each pin to SSI signals*/
	GPIOA->DEN |= 0x2C ;        /*digital enable pA2,3,5*/
	GPIOA->DATA |= 0x08 ;      /*keep CE/RST pin idle HIGH */
	//SSI configuration
	SSI0->CR1 &= ~0x02 ;        /* disable SSI */
  SSI0->CR1 |= 0x00 ;   /*select SSI as Master*/	
	SSI0->CC  = 0x00 ;    /*system clock ssi clock source select */
	SSI0->CPSR = 4 ;      /*clock prescaler divisor frequency = 16m/4*/
	SSI0->CR0 |= 0 ;  //SCR
	SSI0->CR0 |= 0x27 ;    /*serial clock rate , clock phase/polarity , protocol mode ,the data size*/
                        /*MICROWIRE Frame Format */
	SSI0->CR1 = 0x02 ; /*enable SSI */
	
}
void SPI_Write (uint8_t data )
{
   uint8_t buffer= MSB_to_LSB(data);//buffer to store the data parameter after conversion from MSB to LSB
    CE_LOW();//	GPIOA->DATA &= ~RST; /*make CE LOW */
 	  while((SSI0->SR & 0x02)== 0	);/*wait untill Transmission FIFO is not full*/
	  SSI0->DR= buffer;/*transmit data over SSI0 TX line */
  	while(SSI0->SR & 0x10);//== 0);/*wait untill SSI is idle  */
	  LED_BLINK(); //blink led after successfull transfer
    CE_HIGH();//	GPIOA->DATA = RST;  /*make CE pin HIGH when idle */
	  
//	
}
void CE_HIGH (void )
{
	GPIOA->DATA |= RST;
	
}

void CE_LOW(void )
{
	
	GPIOA->DATA &= ~RST;
}

uint8_t SPI_READ (uint8_t data)
{
	uint8_t Data = 0x00;
	//CE_LOW(); /*start reading from slave */
	SPI_Write(data);
	while((SSI0->SR & 0x08) == 1 );/* wait untill receive FIFO is not full */
	Data = SSI0->DR ; // read the received data from the data line
	//LED_BLINK();//blink LED after succesfull read from the slave 6
	while(SSI0->SR & 0x10);/* wait untill LSB is read */
	CE_HIGH();/*CE high after last bit is read */
	Data =  MSB_to_LSB(Data);
	return Data; //return the received data 
}


/*function to convert from MSB To LSB and vice versa*/
int MSB_to_LSB(int data)
{
  int a= data;
  a=((a & 0xF0)>>4) |((a &0x0F)<<4);
  a=((a & 0xCC)>>2) |((a &0x33)<<2);
  a=((a & 0xAA)>>1) |((a &0x55)<<1);
  return a;


}
void LED_BLINK()
{
  SYSCTL->RCGCGPIO |= 0x20;
  GPIOF->DIR |= 0x04;
  GPIOF->DEN |= 0x04;
  GPIOF->DATA |= 0x04;
  delay_ms(50);
  GPIOF->DATA &= ~0x04;	
	
}

