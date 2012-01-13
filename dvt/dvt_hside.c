/*
 * dvt/dvt_hside.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
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


#if (!CONFIG_VLSI_SIMULATION)
# define msg		printf
#else
# define msg		//
#endif


int dvt_hside(void)
{
	SIMPORT(0x60);

	__iow8(0x0027, 0x41);
	msg("hside initial start...\n");

	/*
	 * SIU initial
	 */
	SIMPORT(0x61);

	// initial ch0
	siu[0].x_ofs		= 0;
	siu[0].y_ofs		= 0;
	siu[0].width		= 640;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 640;

	siu[0].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[0].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[0].cf1.b.online	= 0;
	siu[0].cf1.b.raw8lsb	= 0;

	siu[0].cf2.b.ext	= 2;
	siu[0].cf2.b.sync	= 2;
	siu[0].cf2.b.sedge	= 0;
	siu[0].cf2.b.hmode	= 0;

	// initial ch1
	siu[1].x_ofs		= 0;
	siu[1].y_ofs		= 0;
	siu[1].width		= 640;
	siu[1].height		= 480;
	siu[1].fb1		= 0x00800000;
	siu[1].fb2		= 0x00a00000;
	siu[1].fb3		= 0x00c00000;
	siu[1].jmp		= 640;

	siu[1].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 0;

	siu[1].cf2.b.ext	= 2;	// VSYNC high active, HSYNC high active
	siu[1].cf2.b.sync	= 2;
	siu[1].cf2.b.sedge	= 0;
	siu[1].cf2.b.hmode	= 0;


	siuc.cf6.b.progressive0	= 0;	// 1 = progressive, 0 = interlace
	siuc.cf6.b.progressive1	= 0;
	siuc.cf6.b.single0	= 0;	// 1 = single capture
	siuc.cf6.b.single1	= 0;
	siuc.cf6.b.parser_en	= 0;	// 1 = enable
	siuc.cf6.b.parser_chsel	= 0;	// 1 = channel 1, 0 = channel 0
	siuc.cf6.b.parser_rst	= 0;	// 0 = reset

	// write to hardware register
//	siu_init();
//	siu_startup();


	/*
	 * SOU initial for interlace
	 */
	SIMPORT(0x62);

	__iow8(SOUCLK, 0x03);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->multich		= 0;			// enable channel 0 only
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(8000*2);
	sou0->height		= __le16(4);

	sou0->ppl		= __le16(8100*2);
	sou0->hsync_start	= __le16(2);
	sou0->hsync_end		= __le16(34);
	sou0->hactive_start	= __le16(138);
	sou0->hactive_end	= __le16(138+8000*2-1);

	sou0->lpf		= __le16(525);
	sou0->vsync_start_line	= __le16(1);
	sou0->vsync_start_clk	= __le16(1);
	sou0->vsync_end_line	= __le16(20);
	sou0->vsync_end_clk	= __le16(1);
	sou0->vactive_start	= __le16(21);
	sou0->vactive_end	= __le16(21+4-1);

	sou0->ccir656_f_start	= __le16(265);
	sou0->ccir656_f_end	= __le16(3);

	sou0->tstmode		= GREEN;
	sou0->mode		= 2;		// 0=ccir656, 1=ccir601, 2=raw8, 3=raw10

	sou0->cfg.b.interlace	= 0;
	sou0->cfg.b.gateclk	= 1;
	sou0->cfg.b.enable	= 1;

	// initial TG1
	sou1->tstmode		= RED;
	sou1->mode		= 2;		// 0=ccir656, 1=ccir601, 2=raw8, 3=raw10

	sou1->cfg.b.interlace	= 0;
	sou1->cfg.b.gateclk	= 1;
	sou1->cfg.b.enable	= 0;


	/*
	 * IPU initial
	 */
	SIMPORT(0x63);

	// flush DFU cache
	__iow8(0x032f, 0x20);
	__iow8(0x032f, 0x00);

	// ch0 frame addr
	ipui[0].width		= 8000;
	ipui[0].height		= 4;
	ipui[0].jmp		= 8000;

	ipui[0].crop		= 8000;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0;
	ipui[0].fb2		= 0;
	ipui[0].fb3		= 0;

	// ch1 frame addr
	ipui[1].width		= 8000;
	ipui[1].height		= 4;
	ipui[1].jmp		= 8000;

	ipui[1].crop		= 8000;
	ipui[1].lstart		= 0;
	ipui[1].lend		= 30;

	ipui[1].fb1		= 8000;
	ipui[1].fb2		= 8000;
	ipui[1].fb3		= 8000;
	ipui_init();

	ipuc.cf4.b.r_pos	= 0;
	ipuc.cf4.b.gr_pos	= 0;
	ipuc.cf4.b.gb_pos	= 0;
	ipuc.cf4.b.b_pos	= 0;
	ipuc.cf4.b.hdr		= 0;
	ipuc.cf4.b.clamp_sel	= 0;

	ipuc.cf56.b.fussy_factor = 16;
	ipuc.cf56.b.fussy_hold	 = 0;
	ipuc.overlap		 = 0;

	ipuc.cf1.b.order0	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf2.b.in_sel1	= 0;		// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;		// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;		// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;		// 1 = co-work mode

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 1;		// 0 = channel indepent
						// 1 = horizontal side by side
						// 2 = vertical side by side
						// 3 = fussy stitch
						// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	// set channel0 stchu PMU table
	__iow32(IPU_PMUTBL0, 0x00c00000);

	// set channel1 stchu PMU table
	__iow32(IPU_PMUTBL1, 0x00c00000);

	// enable & set stchu
	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc.ctrl.b.stchu0en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu1en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu0mode	= 0;	// 1 = stitch mode
	ipuc.ctrl.b.stchu1mode	= 0;	// 1 = stitch mode
	ipuc_startup();

	msg("hside initial done...\n");

	SIMPORT(0x6F);
	return 0;
}



