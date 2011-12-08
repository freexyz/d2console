/*
 * lib/misc.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.25	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <absacc.h>

#include <configs.h>
#include <serial.h>
#include <regs_sys.h>


#if (CONFIG_TERMINAL)

static __code const char	ascii_tbl[16] = "0123456789ABCDEF";
static __xdata char		linebuf[90];
static unsigned short		paddr;


void bin2hex(char *buf, long x, int nbytes)
{
        int	i;
        int	s = 4 * (2 * nbytes - 1);

        for (i = 0; i < 2 * nbytes; i++){
                buf[i] = ascii_tbl[(x >> s) & 0xf];
                s -= 4;
        }
        buf[2 * nbytes] = 0;
}

/*
 * dump hex
 */
#define BL_ISPRINT(ch)		(((ch) >= ' ') && ((ch) < 128))
void hex_dump(unsigned char *dat, unsigned short num)
{
	int	i;
	long	oldNum;
	char	*bufp;
	int	line_resid;

	while (num) {
		bufp    = linebuf;
		bin2hex(bufp, (unsigned long) dat, 4);
		bufp   += 8;
		*bufp++ = ':';
		*bufp++ = ' ';

		oldNum = num;

		for (i = 0; i < 16 && num; i++, num--) {
			bin2hex(bufp, (unsigned long) dat[i], 1);
			bufp += 2;
			*bufp++ = (i == 7) ? '-' : ' ';
		}

		line_resid = (16 - i) * 3;
		if (line_resid) {
			memset(bufp, ' ', line_resid);
			bufp += line_resid;
		}

		memcpy(bufp, "; ", 2);
		bufp += 2;

		for (i = 0; i < 16 && oldNum; i++, oldNum--) {
			*bufp++ = BL_ISPRINT(dat[i]) ? dat[i] : '.';
		}

		line_resid = 16 - i;
		if (line_resid) {
			memset(bufp, ' ', 16 - i);
			bufp += 16 - i;
		}

		*bufp++ = '\r';
		*bufp++ = '\n';
		*bufp++ = '\0';
		puts(linebuf);
		dat += 16;
	}
}


void hex_dump_linear(unsigned long dat, unsigned long num)
{
	int	i;
	long	oldNum;
	char	*bufp;
	int	line_resid;
	char	c;

	// keep current memory bank register
	paddr = __ior16(HADDRL) & 0x01FF;

	while (num) {
		bufp    = linebuf;
		bin2hex(bufp, (unsigned long) dat, 4);
		bufp   += 8;
		*bufp++ = ':';
		*bufp++ = ' ';

		oldNum = num;

		for (i = 0; i < 16 && num; i++, num--) {
			__iow16(HADDRL, HIWORD((dat+i) << 1));
			c = XBYTE[0x8000+(LOWORD(dat+i) & 0x7FFF)];
			bin2hex(bufp, (unsigned long) c, 1);
			bufp += 2;
			*bufp++ = (i == 7) ? '-' : ' ';
		}

		line_resid = (16 - i) * 3;
		if (line_resid) {
			memset(bufp, ' ', line_resid);
			bufp += line_resid;
		}

		memcpy(bufp, "; ", 2);
		bufp += 2;

		for (i = 0; i < 16 && oldNum; i++, oldNum--) {
			__iow16(HADDRL, HIWORD((dat+i) << 1));
			c = XBYTE[0x8000+(LOWORD(dat+i) & 0x7FFF)];
			*bufp++ = BL_ISPRINT(c) ? c : '.';
		}

		line_resid = 16 - i;
		if (line_resid) {
			memset(bufp, ' ', 16 - i);
			bufp += 16 - i;
		}

		*bufp++ = '\r';
		*bufp++ = '\n';
		*bufp++ = '\0';
		puts(linebuf);
		dat += 16;
	}

	// restore memory bank register
	__iow16(HADDRL, paddr);
}


#endif	/* CONFIG_TERMINAL */
