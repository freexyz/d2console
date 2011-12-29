/*
 * include/d2.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.14	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__D2_H__)
#define __D2_H__

#include <reg52.h>
#include <common.h>


/*
 *****************************************************************************
 *
 * for D2 Definition
 *
 *****************************************************************************
 */
enum d2channel {
	CH0,
	CH1,
	BOTH
};

enum d2stream {
	STANDALONE,
	ONLINE
};

enum d2tg {
	TG0,
	TG1
};


/* Register Base Definition */
#define SYS_BASE		0x0000		/* System Register		*/
#define SDRAM_BASE		0x0100		/* SDRAM Controller		*/
#define SIU_BASE		0x0200		/* Sensor Input Unit		*/
#define IPU_BASE		0x0300		/* Image Processing Unit	*/
#define SOU_BASE		0x0400		/* Sensor Output Unit		*/
#define PIO_BASE		0x0500		/* Programmable IO (PIO)	*/
#define SPI_BASE		0x0600		/* SPI Flash Controller		*/
#define AALIGN_BASE		0x0800		/* Auto Alignment Unit		*/
#define SRAM_BASE		0x7000		/* Embedded SRAM for MCU	*/
#define I2C_MODE		0x7FFF		/* I2C Mode Register		*/



/* Function Prototype */
extern void	sys_init(void);
extern void	d2_init(void);



#endif /* __D2_H__ */
