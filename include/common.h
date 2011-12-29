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


/*
#if defined(__CONSOLE_MODE__)
# define MSG		printf
#else
# define MSG		//
#endif
*/


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

/* PIO0 */
#define GPIO00			(00)
#define GPIO01			(01)
#define GPIO02			(02)
#define GPIO03			(03)
#define GPIO04			(04)
#define GPIO05			(05)
#define GPIO06			(06)
#define GPIO07			(07)
/* PIO1 */
#define GPIO08			(08)
#define GPIO09			(09)
#define GPIO10			(10)
#define GPIO11			(11)
#define GPIO12			(12)
#define GPIO13			(13)
#define GPIO14			(14)
#define GPIO15			(15)   
/* PIO2 */
#define GPIO16			(16)
#define GPIO17			(17)
#define GPIO18			(18)
#define GPIO19			(19)
#define GPIO20			(20)
#define GPIO21			(21)
#define GPIO22			(22)
#define GPIO23			(23)
/* PIO3 */
#define GPIO24			(24)
#define GPIO25			(25)
#define GPIO26			(26)
#define GPIO27			(27)
#define GPIO28			(28)
#define GPIO29			(29)
#define GPIO30			(30)
#define GPIO31			(31)
/* PIO4 */
#define GPIO32			(32)
#define GPIO33			(33)
#define GPIO34			(34)
#define GPIO35			(35)
#define GPIO36			(36)
#define GPIO37			(37)
#define GPIO38			(38)
#define GPIO39			(39)
/* PIO5 */
#define GPIO40			(40)
#define GPIO41			(41)
#define GPIO42			(42)
#define GPIO43			(43)
#define GPIO44			(44)
#define GPIO45			(45)
#define GPIO46			(46)
#define GPIO47			(47)
/* PIO6 */
#define GPIO48			(48)
#define GPIO49			(49)
#define GPIO50			(50)
#define GPIO51			(51)
#define GPIO52			(52)
#define GPIO53			(53)
#define GPIO54			(54)
#define GPIO55			(55)
/* PIO7 */
#define GPIO56			(56)
#define GPIO57			(57)
#define GPIO58			(58)
#define GPIO59			(59)
#define GPIO60			(60)
#define GPIO61			(61)
#define GPIO62			(62)
#define GPIO63			(63)
/* PIO8 */
#define GPIO64			(64)
#define GPIO65			(65)
#define GPIO66			(66)
#define GPIO67			(67)
#define GPIO68			(68)
#define GPIO69			(69)
#define GPIO70			(70)
#define GPIO71			(71)
/* PIO9 */
#define GPIO72			(72)
#define GPIO73			(73)
#define GPIO74			(74)
#define GPIO75			(75)
#define GPIO76			(76)
#define GPIO77			(77)
#define GPIO78			(78)
#define GPIO79			(79)
/* PIO10 */
#define GPIO80			(80)
#define GPIO81			(81)
#define GPIO82			(82)
#define GPIO83			(83)
#define GPIO84			(84)
#define GPIO85			(85)
#define GPIO86			(86)
#define GPIO87			(87)


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
extern long		d2Bmempicmp(unsigned long p, unsigned long i, unsigned short x, unsigned short y);

/* TV decoder */
extern void		t515bm_init(void);


#endif /* __COMMON_H__ */
