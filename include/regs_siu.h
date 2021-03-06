/*
 * include/regs_siu.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.11.22	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <configs.h>

#if !defined(__REGS_SIU_H__)
#define __REGS_SIU_H__

#if !defined(SIU_BASE)
#error Please define 'SIU_BASE'
#endif


/*
 * Register Definition
 */
#define SIU_CTRL			(SIU_BASE+0x0000)	/* R/W, 0, Control register			*/
#define SIU_CONF1			(SIU_BASE+0x0001)	/* R/W, 0, Config register			*/
#define SIU_CONF2			(SIU_BASE+0x0002)	/* R/W, 0, Config register			*/
#define SIU_CONF3			(SIU_BASE+0x0003)	/* R/W, 0, Status & clear frame interrupt	*/
#define SIU_CH0_JMP0			(SIU_BASE+0x0010)	/* R/W, 0, Channel0 addres jump 7~0		*/
#define SIU_CH0_JMP1			(SIU_BASE+0x0011)	/* R/W, 0, Channel0 addres jump 15~8		*/
#define SIU_CH0_JMP2			(SIU_BASE+0x0012)	/* R/W, 0, Channel0 addres jump 23~16		*/
#define SIU_CH1_JMP0			(SIU_BASE+0x0017)	/* R/W, 0, Channel1 addres jump 7~0		*/
#define SIU_CH1_JMP1			(SIU_BASE+0x0018)	/* R/W, 0, Channel1 addres jump 15~8		*/
#define SIU_CH1_JMP2			(SIU_BASE+0x0019)	/* R/W, 0, Channel1 addres jump 23~16		*/
#define SIU_CH0_F1S0			(SIU_BASE+0x001a)	/* R/W, 0, Channel 0 frame1 start address 7~0	*/
#define SIU_CH0_F1S1			(SIU_BASE+0x001b)	/* R/W, 0, Channel 0 frame1 start address 15~8	*/
#define SIU_CH0_F1S2			(SIU_BASE+0x001c)	/* R/W, 0, Channel 0 frame1 start address 23~16	*/
#define SIU_CH0_F1S3			(SIU_BASE+0x001d)	/* R/W, 0, Channel 0 frame1 start address 31~24	*/
#define SIU_CH0_F2S0			(SIU_BASE+0x001e)	/* R/W, 0, Channel 0 frame2 start address 7~0	*/
#define SIU_CH0_F2S1			(SIU_BASE+0x001f)	/* R/W, 0, Channel 0 frame2 start address 15~8	*/
#define SIU_CH0_F2S2			(SIU_BASE+0x0020)	/* R/W, 0, Channel 0 frame2 start address 23~16	*/
#define SIU_CH0_F2S3			(SIU_BASE+0x0021)	/* R/W, 0, Channel 0 frame2 start address 31~24	*/
#define SIU_CH0_F3S0			(SIU_BASE+0x0022)	/* R/W, 0, Channel 0 frame3 start address 7~0	*/
#define SIU_CH0_F3S1			(SIU_BASE+0x0023)	/* R/W, 0, Channel 0 frame3 start address 15~8	*/
#define SIU_CH0_F3S2			(SIU_BASE+0x0024)	/* R/W, 0, Channel 0 frame3 start address 23~16	*/
#define SIU_CH0_F3S3			(SIU_BASE+0x0025)	/* R/W, 0, Channel 0 frame3 start address 31~24	*/
#define SIU_CH1_F1S0			(SIU_BASE+0x0026)	/* R/W, 0, Channel 1 frame1 start address 7~0	*/
#define SIU_CH1_F1S1			(SIU_BASE+0x0027)	/* R/W, 0, Channel 1 frame1 start address 15~8	*/
#define SIU_CH1_F1S2			(SIU_BASE+0x0028)	/* R/W, 0, Channel 1 frame1 start address 23~16	*/
#define SIU_CH1_F1S3			(SIU_BASE+0x0029)	/* R/W, 0, Channel 1 frame1 start address 31~24	*/
#define SIU_CH1_F2S0			(SIU_BASE+0x002a)	/* R/W, 0, Channel 1 frame2 start address 7~0	*/
#define SIU_CH1_F2S1			(SIU_BASE+0x002b)	/* R/W, 0, Channel 1 frame2 start address 15~8	*/
#define SIU_CH1_F2S2			(SIU_BASE+0x002c)	/* R/W, 0, Channel 1 frame2 start address 23~16	*/
#define SIU_CH1_F2S3			(SIU_BASE+0x002d)	/* R/W, 0, Channel 1 frame2 start address 31~24	*/
#define SIU_CH1_F3S0			(SIU_BASE+0x002e)	/* R/W, 0, Channel 1 frame3 start address 7~0	*/
#define SIU_CH1_F3S1			(SIU_BASE+0x002f)	/* R/W, 0, Channel 1 frame3 start address 15~8	*/
#define SIU_CH1_F3S2			(SIU_BASE+0x0030)	/* R/W, 0, Channel 1 frame3 start address 23~16	*/
#define SIU_CH1_F3S3			(SIU_BASE+0x0031)	/* R/W, 0, Channel 1 frame3 start address 31~24	*/
#define SIU_CH0_X0			(SIU_BASE+0x0032)	/* R/W, 0, Channel 0 start x position 7~0	*/
#define SIU_CH0_X1			(SIU_BASE+0x0033)	/* R/W, 0, Channel 0 start x position 13~8	*/
#define SIU_CH0_Y0			(SIU_BASE+0x0034)	/* R/W, 0, Channel 0 start y position 7~0	*/
#define SIU_CH0_Y1			(SIU_BASE+0x0035)	/* R/W, 0, Channel 0 start y position 13~8	*/
#define SIU_CH0_WIDTH0			(SIU_BASE+0x0036)	/* R/W, 0, Channel 0 image width 7~0		*/
#define SIU_CH0_WIDTH1			(SIU_BASE+0x0037)	/* R/W, 0, Channel 0 image width 13~8		*/
#define SIU_CH0_HEIGHT0			(SIU_BASE+0x0038)	/* R/W, 0, Channel 0 image height 7~0		*/
#define SIU_CH0_HEIGHT1			(SIU_BASE+0x0039)	/* R/W, 0, Channel 0 image height 12~8		*/
#define SIU_CONF4			(SIU_BASE+0x003a)	/* R/W, 0, Config register			*/
#define SIU_CH1_X0			(SIU_BASE+0x003b)	/* R/W, 0, Channel 1 start x position 7~0	*/
#define SIU_CH1_X1			(SIU_BASE+0x003c)	/* R/W, 0, Channel 1 start x position 13~8	*/
#define SIU_CH1_Y0			(SIU_BASE+0x003d)	/* R/W, 0, Channel 1 start y position 7~0	*/
#define SIU_CH1_Y1			(SIU_BASE+0x003e)	/* R/W, 0, Channel 1 start y position 13~8	*/
#define SIU_CH1_WIDTH0			(SIU_BASE+0x003f)	/* R/W, 0, Channel 1 image width 7~0		*/
#define SIU_CH1_WIDTH1			(SIU_BASE+0x0040)	/* R/W, 0, Channel 1 image width 13~8		*/
#define SIU_CH1_HEIGHT0			(SIU_BASE+0x0041)	/* R/W, 0, Channel 1 image height 7~0		*/
#define SIU_CH1_HEIGHT1			(SIU_BASE+0x0042)	/* R/W, 0, Channel 1 image height 12~8		*/
#define SIU_CONF5			(SIU_BASE+0x0043)	/* R/W, 0, Config register			*/
#define SIU_CONF6			(SIU_BASE+0x0044)	/* R/W, 0, Config register			*/

/*
 * Structure Definition
 */
struct siuinface {
	// sensor interface
	unsigned short	x_ofs;
	unsigned short	y_ofs;
	unsigned short	width;
	unsigned short	height;

	// memory interface
	unsigned long	fb1;
	unsigned long	fb2;
	unsigned long	fb3;
	unsigned long	jmp;

	// control
	union {
		unsigned char	v;
		struct {
			unsigned char	scan	: 1;	// 0 = progressive, 1 = interlace
			unsigned char	rsv0	: 1;	// reserve
			unsigned char	format	: 1;	// 0 = raw8/yuv,    1 = raw10
			unsigned char	rsv1	: 1;	// reserve
			unsigned char	online	: 1;	// 0 = off-line,    1 = on-line
			unsigned char	rsv2	: 1;	// reserve
			unsigned char	raw8lsb : 1;	// raw8_lsb
			unsigned char	rsv3	: 1;	// reserve
		} b;
	} cf1;
	union {
		unsigned char	v;
		struct {
			unsigned char	ext	: 4;
			unsigned char	sync	: 2;	// 0 = , 1 = , 2 = , 3 =
			unsigned char	sedge	: 1;	// 0 = rising-edge, 1 = falling-edge
			unsigned char	hmode	: 1;	// 0 = H-SYNC,      1 = HREF
		} b;
	} cf2;
};


struct siuctrl {
	union {
		unsigned char	v;
		struct {
			unsigned char	progressive0	: 1;	// 1 = progressive, 0 = interlace
			unsigned char	progressive1	: 1;
			unsigned char	single0		: 1;	// 1 = single capture
			unsigned char	single1		: 1;
			unsigned char	parser_en	: 1;	// 1 = enable
			unsigned char	parser_chsel	: 1;	// 1 = channel 1, 0 = channel 0
			unsigned char	parser_rst	: 1;	// 0 = reset
		} b;
	} cf6;
};


extern struct siuinface		siu[2];
extern struct siuctrl		siuc;


/* */
extern void	siu_init(void);
extern void	siu_startup(void);
extern void 	siu_stop(void);


#endif /* __REGS_SIU_H__ */
