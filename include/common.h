/*
 * include/common.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.14	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__COMMON_H__)
#define __COMMON_H__

/*
 * Macro Definition
 */
#if defined(__C51__) || defined(__CX51__)
# define __code			code		/* movc @A+DPTR */
# define __data			data		/* mov A,#30h */
# define __bdata		bdata		/* mov A,#25h */
# define __idata		idata		/* mov A,@R0 */
# define __pdata		pdata		/* movx A,@R0 */
# define __xdata		xdata		/* movx A,@DPTR */
#else
# define __code
# define __data
# define __bdata
# define __idata
# define __pdata
# define __xdata
#endif

#define BIT(n)			(1UL <<  (n))
#define XREG(a)			(*((unsigned char volatile __xdata *) (a)))

#define HIBYTE(a)		((unsigned char) (((unsigned short) a) >> 8))
#define LOBYTE(a)		((unsigned char) (((unsigned short) a)     ))

#define HIWORD(a)		((unsigned short) (((unsigned long) a) >> 16))
#define LOWORD(a)		((unsigned short) (((unsigned long) a)      ))


#define __iow8(a, d)		(*((unsigned char volatile __xdata *) (a)) = (d))
#define __ior8(a)		(*((unsigned char volatile __xdata *) (a)))

/* for little endian */
#define __iow16(a, d)		{ __iow8(a, LOBYTE(d)); __iow8(a+1, HIBYTE(d)); }
#define __ior16(a)		((((unsigned short) __ior8(a+1)) <<  8) | ((unsigned short) __ior8(a)))

/* for little endian */
#define __iow24(a, d)		{ __iow16(a, LOWORD(d)); __iow8(a+2, LOBYTE(HIWORD(d))); }
#define __ior24(a)		((((unsigned long) __ior8(a+2)) << 16) | ((unsigned long) __ior16(a)))

/* for little endian */
#define __iow32(a, d)		{ __iow16(a, LOWORD(d)); __iow16(a+2, HIWORD(d)); }
#define __ior32(a)		((((unsigned long) __ior16(a+2)) << 16) | ((unsigned long) __ior16(a)))

/* big to little endian */
#define __le16(a)		((((unsigned short) a) << 8) | (((unsigned short) a) >> 8))
#define __le32(a)		((((unsigned long) __le16(LOWORD(a))) << 16) | ((unsigned long) __le16(HIWORD(a))))


#if defined(__CONSOLE_MODE__)
# define msg		printf
#else
# define msg		//
#endif



#if !defined(TRUE)
# define TRUE			1
#endif
#if !defined(FALSE)
# define FALSE			0
#endif
#if !defined(true)
# define true			1
#endif
#if !defined(false)
# define false			0
#endif

#if !defined(HIGH)
# define HIGH			1
#endif
#if !defined(LOW)
# define LOW			0
#endif



/* delay function */
extern void		udelay(unsigned char usec);
extern void		mdelay(unsigned short msec);

/* dump hex */
extern void		hex_dump(unsigned char *dat, unsigned short num);
extern void		hex_dump_linear(unsigned long dat, unsigned long num);

/* memory operation */
extern unsigned long	d2Bmemset(unsigned long addr, char c, unsigned long num);
extern unsigned long	d2Wmemset(unsigned long addr, short c, unsigned long num);
extern unsigned long	d2Dmemset(unsigned long addr, unsigned long c, unsigned long num);
extern long		d2Bmemcmp(unsigned long a1, unsigned long a2, unsigned long num);


#endif /* __COMMON_H__ */
