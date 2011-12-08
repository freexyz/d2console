/*
 * include/serial.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__SERIAL_H__)
#define __SERIAL_H__

#define getc		serial_getc
#define putc		serial_putc
#define puts		serial_puts
#define tstc		serial_tstc
#define putcx		serial_putcx

extern void		serial_init(void);
extern unsigned char	serial_getc(void);
extern void		serial_putc(unsigned char c);
extern void		serial_putcx(unsigned char c);
extern void		serial_puts(const char *s);
extern unsigned	char	serial_tstc(unsigned short msec);

#endif /* __SERIAL_H__ */
