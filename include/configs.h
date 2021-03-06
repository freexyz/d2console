/*
 * include/configs.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.11.14	T.C. Chiu	create file
 */

#if !defined(__CONFIGS_H__)
#define __CONFIGS_H__

/* for VLSI simulation */
#define CONFIG_VLSI_SIMULATION		0

/* for firmware debug */
#define CONFIG_DEBUG			0

/* for main clock */
#define CONFIG_FOSC			(66000000UL)
//#define CONFIG_FOSC			(48000000UL)
//#define CONFIG_FOSC			(24000000UL)	// dram fail
//#define CONFIG_FOSC			(12000000UL)	// dram fail
#define CONFIG_FSCLK			(CONFIG_FOSC)	/* where fsclk is the frequency of the state machine clock. */

#define CONFIG_UART_USE_T0		0
#define CONFIG_UART_USE_T1		1
#define CONFIG_UART_USE_T2		2
#define CONFIG_UART_CLKSRC		CONFIG_UART_USE_T1
//#define CONFIG_UART_CLKSRC		CONFIG_UART_USE_T2

#if (CONFIG_UART_CLKSRC == CONFIG_UART_USE_T2)
# define CONFIG_BAUDRATE		(115200UL)	/* UART baud rate */
#else
# define CONFIG_BAUDRATE		(9600UL)	/* UART baud rate */
//# define CONFIG_BAUDRATE		(19200UL)	/* UART baud rate */
#endif

// for console definition
#define CONFIG_CBSIZE			64
#define CONFIG_PBSIZE			16
#define CONFIG_PROMPT			"[d2]# "

#define CONFIG_LINEAR_DRAM		1


/* for function */
#if (CONFIG_VLSI_SIMULATION)
# define CONFIG_SERIAL			0		/* serial port */
#else
# define CONFIG_SERIAL			1		/* serial port */
#endif
#define CONFIG_TERMINAL			1		/* terminal */
#define CONFIG_MEM			1		/* memory dump */
#define CONFIG_XMODEM			1		/* xmodem function */
#define CONFIG_SOFT_I2C			0		/* i2c function */

#define CONFIG_ALIGN			1		/* auto align function */
#define CONFIG_DVT_MEM			1		/* test memory function */


#include <d2.h>

/* for debug */
#undef DEBUG_GETCMD
#undef DEBUG_EXECFUNC

/* for VLSI simulation */
#if (CONFIG_VLSI_SIMULATION) || (CONFIG_DEBUG)
# define DEBUG_PORT			(0x0f40)
# define SIMPORT(a)			__iow8(DEBUG_PORT, (a))
#else
# define SIMPORT(a)
#endif


#endif /* __CONFIGS_H__ */