/**************************************************************************//**
* @file
* @brief EFM32 Segment LCD Display driver, header file
* @version 5.2.2
******************************************************************************
* # License
* <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
*******************************************************************************
*
* This file is licensed under the Silabs License Agreement. See the file
* "Silabs_License_Agreement.txt" for details. Before using this software for
* any purpose, you must agree to the terms of that agreement.
*
******************************************************************************/

#ifndef SEGMENTLCD_H
#define SEGMENTLCD_H

#include "segmentlcdconfig.h"

/***************************************************************************//**
 * @addtogroup kitdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SegmentLcd
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define SEGMENT_LCD_BLOCK_MODE_BLANK          0
#define SEGMENT_LCD_BLOCK_MODE_FILL           1
#define SEGMENT_LCD_BLOCK_MODE_OUTLINE        2
#define SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL   3

#define SEGMENT_LCD_NUM_BLOCK_COLUMNS         7
/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/
//
typedef enum {
  segmentLCDBlockModeBlank = SEGMENT_LCD_BLOCK_MODE_BLANK,              /**< Blank */
  segmentLCDBlockModeFill = SEGMENT_LCD_BLOCK_MODE_FILL,                /**< Fill */
  segmentLCDBlockModeOutline = SEGMENT_LCD_BLOCK_MODE_OUTLINE,          /**< Outline */
  segmentLCDBlockModeOutlineFill = SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL, /**< Outline and fill */
} SegmentLCD_BlockMode_TypeDef;

typedef struct
{
  uint8_t com[14]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[14]; /**< LCD bit number */
} CHAR_TypeDef;

typedef struct
{
  uint8_t com[7]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[7]; /**< LCD bit number */
} NUMBER_TypeDef;

typedef struct
{
  uint8_t com[5]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[5]; /**< LCD bit number */
} EM_TypeDef;

typedef struct
{
  uint8_t com[8]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[8]; /**< LCD bit number */
} ARING_TypeDef;

typedef struct
{
  uint8_t com[4]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[4]; /**< LCD bit number */
} BATTERY_TypeDef;

typedef struct
{
  uint8_t com[8]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[8]; /**< LCD bit number */
} Block_TypeDef;

typedef struct
{
  CHAR_TypeDef    Text[7];      /**< Text on display */
  NUMBER_TypeDef  Number[4];    /**< Numbers on display */
  EM_TypeDef      EMode;        /**< Display energy mode */
  ARING_TypeDef   ARing;        /**< Display ring */
  BATTERY_TypeDef Battery;      /**< Display battery */
  Block_TypeDef   TopBlocks[7]; /**< Display top blocks */
  Block_TypeDef   BotBlocks[7]; /**< Display bottom blocks */

} MCU_DISPLAY;
//
static const MCU_DISPLAY EFM_Display = EFM_DISPLAY_DEF;
/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/

/* Regular functions */
void SegmentLCD_AllOff(void);
void SegmentLCD_AllOn(void);
void SegmentLCD_AlphaNumberOff(void);
void SegmentLCD_ARing(int anum, int on);
void SegmentLCD_Battery(int batteryLevel);
void SegmentLCD_Block(SegmentLCD_BlockMode_TypeDef topMode[SEGMENT_LCD_NUM_BLOCK_COLUMNS],
                      SegmentLCD_BlockMode_TypeDef botMode[SEGMENT_LCD_NUM_BLOCK_COLUMNS]);
void SegmentLCD_Disable(void);
void SegmentLCD_EnergyMode(int em, int on);
void SegmentLCD_Init(bool useBoost);
void SegmentLCD_LowerHex(uint32_t num);
void SegmentLCD_LowerNumber(int num);
void SegmentLCD_Number(int value);
void SegmentLCD_NumberOff(void);
void SegmentLCD_Symbol(lcdSymbol s, int on);
void SegmentLCD_UnsignedHex(uint16_t value);
void SegmentLCD_Write(const char *string);

#ifdef __cplusplus
}
#endif

/** @} (end group SegmentLcd) */
/** @} (end group Drivers) */

#endif
