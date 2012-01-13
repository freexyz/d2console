/*
 * dvt/dvt_csp.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.30	T.C. Chiu <tc.chiu@zealtek.com.tw>
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



/*
 *****************************************************************************
 *
 * Change Start Pointer
 *
 *****************************************************************************
 */
int dvt_csp(void)
{
	SIMPORT(0xF0);

	/*
	 * startup IPU->SOU->SIU
	 */
	SIMPORT(0x51);
	msg("startup IPU->SOU->SIU ...\n");
	dvt_lpbk_raw8();


	/*
	 * change start pointer (sp)
	 */
	SIMPORT(0x55);
	msg("change start pointer (sp) ...\n");

	dvt_wait_vsync(3);


	SIMPORT(0x5F);
	return 0;
}

