#ifndef __GAMEFUNCTIONS_H__
#define __GAMEFUNCTIONS_H__

#include "em_device.h"
#include "em_chip.h"
#include "mytype.h"
#include "em_adc.h"
//#include ""

void SnakeInitialization(void);
void MakeFood(void);
void Position(void);
uint8_t GetrandomNumber(void);
#endif
