/*
 * include/terminal.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__TERMINAL_H__)
#define __TERMINAL_H__

#define CTL_CH(c)		((c) - 'a' + 1)

#define CTL_BACKSPACE		('\b')
#define DEL			((char) 255)
#define DEL7			((char) 127)
#define CREAD_HIST_CHAR		('!')

enum parse_state {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};



extern void	execfunc(int argc, const char **argv);
extern void	execcmd(void);
extern void	getcmd(void);
extern void	terminal(void);


#endif /* __TERMINAL_H__ */
