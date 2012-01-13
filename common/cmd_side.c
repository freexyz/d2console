/* common/cmd_side.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF ZEALTEK.
 *
 * History:
 *	2011.12.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include <configs.h>
#include <command.h>

#include <dvt.h>


void cmd_hside(int argc, const char *argv[])
{
	argv[1] = NULL;
	if (argc != 1) {
		printf("invalid 'hside' command: too few(many) arguments\n");
		return;
	}

	dvt_hside();
}

command_t	cmd_hside_t = {
	"hside",
	cmd_hside,
	"hside \t\t\t\t-- hside max test"
};


void cmd_vside(int argc, const char *argv[])
{
	argv[1] = NULL;
	if (argc != 1) {
		printf("invalid 'vside' command: too few(many) arguments\n");
		return;
	}

	dvt_vside();
}

command_t	cmd_vside_t = {
	"vside",
	cmd_vside,
	"vside \t\t\t\t-- vside max test"
};

