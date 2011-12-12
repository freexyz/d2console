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


static __code const char	*lpbk_help = {
	"\n"									\
	"IPU->SOU->SIU loopback mode test\n"					\
	"   [IPU] frame buffer:\n"						\
	"      <CH0>: fb1 = 0x00000000, fb2 = 0x00000000, fb3 = 0x00000000\n"	\
	"      <CH1>: fb1 = 0x00100000, fb2 = 0x00100000, fb3 = 0x00100000\n"	\
	"\n"									\
	"   [SIU] frame buffer:\n"						\
	"      <CH0>: fb1 = 0x00200000, fb2 = 0x00400000, fb3 = 0x00600000\n"	\
	"      <CH1>: fb1 = 0x00800000, fb2 = 0x00a00000, fb3 = 0x00c00000\n"	\
};


void cmd_loopback(int argc, const char *argv[])
{
	argc = argc;
	argv = argv;


	if (argc != 1) {
		printf("invalid 'loopback' command: too few(many) arguments\n");
		return;
	}

	printf("%s", lpbk_help);

	dvt_lpbk_startup();

}

command_t	cmd_loopback_t = {
	"loopback",
	cmd_loopback,
	"loopback \t\t\t\t-- IPU->SOU->SIU loopback mode"
};











