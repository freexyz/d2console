/*
 * dvt/dvt_hside.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.29	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <stdio.h>

#include <configs.h>
#include <dvt.h>

#include <regs_sys.h>
#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_pio.h>


#define SOU_WIDTH		2000
#define SOU_HEIGHT		333


static __code const struct regs_object		hside_tbl[] = {

	// set clock ctrl
//	{ SDRAM_CLK,			0x03 },		// sdr div
	{ MCLK,				0x02 },		// mclk div
	{ CLKSEL,			0x08 },		// select sou out clk source
	{ SOU_CLK,			0x02 },		// sou out clk div
	{ 0x0F40,			0x83 },		// for sim use, fpga not use
	{ BYPASS,			0x03 },		// enable sensor0, sensor1

	// initialize sou & enable
	{ SOU_MULTI_CH_EN,		0 },
	{ SOU_ENCODER_0_MODE,		0x03 },
	{ SOU_TG0_WIDTH_0,		LOBYTE(SOU_WIDTH) },
	{ SOU_TG0_WIDTH_1,		HIBYTE(SOU_WIDTH) },
	{ SOU_TG0_HEIGHT_0,		LOBYTE(SOU_HEIGHT) },
	{ SOU_TG0_HEIGHT_1,		HIBYTE(SOU_HEIGHT) },

	// total horizontal clk pixel
	{ SOU_TG0_CLKS_PERH_0, 		LOBYTE(SOU_WIDTH+10) },
	{ SOU_TG0_CLKS_PERH_1, 		HIBYTE(SOU_WIDTH+10) },

	// horizontal start clk pixel
	{ SOU_TG0_HSYNC_START_0,	0x06 },
	{ SOU_TG0_HSYNC_START_1,	0x00 },

	// horizontal end   clk pixel
	{ SOU_TG0_HSYNC_END_0,		0x07 },
	{ SOU_TG0_HSYNC_END_1,		0x00 },

	// h active start
	{ SOU_TG0_HACTIVE_START_0,	0x0a },
	{ SOU_TG0_HACTIVE_START_1,	0x00 },

	// h active end
	{ SOU_TG0_HACTIVE_END_0,	LOBYTE(SOU_WIDTH+10 - 1) },
	{ SOU_TG0_HACTIVE_END_1,	HIBYTE(SOU_WIDTH+10 - 1) },

	// total v
	{ SOU_TG0_LINES_PERV_0,		LOBYTE(SOU_HEIGHT+4 - 1) },
	{ SOU_TG0_LINES_PERV_1		HIBYTE(SOU_HEIGHT+4 - 1) },

	// v start line ,end line
	{ SOU_TG0_VSYNC_START_LINE_0,	0x01 },
	{ SOU_TG0_VSYNC_START_LINE_1,   0x00 },
	{ SOU_TG0_VSYNC_END_LINE_0,     0x02 },
	{ SOU_TG0_VSYNC_END_LINE_1,     0x00 },

	// v start clk, end clk
	{ SOU_TG0_VSYNC_START_CLK_0,	0x01 },
	{ SOU_TG0_VSYNC_START_CLK_1,	0x00 },
	{ SOU_TG0_VSYNC_END_CLK_0,	0x06 },
	{ SOU_TG0_VSYNC_END_CLK_1,	0x00 },

	// v active start,active end
	{ SOU_TG0_VACTIVE_START_0,	0x02 },
	{ SOU_TG0_VACTIVE_START_1,      0x00 },
	{ SOU_TG0_VACTIVE_END_0,        LOBYTE(SOU_HEIGHT+4 - 3) },
	{ SOU_TG0_VACTIVE_END_1,        HIBYTE(SOU_HEIGHT+4 - 3) },


	{ SOU_ENCODER_1_MODE,		0x03 },
	{ SOU_TG1_WIDTH_0,		0x80 },	
	{ SOU_TG1_WIDTH_1,		0x02 },	
	{ SOU_TG1_HEIGHT_0,		0x40 },	
	{ SOU_TG1_HEIGHT_1,		0x00 },	

	{ SOU_TG1_CLKS_PERH_0,		0xa0 },
	{ SOU_TG1_CLKS_PERH_1,		0x02 },
	{ SOU_TG1_HSYNC_START_0,	0x04 },
	{ SOU_TG1_HSYNC_START_1,	0x00 },
	{ SOU_TG1_HSYNC_END_0,		0x08 },
	{ SOU_TG1_HSYNC_END_1,		0x00 },
	{ SOU_TG1_HACTIVE_START_0,	0x1f },
	{ SOU_TG1_HACTIVE_START_1,	0x00 },

	{ SOU_TG1_HACTIVE_END_0,	0x9e },
	{ SOU_TG1_HACTIVE_END_1,	0x02 },
	{ SOU_TG1_LINES_PERV_0,		0x40 },
	{ SOU_TG1_LINES_PERV_1,		0x00 },

	{ SOU_TG1_VSYNC_START_LINE_0,	0x01 },
	{ SOU_TG1_VSYNC_START_LINE_1,	0x00 },
	{ SOU_TG1_VSYNC_END_LINE_0,	0x05 },
	{ SOU_TG1_VSYNC_END_LINE_1,	0x00 },

	{ SOU_TG1_VSYNC_START_CLK_0,	0x01 },
	{ SOU_TG1_VSYNC_START_CLK_1,	0x00 },
	{ SOU_TG1_VSYNC_END_CLK_0,	0x01 },
	{ SOU_TG1_VSYNC_END_CLK_1,	0x00 },

	{ SOU_TG1_VACTIVE_START_0,	0x01 },
	{ SOU_TG1_VACTIVE_START_1,      0x00 },
	{ SOU_TG1_VACTIVE_END_0,        0x40 },
	{ SOU_TG1_VACTIVE_END_1,        0x00 },

	{ SOU_TG0_CFG,			0x01 },
	{ SOU_TG1_CFG,			0x00 },
};
















void dvt_hside(void)
{
	unsigned char	loop;
	unsigned char	i;


	loop = sizeof(hside_tbl) / sizeof(struct regs_object);

	/* write */
	for (i=0; i<loop; i++) {
		__iow8(hside_tbl[i].address, hside_tbl[i].value);
	}

}



