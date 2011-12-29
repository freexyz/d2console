/*
 * include/regs_align.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.11.14	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */

#include <configs.h>

#if !defined(__REGS_ALIGN_H__)
#define __REGS_ALIGN_H__

#if !defined(AALIGN_BASE)
#error Please define 'AALIGN_BASE'
#endif


/*
 * Register Definition
 */
#define AUTO_ALIGN_CFG			(AALIGN_BASE+0x0000)	/*  */
# define AUTO_ALIGN_TRIGGER		BIT(0)			/* RW, 0, Auto_Align module trigger, the trigger needs a pulse */

#define AUTO_ALIGN_STATUS		(AALIGN_BASE+0x0001)	/*  */
# define AUTO_ALIGN_BUSY		BIT(0)			/* R , x, Auto_Align module busy status */
								/*        '0': module ready for next trigger */
								/*        '1': module is busy */

#define RAM_PORT_EN			(AALIGN_BASE+0x0002)	/*  */
# define RAM_PORT_ENB			BIT(0)			/* RW, 0, MPU RAM port enable */
								/*        '0': Auto_Align write position ram */
								/*        '1': MPU read position ram */

#define RAM_PORT_ADDR			(AALIGN_BASE+0x0003)	/* RW, 0, [5:0] MPU RAM port read address */
#define RAM_PORT_DATA			(AALIGN_BASE+0x0004)	/* R , x, [6:0] MPU RAM port read data */

#define AUTO_ALIGN_CFG2			(AALIGN_BASE+0x0005)	/*  */
# define AUTO_ALIGN_CH_ID		BIT(0)			/* RW, 0, Channel ID */
								/*        '0': 64x64 is CH_0,128X64 is CH_1 */
								/*        '1': 64x64 is CH_1,128X64 is CH_0 */
# define AUTO_ALIGN_RAW_MODE		BIT(1)			/* RW, 1, RAW mode */
								/*        '0': Even line don't do one pixel offset */
								/*        '1': Even line do one pixel offset because of mode is raw */
# define AUTO_ALIGN_SAMPLE_X4		BIT(2)			/* RW, 0, Sample_x4 mode */
								/*        '0': One sample contain 1 pixel */
								/*        '1': One sample contain 4 pixel */

#define AUTO_ALIGN_SCALE		(AALIGN_BASE+0x0006)	/* RW, 0, [1:0] Auto_Align scale up function, the factor is */
# define AALIGN_SCALE_FACTOR1		0x00			/*        00 : Scale factor x1 */
# define AALIGN_SCALE_FACTOR2		0x01			/*        01 : Scale factor x2 */
# define AALIGN_SCALE_FACTOR3		0x02			/*        10 : Scale factor x3 */
# define AALIGN_SCALE_FACTOR4		0x03			/*        11 : Scale factor x4 */

#define AUTO_ALIGN_REG_UPDATE		(AALIGN_BASE+0x0007)	/*  */
# define AUTO_ALIGN_UPDATE		BIT(0)			/* RW, 0, Auto_Align module register update, the update */
								/*        signal needs a pulse, 1->0 */

#define AUTO_ALIGN_64X64_PANNING_X_0	(AALIGN_BASE+0x0008)	/* RW, 0, [7:0] */
#define AUTO_ALIGN_64X64_PANNING_X_1	(AALIGN_BASE+0x0009)	/* RW, 0, [12:8] Horizontal offset within 64x64 window channel. (unit: pixel) */
#define AUTO_ALIGN_64X64_PANNING_Y_0	(AALIGN_BASE+0x000A)	/* RW, 0, [7:0] */
#define AUTO_ALIGN_64X64_PANNING_Y_1	(AALIGN_BASE+0x000B)	/* RW, 0, [11:8] Vertical offset within 64x64 window channel. (unit: pixel) */

#define AUTO_ALIGN_128X64_PANNING_X_0	(AALIGN_BASE+0x000C)	/* RW, 0, [7:0] */
#define AUTO_ALIGN_128X64_PANNING_X_1	(AALIGN_BASE+0x000D)	/* RW, 0, [12:8] Horizontal offset within 128x64 window channel. (unit: pixel) */
#define AUTO_ALIGN_128X64_PANNING_Y_0	(AALIGN_BASE+0x000E)	/* RW, 0, [7:0] */
#define AUTO_ALIGN_128X64_PANNING_Y_1	(AALIGN_BASE+0x000F)	/* RW, 0, [11:8] Vertical offset within 128x64 window channel. (unit: pixel) */

#define RAM512x11_ADDR0			(AALIGN_BASE+0x0010)
#define RAM512x11_ADDR1			(AALIGN_BASE+0x0011)
#define RAM512x11_DATA			(AALIGN_BASE+0x0012)


/*
 * Structure Definition
 */
struct alignif {
	union {
		unsigned char	v;
		struct {
			unsigned char	trigger		: 1;	// Auto_Align module trigger, the trigger needs a pulse
			unsigned char	rsv		: 7;	// reserve
		} b;
	} cfg;

	union {
		unsigned char	v;
		struct {
			unsigned char	busy		: 1;	// Auto_Align module busy status
			unsigned char	rsv		: 7;	// reserve
		} b;
	} status;

	union {
		unsigned char	v;
		struct {
			unsigned char	enable		: 1;	// MPU RAM port enable
			unsigned char	rsv		: 7;	// reserve
		} b;
	} ram;

	unsigned char	ram_addr;				// [5:0] MPU RAM port read address 
	unsigned char	ram_data;				// [6:0] MPU RAM port read data

	union {
		unsigned char	v;
		struct {
			unsigned char	ch_id		: 1;	// channel ID
								//	0: 64x64 is CH_0,128X64 is CH_1
								//	1: 64x64 is CH_1,128X64 is CH_0
			unsigned char	raw		: 1;	// RAW mode
								//	0: Even line don't do one pixel offset
								//	1: Even line do one pixel offset because of mode is raw
			unsigned char	samplex4	: 1;	// samplex4 mode,
								//	0: One sample contain 1 pixel
								//	1: One sample contain 4 pixel
			unsigned char	rsv		: 5;	// reserve
		} b;
	} cfg2;

	unsigned char	scale;					// [1:0] Auto_Align scale up function
	unsigned char	update;

	unsigned short	x_64x64;
	unsigned short	y_64x64;
	unsigned short	x_128x64;
	unsigned short	y_128x64;

	unsigned short	ram512a;
	unsigned char	ram512d;
};


extern struct alignif volatile __xdata		*align;

/* Function Prototype */



#endif /* __REGS_ALIGN_H__ */
