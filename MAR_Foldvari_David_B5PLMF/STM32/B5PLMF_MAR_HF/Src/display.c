/**
*****************************************************************************
** display.h
*****************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "display.h"
/* ----------------- Publikus fÄ‚Ä˝ggvÄ‚Â©nyek ----------------- */
volatile int sys_delay = 0;
void GLCD_Init(void)
{
	GLCD_MSP_Init();
	// Init GLCD functions
	HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);	// GLCD_E = 0
	HAL_GPIO_WritePin(GPIOD, RESET, GPIO_PIN_SET);	// GLCD_RESET = 1

	GLCD_Write(3,0,0x3F); 	//GLCD bekapcsolÄ‚Ë‡sa
	GLCD_Write(3,0,0xC0);	//GLCD Start Line
	GLCD_Clear();			//KijelzÄ‚Âµ tÄ‚Â¶rlÄ‚Â©se
}
void GLCD_Write(char cs_s,char d_i,char g_data)
{
	uint16_t data = 0x0000;
	switch(cs_s)
	{
	case 1:
		HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_SET);
		break;
	}
	switch(d_i)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_SET);
		break;
	}

	data = GPIOC->IDR;
	data &= 0xFF00;
	data |= g_data;
	GPIOC->ODR = data;

	Sys_DelayUs(1);
	HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
	Sys_DelayUs(2);
	HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
	Sys_DelayUs(4);
	HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_RESET);
}
void GLCD_Clear(void)
{
	char x,y;
	for(x=0;x<8;x++)
	{
		GLCD_Write(3,0,0x40);
		GLCD_Write(3,0,(0xB8|x));
		for(y=0;y<64;y++)
		{
			GLCD_Write(3,1,0x00);
		}
	}
}
void GLCD_WriteDisplay(const uint8_t *DataPtr){
	uint16_t data = 0x0000;
	for(uint8_t i=0;i<8;i++){
		for(uint8_t j=0;j<64;j++){
			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_RESET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= (0x40|j);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_RESET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= (0xB8|i);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_SET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= *(DataPtr+(i*128)+j);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS1, GPIO_PIN_RESET);
		}
	}
	for(uint8_t i=0;i<8;i++){
		for(uint8_t j=0;j<64;j++){
			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_RESET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= (0x40|j);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_RESET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= (0xB8|i);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, DI, GPIO_PIN_SET);
			data = GPIOC->IDR;
			data &= 0xFF00;
			data |= *(DataPtr+(i*128)+j+64);
			GPIOC->ODR = data;
			Sys_DelayUs(1);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);
			Sys_DelayUs(2);
			HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_RESET);
			Sys_DelayUs(4);
			HAL_GPIO_WritePin(GPIOA, CS2, GPIO_PIN_RESET);
		}
	}
}
void GLCD_MSP_Init(void){
	// Init ports
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef portInit;
	/* data: PC0-PC7
	 * RW: PA10
	 * CS1: PA7
	 * CS2: PA6
	 * E: PA5
	 * DI: PA9
	 * RESET: PD2
	 * #GLCDEN: PA8
	 * Backlight PWM: PA15
	 */
	portInit.Mode = GPIO_MODE_OUTPUT_PP;
	portInit.Pull = GPIO_NOPULL;
	portInit.Speed = GPIO_SPEED_FAST;
	// Port C
	portInit.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOC, &portInit);
	// Port D
	portInit.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &portInit);
	// Port A
	portInit.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7|GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOA, &portInit);
	// Minden alapÄ‚Ë‡llapotba
	HAL_GPIO_WritePin(GPIOA, RW, GPIO_PIN_RESET);	// GLCD_RW = 0
	HAL_GPIO_WritePin(GPIOA, E, GPIO_PIN_SET);		// GLCD_E = 1
	HAL_GPIO_WritePin(GPIOD, RESET, GPIO_PIN_RESET);	// GLCD_RESET = 0
	HAL_GPIO_WritePin(GPIOA, nGLCDEN, GPIO_PIN_RESET);	// #GLCDEN = 0
}
void Sys_DelayUs(int us){
	sys_delay = us;
	while(sys_delay);
}
void Sys_DelayMs(int ms){
	sys_delay = ms*1000;
	while(sys_delay);
}
