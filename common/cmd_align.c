/* common/cmd_align.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.20	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include <configs.h>
#include <command.h>

#include <dvt.h>

#if (CONFIG_ALIGN)

void cmd_align(int argc, const char *argv[])
{
	argv = argv;


	if (argc != 1) {
		printf("invalid 'align' command: too few(many) arguments\n");
		return;
	}

	dvt_align();

	argv[1] = NULL;
}

command_t	cmd_align_t = {
	"align",
	cmd_align,
	"align \t\t\t\t-- auto-align"
};

#endif /* CONFIG_ALIGN */
