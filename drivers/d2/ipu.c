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


void ipu_set_fb(enum d2channel ch, unsigned long fb1, unsigned long fb2, unsigned long fb3)
{
	switch (ch) {
	// ch0 frame buffer address
	case CH0:
		__iow32(IPU_CH0_F1S0, fb1);
		__iow32(IPU_CH0_F2S0, fb2);
		__iow32(IPU_CH0_F3S0, fb3);
		break;
 	// ch1 frame buffer address
	case CH1:
		__iow32(IPU_CH1_F1S0, fb1);
		__iow32(IPU_CH1_F2S0, fb2);
		__iow32(IPU_CH1_F3S0, fb3);
		break;

	case BOTH:
		__iow32(IPU_CH0_F1S0, fb1);
		__iow32(IPU_CH0_F2S0, fb2);
		__iow32(IPU_CH0_F3S0, fb3);

		__iow32(IPU_CH1_F1S0, fb1);
		__iow32(IPU_CH1_F2S0, fb2);
		__iow32(IPU_CH1_F3S0, fb3);
		break;
	}

}


void ipu_set_xyjmp(enum d2channel ch, unsigned short width, unsigned short height, unsigned long jmp)
{
	switch (ch) {
	case CH0:
		__iow24(IPU_CH0_JMP0,	jmp);
		__iow16(IPU_CH0_ORI_W0,	width);
		__iow16(IPU_CH0_H0,	height);
		break;

	case CH1:
		__iow24(IPU_CH1_JMP0,	jmp);
		__iow16(IPU_CH1_ORI_W0,	width);
		__iow16(IPU_CH1_H0,	height);
		break;
	
	case BOTH:
		__iow24(IPU_CH0_JMP0,	jmp);
		__iow16(IPU_CH0_ORI_W0,	width);
		__iow16(IPU_CH0_H0,	height);

		__iow24(IPU_CH1_JMP0,	jmp);
		__iow16(IPU_CH1_ORI_W0,	width);
		__iow16(IPU_CH1_H0,	height);
		break;
	}
}


void ipu_set_crop(enum d2channel ch, unsigned short width, unsigned char lstart, unsigned char lend)
{
	switch (ch) {
	case CH0:
		__iow16(IPU_CH0_CROP_W0, width);
		__iow8(IPU_CH0_LSTART,   lstart);
		__iow8(IPU_CH0_LEND,     lend);
		break;

	case CH1:
		__iow16(IPU_CH1_CROP_W0, width);
		__iow8(IPU_CH1_LSTART,   lstart);
		__iow8(IPU_CH1_LEND,     lend);
		break;
	
	case BOTH:
		__iow16(IPU_CH0_CROP_W0, width);
		__iow8(IPU_CH0_LSTART,   lstart);
		__iow8(IPU_CH0_LEND,     lend);

		__iow16(IPU_CH1_CROP_W0, width);
		__iow8(IPU_CH1_LSTART,   lstart);
		__iow8(IPU_CH1_LEND,     lend);
		break;
	}
}


void ipu_set_format(unsigned char format)
{
	__iow8(IPU_CONF1, format);
}


void ipu_set_opmode(unsigned char op, unsigned char factor, unsigned short overlap)
{
	__iow8(IPU_CONF3,	op);

	// fussy stitch
	__iow8(IPU_CONF5,	factor);	// fussy factor
	__iow16(IPU_OVERLAP0,	overlap);	// overlap
}


void ipu_set_cowork(unsigned char dsrc)
{
	unsigned char	tmp;

	tmp = __ior8(IPU_CONF2) & 0x0F;
#if 1
	tmp = ((tmp << 3) & 0x08) |
	      ((tmp << 2) & 0x04) |
	      ((tmp >> 2) & 0x02) |
	      ((tmp >> 3) & 0x01);
#endif
	__iow8(IPU_CONF2, (tmp | (dsrc & 0x30)));
}


void ipu_startup(enum d2stream op)
{
	unsigned char	tmp;

	// update register
	tmp = __ior8(IPU_CONF2) & 0x0F;
#if 1
	tmp = ((tmp << 3) & 0x08) |
	      ((tmp << 2) & 0x04) |
	      ((tmp >> 2) & 0x02) |
	      ((tmp >> 3) & 0x01);
#endif
	__iow8(IPU_CONF2, (tmp | 0x05));
	__iow8(IPU_CONF2, (tmp & 0xFA));

	// enable
	if (op == STANDALONE) {
//		__iow8(IPU_CTRL, 0x03);
		__iow8(IPU_CTRL, 0x01);
	} else {
		__iow8(IPU_CTRL, 0x0C);
	}
}


void ipu_stop(void)
{
	// disable
	__iow8(IPU_CTRL, 0);
}

