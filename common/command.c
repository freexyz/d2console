/*
 * init/command.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stdio.h>
#include <string.h>
#include <configs.h>
#include <command.h>
#include <terminal.h>

/*
 *****************************************************************************
 *
 * Command Table
 *
 *****************************************************************************
 */
/* test command */
extern command_t	cmd_memtst_t;

extern command_t	cmd_lpbkraw8_t;
extern command_t	cmd_lpbk656i_t;
extern command_t	cmd_lpbk656p_t;

extern command_t	cmd_accurate_t;

/* utility command */
extern command_t	cmd_xmodem_send_t;
extern command_t	cmd_xmodem_receive_t;

extern command_t	cmd_movx_rd_t;
extern command_t	cmd_movx_wr_t;
extern command_t	cmd_mov_rd_t;
extern command_t	cmd_mov_wr_t;
extern command_t	cmd_xmem_dump_t;
extern command_t	cmd_imem_dump_t;
extern command_t	cmd_dump_mem_t;
extern command_t	cmd_swbank_t;
extern command_t	cmd_memcmp_t;
extern command_t	cmd_msetb_t;
extern command_t	cmd_msetw_t;
extern command_t	cmd_msetdw_t;

extern command_t	cmd_help_t;


__code const command_t		*cmd_tbl[] = {

	&cmd_lpbkraw8_t,
	&cmd_lpbk656i_t,
	&cmd_lpbk656p_t,

	&cmd_accurate_t,

#if (CONFIG_DVT_MEM)
	&cmd_memtst_t,
#endif

	/* xmodem */
#if (CONFIG_XMODEM)
	&cmd_xmodem_send_t,
	&cmd_xmodem_receive_t,
#endif

	/* memory access */
#if (CONFIG_MEM)
	&cmd_xmem_dump_t,
	&cmd_imem_dump_t,
	&cmd_dump_mem_t,
	&cmd_movx_rd_t,
	&cmd_movx_wr_t,
	&cmd_mov_rd_t,
	&cmd_mov_wr_t,
	&cmd_swbank_t,
	&cmd_memcmp_t,
	&cmd_msetb_t,
	&cmd_msetw_t,
	&cmd_msetdw_t,
#endif

	/* help */
#if (CONFIG_TERMINAL)
	&cmd_help_t,
#endif

	NULL,
};


/*
 *****************************************************************************
 *
 * help command
 *
 *****************************************************************************
 */
#if (CONFIG_TERMINAL)

void cmd_help(int argc, const char **argv)
{
	unsigned char	curr;
	command_t	*cmd;

	/* help <command>. invoke <command> with 'help' as an argument */
	if (argc == 2) {
		if (strncmp(argv[1], "help", strlen(argv[1])) == 0) {
			printf("Are you kidding?\n");
			return;
		}

		cmd = findcmd(argv[1]);
		if (cmd == NULL) {
			return;
		}
		printf("   %s\n", cmd->help);
		return;
	}

	printf("Usage:\n");
	curr = 0;
	while (cmd_tbl[curr] != NULL) {
		printf("   %s\n", cmd_tbl[curr]->help);
		curr++;
	}
	argv[1] = NULL;
}

command_t	cmd_help_t = {
	"help",
	cmd_help,
	"help <cmds>\t\t\t\t-- Help about help?"
};


/* find command */
command_t *findcmd(const char *cmdname)
{
	unsigned char	curr;

	/*
	 * do da string compare for the first offset character of cmdstr
	 * against each number of the cmdlist
	 */
	curr = 0;
	while (cmd_tbl[curr] != NULL) {
		if (strncmp(cmd_tbl[curr]->name, cmdname, strlen(cmdname)) == 0)
			return cmd_tbl[curr];
		curr++;
	}
	printf("Could not found '%s' command\n", cmdname);
	printf("If you want to konw available commands, type 'help'\n"); 
	return NULL;
}

#else
command_t *findcmd(const char *cmdname)
{
	/* nothing to do */
	cmdname = cmdname;
	return NULL;
}

#endif /* CONFIG_TERMINAL */

