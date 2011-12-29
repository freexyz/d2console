/*
 * include/regs_sou.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *	2011.11.22	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */

#include <configs.h>

#if !defined(__REGS_SOU_H__)
#define __REGS_SOU_H__

#if !defined(SOU_BASE)
#error Please define 'SOU_BASE'
#endif

#define	SOU_POLARITY				(SOU_BASE+0x0000)	/* R/W,	   0,							*/
#define	SOU_MULTI_CH_EN				(SOU_BASE+0x0001)	/* R/W,	    , SOU multi-channel	enable bits			*/
#define SOU_INT_STATE				(SOU_BASE+0x0002)	/* R/W,    x, SOU status register				*/
#define SOU_INT_CLR				(SOU_BASE+0x0003)
#define SOU_INT_MASK				(SOU_BASE+0x0004)
#define SOU_BLANK0				(SOU_BASE+0x0005)
#define SOU_BLANK1				(SOU_BASE+0x0006)
#define SOU_BLANK2				(SOU_BASE+0x0007)
#define SOU_BLANK3				(SOU_BASE+0x0008)

#define	SOU_ENCODER_0_MODE			(SOU_BASE+0x0010)	/* R/W,	    ,							*/
#define	SOU_TG0_CFG				(SOU_BASE+0x0011)	/* R/W,	    ,							*/

// UNIT: Pixel
#define	SOU_TG0_WIDTH_0				(SOU_BASE+0x0012)	/* R/W,	0x0C, The width	of SOU_TG_0 panning windows		*/
#define	SOU_TG0_WIDTH_1				(SOU_BASE+0x0013)	/* R/W,	0x03,  within IPU active region				*/
#define	SOU_TG0_HEIGHT_0			(SOU_BASE+0x0014)	/* R/W,	0x07, The height of SOU_TG_0 panning windows		*/
#define	SOU_TG0_HEIGHT_1			(SOU_BASE+0x0015)	/* R/W,	0x01,  within IPU active region				*/
#define	SOU_TG0_PANNING_X_0			(SOU_BASE+0x0016)	/* R/W,	   0, Horizontal offset	within IPU active region	*/
#define	SOU_TG0_PANNING_X_1			(SOU_BASE+0x0017)	/* R/W,	   0,							*/
#define	SOU_TG0_PANNING_Y_0			(SOU_BASE+0x0018)	/* R/W,	   0,							*/
#define	SOU_TG0_PANNING_Y_1			(SOU_BASE+0x0019)	/* R/W,	   0,							*/

#define SOU_TG0_TMODE				(SOU_BASE+0x001A)

// UNIT: byte
#define	SOU_TG0_CLKS_PERH_0			(SOU_BASE+0x001B)	/* R/W,	0x0C, Set the clock counts per line			*/
#define	SOU_TG0_CLKS_PERH_1			(SOU_BASE+0x001C)	/* R/W,	0x03,							*/
#define	SOU_TG0_HSYNC_START_0			(SOU_BASE+0x001D)	/* R/W,	0x01, The starting clock count of Hsync	signal		*/
#define	SOU_TG0_HSYNC_START_1			(SOU_BASE+0x001E)	/* R/W,	   0,							*/
#define	SOU_TG0_HSYNC_END_0			(SOU_BASE+0x001F)	/* R/W,	0x0B, The ending clock count of	Hsync signal		*/
#define	SOU_TG0_HSYNC_END_1			(SOU_BASE+0x0020)	/* R/W,	   0,							*/
#define	SOU_TG0_HACTIVE_START_0			(SOU_BASE+0x0021)	/* R/W,	0x50, Horizontal active	region start position		*/
#define	SOU_TG0_HACTIVE_START_1			(SOU_BASE+0x0022)	/* R/W,	0x00,							*/
#define	SOU_TG0_HACTIVE_END_0			(SOU_BASE+0x0023)	/* R/W,	0xD0, Horizontal active	region end position		*/
#define	SOU_TG0_HACTIVE_END_1			(SOU_BASE+0x0024)	/* R/W,	   2,							*/
#define	SOU_TG0_LINES_PERV_0			(SOU_BASE+0x0025)	/* R/W,	0x07, Set the line counts per frame			*/
#define	SOU_TG0_LINES_PERV_1			(SOU_BASE+0x0026)	/* R/W,	0x01,							*/
#define	SOU_TG0_VSYNC_START_LINE_0		(SOU_BASE+0x0027)	/* R/W,	0x01, VSync Starting line, In Interlace	mode,		*/
#define	SOU_TG0_VSYNC_START_LINE_1		(SOU_BASE+0x0028)	/* R/W,	   0, this register will be the	odd field setting	*/
#define	SOU_TG0_VSYNC_START_CLK_0		(SOU_BASE+0x0029)	/* R/W,	0x01, VSync Starting clock				*/
#define	SOU_TG0_VSYNC_START_CLK_1		(SOU_BASE+0x002A)	/* R/W,	   0,							*/
#define	SOU_TG0_VSYNC_END_LINE_0		(SOU_BASE+0x002B)	/* R/W,	0x05, VSync Ending line					*/
#define	SOU_TG0_VSYNC_END_LINE_1		(SOU_BASE+0x002C)	/* R/W,	   0,							*/
#define	SOU_TG0_VSYNC_END_CLK_0			(SOU_BASE+0x002D)	/* R/W,	0x05, VSync Ending clock				*/
#define	SOU_TG0_VSYNC_END_CLK_1			(SOU_BASE+0x002E)	/* R/W,	   0,							*/
#define	SOU_TG0_VACTIVE_START_0			(SOU_BASE+0x002F)	/* R/W,	0x14, Vertical active region start			*/
#define	SOU_TG0_VACTIVE_START_1			(SOU_BASE+0x0030)	/* R/W,	   0,							*/
#define	SOU_TG0_VACTIVE_END_0			(SOU_BASE+0x0031)	/* R/W,	0x04, Vertical active region end			*/
#define	SOU_TG0_VACTIVE_END_1			(SOU_BASE+0x0032)	/* R/W,	0x01,							*/
#define	SOU_TG0_EVEN_VSYNC_START_LINE_0		(SOU_BASE+0x0033)	/* R/W,	0x01, Even VSync Starting line,	In Interlace mode,	*/
#define	SOU_TG0_EVEN_VSYNC_START_LINE_1		(SOU_BASE+0x0034)	/* R/W,	   0, this register will be the	even field setting	*/
#define	SOU_TG0_EVEN_VSYNC_START_CLK_0		(SOU_BASE+0x0035)	/* R/W,	0x01, Even VSync Starting clock				*/
#define	SOU_TG0_EVEN_VSYNC_START_CLK_1		(SOU_BASE+0x0036)	/* R/W,	   0,							*/
#define	SOU_TG0_EVEN_VSYNC_END_LINE_0		(SOU_BASE+0x0037)	/* R/W,	0x05, Even VSync Ending	line				*/
#define	SOU_TG0_EVEN_VSYNC_END_LINE_1		(SOU_BASE+0x0038)	/* R/W,	   0,							*/
#define	SOU_TG0_EVEN_VSYNC_END_CLK_0		(SOU_BASE+0x0039)	/* R/W,	0x05, Even VSync Ending	clock				*/
#define	SOU_TG0_EVEN_VSYNC_END_CLK_1		(SOU_BASE+0x003A)	/* R/W,	   0,							*/
#define	SOU_TG0_EVEN_VACTIVE_START_0		(SOU_BASE+0x003B)	/* R/W,	0x14, Even Vertical active region start			*/
#define	SOU_TG0_EVEN_VACTIVE_START_1		(SOU_BASE+0x003C)	/* R/W,	   0,							*/
#define	SOU_TG0_EVEN_VACTIVE_END_0		(SOU_BASE+0x003D)	/* R/W,	0x04, Even Vertical active region end			*/
#define	SOU_TG0_EVEN_VACTIVE_END_1		(SOU_BASE+0x003E)	/* R/W,	0x01,							*/
#define	SOU_TG0_CCIR656_F_START_0		(SOU_BASE+0x003F)	/* R/W,	   0, CCIR656 F	Start register				*/
#define	SOU_TG0_CCIR656_F_START_1		(SOU_BASE+0x0040)	/* R/W,	   0,							*/
#define	SOU_TG0_CCIR656_F_END_0			(SOU_BASE+0x0041)	/* R/W,	   0, CCIR656 F	End register				*/
#define	SOU_TG0_CCIR656_F_END_1			(SOU_BASE+0x0042)	/* R/W,	   0,							*/
#define SOU_TG0_RAW8_MASK			(SOU_BASE+0x0043)

#define	SOU_ENCODER_1_MODE			(SOU_BASE+0x0050)	/* R/W,	   0, Encoder_1	mode selection				*/
#define	SOU_TG1_CFG				(SOU_BASE+0x0051)	/* R/W,	   0,							*/
#define	SOU_TG1_WIDTH_0				(SOU_BASE+0x0052)	/* R/W,	0x0C, The width	of SOU_TG_1 panning windows		*/
#define	SOU_TG1_WIDTH_1				(SOU_BASE+0x0053)	/* R/W,	0x03, within IPU active	region				*/
#define	SOU_TG1_HEIGHT_0			(SOU_BASE+0x0054)	/* R/W,	0x07, The height of SOU_TG_1 panning windows		*/
#define	SOU_TG1_HEIGHT_1			(SOU_BASE+0x0055)	/* R/W,	0x01, within IPU active	region				*/
#define	SOU_TG1_PANNING_X_0			(SOU_BASE+0x0056)	/* R/W,	   0, Horizontal offset	within IPU active region	*/
#define	SOU_TG1_PANNING_X_1			(SOU_BASE+0x0057)	/* R/W,	   0,							*/
#define	SOU_TG1_PANNING_Y_0			(SOU_BASE+0x0058)	/* R/W,	   0, Vertical offset within IPU active	region		*/
#define	SOU_TG1_PANNING_Y_1			(SOU_BASE+0x0059)	/* R/W,	   0,							*/
#define	SOU_TG1_TMODE				(SOU_BASE+0x005A)	/* R/W,	   0,							*/
#define	SOU_TG1_CLKS_PERH_0			(SOU_BASE+0x005B)	/* R/W,	0x0C, Set the clock counts per line			*/
#define	SOU_TG1_CLKS_PERH_1			(SOU_BASE+0x005C)	/* R/W,	0x03,							*/
#define	SOU_TG1_HSYNC_START_0			(SOU_BASE+0x005D)	/* R/W,	0x01, The starting clock count of Hsync	signal		*/
#define	SOU_TG1_HSYNC_START_1			(SOU_BASE+0x005E)	/* R/W,	   0,							*/
#define	SOU_TG1_HSYNC_END_0			(SOU_BASE+0x005F)	/* R/W,	0x0B, The ending clock count of	Hsync signal		*/
#define	SOU_TG1_HSYNC_END_1			(SOU_BASE+0x0060)	/* R/W,	   0,							*/
#define	SOU_TG1_HACTIVE_START_0			(SOU_BASE+0x0061)	/* R/W,	0x50, Horizontal active	region start position		*/
#define	SOU_TG1_HACTIVE_START_1			(SOU_BASE+0x0062)	/* R/W,	0x00,							*/
#define	SOU_TG1_HACTIVE_END_0			(SOU_BASE+0x0063)	/* R/W,	0xD0, Horizontal active	region end position		*/
#define	SOU_TG1_HACTIVE_END_1			(SOU_BASE+0x0064)	/* R/W,	   2,							*/
#define	SOU_TG1_LINES_PERV_0			(SOU_BASE+0x0065)	/* R/W,	0x07, Set the line counts per frame			*/
#define	SOU_TG1_LINES_PERV_1			(SOU_BASE+0x0066)	/* R/W,	0x01,							*/
#define	SOU_TG1_VSYNC_START_LINE_0		(SOU_BASE+0x0067)	/* R/W,	0x01, VSync Starting line, In Interlace	mode,		*/
#define	SOU_TG1_VSYNC_START_LINE_1		(SOU_BASE+0x0068)	/* R/W,	   0, this register will be the	odd field setting	*/
#define	SOU_TG1_VSYNC_START_CLK_0		(SOU_BASE+0x0069)	/* R/W,	0x01, VSync Starting clock				*/
#define	SOU_TG1_VSYNC_START_CLK_1		(SOU_BASE+0x006A)	/* R/W,	   0,							*/
#define	SOU_TG1_VSYNC_END_LINE_0		(SOU_BASE+0x006B)	/* R/W,	0x05, VSync Ending line					*/
#define	SOU_TG1_VSYNC_END_LINE_1		(SOU_BASE+0x006C)	/* R/W,	   0,							*/
#define	SOU_TG1_VSYNC_END_CLK_0			(SOU_BASE+0x006D)	/* R/W,	0x05, VSync Ending clock				*/
#define	SOU_TG1_VSYNC_END_CLK_1			(SOU_BASE+0x006E)	/* R/W,	   0,							*/
#define	SOU_TG1_VACTIVE_START_0			(SOU_BASE+0x006F)	/* R/W,	0x14, Vertical active region start			*/
#define	SOU_TG1_VACTIVE_START_1			(SOU_BASE+0x0070)	/* R/W,	   0,							*/
#define	SOU_TG1_VACTIVE_END_0			(SOU_BASE+0x0071)	/* R/W,	0x04, Vertical active region end			*/
#define	SOU_TG1_VACTIVE_END_1			(SOU_BASE+0x0072)	/* R/W,	0x01,							*/
#define	SOU_TG1_EVEN_VSYNC_START_LINE_0		(SOU_BASE+0x0073)	/* R/W,	0x01, Even VSync Starting line,	In Interlace mode,	*/
#define	SOU_TG1_EVEN_VSYNC_START_LINE_1		(SOU_BASE+0x0074)	/* R/W,	   0, this register will be the	even field setting	*/
#define	SOU_TG1_EVEN_VSYNC_START_CLK_0		(SOU_BASE+0x0075)	/* R/W,	0x01, Even VSync Starting clock				*/
#define	SOU_TG1_EVEN_VSYNC_START_CLK_1		(SOU_BASE+0x0076)	/* R/W,	   0,							*/
#define	SOU_TG1_EVEN_VSYNC_END_LINE_0		(SOU_BASE+0x0077)	/* R/W,	0x05, Even VSync Ending	line				*/
#define	SOU_TG1_EVEN_VSYNC_END_LINE_1		(SOU_BASE+0x0078)	/* R/W,	   0,							*/
#define	SOU_TG1_EVEN_VSYNC_END_CLK_0		(SOU_BASE+0x0079)	/* R/W,	0x05, Even VSync Ending	clock				*/
#define	SOU_TG1_EVEN_VSYNC_END_CLK_1		(SOU_BASE+0x007A)	/* R/W,	   0,							*/
#define	SOU_TG1_EVEN_VACTIVE_START_0		(SOU_BASE+0x007B)	/* R/W,	0x14, Even Vertical active region start			*/
#define	SOU_TG1_EVEN_VACTIVE_START_1		(SOU_BASE+0x007C)	/* R/W,	   0,							*/
#define	SOU_TG1_EVEN_VACTIVE_END_0		(SOU_BASE+0x007D)	/* R/W,	0x04, Even Vertical active region end			*/
#define	SOU_TG1_EVEN_VACTIVE_END_1		(SOU_BASE+0x007E)	/* R/W,	0x01,							*/
#define	SOU_TG1_CCIR656_F_START_0		(SOU_BASE+0x007F)	/* R/W,	   0, CCIR656 F	Start register				*/
#define	SOU_TG1_CCIR656_F_START_1		(SOU_BASE+0x0080)	/* R/W,	   0,							*/
#define	SOU_TG1_CCIR656_F_END_0			(SOU_BASE+0x0081)	/* R/W,	   0, CCIR656 F	End register				*/
#define	SOU_TG1_CCIR656_F_END_1			(SOU_BASE+0x0082)	/* R/W,	   0,							*/
#define SOU_TG1_RAW8_MASK			(SOU_BASE+0x0083)


enum sou_tmode {
	WHITE = 0,
	YELLOW,
	CYAN,
	GREEN,
	MAGENTA,
	RED,
	BLUE,
	BLACK,
};


/*
 * Structure Definition
 */
struct souinface {
	unsigned char	mode;
	union {
		unsigned char	v;
		struct {
			unsigned char	enable		: 1;	// 0 = disable, 1 = enable
			unsigned char	interlace	: 1;	// 0 = progressive, 1 = interlace
			unsigned char	gateclk		: 1;	// 1 = enable gate clock
			unsigned char	rsv		: 5;	// reserve
		} b;
	} cfg;

	// ipu interface
	unsigned short	width;					// active pixel per line
	unsigned short	height;					// active line per frame
	unsigned short	x_panning;
	unsigned short	y_panning;

	// output interface
	unsigned char	tstmode;
	unsigned short	ppl;					// pixel per line
	unsigned short	hsync_start;
	unsigned short	hsync_end;
	unsigned short	hactive_start;
	unsigned short	hactive_end;
	unsigned short	lpf;					// line per frame
	unsigned short	vsync_start_line;
	unsigned short	vsync_start_clk;
	unsigned short	vsync_end_line;
	unsigned short	vsync_end_clk;
	unsigned short	vactive_start;
	unsigned short	vactive_end;
	unsigned short	even_vsync_start_line;
	unsigned short	even_vsync_start_clk;
	unsigned short	even_vsync_end_line;
	unsigned short	even_vsync_end_clk;
	unsigned short	even_vactive_start;
	unsigned short	even_vactive_end;
	unsigned short	ccir656_f_start;
	unsigned short	ccir656_f_end;
	unsigned char	raw8_mask;
};


struct souctrl {
	union {
		unsigned char	v;
		struct {
			unsigned char	hsync	: 1;	// 0 = active low, 1 = active high
	 		unsigned char	vsync	: 1;	// 0 = active low, 1 = active high
			unsigned char	href	: 1;	// 0 = active low, 1 = active high
			unsigned char	pclk	: 1;	// 1 = inverse the SOU_Clk
			unsigned char	rsv1	: 4;
		} b;
	} polarity;

	unsigned char	multich;
	unsigned char	int_state; 
	unsigned char	int_clr;
	unsigned char	int_mask;
	unsigned long	blinkval;			// raw mode: B Gb Gr R, YCbCr mode: x Cr Cb Y
};


extern struct souinface volatile __xdata	*sou0;
extern struct souinface volatile __xdata	*sou1;
extern struct souctrl   volatile __xdata	*souc;

/* Function Prototype */
extern void		sou_stop(void);



#endif /* __REGS_SOU_H__ */
