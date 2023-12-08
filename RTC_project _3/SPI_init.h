#ifndef _SPI__INIT_H
#define _SPI__INIT_H
#include <stdint.h>
/*function to initialize spi protocol */
void SPI_Init(void);
/*function to trasmit data from master to slave 
the data is 8 bit */
void SPI_Write (__UINT8_TYPE__ data );
uint8_t SPI_READ (uint8_t data);
int MSB_to_LSB(int data);
void CE_HIGH (void); /* RST pin on */
void CE_LOW (void); /*RST pin off */
void LED_BLINK(); /* function to blink blue LEd this function is for deburgging purpose  */
#endif
