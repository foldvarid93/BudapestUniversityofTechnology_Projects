#ifndef __DISPLAYFUNCTIONS_H__
#define __DISPLAYFUNCTIONS_H__

#include "em_device.h"
#include "em_chip.h"
#include "em_lcd.h"
#include "segmentlcd.h"
#include "segmentlcd_spec.h"
#include "segmentlcdconfig.h"
#include "mytype.h"
#include "stdbool.h"
//#include ""

void ConvertToDisplayMtrx(void);
void ClearDisplay(void);
void SendToDisplay(void);
bool DisplayDots(bool state);
void NumberDisplay(uint16_t score);

#endif
