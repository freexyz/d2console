/*
 * terminal/terminal.c -- It's a simple serial terminal
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <configs.h>
#include <serial.h>
#include <command.h>
#include <terminal.h>

#if (CONFIG_TERMINAL)
/*
 *
 * Macro Definitions
 *
 */
#if defined(DEBUG_GETCMD)
# define DBG_GETCMD			printf
#else
# define DBG_GETCMD			//
#endif
#if defined(DEBUG_EXECFUNC)
# define DBG_EXECFUNC			printf
#else
# define DBG_EXECFUNC			//
#endif

#if !defined(CONFIG_CBSIZE)
# define CONFIG_CBSIZE			64
#endif
#if !defined(CONFIG_PBSIZE)
# define CONFIG_PBSIZE			16
#endif
#if !defined(CONFIG_PROMPT)
# define CONFIG_PROMPT			"[term]# "
#endif


/*
 *
 * Variable Declarations
 *
 */
static __code const char	prompt[CONFIG_PBSIZE] = CONFIG_PROMPT;

static char			cmd_buf[CONFIG_CBSIZE];

static int			argc;
static char			*argv[CONFIG_CBSIZE];

static enum parse_state		last_state;
static enum parse_state		new_state;
static enum parse_state		stacked_state;


/*
 *
 * Local Function
 *
 */
/* parse user command line */
static void parseargs(char *argstr, int *argc_p, char **argv, char** resid)
{
	char	c;


	argc = 0;

	/* tokenize the argstr */
	last_state = PS_WHITESPACE;

	while ((c = *argstr) != 0) {
		if (c == ';' && last_state != PS_STRING && last_state != PS_ESCAPE)
			break;

		if (last_state == PS_ESCAPE) {
			new_state = stacked_state;

		} else if (last_state == PS_STRING) {
			if (c == '"') {
				new_state = PS_WHITESPACE;
				*argstr   = 0;
			} else {
				new_state = PS_STRING;
			}

		} else if ((c == ' ') || (c == '\t')) {
			/* whitespace character */
			*argstr   = 0;
			new_state = PS_WHITESPACE;

		} else if (c == '"') {
			new_state = PS_STRING;
			*argstr++    = 0;
			argv[argc++] = argstr;

		} else if (c == '\\') {
			stacked_state = last_state;
			new_state     = PS_ESCAPE;

		} else {
			/* token */
			if (last_state == PS_WHITESPACE) {
				argv[argc++] = argstr;
			}
			new_state = PS_TOKEN;
		}

		last_state = new_state;
		argstr++;
	}

#if 0 /* for debugging */
	{
		int i;
		putLabeledWord("parseargs: argc=", argc);
		for (i = 0; i < argc; i++) {
			puts("   ");
			puts(argv[i]);
			puts("\r\n");
		}
	}
#endif
	
	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';') {
		*argstr++ = '\0';
	}
	*resid = argstr;
}


/*
 *****************************************************************************
 *
 * Global Function
 *
 *****************************************************************************
 */
/* execute a function */
void execfunc(int argc, const char **argv)
{
	command_t	*cmd = findcmd(argv[0]);

	if (cmd == NULL) {
		return;
	}
	DBG_EXECFUNC("execcmd: cmd=%s, argc=%d\n", argv[0], argc);
	cmd->cmdfunc(argc, argv);
}


/* parse and execute a string */
void execcmd(void)
{
	char	*resid;
	char	*p = cmd_buf;

	while (*p) {
		memset(argv, 0, sizeof(argv));
		parseargs(p, &argc, argv, &resid);
		/* execute a function */
		if (argc > 0) {
			execfunc(argc, (const char **) argv);
		}
		p = resid;
	}
}


/* get a command */
void getcmd(void)
{
	char	c;
	char	curpos   = 0;	/* current position - index into cmd_buf */
	int	cmd_echo = 1;

	/* clear out the buffer */
	memset(cmd_buf, 0, CONFIG_CBSIZE);

	for (;;) {
		c = getc();
		switch (c) {
		case 0x08:
		case 0x06:
		case 0x07:
		case 0x7E:
		case 0x7F:	/* backspace or delete */
			/* we're not at the beginning of the line */
			if (curpos) {
				curpos--;
				putc(0x08);	/* go backwards */
				putc(' ');	/* overwrite the char */
				putc(0x08);	/* go back again */
			}
			cmd_buf[curpos] = '\0';
			break;
		case '\r':
		case '\n':
		case '\0':
			putc('\r');
			putc('\n');
			goto end_cmd;

		case CTL_CH('x'):
			curpos = 0;
			break;

		default:
			if (curpos < CONFIG_CBSIZE) {
				cmd_buf[curpos] = c;
				/* echo it back out to the screen */
				if (cmd_echo)
					putc(c);
				curpos++;
			}
			break;
		}
	}
end_cmd:
	DBG_GETCMD("COMMAND: %s\n", cmd_buf);
}


/* terminal mode */
void terminal(void)
{
	for (;;) {
		printf("%s", prompt);

		getcmd();

		/* execute a user command */
		if (cmd_buf[0])
			execcmd();
	}
}

#else
void terminal(void)
{
	while (1)
		;	/* nothing to do */
}

#endif /* CONFIG_TERMINAL */

