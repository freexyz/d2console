/*
 * drivers/i2c/soft_i2c.c -- 
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
 */
#include <configs.h>

#include <regs_sys.h>
#include <regs_pio.h>

struct pioif volatile __xdata		*pio     = (struct pioif volatile __xdata *) P0_DATA;
unsigned char volatile __xdata		*piomode = (unsigned char volatile __xdata *) PIO0_MODE;

