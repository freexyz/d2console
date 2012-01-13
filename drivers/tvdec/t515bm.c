/* drivers/tvdec/t515bm.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.27	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <configs.h>
#include <common.h>

#include <i2c.h>


static __code const unsigned char	t515bm_init_tbl[] = {
        0x0a, 0x20,
        0x0F, 0x00,
        0x11, 0x0C,
        0x18, 0x00,	// $B0, W, Y, $0000, 18, 00, 48, 83,
        0x19, 0x0a,	// 0x0a, 0x08
//	0x19, 0x08,
//	0x1A, 0x83,
        0x21, 0x09,
        0x59, 0x8A,
        0xD2, 0x26,
        0xE0, 0xb0,
        0x5F, 0x00,
	0x27, 0x20,	//blue screen 0x20:auto,  0x10:enable
};

void t515bm_init(void)
{
	char	i;

	for (i=0; i<sizeof(t515bm_init_tbl); i+=2) {
		i2c_write_byte(&i2cdev[2], 0xb8, t515bm_init_tbl[i], t515bm_init_tbl[i+1]);
	}
}

