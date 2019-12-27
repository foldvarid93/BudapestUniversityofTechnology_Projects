/**************************************************************************//**
 * B5PLMF F�ldv�ri D�vid
 * E8RNVF Sokoray Tam�s
 * 2017.11.20. Be�gyazott �s ambiens rendszerek h�zi feladat
 * Giant Gecko STK3700
 * Snake j�t�k.
 * R�vid le�r�s: PB0 nyom�gombra balra, PB1-re jobbra fordul. A k�gy� az alfanumerikus kijelz� szegmensein mozog.
 * A fels� 4 digites 7 szegmenses kijelz� r�szen az aktu�lis pontsz�m.
 * A j�t�k v�g�t a kijelz� alj�n villog� pontok jelzik.
 * A j�t�k �jraind�that� ha v�ge lett �s PB0&PB1 egyszerre le van nyomva.
 * Az �telhez random sz�mot egy ADC bemenet zaj�b�l nyer�nk
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "InitDevice.h"
#include "GameFunctions.h"
#include "DisplayFunctions.h"
/**************************************************************************//**
 * @brief V�ltoz�k �s konstansok
 *****************************************************************************/
uint8_t DisplayData [7][14],Game,Length,Dir,LastDir,NewDir,TimeTick=0;
uint16_t TimerVar=0,Button0Mask=0x200,Button1Mask=0x400;
bool Button0LastState=true, Button1LastState=true,ButtonInhibit=false,DotToggleState=true;//flag villogtat�shoz
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
 * @brief  Nyom�gombok beolvas�sa
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
	enter_DefaultMode_from_RESET();//reset ut�ni inicializ�l�sok, GPIO, TIMER, ADC
	SegmentLCD_Init(false);//LCD inicializ�l�, be�p�tett
	SnakeInitialization();//Kezdeti �rt�kek, k�perny� bal sz�le, ir�nya jobbra indul el, stb...
	while (1) {
	    while(Game == 1){
	    	SendToDisplay();//a k�gy� r�szeit kirajzolja a kijelz�re, de csak az alfanumerikus r�sszel foglalkozik
	    	NumberDisplay(Length-1);//a pontsz�mot ki�rja a fels� 7 szegmenses r�szre.
	        while(1){ //wait
		        	if(TimeTick){
			        	TimeTick=0;
			        	break;
		        	}
		        }
	    	Position();// a k�gy� mozg�s�t ez a f�ggv�ny val�s�tja meg
	    }
		while (Game == 0) { //GameOver
			uint32_t ButtonTemp = GPIO_PortInGet(gpioPortB);
			ButtonTemp &= Button0Mask|Button1Mask;//ha mindk�t gomb egyszerre van nyomva
			if (TimeTick) {
				DotToggleState = DisplayDots(DotToggleState);
				TimeTick = 0;
				if (!ButtonTemp) { //�j j�t�k
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
	ButtonRead();//gombok beolvas�sa 1ms-onk�nt lefut��let figyelj�k
	TimerVar++;
	if(TimerVar==2500){
		TimeTick=1;
		TimerVar=0;
	}
	TIMER_IntClear(TIMER0, TIMER_IF_OF); //TIMER flag t�rl�se
}
