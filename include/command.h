/*
 * include/command.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__COMMAND_H__)
#define __COMMAND_H__


typedef struct command {
	const char		*name;
	void			(*cmdfunc)(int argc, const char **argv);
	const char		*help;
} command_t;


/* find command */
extern command_t	*findcmd(const char *cmdname);

#endif /* __COMMAND_H__ */
