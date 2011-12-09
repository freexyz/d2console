/*
 * dvt/dvt_loopback.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.09	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */

#include <stddef.h>
#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>
#include <regs_pio.h>
#include <regs_align.h>

#include <dvt.h>

#define SIU_FIRST		1


void d2_init(void)
{
	__iow8(CLKSEL, 0x00);

#if (SIU_FIRST == 1)
	/*
	 * siu initial
	 */
	SIMPORT(0x13);
	// initial ch0
	siu_set_fb(CH0, 0x00200000, 0x00400000, 0x00600000);
	siu_set_szjmp(CH0, 640, 480, 640);
	siu_set_xyoffset(CH0, 20, 5);

	// initial ch1
	siu_set_fb(CH1, 0x00800000, 0x00a00000, 0x00c00000);
	siu_set_szjmp(CH1, 640, 480, 640);
	siu_set_xyoffset(CH1, 20, 5);

	// initial ch0 & ch1 mode, RAW8, VSYNC high active, HSYNC high active
	siu_set_mode(BOTH, 0x22);
	siu_startup();
#endif

	/*
	 * sou initial
	 */
	SIMPORT(0x11);
//	__iow8(SOU_TG0_TMODE,	   0x03);
//	__iow8(SOU_ENCODER_0_MODE, 0x02);
//	__iow16(SOU_TG0_WIDTH_0,   640*2);
//	__iow16(SOU_TG0_WIDTH_0,   640);
//	__iow16(SOU_TG0_HEIGHT_0,  480);
//	__iow8(SOU_TG0_CFG,	   0x01);

/*
	normal_write(16'h41b, 8'h10);	// SOU_TG_0_Clks_PerH_0
	normal_write(16'h41c, 8'h05);	// SOU_TG_0_Clks_PerH_1
	normal_write(16'h423, 8'h0f);
	normal_write(16'h424, 8'h05);
	normal_write(16'h400, 8'h08);	// SOU_Clk_Inverse
	normal_write(16'h41a, 8'h03);
	normal_write(16'h410, 8'h02);
	normal_write(16'h412, 8'h80);	// SOU_TG_0_Width_0
	normal_write(16'h413, 8'h04);	// SOU_TG_0_Width_1
	normal_write(16'h414, 8'he0);	// 00
	normal_write(16'h415, 8'h01);	// 05
	normal_write(16'h411, 8'h05); 
*/
	sou_set_ppl(TG0, 700, 640, 20, 20);
	sou_set_lpf(TG0, 500, 480, 5, 5);

	__iow8(SOU_POLARITY,		0x08);		// SOU_Clk_Inverse
	__iow8(SOU_TG0_TMODE,		0x03);
	__iow8(SOU_ENCODER_0_MODE,	0x02);

	__iow16(SOU_TG0_WIDTH_0,	640);	// SOU_TG_0_Width_0, SOU_TG_0_Width_1
	__iow16(SOU_TG0_HEIGHT_0,	480);
	__iow8(SOU_TG0_CFG,		0x05);

	/*
	 * ipu initial
	 */
	SIMPORT(0x12);
	// initial ch0
	ipu_set_fb(CH0, 0x00000000, 0x00000000, 0x00000000);
	ipu_set_xyjmp(CH0, 640, 480, 640);
	ipu_set_crop(CH0, 640, 0, 30);

	//initial ch1
	ipu_set_fb(CH1, 0x00100000, 0x00100000, 0x00100000);
	ipu_set_xyjmp(CH1, 640, 480, 640);
	ipu_set_crop(CH1, 640, 0, 30);

	ipu_set_format(0x50);			// raw8

//	ipu_set_cowork(0x30);			// co-work
	ipu_set_cowork(0);			// no co-work
//	ipu_set_opmode(0x02, 0x10, 0x80);	// 2: h side by side, 6: fussy
	ipu_set_opmode(0x00, 0x10, 0x80);	// channel indepent

	ipu_startup(STANDALONE);



#if (SIU_FIRST == 0)
	/*
	 * siu initial
	 */
	SIMPORT(0x13);
	// initial ch0
	siu_set_fb(CH0, 0x00200000, 0x00400000, 0x00600000);
	siu_set_szjmp(CH0, 640, 480, 640);
	siu_set_xyoffset(CH0, 20, 5);

	// initial ch1
	siu_set_fb(CH1, 0x00800000, 0x00a00000, 0x00c00000);
	siu_set_szjmp(CH1, 640, 480, 640);
	siu_set_xyoffset(CH1, 20, 5);

	// initial ch0 & ch1 mode, RAW8, VSYNC high active, HSYNC high active
	siu_set_mode(BOTH, 0x22);
	siu_startup();
#endif

	SIMPORT(0x1F);
}

