/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "segmentlcd.h"
#include "segmentlcd_spec.h"
#include "segmentlcdconfig.h"

/**************************************************************************//**
 * @brief  A simple delay loop
 *****************************************************************************/

void delay() {
	for(int d=0;d<500000;d++);
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();
  SegmentLCD_Init(false);

  SegmentLCD_SegmentData_TypeDef segmentField[7];

  /* Infinite loop */
  while (1) {

	  // Clear all segments
	  for (uint8_t p = 0; p < 7; p++) {
		  segmentField[p].raw = 0;
		  displaySegmentField(segmentField);
	  }

	  // Turn on all segments one-by-one
	  // Only one segment is turned on at any given time
	  // Using 14 bit binary value
	  for (uint8_t p = 0; p < 7; p++) {
		  for (uint8_t s = 0; s < 15; s++) {
			  segmentField[p].raw = 1 << s;
			  displaySegmentField(segmentField);
			  delay();
		  }
	  }

	  // Turn on all segments one-by-one
	  // All the previous segments are left turned on
	  // Using dedicated bit field values
	  for (uint8_t p = 0; p < 7; p++) {
		  segmentField[p].a = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].b = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].c = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].d = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].e = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].f = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].g = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].h = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].j = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].k = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].m = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].n = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].p = 1;
		  displaySegmentField(segmentField);
		  delay();

		  segmentField[p].q = 1;
		  displaySegmentField(segmentField);
		  delay();
	  }

  }

}
