#ifndef __USART1_H
#define __USART1_H 

#include "stm32f10x.h"
#include <stdio.h>

//void NVIC_Configuration(void);
void USART1GPIO_Init(void);
void USART1_Config(void);
void USART1_Init(void);
int fputc(int ch,FILE *f);
int fgetc(FILE *f);
uint8_t USART1_send_char(uint8_t ch);
void USART1_send_data(uint8_t * buf , u16 len);
#endif
