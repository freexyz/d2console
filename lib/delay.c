/*
 * lib/delay.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.24	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <reg52.h>
#include <configs.h>
#include <intrins.h>

void udelay(unsigned char usec)
{
	usec <<= 1;
	while (usec--) {
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
}

void mdelay(unsigned short msec)
{
	TMOD	= (TMOD & 0xF0) | 0x01;
	do {
		TL0 = (unsigned char)  ((65536UL - ((CONFIG_FOSC / 1000UL) >> 1)) & 0x00FF);
		TH0 = (unsigned char) (((65536UL - ((CONFIG_FOSC / 1000UL) >> 1)) & 0xFF00) >> 8);
		TF0 = 0;
		TR0 = 1;

		while (!TF0)
			;	/* wait timer overflow */
	} while (--msec);
}

