/*
 * lib/putchar.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <configs.h>
#include <serial.h>

char putchar(char c)
{
	putc((unsigned char) c);
	return (c);
}


