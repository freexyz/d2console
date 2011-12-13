/*
 * common/cmd_lpbk.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.09	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include <configs.h>
#include <command.h>

#include <dvt.h>


void cmd_loopback(int argc, const char *argv[])
{
	argc = argc;
	argv = argv;


	if (argc != 1) {
		printf("invalid 'loopback' command: too few(many) arguments\n");
		return;
	}

	dvt_lpbk_raw8();

}

command_t	cmd_loopback_t = {
	"loopback",
	cmd_loopback,
	"loopback \t\t\t\t-- IPU->SOU->SIU loopback mode"
};











