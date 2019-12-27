#include "DisplayFunctions.h"

extern Element Snake[],Food;
extern uint8_t DisplayData[7][14],Numbers[10],Length;

void ConvertToDisplayMtrx(void){
	uint8_t digit;
	uint8_t segment;
	for(uint8_t i=0; i<Length; i++){
		digit=Snake[i].Digit;
		segment=Snake[i].Segment;
		if(segment==6){
			DisplayData[digit][segment]=1;
			DisplayData[digit][10]=1;
		}
		DisplayData[digit][segment]=1;
	}
	digit=Food.Digit;
	segment=Food.Segment;
	if (segment == 6) {
		DisplayData[digit][segment] = 1;
		DisplayData[digit][10] = 1;
	}
	DisplayData[digit][segment] = 1;
}
void ClearDisplay(void){
	for (uint8_t i = 0; i < 7; i++) {
		for (uint8_t j=0; j < 14; j++) {
			DisplayData[i][j] = 0;
		}
	}
}
void SendToDisplay(void){
	uint32_t com, bit;
	uint8_t digit, segment;
	/* If an update is in progress we must block, or there might be tearing */
	LCD_SyncBusyDelay(0xFFFFFFFF);

	/* Freeze LCD to avoid partial updates */
	LCD_FreezeEnable(true);

	/* Turn all segments off */
	SegmentLCD_AlphaNumberOff();
	ClearDisplay();
	ConvertToDisplayMtrx();
	for(digit=0;digit<7;digit++){
		for(segment=0;segment<14;segment++){
			bit = EFM_Display.Text[digit].bit[segment];
			com = EFM_Display.Text[digit].com[segment];
			if(DisplayData[digit][segment]==1){
				LCD_SegmentSet(com, bit, true);
			}
			else LCD_SegmentSet(com, bit, false);
		}
	}
	LCD_FreezeEnable(false);
}
bool DisplayDots(bool state){
	uint8_t bit,com;
	bit = LCD_SYMBOL_DP2_SEG;
	com = LCD_SYMBOL_DP2_COM;
	LCD_SegmentSet(com, bit, state);
	bit = LCD_SYMBOL_DP3_SEG;
	com = LCD_SYMBOL_DP3_COM;
	LCD_SegmentSet(com, bit, state);
	bit = LCD_SYMBOL_DP3_SEG;
	com = LCD_SYMBOL_DP3_COM;
	LCD_SegmentSet(com, bit, state);
	bit = LCD_SYMBOL_DP4_SEG;
	com = LCD_SYMBOL_DP4_COM;
	LCD_SegmentSet(com, bit, state);
	bit = LCD_SYMBOL_DP5_SEG;
	com = LCD_SYMBOL_DP5_COM;
	LCD_SegmentSet(com, bit, state);
	bit = LCD_SYMBOL_DP6_SEG;
	com = LCD_SYMBOL_DP6_COM;
	LCD_SegmentSet(com, bit, state);
	return !state;
}
void NumberDisplay(uint16_t score){
	uint8_t bit;
	uint8_t com;
	uint8_t digits[4];
	if(score>9999){
		score=0;
	}
	digits[0]=score%10;//
	score/=10;
	digits[1]=score%10;
	score/=10;
	digits[2]=score%10;
	score/=10;
	digits[3]=score%10;
	for (uint8_t digit = 0; digit < 4; digit++) {
		for (uint8_t segment = 0, mask = 0x01; segment < 7;
				segment++, mask = mask << 1) {
			bit = EFM_Display.Number[digit].bit[segment];
			com = EFM_Display.Number[digit].com[segment];
			if (Numbers[digits[digit]] & mask) {
				LCD_SegmentSet(com, bit, true);
			} else
				LCD_SegmentSet(com, bit, false);
		}
	}
}
