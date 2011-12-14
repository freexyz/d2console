/* regs_sys.h --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */

#include <configs.h>

#if !defined(__REGS_SYS_H__)
#define __REGS_SYS_H__

#if !defined(SYS_BASE)
#error Please define 'SYS_BASE'
#endif


/*
 * Register Definition
 */
#define PLL_M			(SYS_BASE+0x0000)	/* RW, 0x14, PLL Feedback divider control					*/
							/*	PLL_OUT = Xin * (pll_m/pll_n) * (1/1+pll_k)				*/
#define PLL_N			(SYS_BASE+0x0001)	/* RW, 0x02, PLL Input divider control						*/
#define PLL_K			(SYS_BASE+0x0002)	/* RW, 0x00, PLL post divider for output clock					*/
							/*		[0] :	0 ¡V pass through					*/
							/*			1 ¡V divided by 2					*/
							/*		[1] : PLL power down control					*/
							/*			0 ¡V Normal operation					*/
							/*			1 ¡V Power down mode					*/
							/*		[3:2]: PLL test mode						*/
							/*			00 ¡V normal operation					*/
#define CLKSEL			(SYS_BASE+0x0003)	/* RW,    0,									*/
							/*		[0] :	Input clock source select				*/
							/*			0 ¡V Xin							*/
							/*			1 ¡V Sensor pixel clock					*/
							/*		[1] :	Sensor clock source select				*/
							/*			0 ¡V Sensor0 pixel clock					*/
							/*			1 ¡V Sensor1 pixel clock					*/
							/*		[2] :	Main clock source select				*/
							/*			0 ¡V Input clock mux select result			*/
							/*			1 ¡V PLL output						*/
							/*		[3] :	Output clock source select				*/
							/*			0 ¡V Sensor clock mux result				*/
							/*			1 ¡V Divide by main clock				*/
#define MUX_MODE		(SYS_BASE+0x0004)	/* RW,    0,									*/
							/* 		[0] :	Input clock mux mode select.				*/
							/* 			Two input clock must be active on glitch free mode.	*/
							/* 			When all input clocks source are active, suggest use	*/
							/* 			glitch free mode.					*/
							/* 			0 ¡V Combination mode					*/
							/* 			1 - glitch free mode					*/
							/* 		[1] : 	Sensor clock mux mode select				*/
							/* 			0 ¡V Combination mode					*/
							/* 			1 - glitch free mode					*/
							/* 		[2] :	Main clock mux mode select				*/
							/* 			0 ¡V Combination mode					*/
							/* 			1- glitch free mode					*/
							/* 		[3] :	Output clock mux mode select				*/
							/* 			0 ¡V Combination mode					*/
							/* 			1- glitch free mode					*/
#define SDRCLK			(SYS_BASE+0x0005)	/* RW, 0x80,									*/
							/*		[3:0]: SDRAM clock divider control register			*/
							/*			0  ¡V bypass mode					*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
							/*		[7] :	SDRAM clock output enable				*/
							/*			 When SDRAM free mode, must be disable			*/
#define MCLK			(SYS_BASE+0x0006)	/* RW,    0,									*/
							/*		[3:0]: Main clock divider control register			*/
							/*			0  ¡V bypass mode					*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
#define SOUCLK			(SYS_BASE+0x0007)	/* RW,    0,									*/
							/*		[3:0]: SOU clock divider control register			*/
							/*			0  ¡V bypass mode					*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
							/*		[7]:	For multi-channel CCIR mode,				*/
							/*			SOU_CLK and HSN_CLK relation must be 2x			*/
							/*			0 ¡V Disable						*/
							/*			1 ¡V Enable						*/
#define SPICLK			(SYS_BASE+0x0008)	/* RW,    0,									*/
							/*		[3:0]:	SPI flash controller clock divider control register	*/
							/*			0  ¡V 1/2						*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
#define SPI_CLK_WIDTH		(SYS_BASE+0x0009)	/* RW,    0, [3:0] SPI flash clock duty control					*/
#define SN0CLK			(SYS_BASE+0x000A)	/* RW, 0x80, [3:0] Sensor0 output clock divider control register		*/
							/*			0  ¡V bypass mode					*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
							/*           [7] Sensor 0 clock output enable					*/
#define SN1CLK			(SYS_BASE+0x000B)	/* RW, 0x80, [3:0] Sensor1 output clock divider control register		*/
							/*			0  ¡V bypass mode					*/
							/*			1  ¡V 1/2						*/
							/*			2  ¡V 1/3						*/
							/*			15 ¡V 1/16						*/
							/*	     [7] Sensor 1 clock output enable					*/
#define SDRAM_DLY		(SYS_BASE+0x000C)	/* RW,    0, [4:0] SDR SDRAM clock output delay select				*/
							/*			00 ¡V no delay						*/
							/*			01 ¡V delay 0.5ns (It¡¦s estimate)			*/
							/*			02 - 							*/
#define HSN_DLY			(SYS_BASE+0x000D)	/* RW,    0, [4:0] Host sensor output clock delay select			*/
							/*			00 ¡V no delay						*/
							/*			01 ¡V delay 0.5ns (It¡¦s estimate)			*/
							/*			02 - 							*/
#define SN0_DLY			(SYS_BASE+0x000E)	/* RW,    0, [4:0] Sensor 0 output clock delay select				*/
							/*			00 ¡V no delay						*/
							/*			01 ¡V delay 0.5ns (It¡¦s estimate)			*/
#define SN1_DLY			(SYS_BASE+0x000F)	/* RW,    0, [4:0] Sensor 1 output clock delay select				*/
							/*			00 ¡V no delay						*/
							/*			01 ¡V delay 0.5ns (It¡¦s estimate)			*/
#define PIO0_MODE		(SYS_BASE+0x0010)	/* RW, 0xFF, PIO0  MODE register						*/
							/*		0 ¡V PIO mode							*/
							/*		1 ¡V Normal mode							*/
#define PIO1_MODE		(SYS_BASE+0x0011)	/* RW, 0xFF, PIO1  MODE register						*/
#define PIO2_MODE		(SYS_BASE+0x0012)	/* RW, 0xFF, PIO2  MODE register						*/
#define PIO3_MODE		(SYS_BASE+0x0013)	/* RW, 0xFF, PIO3  MODE register						*/
#define PIO4_MODE		(SYS_BASE+0x0014)	/* RW, 0xFF, PIO4  MODE register						*/
#define PIO5_MODE		(SYS_BASE+0x0015)	/* RW, 0xFF, PIO5  MODE register						*/
#define PIO6_MODE		(SYS_BASE+0x0016)	/* RW, 0xFF, PIO6  MODE register						*/
#define PIO7_MODE		(SYS_BASE+0x0017)	/* RW, 0xFF, PIO7  MODE register						*/
#define PIO8_MODE		(SYS_BASE+0x0018)	/* RW, 0xFF, PIO8  MODE register						*/
#define PIO9_MODE		(SYS_BASE+0x0019)	/* RW, 0xFF, PIO9  MODE register						*/
#define PIO10_MODE		(SYS_BASE+0x001A)	/* RW, 0xFF, PIO10 MODE register						*/
#define HADDRL			(SYS_BASE+0x0020)	/* RW,    0, [7:0] XRAM to MEM bank register					*/
#define HADDRH			(SYS_BASE+0x0021)	/* RW,    0, [0]   XRAM to MEM bank register					*/
							/*		MEM addr = { HADDRH[0], HADDRL[7:0] , XRAM[14:0] }		*/
#define BYPASS			(SYS_BASE+0x0022)	/* RW,    0, [0] Sensor input select when bypass mode				*/
							/*	     [1] Bypass mode							*/
							/*		0 ¡V bypass all HW module, output source select by sn_in_sel	*/
							/*		1 ¡V Host sensor output from SOU					*/

#endif /* __REGS_SYS_H__ */

