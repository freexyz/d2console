/*
 * lib/getkey.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <configs.h>
#include <serial.h>

char _getkey(void)
{
	char	c;
	
	c = (char) getc();
	return (c);
}

