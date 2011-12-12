/*
 * init/main.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stddef.h>
#include <stdio.h>
#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>
#include <regs_pio.h>
#include <regs_align.h>

#include <dvt.h>



void d2_init(void)
{
	SIMPORT(0xE0);

#if (CONFIG_FOSC < 48000000UL)
	__iow8(CLKSEL, 0x04);
#else
	__iow8(CLKSEL, 0x00);
#endif

	/*********************************************************************
	 * siu initial
	 ********************************************************************/
	SIMPORT(0xE1);
	printf("SIU initial\n");

	// initial ch0
	siu[0].x_ofs  = 0;
	siu[0].y_ofs  = 0;
	siu[0].width  = 640*2;
	siu[0].height = 480;
	siu[0].fb1    = 0x00200000;
	siu[0].fb2    = 0x00400000;
	siu[0].fb3    = 0x00600000;
	siu[0].jmp    = 640*2;

	// initial ch1
	siu[1].x_ofs  = 0;
	siu[1].y_ofs  = 0;
	siu[1].width  = 640*2;
	siu[1].height = 480;
	siu[1].fb1    = 0x00800000;
	siu[1].fb2    = 0x00a00000;
	siu[1].fb3    = 0x00c00000;
	siu[1].jmp    = 640*2;

	// initial ch0 mode, RAW8, VSYNC high active, HSYNC high active
	siu[0].cf1.b.scan    = 1;
	siu[0].cf1.b.format  = 0;
	siu[0].cf1.b.online  = 0;
	siu[0].cf1.b.raw8lsb = 1;

	siu[0].cf2.b.ext     = 0;
	siu[0].cf2.b.sync    = 0;
	siu[0].cf2.b.sedge   = 0;
	siu[0].cf2.b.hmode   = 0;

	// initial ch1 mode, RAW8, VSYNC high active, HSYNC high active
	siu[1].cf1.b.scan    = 1;
	siu[1].cf1.b.format  = 0;
	siu[1].cf1.b.online  = 0;
	siu[1].cf1.b.raw8lsb = 0;

	siu[1].cf2.b.ext     = 0;
	siu[1].cf2.b.sync    = 0;
	siu[1].cf2.b.sedge   = 0;
	siu[1].cf2.b.hmode   = 0;


	// write to hardware register
	siu_init();
	siu_startup();


	/*********************************************************************
	 * sou initial
	 ********************************************************************/
	SIMPORT(0xE2);
	printf("SOU initial\n");

	souc->polarity.b.hsync		= 0;
	souc->polarity.b.vsync		= 0;
	souc->polarity.b.href		= 0;
	souc->polarity.b.pclk		= 1;
	souc->blinkval			= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width			= __le16(640*2);
	sou0->height			= __le16(480);

	sou0->ppl			= __le16(858*2);
	sou0->hsync_start		= __le16(4);
	sou0->hsync_end			= __le16(68);
	sou0->hactive_start		= __le16(276);
	sou0->hactive_end		= __le16(276+640*2-1);

	sou0->lpf			= __le16(525);
	sou0->vsync_start_line		= __le16(1);
	sou0->vsync_start_clk		= __le16(1);
	sou0->vsync_end_line		= __le16(20);
	sou0->vsync_end_clk		= __le16(1);
	sou0->vactive_start		= __le16(21);
	sou0->vactive_end		= __le16(21+480/2);

	sou0->even_vsync_start_line	= __le16(264);
	sou0->even_vsync_start_clk	= __le16(1);
	sou0->even_vsync_end_line	= __le16(282);
	sou0->even_vsync_end_clk	= __le16(1);
	sou0->even_vactive_start	= __le16(283);
	sou0->even_vactive_end		= __le16(283+480/2-1);
	sou0->ccir656_f_start		= __le16(265);
	sou0->ccir656_f_end		= __le16(3);

	sou0->tstmode			= GREEN;
	sou0->mode			= 0;

	sou0->cfg.b.interlace		= 1;
	sou0->cfg.b.gateclk		= 0;
	sou0->cfg.b.enable		= 1;

	// initial TG1
	sou1->tstmode			= RED;
	sou1->mode			= 0;

	sou1->cfg.b.interlace		= 1;
	sou1->cfg.b.gateclk		= 0;
	sou1->cfg.b.enable		= 0;


	/*********************************************************************
	 * ipu initial
	 ********************************************************************/
	SIMPORT(0xE3);
	printf("IPU initial\n");

	// initial ch0
	ipui[0].width	= 640*2;
	ipui[0].height	= 480;
	ipui[0].jmp	= 640*2;

	ipui[0].crop	= 640*2;
	ipui[0].lstart	= 0;
	ipui[0].lend	= 30;

	ipui[0].fb1	= 0x00000000;
	ipui[0].fb2	= 0x00000000;
	ipui[0].fb3	= 0x00000000;

	//initial ch1
	ipui[1].width	= 640*2;
	ipui[1].height	= 480;
	ipui[1].jmp	= 640*2;

	ipui[1].crop	= 640*2;
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
	ipuc.cf1.b.format0	= 2;		// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 2;		// 0 = raw10, 1 = raw8, 2 = yuv

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

	SIMPORT(0xEF);
}

