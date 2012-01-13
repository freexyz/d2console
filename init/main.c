/*
 * init/main.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * Modifications:
 *	$Id$
 */

#include <stdio.h>
#include <configs.h>
#include <terminal.h>
#include <dvt.h>



static __code const char	*d2_banner = {
	"\n" \
	"************************************************************\n" \
	"*                     D2 Test Program                      *\n" \
	"*                                                   by TCC *\n" \
	"*                                                          *\n" \
	"*                            FPGA version (stable) is: %s *\n" \
	"*                     Build time is: %s  %s *\n" \
	"************************************************************\n"
};

/*
 * Main Loop
 */
void main(void)
{
	SIMPORT(0x10);

	/* initial deivce */
	EA = 0;
	sys_init();
	EA = 1;

	SIMPORT(0x20);

#if 0
	SIMPORT(0x21);
	dvt_sdram();
	SIMPORT(0x22);
	dvt_2ksram();
	SIMPORT(0x23);
	dvt_iram();
	SIMPORT(0x24);
#endif

	SIMPORT(0x30);

	/* main menu */
	printf(d2_banner, CONFIG_STABLE_FPGA, __DATE__ , __TIME__);

	SIMPORT(0x40);
	terminal();
}

