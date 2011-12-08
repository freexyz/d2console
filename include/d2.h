/*
 * include/d2.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.14	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__D2_H__)
#define __D2_H__

#include <reg52.h>
#include <common.h>


/*
 *****************************************************************************
 *
 * for D2 Definition
 *
 *****************************************************************************
 */
enum d2channel {
	CH0,
	CH1,
	BOTH
};

enum d2stream {
	STANDALONE,
	ONLINE
};

enum d2tg {
	TG0,
	TG1
};


/* Register Base Definition */
#define SYS_BASE		0x0000		/* System Register		*/
#define SDRAM_BASE		0x0100		/* SDRAM Controller		*/
#define SIU_BASE		0x0200		/* Sensor Input Unit		*/
#define IPU_BASE		0x0300		/* Image Processing Unit	*/
#define SOU_BASE		0x0400		/* Sensor Output Unit		*/
#define PIO_BASE		0x0500		/* Programmable IO (PIO)	*/
#define SPI_BASE		0x0600		/* SPI Flash Controller		*/
#define AALIGN_BASE		0x0800		/* Auto Alignment Unit		*/
#define SRAM_BASE		0x7000		/* Embedded SRAM for MCU	*/
#define I2C_MODE		0x7FFF		/* I2C Mode Register		*/



/* Function Prototype */
extern void	d2_init(void);

/* siu */
extern void	siu_set_fb(enum d2channel ch, unsigned long fb1, unsigned long fb2, unsigned long fb3);
extern void	siu_set_szjmp(enum d2channel ch, unsigned short width, unsigned short height, unsigned long jmp);
extern void	siu_set_xyoffset(enum d2channel ch, unsigned short x, unsigned short y);
extern void	siu_set_mode(enum d2channel ch, unsigned char mode);
extern void	siu_startup(void);
extern void 	siu_stop(void);

/* ipu */
extern void	ipu_set_fb(enum d2channel ch, unsigned long fb1, unsigned long fb2, unsigned long fb3);
extern void	ipu_set_xyjmp(enum d2channel ch, unsigned short width, unsigned short height, unsigned long jmp);
extern void	ipu_set_crop(enum d2channel ch, unsigned short width, unsigned char lstart, unsigned char lend);
extern void	ipu_set_format(unsigned char format);
extern void	ipu_set_opmode(unsigned char op, unsigned char factor, unsigned short overlap);
extern void	ipu_set_cowork(unsigned char dsrc);
extern void	ipu_startup(enum d2stream op);
extern void	ipu_stop(void);

/* sou */
extern char	sou_set_ppl(enum d2tg ch, unsigned short total, unsigned short active, unsigned short dummy, unsigned short blink);
extern char	sou_set_lpf(enum d2tg ch, unsigned short total, unsigned short active, unsigned short dummy, unsigned short blink);




#endif /* __D2_H__ */
