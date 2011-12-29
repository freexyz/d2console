/* dvt/dvt_siu.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.27	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <stddef.h>
#include <stdio.h>

#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>
#include <regs_align.h>

#include <dvt.h>


int dvt_siu_ccir656i(void)
{
	SIMPORT(0x50);

	__iow8(0x0027, 0x01);

	/*
	 * SIU initial
	 */
	SIMPORT(0x51);
	msg(siu_string, mode_string[2]);

	// initial ch0
	siu[0].x_ofs		= 0;
	siu[0].y_ofs		= 0;
	siu[0].width		= 640*2;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 640*2;

	siu[0].cf1.b.scan	= 1;	// 0 = progressive, 1 = interlace write
	siu[0].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[0].cf1.b.online	= 0;
	siu[0].cf1.b.raw8lsb	= 0;

	siu[0].cf2.b.ext	= 0;	// 
	siu[0].cf2.b.sync	= 0;
	siu[0].cf2.b.sedge	= 0;
	siu[0].cf2.b.hmode	= 0;

	// initial ch1
	siu[1].x_ofs		= 0;
	siu[1].y_ofs		= 0;
	siu[1].width		= 640*2;
	siu[1].height		= 480;
	siu[1].fb1		= 0x00800000;
	siu[1].fb2		= 0x00a00000;
	siu[1].fb3		= 0x00c00000;
	siu[1].jmp		= 640*2;

	siu[1].cf1.b.scan	= 1;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 0;

	siu[1].cf2.b.ext	= 0;	//
	siu[1].cf2.b.sync	= 0;
	siu[1].cf2.b.sedge	= 0;
	siu[1].cf2.b.hmode	= 0;

	siuc.cf6.b.progressive0 = 0;	// 1 = progressive, 0 = interlace
	siuc.cf6.b.progressive1	= 0;
	siuc.cf6.b.single0	= 0;	// 1 = single capture
	siuc.cf6.b.single1	= 0;
	siuc.cf6.b.parser_en	= 0;	// 1 = enable
	siuc.cf6.b.parser_chsel	= 0;	// 1 = channel 1, 0 = channel 0

	// write to hardware register
	siu_init();
	siu_startup(1);


	SIMPORT(0x5F);
	msg(done_string);
	return 0;
}

