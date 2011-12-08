/*
 * lib/memory.c
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
#include <absacc.h>

#include <configs.h>
#include <d2.h>

#include <regs_sys.h>


#if (CONFIG_MEM)

static unsigned short	paddr;


unsigned long d2Bmemset(unsigned long addr, char c, unsigned long num)
{
	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	while (num--) {
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = c;
		addr++;
	}

	// restore memory bank register
	__iow16(HADDRL, paddr);

	return addr;
}

unsigned long d2Wmemset(unsigned long addr, short c, unsigned long num)
{
	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	while (num--) {
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = LOBYTE(c);
		addr++;
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = HIBYTE(c);
		addr++;
	}

	// restore memory bank register
	__iow16(HADDRL, paddr);

	return addr;
}

unsigned long d2Dmemset(unsigned long addr, unsigned long c, unsigned long num)
{
	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	while (num--) {
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = LOWORD(LOBYTE(c));
		addr++;
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = LOWORD(HIBYTE(c));
		addr++;
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = HIWORD(LOBYTE(c));
		addr++;
		__iow16(HADDRL, HIWORD(addr << 1));
		XBYTE[0x8000+(LOWORD(addr) & 0x7FFF)] = HIWORD(HIBYTE(c));
		addr++;
	}

	// restore memory bank register
	__iow16(HADDRL, paddr);

	return addr;
}

long d2Bmemcmp(unsigned long a1, unsigned long a2, unsigned long num)
{
	long	state;
	char	a;
	char	b;


	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	state = -1;
	while (num--) {
		__iow16(HADDRL, HIWORD(a1 << 1));
		a = XBYTE[0x8000+(LOWORD(a1) & 0x7FFF)];
		__iow16(HADDRL, HIWORD(a2 << 1));
		b = XBYTE[0x8000+(LOWORD(a2) & 0x7FFF)];
		if (a != b) {
			state = (long) a1;
			break;
		}
		a1++;
		a2++;
	}

	// restore memory bank register
	__iow16(HADDRL, paddr);

	return state;
}


#endif	/* CONFIG_MEM */
