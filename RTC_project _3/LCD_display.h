#ifndef _LCD_DELAY__H
#define _LCD_DELAY__H
void LCD_init(void);
void LCD_CMD(unsigned char command);
void LCD_DATA(unsigned char data);
void string_data(char *ptr);
#endif