/* dvt_aalign.c -- Design Verification Test for Auto Align module
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.20	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */
#include <stddef.h>
#include <stdio.h>
#include <absacc.h>

#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>
#include <regs_align.h>

#include <dvt.h>

#if (CONFIG_ALIGN)

#if (!CONFIG_VLSI_SIMULATION)
# define msg		printf
#else
# define msg		//
#endif


/*
 *****************************************************************************
 *
 * Wait for VSYNC
 *
 *****************************************************************************
 */
void dvt_wait_vsync(unsigned char n)
{
#if (CONFIG_VLSI_SIMULATION == 0)
	unsigned char	state = 0;
	unsigned char	i     = 0;


	while (1) {
		switch (state) {
		case 0:
			if (!(__ior8(SIU_CTRL) & 0x10))
				state = 1;
			break;
		case 1:
			if (__ior8(SIU_CTRL) & 0x10)
				state = 2;
			break;
		case 2:
			msg("   get VSYNC=%02d\n", (int) i);
			i++;
			state = 0;
			break;
		}
		if (i >= n) {
			break;
		}
	}
#endif
}


/*
 *****************************************************************************
 *
 * Auto-Align
 *
 *****************************************************************************
 */
int dvt_align(void)
{
	int		i;


	SIMPORT(0x90);

	__iow8(0x0027, 0xC1);
	msg("auto-align initialize...\n");

	/*
	 * Auti-Align initial
	 */
	SIMPORT(0x95);
	align->ram.v		= 0;
	align->ram_addr		= 0;

	align->scale		= 0;

	align->cfg2.b.ch_id	= 0;		// 
	align->cfg2.b.raw	= 1;
	align->cfg2.b.samplex4	= 1;

	align->x_64x64		= __le16(9);	// channel 0
	align->y_64x64		= __le16(4);
	align->x_128x64		= __le16(5);	// channel 1
	align->y_128x64		= __le16(2);

	align->update		= 1;
	align->update		= 0;

	align->cfg.b.trigger	= 1;
	align->cfg.b.trigger	= 0;


	/*
	 * SIU initial
	 */
	SIMPORT(0x91);

	// initial ch0
	siu[0].x_ofs		= 104;
	siu[0].y_ofs		= 1;
	siu[0].width		= 640;
	siu[0].height		= 150;
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
	siu[1].x_ofs		= 104;
	siu[1].y_ofs		= 151;
	siu[1].width		= 640;
	siu[1].height		= 150;
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
	siu_init();
	siu_startup(0);


	/*
	 * SOU initial for interlace
	 */
	SIMPORT(0x92);

	__iow8(SOUCLK, 0x03);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->multich		= 0;			// enable channel 0 only
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(640);
	sou0->height		= __le16(300);

	sou0->ppl		= __le16(858);
	sou0->hsync_start	= __le16(2);
	sou0->hsync_end		= __le16(34);
	sou0->hactive_start	= __le16(138);
	sou0->hactive_end	= __le16(138+640-1);

	sou0->lpf		= __le16(525);
	sou0->vsync_start_line	= __le16(1);
	sou0->vsync_start_clk	= __le16(1);
	sou0->vsync_end_line	= __le16(20);
	sou0->vsync_end_clk	= __le16(1);
	sou0->vactive_start	= __le16(21);
	sou0->vactive_end	= __le16(21+300-1);

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
	SIMPORT(0x93);

	// flush DFU cache
	__iow8(0x032f, 0x20);
	__iow8(0x032f, 0x00);

	// ch0 frame addr
	ipui[0].width		= 640;
	ipui[0].height		= 300;
	ipui[0].jmp		= 640;

	ipui[0].crop		= 640;
	ipui[0].lstart		= 0;
	ipui[0].lend		= 30;

	ipui[0].fb1		= 0x00000000;
	ipui[0].fb2		= 0x00000000;
	ipui[0].fb3		= 0x00000000;

	// ch1 frame addr
	ipui[1].width		= 640;
	ipui[1].height		= 300;
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

	ipuc.cf1.b.order0	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.order1	= 0;		// 0 = UYVY, 1 = YUYV, 2 = VYUY, 3 = YVYU
	ipuc.cf1.b.format0	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv
	ipuc.cf1.b.format1	= 1;		// 0 = raw10, 1 = raw8, 2 = yuv

	ipuc.cf2.b.in_sel1	= 0;		// 0 = SIU1, 1 = SIU0
	ipuc.cf2.b.in_sel0	= 0;		// 0 = SIU0, 1 = SIU1
	ipuc.cf2.b.cowrok0	= 0;		// 1 = co-work mode
	ipuc.cf2.b.cowork1	= 0;		// 1 = co-work mode

	ipuc.cf3.b.slv_slv	= 0;
	ipuc.cf3.b.opmode	= 0;		// 0 = channel indepent
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

	msg("auto-align done...\n");

	msg("auto-align wait for VSYNC...\n");
	dvt_wait_vsync(5);

	msg("auto-align dump result\n");
	msg("= RAM 64x7 =\n");
	align->ram.v	= 1;
	align->ram_addr	= 0;
	for (i=0; i<64; i++) {
		XBYTE[0x7400+i] = align->ram_data;
	};
	hex_dump((unsigned char __xdata *) 0x7400, 64);

	msg("= RAM 512x11 =\n");
	__iow8(RAM512x11_ADDR1, 0);
	__iow8(RAM512x11_ADDR0, 0);
	for (i=0; i<512; i++) {
		XBYTE[0x7400+i] = align->ram512d;
	};
	hex_dump((unsigned char __xdata *) 0x7400, 512);

	SIMPORT(0x9F);
	return 0;

}


#endif /* CONFIG_ALIGN */
