/*
 * dvt/dvt_mem.c -- Design Verification Test for memory
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.12.06	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <absacc.h>

#include <reg52.h>
#include <configs.h>
#include <regs_sys.h>


#if (CONFIG_DVT_MEM)

static __code const unsigned char	mchktbl[] = {
	0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F,
	0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0,
	0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F, 0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78,
	0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0, 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87,
};

int dvt_iram(void)
{
	unsigned char	bp;
	unsigned char	i;

	printf("<iram> Start\n");
	bp  = (SP & 0xF0) + (SP & 0x0F) ? 0x10: 0;
	if ((bp + 0x10) >= 0x80) {
		// memory capacity is not enough
		return 1;
	}
	printf("<iram> Display Original Value\n");
	hex_dump((char __data *) bp, (unsigned short) 16);

	printf("<iram> Write New Value\n");
	for (i=0; i<16; i++) {
		DBYTE[bp+i] = mchktbl[i];
	}
	printf("<iram> Display New Value\n");
	hex_dump((char __data *) bp, (unsigned short) 16);

	printf("<iram> Check Value in Memory\n");
	for (i=0; i<16; i++) {
		if (mchktbl[i] != DBYTE[bp+i]) {
			// fail
			printf("<iram> >>> Fail <<<\n");
			return -1;
		}
	}
	printf("<iram> >>> Pass <<<\n");
	// pass
	return 0;
}


#define SARM2K_BP		(0x7000 + (2 * 1024) - 32)
int dvt_2ksram(void)
{
	unsigned char	i;

	printf("<2ksram> Start\n");
	printf("<2ksram> Display Original Value\n");
	hex_dump((char __xdata *) SARM2K_BP, (unsigned short) 32);

	printf("<2ksram> Write New Value\n");
	for (i=0; i<32; i++) {
		XBYTE[SARM2K_BP+i] = mchktbl[i];
	}
	printf("<2ksram> Display New Value\n");
	hex_dump((char __xdata *) SARM2K_BP, (unsigned short) 32);

	printf("<2ksram> Check Value in Memory\n");
	for (i=0; i<32; i++) {
		if (mchktbl[i] != XBYTE[SARM2K_BP+i]) {
			// fail
			printf("<2ksram> >>> Fail <<<\n");
			return -1;
		}
	}
	// pass
	printf("<2ksram> >>> Pass <<<\n");
	return 0;
}

static __code unsigned long		mmatbl[] = {
	0x00008000, 0x0000FFE0,
	0x00028000, 0x0004FFE0,
	0x00068000, 0x0008FFE0,
};

int dvt_sdram(void)
{
	unsigned char	i, j, c;
	unsigned long	bp;
	unsigned short	paddr;
	int		state;

	printf("<sdram> Start\n");
	printf("<sdram> Display Original Value\n");
	for (i=0; i<sizeof(mmatbl)/sizeof(unsigned long); i++) {
		hex_dump_linear(mmatbl[i], 16*4);
	}

	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	printf("<sdram> Write New Value\n");
	for (i=0; i<sizeof(mmatbl)/sizeof(unsigned long); i++) {
		bp = mmatbl[i];
		for (j=0; j<(16*4); j++, bp++) {
			__iow16(HADDRL, HIWORD(bp << 1));
			XBYTE[0x8000+(LOWORD(bp) & 0x7FFF)] = mchktbl[j];
		}
	}

	printf("<sdram> Display New Value\n");
	for (i=0; i<sizeof(mmatbl)/sizeof(unsigned long); i++) {
		hex_dump_linear(mmatbl[i], 16*4);
	}

	state = 0;
	printf("<sdram> Check Value in Memory\n");
	for (i=0; i<sizeof(mmatbl)/sizeof(unsigned long); i++) {
		bp = mmatbl[i];
		for (j=0; j<(16*4); j++, bp++) {
			__iow16(HADDRL, HIWORD(bp << 1));
			c = XBYTE[0x8000+(LOWORD(bp) & 0x7FFF)];
			if (mchktbl[j] != c) {
				state = -1;
				goto exit;
			}
		}
	}
exit:
	// restore memory bank register
	__iow16(HADDRL, paddr);

	// pass/fail
	printf("<sdram> >>> %s <<<\n", (state == 0) ? "Pass" : "Fail");
	return state;
}


#endif /* CONFIG_DVT_MEM */

