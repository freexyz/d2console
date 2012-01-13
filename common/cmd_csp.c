/* common/cmd_csp.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.30	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include <configs.h>
#include <command.h>

#include <dvt.h>


void cmd_csp(int argc, const char *argv[])
{
	argv[1] = NULL;
	if (argc != 1) {
		printf("invalid 'csp' command: too few(many) arguments\n");
		return;
	}

	dvt_csp();
}

command_t	cmd_csp_t = {
	"csp",
	cmd_csp,
	"csp \t\t\t\t\t-- change start pointer"
};



