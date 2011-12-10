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


struct souinface	soui[2];
struct souctrl		souc;


/*
 * Setting Pixels Per Line
 *
 *	-+         +---------------------------------------------------------+
 *	 |         |           ////////////////////////////////////          |
 *	 +---------+           ////////////////////////////////////          +--------
 *	 |  blink  |  dummy   |            column/row             |          |
 *	 +---------+----------+-----------------------------------+----------+
 *	 |                              ppl/lpf                              |
 */
void soui_init(void)
{
	/*
	 * TG0 initial
	 */
	// set line
	__iow16(SOU_TG0_CLKS_PERH_0,		soui[0].ppl);

	__iow16(SOU_TG0_HSYNC_START_0,		1);
	__iow16(SOU_TG0_HSYNC_END_0,		soui[0].hblink);

	__iow16(SOU_TG0_HACTIVE_START_0,	soui[0].hblink + soui[0].hdummy);
	__iow16(SOU_TG0_HACTIVE_END_0,		soui[0].hblink + soui[0].hdummy + soui[0].owidth - 1);

	// set frame
	__iow16(SOU_TG0_LINES_PERV_0,		soui[0].lpf);

	__iow16(SOU_TG0_VSYNC_START_LINE_0,	1);
	__iow16(SOU_TG0_VSYNC_END_LINE_0,	soui[0].vblink);

	__iow16(SOU_TG0_VACTIVE_START_0,	soui[0].vblink + soui[0].vdummy);
	__iow16(SOU_TG0_VACTIVE_END_0,		soui[0].vblink + soui[0].vdummy + soui[0].oheight - 1);

	// misc
	__iow8(SOU_TG0_TMODE,			soui[0].tstmode);
	__iow8(SOU_ENCODER_0_MODE,		soui[0].mode);

	__iow16(SOU_TG0_WIDTH_0,		soui[0].iwidth);
	__iow16(SOU_TG0_HEIGHT_0,		soui[0].iheight);

	// must be written in the last
	__iow8(SOU_TG0_CFG,			soui[0].cfg.v);

	/*
	 * TG1 initial
	 */
	// set line
	__iow16(SOU_TG1_CLKS_PERH_0,		soui[1].ppl);

	__iow16(SOU_TG1_HSYNC_START_0,		1);
	__iow16(SOU_TG1_HSYNC_END_0,		soui[1].hblink);

	__iow16(SOU_TG1_HACTIVE_START_0,	soui[1].hblink + soui[1].hdummy);
	__iow16(SOU_TG1_HACTIVE_END_0,		soui[1].hblink + soui[1].hdummy + soui[1].owidth - 1);

	// set frame
	__iow16(SOU_TG1_LINES_PERV_0,		soui[1].lpf);

	__iow16(SOU_TG1_VSYNC_START_LINE_0,	1);
	__iow16(SOU_TG1_VSYNC_END_LINE_0,	soui[1].vblink);

	__iow16(SOU_TG1_VACTIVE_START_0,	soui[1].vblink + soui[1].vdummy);
	__iow16(SOU_TG1_VACTIVE_END_0,		soui[1].vblink + soui[1].vdummy + soui[1].oheight - 1);

	// misc
	__iow8(SOU_TG1_TMODE,			soui[1].tstmode);
	__iow8(SOU_ENCODER_1_MODE,		soui[1].mode);

	__iow16(SOU_TG1_WIDTH_0,		soui[1].iwidth);
	__iow16(SOU_TG1_HEIGHT_0,		soui[1].iheight);

	// must be written in the last
	__iow8(SOU_TG1_CFG,			soui[1].cfg.v);
}


void souc_init(void)
{
	__iow8(SOU_POLARITY, souc.polarity.v);


}

