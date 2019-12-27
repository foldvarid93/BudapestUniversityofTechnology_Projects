/**
*****************************************************************************
** display.h
*****************************************************************************
*/
#pragma once
#ifndef _DISPLAY_H__
#define _DISPLAY_H__

#define E 			GPIO_PIN_5
#define CS2 		GPIO_PIN_6
#define CS1 		GPIO_PIN_7
#define nGLCDEN 	GPIO_PIN_8
#define DI 			GPIO_PIN_9
#define RW 			GPIO_PIN_10
#define LEDPWM 		GPIO_PIN_15
#define RESET 		GPIO_PIN_2

void GLCD_Init(void);
void GLCD_Write(char cs_s,char d_i,char g_data);
void GLCD_Clear(void);
void GLCD_WriteDisplay(const uint8_t *DataPtr);
void Sys_DelayUs(int us);
void Sys_DelayMs(int ms);
void GLCD_MSP_Init(void);
#endif
