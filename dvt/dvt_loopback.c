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
#include <stdio.h>

#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>

#include <dvt.h>



int dvt_lpbk_startup(void)
{
	SIMPORT(0xF0);

#if (CONFIG_FOSC < 48000000UL)
	__iow8(CLKSEL, 0x04);
#else
	__iow8(CLKSEL, 0x00);
#endif

	/*********************************************************************
	 * siu initial
	 ********************************************************************/
	SIMPORT(0xF1);
	printf("SIU initial\n");

	// initial ch0
	siu[0].x_ofs  = 20;
	siu[0].y_ofs  = 5;
	siu[0].width  = 640;
	siu[0].height = 480;
	siu[0].fb1    = 0x00200000;
	siu[0].fb2    = 0x00400000;
	siu[0].fb3    = 0x00600000;
	siu[0].jmp    = 640;

	// initial ch1
	siu[1].x_ofs  = 20;
	siu[1].y_ofs  = 5;
	siu[1].width  = 640;
	siu[1].height = 480;
	siu[1].fb1    = 0x00800000;
	siu[1].fb2    = 0x00a00000;
	siu[1].fb3    = 0x00c00000;
	siu[1].jmp    = 640;

	// initial ch0 mode, RAW8, VSYNC high active, HSYNC high active
	siu[0].cf1.b.scan   = 0;
	siu[0].cf1.b.format = 0;
	siu[0].cf1.b.online = 0;

	siu[0].cf2.b.ext    = 2;
	siu[0].cf2.b.sync   = 2;
	siu[0].cf2.b.sedge  = 0;
	siu[0].cf2.b.hmode  = 0;

	// initial ch1 mode, RAW8, VSYNC high active, HSYNC high active
	siu[1].cf1.b.scan   = 0;
	siu[1].cf1.b.format = 0;
	siu[1].cf1.b.online = 0;

	siu[1].cf2.b.ext    = 2;
	siu[1].cf2.b.sync   = 2;
	siu[1].cf2.b.sedge  = 0;
	siu[1].cf2.b.hmode  = 0;


	// write to hardware register
	siu_init();
	siu_startup();


	/*********************************************************************
	 * sou initial
	 ********************************************************************/
	SIMPORT(0xF2);
	printf("SOU initial\n");

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(640);
	sou0->height		= __le16(480);

	sou0->ppl		= __le16(700);
	sou0->hsync_start	= __le16(1);
	sou0->hsync_end		= __le16(20);
	sou0->hactive_start	= __le16(40);
	sou0->hactive_end	= __le16(640+40-1);

	sou0->lpf		= __le16(500);
	sou0->vsync_start_line	= __le16(1);
	sou0->vsync_start_clk	= __le16(1);
	sou0->vsync_end_line	= __le16(5);
	sou0->vsync_end_clk	= __le16(1);
	sou0->vactive_start	= __le16(10);
	sou0->vactive_end	= __le16(480+10-1);

	sou0->tstmode		= GREEN;
	sou0->mode		= 2;

	sou0->cfg.b.interlace	= 0;
	sou0->cfg.b.gateclk	= 1;
	sou0->cfg.b.enable	= 1;

	// initial TG1
	sou1->width		= __le16(640);
	sou1->height		= __le16(480);

	sou1->ppl		= __le16(700);
	sou1->hsync_start	= __le16(1);
	sou1->hsync_end		= __le16(20);
	sou1->hactive_start	= __le16(40);
	sou1->hactive_end	= __le16(640+40-1);

	sou1->lpf		= __le16(500);
	sou1->vsync_start_line	= __le16(1);
	sou1->vsync_start_clk	= __le16(1);
	sou1->vsync_end_line	= __le16(5);
	sou1->vsync_end_clk	= __le16(1);
	sou1->vactive_start	= __le16(10);
	sou1->vactive_end	= __le16(480+10-1);

	sou1->tstmode		= RED;
	sou1->mode		= 2;

	sou1->cfg.b.interlace	= 0;
	sou1->cfg.b.gateclk	= 1;
	sou1->cfg.b.enable	= 0;


	/*********************************************************************
	 * ipu initial
	 ********************************************************************/
	SIMPORT(0xF3);
	printf("IPU initial\n");

	// initial ch0
	ipui[0].width	= 640;
	ipui[0].height	= 480;
	ipui[0].jmp	= 640;

	ipui[0].crop	= 640;
	ipui[0].lstart	= 0;
	ipui[0].lend	= 30;

	ipui[0].fb1	= 0x00000000;
	ipui[0].fb2	= 0x00000000;
	ipui[0].fb3	= 0x00000000;

	//initial ch1
	ipui[1].width	= 640;
	ipui[1].height	= 480;
	ipui[1].jmp	= 640;

	ipui[1].crop	= 640;
	ipui[1].lstart	= 0;
	ipui[1].lend	= 30;

	ipui[1].fb1	= 0x00100000;
	ipui[1].fb2	= 0x00100000;
	ipui[1].fb3	= 0x00100000;
	ipui_init();

	ipuc.cf4.b.r_pos	= 0;
	ipuc.cf4.b.gr_pos	= 0;
	ipuc.cf4.b.gb_pos	= 0;
	ipuc.cf4.b.b_pos	= 0;
	ipuc.cf4.b.hdr		= 0;
	ipuc.cf4.b.clamp_sel	= 0;

	ipuc.cf56.b.fussy_factor = 16;
	ipuc.cf56.b.fussy_hold	 = 0;
	ipuc.overlap		 = 128;

	ipuc.cf1.b.order0	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;		// 0 = channel indepent
						// 1 = horizontal side by side
						// 2 = vertical side by side
						// 3 = fussy stitch
						// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	ipuc.cf2.b.in_sel1	= 0;		// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;		// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;		// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;		// 1 = co-work mode

	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc_startup();

	SIMPORT(0xFF);
	return 0;
}

