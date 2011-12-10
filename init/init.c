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
#if (CONFIG_FOSC < 48000000UL)
	__iow8(CLKSEL, 0x04);
#else
	__iow8(CLKSEL, 0x00);
#endif

	/* siu initial */
	SIMPORT(0x13);
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


	/* sou initial */
	SIMPORT(0x11);
	printf("SOU initial\n");

	souc.polarity.b.hsync = 0;
	souc.polarity.b.vsync = 0;
	souc.polarity.b.href  = 0;
	souc.polarity.b.pclk  = 1;
	souc.blinkval         = 0x15851A8A;
	souc_init();

	// initial TG0
	soui[0].ppl	= 700;
	soui[0].lpf	= 500;
	soui[0].owidth	= 640;
	soui[0].oheight = 480;
	soui[0].hblink	= 20;
	soui[0].hdummy	= 20;
	soui[0].vblink	= 10;
	soui[0].vdummy	= 5;

	soui[0].tstmode = GREEN;
	soui[0].mode    = 2;
	soui[0].iwidth  = 640;
	soui[0].iheight = 480;

	soui[0].cfg.b.enable    = 1;
	soui[0].cfg.b.interlace = 0;
	soui[0].cfg.b.gateclk   = 1;

	// initial TG1
	soui[1].ppl	= 700;
	soui[1].lpf	= 500;
	soui[1].owidth	= 640;
	soui[1].oheight	= 480;
	soui[1].hblink	= 20;
	soui[1].hdummy	= 20;
	soui[1].vblink	= 10;
	soui[1].vdummy	= 5;

	soui[1].tstmode = RED;
	soui[1].mode    = 2;
	soui[1].iwidth  = 640;
	soui[1].iheight = 480;

	soui[1].cfg.b.enable    = 0;
	soui[1].cfg.b.interlace = 0;
	soui[1].cfg.b.gateclk   = 1;
	soui_init();


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


	SIMPORT(0x1F);
}

