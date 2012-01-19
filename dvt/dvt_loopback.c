/*
 * dvt/dvt_loopback.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
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

#if (!CONFIG_VLSI_SIMULATION)
# define msg		printf
#else
# define msg		//
#endif

static __code const char	*mode_string[] = {
	"RAW8",
	"RAW10",
	"CCIR-656i",
	"CCIR-656p",
	"multi-channel progressive single edge",
	"multi-channel progressive double edge",
	"multi-channel interlace single edge",
	"multi-channel interlace double edge"
};

static __code const char	*siu_string  = { "SIU %s Initial\n" };
static __code const char	*ipu_string  = { "IPU %s Initial\n" };
static __code const char	*sou_string  = { "SOU %s Initial\n" };
static __code const char	*done_string = { "Done ...\n" };
static __code const char	*lpbk_info   = {
	"\n" \
	"IPU(CH0)->SOU->SIU(CH0) loopback %s mode test\n" \
	"   [IPU] frame buffer:\n" \
	"      <CH0>: fb1 = 0x00000000, fb2 = 0x00000000, fb3 = 0x00000000\n" \
	"      <CH1>: fb1 = 0x00100000, fb2 = 0x00100000, fb3 = 0x00100000\n" \
	"\n" \
	"   [SIU] frame buffer:\n" \
	"      <CH0>: fb1 = 0x00200000, fb2 = 0x00400000, fb3 = 0x00600000\n" \
	"      <CH1>: fb1 = 0x00800000, fb2 = 0x00a00000, fb3 = 0x00c00000\n" \
};


/*
 *****************************************************************************
 *
 * STOP Mode
 *
 *****************************************************************************
 */
int dvt_lpbk_stop(void)
{
	siu_stop();
	sou_stop();
	ipuc_stop();

	return 0;
}


/*
 *****************************************************************************
 *
 * RAW8 Mode
 *
 *****************************************************************************
 */
int dvt_lpbk_raw8(void)
{
	SIMPORT(0xF0);

	__iow8(0x0027, 0x41);
	msg(lpbk_info, mode_string[0]);

	/*
	 * SIU initial
	 */
	SIMPORT(0xF1);
	msg(siu_string, mode_string[0]);

	// initial ch0
	siu[0].x_ofs		= 20;
	siu[0].y_ofs		= 5;
	siu[0].width		= 640;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 640;

	// initial ch1
	siu[1].x_ofs		= 20;
	siu[1].y_ofs		= 5;
	siu[1].width		= 640;
	siu[1].height		= 480;
	siu[1].fb1		= 0x00800000;
	siu[1].fb2		= 0x00a00000;
	siu[1].fb3		= 0x00c00000;
	siu[1].jmp		= 640;

	// initial ch0 mode, RAW8, VSYNC high active, HSYNC high active
	siu[0].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[0].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[0].cf1.b.online	= 0;
	siu[0].cf1.b.raw8lsb	= 1;

	siu[0].cf2.b.ext	= 2;
	siu[0].cf2.b.sync	= 2;
	siu[0].cf2.b.sedge	= 0;
	siu[0].cf2.b.hmode	= 0;

	// initial ch1 mode, RAW8, VSYNC high active, HSYNC high active
	siu[1].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 1;

	siu[1].cf2.b.ext	= 2;
	siu[1].cf2.b.sync	= 2;
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
	siu_startup(0);


	/*
	 * SOU initial
	 */
	SIMPORT(0xF2);
	msg(sou_string, mode_string[0]);

	__iow8(SOUCLK, 0x03);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->multich		= 0;			// enable channel 0 only
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
	sou0->mode		= 2;		// 0=ccir656, 1=ccir601, 2=raw8, 3=raw10

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
	sou1->mode		= 2;		// 0=ccir656, 1=ccir601, 2=raw8, 3=raw10

	sou1->cfg.b.interlace	= 0;
	sou1->cfg.b.gateclk	= 1;
	sou1->cfg.b.enable	= 0;


	/*
	 * IPU initial
	 */
	SIMPORT(0xF3);
	msg(ipu_string, mode_string[0]);

	// initial ch0
	ipui[0].width		= 640;
	ipui[0].height		= 480;
	ipui[0].jmp		= 640;

	ipui[0].crop		= 640;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0x00000000;
	ipui[0].fb2		= 0x00000000;
	ipui[0].fb3		= 0x00000000;

	//initial ch1
	ipui[1].width		= 640;
	ipui[1].height		= 480;
	ipui[1].jmp		= 640;

	ipui[1].crop		= 640;
	ipui[1].lstart		= 0;
	ipui[1].lend		= 30;

	ipui[1].fb1		= 0x00100000;
	ipui[1].fb2		= 0x00100000;
	ipui[1].fb3		= 0x00100000;
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

	ipuc.cf1.b.order0	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 1;	// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 1;	// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;	// 0 = channel indepent
					// 1 = horizontal side by side
					// 2 = vertical side by side
					// 3 = fussy stitch
					// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	ipuc.cf2.b.in_sel1	= 0;	// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;	// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;	// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;	// 1 = co-work mode

	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc.ctrl.b.stchu0en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu1en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu0mode	= 0;	// 1 = stitch mode
	ipuc.ctrl.b.stchu1mode	= 0;	// 1 = stitch mode
	ipuc_startup();

	SIMPORT(0xFF);
	msg(done_string);
	return 0;
}


/*
 *****************************************************************************
 *
 * CCIR-656 Mode Interlace
 *
 *****************************************************************************
 */
int dvt_lpbk_ccir656i(void)
{
	SIMPORT(0xE0);

	__iow8(0x0027, 0x41);

	/*
	 * SIU initial
	 */
	SIMPORT(0xE1);
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


	/*
	 * SOU initial for interlace
	 */
	SIMPORT(0xE2);
	msg(sou_string, mode_string[2]);

	__iow8(SOUCLK, 0x03);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->multich		= 0;			// enable channel 0 only
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(640*2);
	sou0->height		= __le16(480);

	sou0->ppl		= __le16(858*2);
	sou0->hsync_start	= __le16(2*2);
	sou0->hsync_end		= __le16(34*2);
	sou0->hactive_start	= __le16(138*2);
	sou0->hactive_end	= __le16(138*2+640*2-1);

	sou0->lpf		= __le16(525);
	sou0->vsync_start_line	= __le16(1);
	sou0->vsync_start_clk	= __le16(1);
	sou0->vsync_end_line	= __le16(20);
	sou0->vsync_end_clk	= __le16(1);
	sou0->vactive_start	= __le16(21);
	sou0->vactive_end	= __le16(21+480/2-1);

	sou0->even_vsync_start_line	= __le16(264);
	sou0->even_vsync_start_clk	= __le16(1);
	sou0->even_vsync_end_line	= __le16(282);
	sou0->even_vsync_end_clk	= __le16(1);
	sou0->even_vactive_start	= __le16(283);
	sou0->even_vactive_end		= __le16(283+480/2-1);
	sou0->ccir656_f_start		= __le16(265);
	sou0->ccir656_f_end		= __le16(3);

	sou0->tstmode		= GREEN;
	sou0->mode		= 0;

	sou0->cfg.b.interlace	= 1;
	sou0->cfg.b.gateclk	= 0;
	sou0->cfg.b.enable	= 1;

	// initial TG1
	sou1->tstmode		= RED;
	sou1->mode		= 0;

	sou1->cfg.b.interlace	= 1;
	sou1->cfg.b.gateclk	= 0;
	sou1->cfg.b.enable	= 0;


	/*
	 * IPU initial
	 */
	SIMPORT(0xE3);
	msg(ipu_string, mode_string[2]);

	// initial ch0
	ipui[0].width		= 640*2;
	ipui[0].height		= 480;
	ipui[0].jmp		= 640*2;

	ipui[0].crop		= 640*2;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0x00000000;
	ipui[0].fb2		= 0x00000000;
	ipui[0].fb3		= 0x00000000;

	//initial ch1
	ipui[1].width		= 640*2;
	ipui[1].height		= 480;
	ipui[1].jmp		= 640*2;

	ipui[1].crop		= 640*2;
	ipui[1].lstart		= 0;
	ipui[1].lend		= 30;

	ipui[1].fb1		= 0x00100000;
	ipui[1].fb2		= 0x00100000;
	ipui[1].fb3		= 0x00100000;
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

	ipuc.cf1.b.order0	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;	// 0 = channel indepent
					// 1 = horizontal side by side
					// 2 = vertical side by side
					// 3 = fussy stitch
					// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	ipuc.cf2.b.in_sel1	= 0;	// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;	// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;	// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;	// 1 = co-work mode

	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc.ctrl.b.stchu0en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu1en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu0mode	= 0;	// 1 = stitch mode
	ipuc.ctrl.b.stchu1mode	= 0;	// 1 = stitch mode
	ipuc_startup();

	SIMPORT(0xEF);
	msg(done_string);
	return 0;
}


/*
 *****************************************************************************
 *
 * CCIR-656 Mode Progressive
 *
 *****************************************************************************
 */
int dvt_lpbk_ccir656p(void)
{
	SIMPORT(0xD0);

	__iow8(0x0027, 0x41);

	/*
	 * SIU initial
	 */
	SIMPORT(0xD1);
	msg(siu_string, mode_string[3]);

	// initial ch0
	siu[0].x_ofs		= 0;
	siu[0].y_ofs		= 0;
	siu[0].width		= 640*2;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 640*2;

	siu[0].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[0].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[0].cf1.b.online	= 0;
	siu[0].cf1.b.raw8lsb	= 0;

	siu[0].cf2.b.ext	= 0;	// VSYNC high active, HSYNC high active
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

	siu[1].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 0;

	siu[1].cf2.b.ext	= 0;	// VSYNC high active, HSYNC high active
	siu[1].cf2.b.sync	= 0;
	siu[1].cf2.b.sedge	= 0;
	siu[1].cf2.b.hmode	= 0;

	siuc.cf6.b.progressive0 = 1;	// 1 = progressive, 0 = interlace
	siuc.cf6.b.progressive1	= 1;
	siuc.cf6.b.single0	= 0;	// 1 = single capture
	siuc.cf6.b.single1	= 0;
	siuc.cf6.b.parser_en	= 0;	// 1 = enable
	siuc.cf6.b.parser_chsel	= 0;	// 1 = channel 1, 0 = channel 0
	siuc.cf6.b.parser_rst	= 0;	// 0 = reset

	// write to hardware register
	siu_init();
	siu_startup(1);


	/*
	 * SOU initial for interlace
	 */
	SIMPORT(0xD2);
	msg(sou_string, mode_string[3]);

	__iow8(SOUCLK, 0x01);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->multich		= 0;			// enable channel 0 only
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(640*2);
	sou0->height		= __le16(480);

	sou0->ppl		= __le16(858*2);
	sou0->hsync_start	= __le16(2*2);
	sou0->hsync_end		= __le16(34*2);
	sou0->hactive_start	= __le16(138*2);
	sou0->hactive_end	= __le16(138*2+640*2-1);

	sou0->lpf		= __le16(525);
	sou0->vsync_start_line	= __le16(1);
	sou0->vsync_start_clk	= __le16(1);
	sou0->vsync_end_line	= __le16(20);
	sou0->vsync_end_clk	= __le16(1);
	sou0->vactive_start	= __le16(21);
	sou0->vactive_end	= __le16(21+480-1);

	sou0->ccir656_f_start	= __le16(265);
	sou0->ccir656_f_end	= __le16(3);

	sou0->tstmode		= GREEN;
	sou0->mode		= 0;

	sou0->cfg.b.interlace	= 0;
	sou0->cfg.b.gateclk	= 0;
	sou0->cfg.b.enable	= 1;

	// initial TG1
	sou1->tstmode		= RED;
	sou1->mode		= 0;

	sou1->cfg.b.interlace	= 0;
	sou1->cfg.b.gateclk	= 0;
	sou1->cfg.b.enable	= 0;

	/*
	 * IPU initial
	 */
	SIMPORT(0xD3);
	msg(ipu_string, mode_string[3]);

	// initial ch0
	ipui[0].width		= 640*2;
	ipui[0].height		= 480;
	ipui[0].jmp		= 640*2;

	ipui[0].crop		= 640*2;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0x00000000;
	ipui[0].fb2		= 0x00000000;
	ipui[0].fb3		= 0x00000000;

	//initial ch1
	ipui[1].width		= 640*2;
	ipui[1].height		= 480;
	ipui[1].jmp		= 640*2;

	ipui[1].crop		= 640*2;
	ipui[1].lstart		= 0;
	ipui[1].lend		= 30;

	ipui[1].fb1		= 0x00100000;
	ipui[1].fb2		= 0x00100000;
	ipui[1].fb3		= 0x00100000;
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

	ipuc.cf1.b.order0	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;	// 0 = channel indepent
					// 1 = horizontal side by side
					// 2 = vertical side by side
					// 3 = fussy stitch
					// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	ipuc.cf2.b.in_sel1	= 0;	// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;	// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;	// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;	// 1 = co-work mode

	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc.ctrl.b.stchu0en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu1en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu0mode	= 0;	// 1 = stitch mode
	ipuc.ctrl.b.stchu1mode	= 0;	// 1 = stitch mode
	ipuc_startup();

	SIMPORT(0xDF);
	msg(done_string);
	return 0;
}


/*
 *****************************************************************************
 *
 * Multi-channel CCIR-656 Mode
 *
 *****************************************************************************
 */
#define msg_multich(s) \
	if (scan == 'p') { \
		msg(s, mode_string[((edge == 's') ? 4 : 5)]); \
	} else { \
		msg(s, mode_string[((edge == 's') ? 6 : 7)]); \
	}

int dvt_lpbk_multich(char scan, char edge)
{
	SIMPORT(0xC0);

	__iow8(0x0027, 0x41);

	msg_multich(lpbk_info);

	/*
	 * SIU initial
	 */
	SIMPORT(0xC1);
	msg_multich(siu_string);

	// initial ch0
	siu[0].x_ofs		= 0;
	siu[0].y_ofs		= 0;
	siu[0].width		= 640*2;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 640*2;

	siu[0].cf1.b.scan	= (scan == 'p') ? 0 : 1;	// 0 = progressive, 1 = interlace write
	siu[0].cf1.b.format	= 0;				// 0 = raw8/yuv,    1 = raw10
	siu[0].cf1.b.online	= 0;
	siu[0].cf1.b.raw8lsb	= 0;

	siu[0].cf2.b.ext	= (edge == 's') ? 0x0c : 0x04;
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

	siu[1].cf1.b.scan	= (scan == 'p') ? 0 : 1;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;				// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 0;

	siu[1].cf2.b.ext	= (edge == 's') ? 0x0c : 0x04;
	siu[1].cf2.b.sync	= 0;
	siu[1].cf2.b.sedge	= 0;
	siu[1].cf2.b.hmode	= 0;

	siuc.cf6.b.progressive0 = (scan == 'p') ? 1 : 0;	// 1 = progressive, 0 = interlace
	siuc.cf6.b.progressive1	= 1;
	siuc.cf6.b.single0	= 0;	// 1 = single capture
	siuc.cf6.b.single1	= 0;
	siuc.cf6.b.parser_en	= 1;	// 1 = enable
	siuc.cf6.b.parser_chsel	= 0;	// 1 = channel 1, 0 = channel 0
	siuc.cf6.b.parser_rst	= 0;	// 0 = reset

	// write to hardware register
	siu_init();
	siu_startup(1);

	/*
	 * SOU initial
	 */
	SIMPORT(0xC2);
	msg_multich(sou_string);

	__iow8(SOUCLK, ((edge == 's') ? 0x83 : 0x03));

	souc->polarity.b.hsync		= 0;
	souc->polarity.b.vsync		= 0;
	souc->polarity.b.href		= 0;
	souc->polarity.b.pclk		= 1;
	souc->multich			= 2;			// enable multi-channel
	souc->blinkval			= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width			= __le16(640*2);
	sou0->height			= __le16(480);

	sou0->ppl			= __le16(858*2);
	sou0->hsync_start		= __le16(2*2);
	sou0->hsync_end			= __le16(34*2);
	sou0->hactive_start		= __le16(138*2);
	sou0->hactive_end		= __le16(138*2+640*2-1);

	sou0->lpf			= __le16(525);
	sou0->vsync_start_line		= __le16(1);
	sou0->vsync_start_clk		= __le16(1);
	sou0->vsync_end_line		= __le16(20);
	sou0->vsync_end_clk		= __le16(1);
	sou0->vactive_start		= __le16(21);
	sou0->vactive_end		= (scan == 'p') ? __le16(21+480-1) : __le16(21+480/2-1);

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

	sou0->cfg.b.interlace		= (scan == 'p') ? 0 : 1;
	sou0->cfg.b.gateclk		= 0;
	sou0->cfg.b.enable		= 1;

	// initial TG1
	sou1->width			= __le16(640*2);
	sou1->height			= __le16(480);

	sou1->ppl			= __le16(858*2);
	sou1->hsync_start		= __le16(2*2);
	sou1->hsync_end			= __le16(34*2);
	sou1->hactive_start		= __le16(138*2);
	sou1->hactive_end		= __le16(138*2+640*2-1);

	sou1->lpf			= __le16(525);
	sou1->vsync_start_line		= __le16(1);
	sou1->vsync_start_clk		= __le16(1);
	sou1->vsync_end_line		= __le16(20);
	sou1->vsync_end_clk		= __le16(1);
	sou1->vactive_start		= __le16(21);
	sou1->vactive_end		= (scan == 'p') ? __le16(21+480-1) : __le16(21+480/2-1);

	sou1->even_vsync_start_line	= __le16(264);
	sou1->even_vsync_start_clk	= __le16(1);
	sou1->even_vsync_end_line	= __le16(282);
	sou1->even_vsync_end_clk	= __le16(1);
	sou1->even_vactive_start	= __le16(283);
	sou1->even_vactive_end		= __le16(283+480/2-1);
	sou1->ccir656_f_start		= __le16(265);
	sou1->ccir656_f_end		= __le16(3);

	sou1->tstmode			= RED;
	sou1->mode			= 0;

	sou1->cfg.b.interlace		= (scan == 'p') ? 0 : 1;
	sou1->cfg.b.gateclk		= 0;
	sou1->cfg.b.enable		= 1;

	/*
	 * IPU initial
	 */
	SIMPORT(0xC3);
	msg_multich(ipu_string);

	// initial ch0
	ipui[0].width		= 640*2;
	ipui[0].height		= 480;
	ipui[0].jmp		= 640*2;

	ipui[0].crop		= 640*2;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0x00000000;
	ipui[0].fb2		= 0x00000000;
	ipui[0].fb3		= 0x00000000;

	//initial ch1
	ipui[1].width		= 640*2;
	ipui[1].height		= 480;
	ipui[1].jmp		= 640*2;

	ipui[1].crop		= 640*2;
	ipui[1].lstart		= 0;
	ipui[1].lend		= 30;

	ipui[1].fb1		= 0x00000000;
	ipui[1].fb2		= 0x00000000;
	ipui[1].fb3		= 0x00000000;
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

	ipuc.cf1.b.order0	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;	// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 2;	// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;	// 0 = channel indepent
					// 1 = horizontal side by side
					// 2 = vertical side by side
					// 3 = fussy stitch
					// 4 = red cyan stitch
	ipuc.cf3.b.online	= 0;
	ipuc.cf3.b.out_sel	= 0;
	ipuc.cf3.b.half_side	= 0;

	ipuc.cf2.b.in_sel1	= 0;	// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;	// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;	// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;	// 1 = co-work mode

	ipuc.ctrl.b.stdalone0	= 1;
	ipuc.ctrl.b.stdalone1	= 1;
	ipuc.ctrl.b.online0	= 0;
	ipuc.ctrl.b.online1	= 0;
	ipuc.ctrl.b.stchu0en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu1en	= 0;	// 0 = disable, 1 = enable
	ipuc.ctrl.b.stchu0mode	= 0;	// 1 = stitch mode
	ipuc.ctrl.b.stchu1mode	= 0;	// 1 = stitch mode
	ipuc_startup();

	SIMPORT(0xCF);
	return 0;
}

