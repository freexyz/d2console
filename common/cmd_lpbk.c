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


void cmd_lpbkraw8(int argc, const char *argv[])
{
	argc = argc;
	argv = argv;


	if (argc != 1) {
		printf("invalid 'raw8' command: too few(many) arguments\n");
		return;
	}

	dvt_lpbk_raw8();

}

command_t	cmd_lpbkraw8_t = {
	"raw8",
	cmd_lpbkraw8,
	"raw8 \t\t\t\t-- RAW8 loopback mode"
};


void cmd_lpbk656i(int argc, const char *argv[])
{
	argc = argc;
	argv = argv;


	if (argc != 1) {
		printf("invalid 'ccir656i' command: too few(many) arguments\n");
		return;
	}

	dvt_lpbk_ccir656i();

}

command_t	cmd_lpbk656i_t = {
	"ccir656i",
	cmd_lpbk656i,
	"ccir656i \t\t\t\t-- CCIR-656 interlace loopback mode"
};


void cmd_lpbk656p(int argc, const char *argv[])
{
	argc = argc;
	argv = argv;


	if (argc != 1) {
		printf("invalid 'ccir656p' command: too few(many) arguments\n");
		return;
	}

	dvt_lpbk_ccir656p();

}

command_t	cmd_lpbk656p_t = {
	"ccir656p",
	cmd_lpbk656p,
	"ccir656p \t\t\t\t-- CCIR-656 progressive loopback mode"
};





