#include "inttypes.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
//MAX7219 register definitions
#define REG_NO_OP			0x00
#define REG_DIG0			0x01
#define REG_DIG1			0x02
#define REG_DIG2			0x03
#define REG_DIG3			0x04
#define REG_DIG4			0x05
#define REG_DIG5			0x06
#define REG_DIG6			0x07
#define REG_DIG7			0x08
#define REG_DECODE			0x09
#define REG_INTENSITY		0x0A
#define REG_SCANLIMIT		0x0B
#define REG_SHTDWN			0x0C
#define REG_DISPTEST		0x0D
//MAX7219 Shutdown commands
#define SHUTDOWN_MODE		0x00
#define NORMAL_MODE			0x01
//MAX7219 decode mode commands
#define NO_DECODE			0x00
#define DECODE0				0x01
#define DECODE3_0			0x0F
#define DECODE7_0			0xFF
//MAX7219 Intensity values
#define INTENSITY_1			0x00
#define INTENSITY_3			0x01
#define INTENSITY_5			0x02
#define INTENSITY_7			0x03
#define INTENSITY_9			0x04
#define INTENSITY_11		0x05
#define INTENSITY_13		0x06
#define INTENSITY_15		0x07
#define INTENSITY_17		0x08
#define INTENSITY_19		0x09
#define INTENSITY_21		0x0A
#define INTENSITY_23		0x0B
#define INTENSITY_25		0x0C
#define INTENSITY_27		0x0D
#define INTENSITY_29		0x0E
#define INTENSITY_31		0x0F
//MAX7219 Scan limit values
#define	DISP0				0x00
#define	DISP0_1				0x01
#define	DISP0_2				0x02
#define	DISP0_3				0x03
#define	DISP0_4				0x04
#define	DISP0_5				0x05
#define	DISP0_6				0x06
#define	DISP0_7				0x07
//No operation
#define NOP					0x00
/***********************************************///MAX7219 define constants end


