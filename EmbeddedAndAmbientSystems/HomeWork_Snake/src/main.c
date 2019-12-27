/**************************************************************************//**
 * B5PLMF Földvári Dávid
 * E8RNVF Sokoray Tamás
 * 2017.11.20. Beágyazott és ambiens rendszerek házi feladat
 * Giant Gecko STK3700
 * Snake játék.
 * Rövid leírás: PB0 nyomógombra balra, PB1-re jobbra fordul. A kígyó az alfanumerikus kijelzõ szegmensein mozog.
 * A felsõ 4 digites 7 szegmenses kijelzõ részen az aktuális pontszám.
 * A játék végét a kijelzõ alján villogó pontok jelzik.
 * A játék újraindítható ha vége lett és PB0&PB1 egyszerre le van nyomva.
 * Az ételhez random számot egy ADC bemenet zajából nyerünk
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "InitDevice.h"
#include "GameFunctions.h"
#include "DisplayFunctions.h"
/**************************************************************************//**
 * @brief Változók és konstansok
 *****************************************************************************/
uint8_t DisplayData [7][14],Game,Length,Dir,LastDir,NewDir,TimeTick=0;
uint16_t TimerVar=0,Button0Mask=0x200,Button1Mask=0x400;
bool Button0LastState=true, Button1LastState=true,ButtonInhibit=false,DotToggleState=true;//flag villogtatáshoz
Element Snake[30],Food, FoodPossibilities[37];
uint8_t const Numbers[10]={
	0b00111111,//0
	0b00000110,//1
	0b01011011,//2
	0b01001111,//3
	0b01100110,//4
	0b01101101,//5
	0b01111101,//6
	0b00000111,//7
	0b01111111,//8
	0b01101111///9
};
/**************************************************************************//**
 * @brief  Nyomógombok beolvasása
 *****************************************************************************/
void ButtonRead(void){
	bool Button0NewState,Button1NewState;
	uint32_t ButtonTemp = GPIO_PortInGet(gpioPortB);
	if(ButtonTemp&Button0Mask){
		Button0NewState=true;
	}
	else Button0NewState=false;
	if(ButtonTemp&Button1Mask){
		Button1NewState=true;
	}
	else Button1NewState=false;

	if (Button1LastState == true && Button1NewState == false&&ButtonInhibit==false) {
		if(Dir==0){
			Dir=3;
		}
		else Dir--;
		ButtonInhibit=true;
	}
	if (Button0LastState == true && Button0NewState == false&&ButtonInhibit==false) {
		if(Dir==3){
			Dir=0;
		}
		else Dir++;
		ButtonInhibit=true;
	}
	Button0LastState = Button0NewState;
	Button1LastState = Button1NewState;
}
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void) {
	/* Chip errata */
	CHIP_Init();
	enter_DefaultMode_from_RESET();//reset utáni inicializálások, GPIO, TIMER, ADC
	SegmentLCD_Init(false);//LCD inicializáló, beépített
	SnakeInitialization();//Kezdeti értékek, képernyõ bal széle, iránya jobbra indul el, stb...
	while (1) {
	    while(Game == 1){
	    	SendToDisplay();//a kígyó részeit kirajzolja a kijelzõre, de csak az alfanumerikus résszel foglalkozik
	    	NumberDisplay(Length-1);//a pontszámot kiírja a felsõ 7 szegmenses részre.
	        while(1){ //wait
		        	if(TimeTick){
			        	TimeTick=0;
			        	break;
		        	}
		        }
	    	Position();// a kígyó mozgását ez a függvény valósítja meg
	    }
		while (Game == 0) { //GameOver
			uint32_t ButtonTemp = GPIO_PortInGet(gpioPortB);
			ButtonTemp &= Button0Mask|Button1Mask;//ha mindkét gomb egyszerre van nyomva
			if (TimeTick) {
				DotToggleState = DisplayDots(DotToggleState);
				TimeTick = 0;
				if (!ButtonTemp) { //új játék
					DisplayDots(false);
					SnakeInitialization();
					break;
				}
			}
		}
	}
}
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
void TIMER0_IRQHandler(void) {
	ButtonRead();//gombok beolvasása 1ms-onként lefutóélet figyeljük
	TimerVar++;
	if(TimerVar==2500){
		TimeTick=1;
		TimerVar=0;
	}
	TIMER_IntClear(TIMER0, TIMER_IF_OF); //TIMER flag törlése
}
