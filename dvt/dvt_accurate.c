/*
 * dvt/dvt_accurate.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.15	T.C. Chiu <tc.chiu@zealtek.com.tw>
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


int dvt_accurate(void)
{
	SIMPORT(0xA0);

#if (CONFIG_FOSC < 48000000UL)
	__iow8(CLKSEL, 0x04);
#else
	__iow8(CLKSEL, 0x00);
#endif

	msg("accurate stitch initialize...\n");
	/*
	 * SIU initial
	 */
	SIMPORT(0xA1);

	// initial ch0
	siu[0].x_ofs		= 0;
	siu[0].y_ofs		= 0;
	siu[0].width		= 672*2;
	siu[0].height		= 480;
	siu[0].fb1		= 0x00200000;
	siu[0].fb2		= 0x00400000;
	siu[0].fb3		= 0x00600000;
	siu[0].jmp		= 672*2;

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
	siu[1].width		= 672*2;
	siu[1].height		= 480;
	siu[1].fb1		= 0x00800000;
	siu[1].fb2		= 0x00a00000;
	siu[1].fb3		= 0x00c00000;
	siu[1].jmp		= 672*2;

	siu[1].cf1.b.scan	= 0;	// 0 = progressive, 1 = interlace write
	siu[1].cf1.b.format	= 0;	// 0 = raw8/yuv,    1 = raw10
	siu[1].cf1.b.online	= 0;
	siu[1].cf1.b.raw8lsb	= 0;

	siu[1].cf2.b.ext	= 0;	// VSYNC high active, HSYNC high active
	siu[1].cf2.b.sync	= 0;
	siu[1].cf2.b.sedge	= 0;
	siu[1].cf2.b.hmode	= 0;


	siuc.cf6.b.progressive0	= 1;	// 1 = progressive, 0 = interlace
	siuc.cf6.b.progressive1	= 1;
	siuc.cf6.b.single0	= 0;	// 1 = single capture
	siuc.cf6.b.single1	= 0;
	siuc.cf6.b.parser_en	= 0;	// 1 = enable
	siuc.cf6.b.parser_chsel	= 0;	// 1 = channel 1, 0 = channel 0
	siuc.cf6.b.parser_rst	= 0;	// 0 = reset

	// write to hardware register
	siu_init();
	siu_startup();


	/*
	 * SOU initial for interlace
	 */
	SIMPORT(0xA2);
	msg(sou_string, mode_string[3]);

	__iow8(SOUCLK, 0x01);

	souc->polarity.b.hsync	= 0;
	souc->polarity.b.vsync	= 0;
	souc->polarity.b.href	= 0;
	souc->polarity.b.pclk	= 1;
	souc->blinkval		= __le32(0x15851A8A);	// B Gb Gr R

	// initial TG0
	sou0->width		= __le16(672*2);
	sou0->height		= __le16(480);

	sou0->ppl		= __le16(858*2);
	sou0->hsync_start	= __le16(4);
	sou0->hsync_end		= __le16(68);
	sou0->hactive_start	= __le16(276);
	sou0->hactive_end	= __le16(276+672*2-1);

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

	sou0->cfg.b.interlace	= 1;
	sou0->cfg.b.gateclk	= 1;
	sou0->cfg.b.enable	= 1;

	// initial TG1
	sou1->tstmode		= RED;
	sou1->mode		= 0;

	sou1->cfg.b.interlace	= 1;
	sou1->cfg.b.gateclk	= 1;
	sou1->cfg.b.enable	= 0;


	/*
	 * IPU initial
	 */
	SIMPORT(0xA3);
	msg(sou_string, mode_string[3]);




//ch0 frame addr
normal_write(16'h304, 8'h00);
normal_write(16'h305, 8'h00);
normal_write(16'h306, 8'h00);
normal_write(16'h307, 8'h00);

normal_write(16'h308, 8'h00);
normal_write(16'h309, 8'h00);
normal_write(16'h30a, 8'h00);
normal_write(16'h30b, 8'h00);

normal_write(16'h30c, 8'h00);
normal_write(16'h30d, 8'h00);
normal_write(16'h30e, 8'h00);
normal_write(16'h30f, 8'h00);

//ch1 frame addr
normal_write(16'h310, 8'h00);
normal_write(16'h311, 8'h00);
normal_write(16'h312, 8'h40);
normal_write(16'h313, 8'h00);

normal_write(16'h314, 8'h00);
normal_write(16'h315, 8'h00);
normal_write(16'h316, 8'h40);
normal_write(16'h317, 8'h00);

normal_write(16'h318, 8'h00);
normal_write(16'h319, 8'h00);
normal_write(16'h31a, 8'h40);
normal_write(16'h31b, 8'h00);



//ch0 size
normal_write(16'h31c, 8'h40);
normal_write(16'h31d, 8'h05);
normal_write(16'h31e, 8'h40);
normal_write(16'h31f, 8'h05);
normal_write(16'h320, 8'he0);
normal_write(16'h321, 8'h01);

//ch1 size
normal_write(16'h322, 8'h40);
normal_write(16'h323, 8'h05);
normal_write(16'h324, 8'h40);
normal_write(16'h325, 8'h05);
normal_write(16'h326, 8'he0);
normal_write(16'h327, 8'h01);

//ch0 &ch1 line start resident &line end resident
normal_write(16'h328, 8'h1e);
normal_write(16'h329, 8'h00);
normal_write(16'h32a, 8'h1e);
normal_write(16'h32b, 8'h00);

normal_write(16'h301, 8'h50); //raw8/yuv
normal_write(16'h302, 8'h00); //stand alone
normal_write(16'h32c, 8'h00); //bypass

////set channel0 stchu PMU table
normal_write(16'h382,8'h00);
normal_write(16'h383,8'h00);
normal_write(16'h384,8'h80);
normal_write(16'h385,8'h00);

////set channel1 stchu PMU table 
normal_write(16'h386,8'h00);
normal_write(16'h387,8'h00);
normal_write(16'h388,8'hc0);
normal_write(16'h389,8'h00);

//reg update
normal_write(16'h302, 8'h05);  
normal_write(16'h302, 8'h00);  

//flush DFU cache
normal_write(16'h32f,8'h20); 
normal_write(16'h32f,8'h00);    
   
//enable & set stchu    
#2000 normal_write(16'h300,8'hf0);


	msg("accurate stitch done..\n");
	return 0;
}

