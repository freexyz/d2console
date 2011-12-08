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


void siu_set_fb(enum d2channel ch, unsigned long fb1, unsigned long fb2, unsigned long fb3)
{
	switch (ch) {
	// ch0 frame buffer address
	case CH0:
		__iow32(SIU_CH0_F1S0, fb1);
		__iow32(SIU_CH0_F2S0, fb2);
		__iow32(SIU_CH0_F3S0, fb3);
		break;
 	// ch1 frame buffer address
	case CH1:
		__iow32(SIU_CH1_F1S0, fb1);
		__iow32(SIU_CH1_F2S0, fb2);
		__iow32(SIU_CH1_F3S0, fb3);
		break;

	case BOTH:
		__iow32(SIU_CH0_F1S0, fb1);
		__iow32(SIU_CH0_F2S0, fb2);
		__iow32(SIU_CH0_F3S0, fb3);

		__iow32(SIU_CH1_F1S0, fb1);
		__iow32(SIU_CH1_F2S0, fb2);
		__iow32(SIU_CH1_F3S0, fb3);
		break;
	}

}


void siu_set_szjmp(enum d2channel ch, unsigned short width, unsigned short height, unsigned long jmp)
{
	switch (ch) {
	case CH0:
		__iow24(SIU_CH0_JMP0,    jmp);
		__iow16(SIU_CH0_WIDTH0,  width);
		__iow16(SIU_CH0_HEIGHT0, height);
		break;

	case CH1:
		__iow24(SIU_CH1_JMP0,    jmp);
		__iow16(SIU_CH1_WIDTH0,  width);
		__iow16(SIU_CH1_HEIGHT0, height);
		break;
	
	case BOTH:
		__iow24(SIU_CH0_JMP0,    jmp);
		__iow16(SIU_CH0_WIDTH0,  width);
		__iow16(SIU_CH0_HEIGHT0, height);

		__iow24(SIU_CH1_JMP0,    jmp);
		__iow16(SIU_CH1_WIDTH0,  width);
		__iow16(SIU_CH1_HEIGHT0, height);
		break;
	}
}


void siu_set_xyoffset(enum d2channel ch, unsigned short x, unsigned short y)
{
	switch (ch) {
	case CH0:
		__iow16(SIU_CH0_X0, x);
		__iow16(SIU_CH0_Y0, y);
		break;

	case CH1:
		__iow16(SIU_CH1_X0, x);
		__iow16(SIU_CH1_Y0, y);
		break;
	}
}


void siu_set_mode(enum d2channel ch, unsigned char mode)
{
	switch (ch) {
	case CH0:
		__iow8(SIU_CONF4, mode);
		break;

	case CH1:
		__iow8(SIU_CONF5, mode);
		break;
	
	case BOTH:
		__iow8(SIU_CONF4, mode);
		__iow8(SIU_CONF5, mode);
		break;
	}
}



void siu_startup(void)
{
	__iow8(SIU_CONF1,	0xc0);

	// ch0 & ch1 sensor controller reset assert
	__iow8(SIU_CONF3,	0x0c);
	__iow8(0x0030,		0x01);		// adapative clock control

	// raw0 & raw1 width update
	__iow8(SIU_CONF2,	0x03);
	__iow8(SIU_CONF2,	0x00);

	// ch0 & ch1 dma enable
	__iow8(SIU_CTRL,	0x03);

	// ch0 & ch1 sensor controller reset de-assert
	__iow8(SIU_CONF3,	0x00);

	// ch0 & ch1 sensor controller, dma enable
	__iow8(SIU_CTRL,	0x0F);

	// sensor register update
	__iow8(SIU_CONF3,	0x03);
}


void siu_stop(void)
{
	// ch0 & ch1 sensor controller, dma disable
	__iow8(SIU_CTRL, 0);
}

