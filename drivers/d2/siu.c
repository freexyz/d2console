/*
 * driver/d2/siu.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * Modifications:
 *	$Id$
 */

#include <configs.h>
#include <regs_siu.h>


struct siuinface	siu[2];
struct siuctrl		siuc;


void siu_init(void)
{
	// channel 0
	__iow16(SIU_CH0_X0,	 siu[0].x_ofs);
	__iow16(SIU_CH0_Y0,	 siu[0].y_ofs);
	__iow16(SIU_CH0_WIDTH0,  siu[0].width);
	__iow16(SIU_CH0_HEIGHT0, siu[0].height);

	__iow32(SIU_CH0_F1S0,	 siu[0].fb1);
	__iow32(SIU_CH0_F2S0,	 siu[0].fb2);
	__iow32(SIU_CH0_F3S0,	 siu[0].fb3);
	__iow24(SIU_CH0_JMP0,	 siu[0].jmp);

	// channel 1
	__iow16(SIU_CH1_X0,	 siu[1].x_ofs);
	__iow16(SIU_CH1_Y0,	 siu[1].y_ofs);
	__iow16(SIU_CH1_WIDTH0,  siu[1].width);
	__iow16(SIU_CH1_HEIGHT0, siu[1].height);

	__iow32(SIU_CH1_F1S0,	 siu[1].fb1);
	__iow32(SIU_CH1_F2S0,	 siu[1].fb2);
	__iow32(SIU_CH1_F3S0,	 siu[1].fb3);
	__iow24(SIU_CH1_JMP0,	 siu[1].jmp);

	// control
	__iow8(SIU_CONF1,	 (siu[1].cf1.v << 1) | siu[0].cf1.v);
	__iow8(SIU_CONF4,	 siu[0].cf2.v);
	__iow8(SIU_CONF5,	 siu[1].cf2.v);

	__iow8(SIU_CONF6,	 siuc.cf6.v);
}


void siu_startup(char mode)
{
//	__iow8(SIU_CONF1,	0xc0);

	// ch0 & ch1 sensor controller reset assert
	__iow8(SIU_CONF3,	0x0c);
	__iow8(SIU_CONF6,	siuc.cf6.v & 0xBF);
	__iow8(0x0030,		0x01);		// adapative clock control

	// raw0 & raw1 width update
	__iow8(SIU_CONF2,	0x03);
	__iow8(SIU_CONF2,	0x00);

	// ch0 & ch1 dma enable
	__iow8(SIU_CTRL,	0x03);

	// ch0 & ch1 sensor controller reset de-assert
	__iow8(SIU_CONF3,	0x00);
	__iow8(SIU_CONF6,	siuc.cf6.v | 0x40);

	// ch0 & ch1 sensor controller, dma enable
	if (mode == 0) {
		__iow8(SIU_CTRL,	0x0F);		// sensor mode
	} else {
#if (CONFIG_FPGA_VERSION <= 520)
		__iow8(SIU_CTRL,	0x0F);
#else
		__iow8(SIU_CTRL,	0x33);		// CIR656 mode
#endif
	}

	// sensor register update
	__iow8(SIU_CONF3,	0x03);
}


void siu_stop(void)
{
	// ch0 & ch1 sensor controller, dma disable
	__iow8(SIU_CTRL, 0);
}

