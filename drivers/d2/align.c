/*
 * driver/d2/ipu.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * Modifications:
 *	2011.12.20	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <configs.h>
#include <regs_align.h>

struct alignif volatile __xdata		*align = (struct alignif volatile __xdata *) AUTO_ALIGN_CFG;


