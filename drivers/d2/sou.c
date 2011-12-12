/*
 * driver/d2/sou.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * Modifications:
 *	$Id$
 */
#include <configs.h>
#include <regs_sou.h>

struct souinface volatile __xdata	*sou0 = (struct souinface volatile __xdata *) SOU_ENCODER_0_MODE;
struct souinface volatile __xdata	*sou1 = (struct souinface volatile __xdata *) SOU_ENCODER_1_MODE;
struct souctrl   volatile __xdata	*souc = (struct souctrl   volatile __xdata *) SOU_POLARITY;


