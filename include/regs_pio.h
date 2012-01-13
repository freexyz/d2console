/*
 * include/regs_pio.h --
 *
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.11.22	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */

#include <configs.h>

#if !defined(__REGS_PIO_H__)
#define __REGS_PIO_H__

#if !defined(PIO_BASE)
# error Please define 'PIO_BASE'
#endif

#define P0_DATA		(PIO_BASE+0x0000)	/* R/W, 0, DATA0 , Write data to set PIO_OUT, Read data form PIO_IO	*/
#define P0_DIR		(PIO_BASE+0x0001)	/* R/W, 0, DATADIR0, Connect PIO_EN to control Input/Output mode	*/
						/*	1 ¡V Force PIO to output mode					*/
						/*	0 ¡V Force PIO to input mode					*/
#define P1_DATA		(PIO_BASE+0x0002)
#define P1_DIR		(PIO_BASE+0x0003)
#define P2_DATA		(PIO_BASE+0x0004)
#define P2_DIR		(PIO_BASE+0x0005)
#define P3_DATA		(PIO_BASE+0x0006)
#define P3_DIR		(PIO_BASE+0x0007)
#define P4_DATA		(PIO_BASE+0x0008)
#define P4_DIR		(PIO_BASE+0x0009)
#define P5_DATA		(PIO_BASE+0x000A)
#define P5_DIR		(PIO_BASE+0x000B)
#define P6_DATA		(PIO_BASE+0x000C)
#define P6_DIR		(PIO_BASE+0x000D)
#define P7_DATA		(PIO_BASE+0x000E)
#define P7_DIR		(PIO_BASE+0x000F)
#define P8_DATA		(PIO_BASE+0x0010)
#define P8_DIR		(PIO_BASE+0x0011)
#define P9_DATA		(PIO_BASE+0x0012)
#define P9_DIR		(PIO_BASE+0x0013)
#define P10_DATA	(PIO_BASE+0x0014)
#define P10_DIR		(PIO_BASE+0x0015)


/*
 * Structure Definition
 */
struct pioif {
	unsigned char	dat;
	unsigned char	dir;
};


extern struct pioif volatile __xdata		*pio;
extern unsigned char volatile __xdata		*piomode;



#endif /* __REGS_PIO_H__ */
