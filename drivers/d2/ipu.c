/*
 * driver/d2/ipu.c
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
#include <regs_ipu.h>


struct ipuinface	ipui[2];
struct ipuctrl		ipuc;

void ipui_init(void)
{
	// channel 0
	__iow16(IPU_CH0_ORI_W0,		ipui[0].width);
	__iow16(IPU_CH0_H0,		ipui[0].height);
	__iow24(IPU_CH0_JMP0,		ipui[0].jmp);

	__iow16(IPU_CH0_CROP_W0,	ipui[0].crop);
	__iow8(IPU_CH0_LSTART,		ipui[0].lstart);
	__iow8(IPU_CH0_LEND,		ipui[0].lend);

	__iow32(IPU_CH0_F1S0,		ipui[0].fb1);
	__iow32(IPU_CH0_F2S0,		ipui[0].fb2);
	__iow32(IPU_CH0_F3S0,		ipui[0].fb3);


	// channel 1
	__iow16(IPU_CH1_ORI_W0,		ipui[1].width);
	__iow16(IPU_CH1_H0,		ipui[1].height);
	__iow24(IPU_CH1_JMP0,		ipui[1].jmp);

	__iow16(IPU_CH1_CROP_W0,	ipui[1].crop);
	__iow8(IPU_CH1_LSTART,		ipui[1].lstart);
	__iow8(IPU_CH1_LEND,		ipui[1].lend);

	__iow32(IPU_CH1_F1S0,		ipui[1].fb1);
	__iow32(IPU_CH1_F2S0,		ipui[1].fb2);
	__iow32(IPU_CH1_F3S0,		ipui[1].fb3);
}

void ipuc_startup(void)
{
	__iow8(IPU_CONF4,	ipuc.cf4.v);
	__iow16(IPU_CONF5,	ipuc.cf56.v);	// fussy factor
	__iow16(IPU_OVERLAP0,	ipuc.overlap);	// overlap

	__iow8(IPU_CONF1,	ipuc.cf1.v);
	__iow8(IPU_CONF3,	ipuc.cf3.v);

	// update register
	__iow8(IPU_CONF2,	(ipuc.cf2.v | 0x05));
	__iow8(IPU_CONF2,	(ipuc.cf2.v & 0xFA));

	// enable
	__iow8(IPU_CTRL,	ipuc.ctrl.v);
}

void ipuc_stop(void)
{
	// disable
	__iow8(IPU_CTRL, 0);
}

