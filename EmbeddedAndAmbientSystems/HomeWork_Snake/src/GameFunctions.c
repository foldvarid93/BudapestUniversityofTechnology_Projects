#include "GameFunctions.h"
extern Element Snake[], FoodPossibilities[],Food;
extern uint8_t Game,Length,Dir,LastDir,NewDir;
extern bool ButtonInhibit;

uint8_t GetRandomNumber(void){
	ADC_Start(ADC0, adcStartSingle);
	while ((ADC0->IF & ADC_IF_SINGLE) == 0){};
	return ADC_DataSingleGet(ADC0) % (37 - Length);
}
void MakeFood(void){
	Element Temp;
	bool Contain=false;
	uint8_t j=0;
	for(uint8_t digit=0;digit<7;digit++){
		Temp.Digit=digit;
		Temp.Segment=0;
		for(uint8_t i=0;i<Length;i++){
			if((Snake[i].Digit==Temp.Digit&&Snake[i].Segment==Temp.Segment)){
				Contain=true;
			}
		}
		if(!Contain){
			FoodPossibilities[j]=Temp;
			j++;
		}
		Contain=false;
		Temp.Segment=3;
		for(uint8_t i=0;i<Length;i++){
			if((Snake[i].Digit==Temp.Digit&&Snake[i].Segment==Temp.Segment)){
				Contain=true;
			}
		}
		if(!Contain){
			FoodPossibilities[j]=Temp;
			j++;
		}
		Contain=false;
		Temp.Segment=4;
		for(uint8_t i=0;i<Length;i++){
			if((Snake[i].Digit==Temp.Digit&&Snake[i].Segment==Temp.Segment)){
				Contain=true;
			}
		}
		if(!Contain){
			FoodPossibilities[j]=Temp;
			j++;
		}
		Contain=false;
		Temp.Segment=5;
		for(uint8_t i=0;i<Length;i++){
			if((Snake[i].Digit==Temp.Digit&&Snake[i].Segment==Temp.Segment)){
				Contain=true;
			}
		}
		if(!Contain){
			FoodPossibilities[j]=Temp;
			j++;
		}
		Contain=false;
		Temp.Segment=6;
		for(uint8_t i=0;i<Length;i++){
			if((Snake[i].Digit==Temp.Digit&&Snake[i].Segment==Temp.Segment)){
				Contain=true;
			}
		}
		if(!Contain){
			FoodPossibilities[j]=Temp;
			j++;
		}
		Contain=false;
		if (digit == 6) {
			Temp.Segment = 1;
			for (uint8_t i = 0; i < Length; i++) {
				if ((Snake[i].Digit == Temp.Digit&& Snake[i].Segment == Temp.Segment)) {
					Contain = true;
				}
			}
			if (!Contain) {
				FoodPossibilities[j] = Temp;
				j++;
			}
			Contain=false;
			Temp.Segment = 2;
			for (uint8_t i = 0; i < Length; i++) {
				if ((Snake[i].Digit == Temp.Digit&& Snake[i].Segment == Temp.Segment)) {
					Contain = true;
				}
			}
			if (!Contain) {
				FoodPossibilities[j] = Temp;
				j++;
			}
			Contain=false;
		}
	}
	Food=FoodPossibilities[GetRandomNumber()];
}
void SnakeInitialization(void) {
	Snake[0].Digit=0;
	Snake[0].Segment=6;
	Length=1;
	Dir=0;
	LastDir=0;
	NewDir=0;
	Game=1;
	MakeFood();
}
void Position(void){
	NewDir=Dir;
	ButtonInhibit=false;
	Element Temp[30];
	for(uint8_t i=0; i<Length; i++){
		Temp[i]=Snake[i];
	}

	if(Snake[0].Segment==0&&LastDir==0&&NewDir==0){//0.szegmensben volt irány: 0
		Snake[0].Digit++;
		if (Snake[0].Digit ==7) {
			Snake[0].Digit = 0;
		}
	}
	if(Snake[0].Segment==0&&LastDir==2&&NewDir==2){//0.digit0.szegmensben volt irány: 2
		Snake[0].Digit--;
		if (Snake[0].Digit ==255) {
			Snake[0].Digit = 6;
		}
	}
	if(Snake[0].Segment==0&&LastDir==2&&NewDir==3){//0.szegmensben volt régi irány:2 új irány 3
		Snake[0].Segment=5;
	}
	if(Snake[0].Segment==0&&LastDir==0&&NewDir==3){//0.szegmensben volt régi irány:0 új irány 3

		if(Snake[0].Digit==6){
			Snake[0].Segment=1;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=5;
		}
	}
	if(Snake[0].Segment==0&&LastDir==2&&NewDir==1){//0.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=4;
	}
	if(Snake[0].Segment==0&&LastDir==0&&NewDir==1){//0.szegmensben volt régi irány:0 új irány 1

		if(Snake[0].Digit==6){
			Snake[0].Segment=2;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=4;
		}
	}
/**************************************************************************/
	if(Snake[0].Segment==6&&LastDir==0&&NewDir==0){//6.digit0.szegmensben volt irány: 0
		Snake[0].Digit++;
		if (Snake[0].Digit ==7) {
			Snake[0].Digit = 0;
		}
	}
	if(Snake[0].Segment==6&&LastDir==2&&NewDir==2){//6.digit0.szegmensben volt irány: 2
		Snake[0].Digit--;
		if (Snake[0].Digit ==255) {
			Snake[0].Digit = 6;
		}
	}
	if(Snake[0].Segment==6&&LastDir==2&&NewDir==3){//0.szegmensben volt régi irány:2 új irány 3
		Snake[0].Segment=4;
	}
	if(Snake[0].Segment==6&&LastDir==0&&NewDir==3){//0.szegmensben volt régi irány:0 új irány 3

		if(Snake[0].Digit==6){
			Snake[0].Segment=2;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=4;
		}
	}
	if(Snake[0].Segment==6&&LastDir==2&&NewDir==1){//0.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=5;
	}
	if(Snake[0].Segment==6&&LastDir==0&&NewDir==1){//0.szegmensben volt régi irány:0 új irány 1

		if(Snake[0].Digit==6){
			Snake[0].Segment=1;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=5;
		}
	}
/**************************************************************************/
	if(Snake[0].Segment==3&&LastDir==0&&NewDir==0){//3.szegmensben volt irány: 0
		Snake[0].Digit++;
		if (Snake[0].Digit ==7) {
			Snake[0].Digit = 0;
		}
	}
	if(Snake[0].Segment==3&&LastDir==2&&NewDir==2){//3.szegmensben volt irány: 2
		Snake[0].Digit--;
		if (Snake[0].Digit ==255) {
			Snake[0].Digit = 6;
		}
	}
	if(Snake[0].Segment==3&&LastDir==2&&NewDir==3){//3.szegmensben volt régi irány:2 új irány 3
		Snake[0].Segment=5;
	}
	if(Snake[0].Segment==3&&LastDir==0&&NewDir==3){//3.szegmensben volt régi irány:0 új irány 3

		if(Snake[0].Digit==6){
			Snake[0].Segment=1;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=5;
		}
	}
	if(Snake[0].Segment==3&&LastDir==2&&NewDir==1){//0.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=4;
	}
	if(Snake[0].Segment==3&&LastDir==0&&NewDir==1){//0.szegmensben volt régi irány:0 új irány 1

		if(Snake[0].Digit==6){
			Snake[0].Segment=2;
		}
		else{
			Snake[0].Digit++;
			Snake[0].Segment=4;
		}
	}
/**************************************************************************///4.5.szegmens egyenes mozgágasi
	if((Snake[0].Segment==4||Snake[0].Segment==5)&&LastDir==1&&NewDir==1){//4.szegmensben volt irány: 0
		Snake[0].Segment++;
		if (Snake[0].Segment == 6) {
			Snake[0].Segment = 4;
		}
	}
	if((Snake[0].Segment==4||Snake[0].Segment==5)&&LastDir==3&&NewDir==3){//4.szegmensben volt irány: 2
		Snake[0].Segment--;
		if (Snake[0].Segment == 3) {
			Snake[0].Segment = 5;
		}
	}
	/****************************************************///forduló mozgások
	if(Snake[0].Segment==4&&LastDir==1&&NewDir==0){//4.szegmensben volt régi irány:1 új irány 0
		Snake[0].Segment=6;
	}
	if(Snake[0].Segment==4&&LastDir==1&&NewDir==2){//4.szegmensben volt régi irány:0 új irány 2
		Snake[0].Segment=6;
		Snake[0].Digit--;
		if(Snake[0].Digit==255){
			Snake[0].Digit=6;
		}
	}
	if(Snake[0].Segment==4&&LastDir==3&&NewDir==0){//4.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=3;
	}
	if(Snake[0].Segment==4&&LastDir==3&&NewDir==2){//4.szegmensben volt régi irány:0 új irány 1
		Snake[0].Segment=3;
		Snake[0].Digit--;
		if(Snake[0].Digit==255){
			Snake[0].Digit=6;
		}
	}
/**************************************************************************/// 5.forduló mozgások
	if(Snake[0].Segment==5&&LastDir==1&&NewDir==0){//5.szegmensben volt régi irány:1 új irány 0
		Snake[0].Segment=0;
	}
	if(Snake[0].Segment==5&&LastDir==1&&NewDir==2){//4.szegmensben volt régi irány:0 új irány 2
		Snake[0].Segment=0;
		Snake[0].Digit--;
		if(Snake[0].Digit==255){
			Snake[0].Digit=6;
		}
	}
	if(Snake[0].Segment==5&&LastDir==3&&NewDir==0){//4.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=6;
	}
	if(Snake[0].Segment==5&&LastDir==3&&NewDir==2){//4.szegmensben volt régi irány:0 új irány 1
		Snake[0].Segment=6;
		Snake[0].Digit--;
		if(Snake[0].Digit==255){
			Snake[0].Digit=6;
		}
	}
/**************************************************************************/// 1.2.forduló mozgások

	if((Snake[0].Segment==1||Snake[0].Segment==2)&&LastDir==1&&NewDir==1){//4.szegmensben volt irány: 0
		Snake[0].Segment--;
		if (Snake[0].Segment == 0) {
			Snake[0].Segment = 2;
		}
	}
	if((Snake[0].Segment==1||Snake[0].Segment==2)&&LastDir==3&&NewDir==3){//4.szegmensben volt irány: 2
		Snake[0].Segment++;
		if (Snake[0].Segment == 3) {
			Snake[0].Segment = 1;
		}
	}
	if(Snake[0].Segment==1&&LastDir==1&&NewDir==2){//1.szegmensben volt régi irány:1 új irány 0
		Snake[0].Segment=0;
	}
	if(Snake[0].Segment==1&&LastDir==1&&NewDir==0){//1.szegmensben volt régi irány:0 új irány 2
		Snake[0].Segment=0;
		Snake[0].Digit=0;
	}
	if(Snake[0].Segment==1&&LastDir==3&&NewDir==2){//4.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=6;
	}
	if(Snake[0].Segment==1&&LastDir==3&&NewDir==0){//4.szegmensben volt régi irány:0 új irány 1
		Snake[0].Segment=6;
		Snake[0].Digit=0;
	}
	/**************************************************************************/
	if(Snake[0].Segment==2&&LastDir==1&&NewDir==2){//1.szegmensben volt régi irány:1 új irány 0
		Snake[0].Segment=6;
	}
	if(Snake[0].Segment==2&&LastDir==1&&NewDir==0){//1.szegmensben volt régi irány:0 új irány 2
		Snake[0].Segment=6;
		Snake[0].Digit=0;
	}
	if(Snake[0].Segment==2&&LastDir==3&&NewDir==2){//4.szegmensben volt régi irány:2 új irány 1
		Snake[0].Segment=3;
	}
	if(Snake[0].Segment==2&&LastDir==3&&NewDir==0){//4.szegmensben volt régi irány:0 új irány 1
		Snake[0].Segment=3;
		Snake[0].Digit=0;
	}
	LastDir=NewDir;

	if(Snake[0].Segment==Food.Segment&&Snake[0].Digit==Food.Digit){
		Length++;
		MakeFood();
	}
	for(uint8_t i=0; i<Length; i++){
		Snake[i+1]=Temp[i];
	}
	for(uint8_t i=1;i<Length;i++){
		if(Snake[0].Segment==Snake[i].Segment&&Snake[0].Digit==Snake[i].Digit){
			Game=0;
			return;
		}
	}

}
