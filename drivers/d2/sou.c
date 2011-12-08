/*
 * driver/d2/sou.c
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
#include <regs_sou.h>



/*
 * Setting Pixels Per Line
 *
 *	         +---------------------------------------------------------+
 *	         |           ////////////////////////////////////          |
 *	---------+           ////////////////////////////////////          +
 *	| blink  |  dummy   |               active              |          |
 *	+--------+----------+-----------------------------------+----------+
 *	|                                total                             |
 */
char sou_set_ppl(enum d2tg ch, unsigned short total, unsigned short active, unsigned short dummy, unsigned short blink)
{
	if ((active + dummy + blink) > total)
		return -1;


	switch (ch) {
	case TG0:
		// total
		__iow16(SOU_TG0_CLKS_PERH_0,		total);

		// blink
		__iow16(SOU_TG0_HSYNC_START_0,		1);
		__iow16(SOU_TG0_HSYNC_END_0,		blink);

		// dummy + active
		__iow16(SOU_TG0_HACTIVE_START_0,	blink + dummy);
		__iow16(SOU_TG0_HACTIVE_END_0,		blink + dummy + active - 1);
		break;

	case TG1:
		// total
		__iow16(SOU_TG1_CLKS_PERH_0,		total);

		// blink
		__iow16(SOU_TG1_HSYNC_START_0,		1);
		__iow16(SOU_TG1_HSYNC_END_0,		blink);

		// dummy + active
		__iow16(SOU_TG1_HACTIVE_START_0,	blink + dummy);
		__iow16(SOU_TG1_HACTIVE_END_0,		blink + dummy + active - 1);
		break;
	}
	return 0;
}


/*
 * Setting Lines Per Frame
 *
 */
char sou_set_lpf(enum d2tg ch, unsigned short total, unsigned short active, unsigned short dummy, unsigned short blink)
{
	if ((active + dummy + blink) > total)
		return -1;


	switch (ch) {
	case TG0:
		// total
		__iow16(SOU_TG0_LINES_PERV_0,		total);

		// blink
		__iow16(SOU_TG0_VSYNC_START_LINE_0,	1);
		__iow16(SOU_TG0_VSYNC_END_LINE_0,	blink);

		// dummy + active
		__iow16(SOU_TG0_VACTIVE_START_0,	blink + dummy);
		__iow16(SOU_TG0_VACTIVE_END_0,		blink + dummy + active - 1);
		break;

	case TG1:
		// total
		__iow16(SOU_TG0_LINES_PERV_0,		total);

		// blink
		__iow16(SOU_TG0_VSYNC_START_LINE_0,	1);
		__iow16(SOU_TG0_VSYNC_END_LINE_0,	blink);

		// dummy + active
		__iow16(SOU_TG0_VACTIVE_START_0,	blink + dummy);
		__iow16(SOU_TG0_VACTIVE_END_0,		blink + dummy + active - 1);
		break;
	}
	return 0;
}

