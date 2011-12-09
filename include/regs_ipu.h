/*
 * include/regs_ipu.h --
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
 *
 */

#include <configs.h>

#if !defined(__REGS_IPU_H__)
#define __REGS_IPU_H__

#if !defined(IPU_BASE)
#error Please define 'IPU_BASE'
#endif

#define IPU_CTRL			(IPU_BASE+0x0000)	/* R/W,    0, Control register				*/
#define IPU_CONF1			(IPU_BASE+0x0001)	/* R/W,    0, Config register				*/
#define IPU_CONF2			(IPU_BASE+0x0002)	/* R/W,    0, Config register				*/
#define IPU_STATUS			(IPU_BASE+0x0003)	/* R/W,    0, Status & clear frame interrupt		*/
#define IPU_CH0_F1S0			(IPU_BASE+0x0004)	/* R/W,    0, Channel 0 frame1 start address 7~0	*/
#define IPU_CH0_F1S1			(IPU_BASE+0x0005)	/* R/W,    0, Channel 0 frame1 start address 15~8	*/
#define IPU_CH0_F1S2			(IPU_BASE+0x0006)	/* R/W,    0, Channel 0 frame1 start address 23~16	*/
#define IPU_CH0_F1S3			(IPU_BASE+0x0007)	/* R/W,    0, Channel 0 frame1 start address 31~24	*/
#define IPU_CH0_F2S0			(IPU_BASE+0x0008)	/* R/W,    0, Channel 0 frame2 start address 7~0	*/
#define IPU_CH0_F2S1			(IPU_BASE+0x0009)	/* R/W,    0, Channel 0 frame2 start address 15~8	*/
#define IPU_CH0_F2S2			(IPU_BASE+0x000A)	/* R/W,    0, Channel 0 frame2 start address 23~16	*/
#define IPU_CH0_F2S3			(IPU_BASE+0x000B)	/* R/W,    0, Channel 0 frame2 start address 31~24	*/
#define IPU_CH0_F3S0			(IPU_BASE+0x000C)	/* R/W,    0, Channel 0 frame3 start address 7~0	*/
#define IPU_CH0_F3S1			(IPU_BASE+0x000D)	/* R/W,    0, Channel 0 frame3 start address 15~8	*/
#define IPU_CH0_F3S2			(IPU_BASE+0x000E)	/* R/W,    0, Channel 0 frame3 start address 23~16	*/
#define IPU_CH0_F3S3			(IPU_BASE+0x000F)	/* R/W,    0, Channel 0 frame3 start address 31~24	*/
#define IPU_CH1_F1S0			(IPU_BASE+0x0010)	/* R/W,    0, Channel 1 frame1 start address 7~0	*/
#define IPU_CH1_F1S1			(IPU_BASE+0x0011)	/* R/W,    0, Channel 1 frame1 start address 15~8	*/
#define IPU_CH1_F1S2			(IPU_BASE+0x0012)	/* R/W,    0, Channel 1 frame1 start address 23~16	*/
#define IPU_CH1_F1S3			(IPU_BASE+0x0013)	/* R/W,    0, Channel 1 frame1 start address 31~24	*/
#define IPU_CH1_F2S0			(IPU_BASE+0x0014)	/* R/W,    0, Channel 1 frame2 start address 7~0	*/
#define IPU_CH1_F2S1			(IPU_BASE+0x0015)	/* R/W,    0, Channel 1 frame2 start address 15~8	*/
#define IPU_CH1_F2S2			(IPU_BASE+0x0016)	/* R/W,    0, Channel 1 frame2 start address 23~16	*/
#define IPU_CH1_F2S3			(IPU_BASE+0x0017)	/* R/W,    0, Channel 1 frame2 start address 31~24	*/
#define IPU_CH1_F3S0			(IPU_BASE+0x0018)	/* R/W,    0, Channel 1 frame3 start address 7~0	*/
#define IPU_CH1_F3S1			(IPU_BASE+0x0019)	/* R/W,    0, Channel 1 frame3 start address 15~8	*/
#define IPU_CH1_F3S2			(IPU_BASE+0x001A)	/* R/W,    0, Channel 1 frame3 start address 23~16	*/
#define IPU_CH1_F3S3			(IPU_BASE+0x001B)	/* R/W,    0, Channel 1 frame3 start address 31~24	*/
#define IPU_CH0_CROP_W0			(IPU_BASE+0x001C)	/* R/W,    0, Channel 0 crop image width 7~0		*/
#define IPU_CH0_CROP_W1			(IPU_BASE+0x001D)	/* R/W,    0, Channel 0 crop image width 15~8		*/
#define IPU_CH0_ORI_W0			(IPU_BASE+0x001E)	/* R/W,    0, Channel 0 original image width 7~0	*/
#define IPU_CH0_ORI_W1			(IPU_BASE+0x001F)	/* R/W,    0, Channel 0 original image width 15~8	*/
#define IPU_CH0_H0			(IPU_BASE+0x0020)	/* R/W,    0, Channel 0 original image width 7~0	*/
#define IPU_CH0_H1			(IPU_BASE+0x0021)	/* R/W,    0, Channel 0 original image width 12~8	*/
#define IPU_CH1_CROP_W0			(IPU_BASE+0x0022)	/* R/W,    0, Channel 1 crop image width 7~0		*/
#define IPU_CH1_CROP_W1			(IPU_BASE+0x0023)	/* R/W,    0, Channel 1 crop image width 15~8		*/
#define IPU_CH1_ORI_W0			(IPU_BASE+0x0024)	/* R/W,    0, Channel 1 original image width 7~0	*/
#define IPU_CH1_ORI_W1			(IPU_BASE+0x0025)	/* R/W,    0, Channel 1 original image width 15~8	*/
#define IPU_CH1_H0			(IPU_BASE+0x0026)	/* R/W,    0, Channel 1 original image width 7~0	*/
#define IPU_CH1_H1			(IPU_BASE+0x0027)	/* R/W,    0, Channel 1 original image width 12~8	*/
#define IPU_CH0_LEND			(IPU_BASE+0x0028)	/* R/W, 0x31, Channel 0 crop frame right width resident	*/
#define IPU_CH0_LSTART			(IPU_BASE+0x0029)	/* R/W,    0, Channel 0 crop frame left  width resident	*/
#define IPU_CH1_LEND			(IPU_BASE+0x002A)	/* R/W, 0x31, Channel 1 crop frame right width resident	*/
#define IPU_CH1_LSTART			(IPU_BASE+0x002B)	/* R/W,    0, Channel 1 crop frame left  width resident	*/
#define IPU_CONF3			(IPU_BASE+0x002C)	/* R/W,    0, Config register				*/
#define IPU_CONF4			(IPU_BASE+0x002D)	/* R/W,    0, Config register				*/
#define IPU_CONF5			(IPU_BASE+0x002E)	/* R/W,    0, Config register				*/
#define IPU_CONF6			(IPU_BASE+0x002F)	/* R/W,    0, Config register				*/
#define IPU_OVERLAP0			(IPU_BASE+0X0030)	/* R/W,    0, Overlap width for fussy stitch 7~0	*/
#define IPU_OVERLAP1			(IPU_BASE+0X0031)	/* R/W,    0, Overlap width for fussy stitch 15~8	*/
#define IPU_RC_A11_L			(IPU_BASE+0X0034)	/* R/W,    0, Red cyan a11[7:0]   cofficoent		*/
#define IPU_RC_A11_M			(IPU_BASE+0x0035)	/* R/W,    0, Red cyan a11[15:8]  cofficoent		*/
#define IPU_RC_A11_H			(IPU_BASE+0x0036)	/* R/W,    0, Red cyan a11[19:16] cofficoent		*/
#define IPU_RC_A12_L			(IPU_BASE+0x0037)	/* R/W,    0, Red cyan a12[7:0]   cofficoent		*/
#define IPU_RC_A12_M			(IPU_BASE+0x0038)	/* R/W,    0, Red cyan a12[15:8]  cofficoent		*/
#define IPU_RC_A12_H			(IPU_BASE+0x0039)	/* R/W,    0, Red cyan a12[19:16] cofficoent		*/
#define IPU_RC_A13_L			(IPU_BASE+0x003A)	/* R/W,    0, Red cyan a13[7:0]   cofficoent		*/
#define IPU_RC_A13_M			(IPU_BASE+0x003B)	/* R/W,    0, Red cyan a13[15:8]  cofficoent		*/
#define IPU_RC_A13_H			(IPU_BASE+0x003C)	/* R/W,    0, Red cyan a13[19:16] cofficoent		*/
#define IPU_RC_A14_L			(IPU_BASE+0x003D)	/* R/W,    0, Red cyan a14[7:0]   cofficoent		*/
#define IPU_RC_A14_M			(IPU_BASE+0x003E)	/* R/W,    0, Red cyan a14[15:8]  cofficoent		*/
#define IPU_RC_A14_H			(IPU_BASE+0x003F)	/* R/W,    0, Red cyan a14[19:16] cofficoent		*/
#define IPU_RC_A15_L			(IPU_BASE+0x0040)	/* R/W,    0, Red cyan a15[7:0]   cofficoent		*/
#define IPU_RC_A15_M			(IPU_BASE+0x0041)	/* R/W,    0, Red cyan a15[15:8]  cofficoent		*/
#define IPU_RC_A15_H			(IPU_BASE+0x0042)	/* R/W,    0, Red cyan a15[19:16] cofficoent		*/
#define IPU_RC_A16_L			(IPU_BASE+0x0043)	/* R/W,    0, Red cyan a16[7:0]   cofficoent		*/
#define IPU_RC_A16_M			(IPU_BASE+0x0044)	/* R/W,    0, Red cyan a16[15:8]  cofficoent		*/
#define IPU_RC_A16_H			(IPU_BASE+0x0045)	/* R/W,    0, Red cyan a16[19:16] cofficoent		*/
#define IPU_RC_A21_L			(IPU_BASE+0x0046)	/* R/W,    0, Red cyan a21[7:0]   cofficoent		*/
#define IPU_RC_A21_M			(IPU_BASE+0x0047)	/* R/W,    0, Red cyan a21[15:8]  cofficoent		*/
#define IPU_RC_A21_H			(IPU_BASE+0x0048)	/* R/W,    0, Red cyan a21[19:16] cofficoent		*/
#define IPU_RC_A22_L			(IPU_BASE+0x0049)	/* R/W,    0, Red cyan a22[7:0]   cofficoent		*/
#define IPU_RC_A22_M			(IPU_BASE+0x004A)	/* R/W,    0, Red cyan a22[15:8]  cofficoent		*/
#define IPU_RC_A22_H			(IPU_BASE+0x004B)	/* R/W,    0, Red cyan a22[19:16] cofficoent		*/
#define IPU_RC_A23_L			(IPU_BASE+0x004C)	/* R/W,    0, Red cyan a23[7:0]   cofficoent		*/
#define IPU_RC_A23_M			(IPU_BASE+0x004D)	/* R/W,    0, Red cyan a23[15:8]  cofficoent		*/
#define IPU_RC_A23_H			(IPU_BASE+0x004E)	/* R/W,    0, Red cyan a23[19:16] cofficoent		*/
#define IPU_RC_A24_L			(IPU_BASE+0x004F)	/* R/W,    0, Red cyan a24[7:0]   cofficoent		*/
#define IPU_RC_A24_M			(IPU_BASE+0x0050)	/* R/W,    0, Red cyan a24[15:8]  cofficoent		*/
#define IPU_RC_A24_H			(IPU_BASE+0x0051)	/* R/W,    0, Red cyan a24[19:16] cofficoent		*/
#define IPU_RC_A25_L			(IPU_BASE+0x0052)	/* R/W,    0, Red cyan a25[7:0]   cofficoent		*/
#define IPU_RC_A25_M			(IPU_BASE+0x0053)	/* R/W,    0, Red cyan a25[15:8]  cofficoent		*/
#define IPU_RC_A25_H			(IPU_BASE+0x0054)	/* R/W,    0, Red cyan a25[19:16] cofficoent		*/
#define IPU_RC_A26_L			(IPU_BASE+0x0055)	/* R/W,    0, Red cyan a26[7:0]   cofficoent		*/
#define IPU_RC_A26_M			(IPU_BASE+0x0056)	/* R/W,    0, Red cyan a26[15:8]  cofficoent		*/
#define IPU_RC_A26_H			(IPU_BASE+0x0057)	/* R/W,    0, Red cyan a26[19:16] cofficoent		*/
#define IPU_RC_A31_L			(IPU_BASE+0x0058)	/* R/W,    0, Red cyan a31[7:0]   cofficoent		*/
#define IPU_RC_A31_M			(IPU_BASE+0x0059)	/* R/W,    0, Red cyan a31[15:8]  cofficoent		*/
#define IPU_RC_A31_H			(IPU_BASE+0x005A)	/* R/W,    0, Red cyan a31[19:16] cofficoent		*/
#define IPU_RC_A32_L			(IPU_BASE+0x005B)	/* R/W,    0, Red cyan a32[7:0]   cofficoent		*/
#define IPU_RC_A32_M			(IPU_BASE+0x005C)	/* R/W,    0, Red cyan a32[15:8]  cofficoent		*/
#define IPU_RC_A32_H			(IPU_BASE+0x005D)	/* R/W,    0, Red cyan a32[19:16] cofficoent		*/
#define IPU_RC_A33_L			(IPU_BASE+0x005E)	/* R/W,    0, Red cyan a33[7:0]   cofficoent		*/
#define IPU_RC_A33_M			(IPU_BASE+0x005F)	/* R/W,    0, Red cyan a33[15:8]  cofficoent		*/
#define IPU_RC_A33_H			(IPU_BASE+0x0060)	/* R/W,    0, Red cyan a33[19:16] cofficoent		*/
#define IPU_RC_A34_L			(IPU_BASE+0x0061)	/* R/W,    0, Red cyan a34[7:0]   cofficoent		*/
#define IPU_RC_A34_M			(IPU_BASE+0x0062)	/* R/W,    0, Red cyan a34[15:8]  cofficoent		*/
#define IPU_RC_A34_H			(IPU_BASE+0x0063)	/* R/W,    0, Red cyan a34[19:16] cofficoent		*/
#define IPU_RC_A35_L			(IPU_BASE+0x0064)	/* R/W,    0, Red cyan a35[7:0]   cofficoent		*/
#define IPU_RC_A35_M			(IPU_BASE+0x0065)	/* R/W,    0, Red cyan a35[15:8]  cofficoent		*/
#define IPU_RC_A35_H			(IPU_BASE+0x0066)	/* R/W,    0, Red cyan a35[19:16] cofficoent		*/
#define IPU_RC_A36_L			(IPU_BASE+0x0067)	/* R/W,    0, Red cyan a36[7:0]   cofficoent		*/
#define IPU_RC_A36_M			(IPU_BASE+0x0068)	/* R/W,    0, Red cyan a36[15:8]  cofficoent		*/
#define IPU_RC_A36_H			(IPU_BASE+0x0069)	/* R/W,    0, Red cyan a36[19:16] cofficoent		*/
#define IPU_RC_C1_L			(IPU_BASE+0x006A)	/* R/W,    0, Red cyan c1[7:0] cofficoent		*/
#define IPU_RC_C1_H			(IPU_BASE+0x006B)	/* R/W,    0, Red cyan c1[8]   cofficoent		*/
#define IPU_RC_C2_L			(IPU_BASE+0x006C)	/* R/W,    0, Red cyan c2[7:0] cofficoent		*/
#define IPU_RC_C2_H			(IPU_BASE+0x006D)	/* R/W,    0, Red cyan c2[8]   cofficoent		*/
#define IPU_RC_C3_L			(IPU_BASE+0x006E)	/* R/W,    0, Red cyan c3[7:0] cofficoent		*/
#define IPU_RC_C3_H			(IPU_BASE+0x006F)	/* R/W,    0, Red cyan c3[8]   cofficoent		*/
#define IPU_RC_C4_L			(IPU_BASE+0x0070)	/* R/W,    0, Red cyan c4[7:0] cofficoent		*/
#define IPU_RC_C4_H			(IPU_BASE+0x0071)	/* R/W,    0, Red cyan c4[8]   cofficoent		*/
#define IPU_RC_C5_L			(IPU_BASE+0x0072)	/* R/W,    0, Red cyan c5[7:0] cofficoent		*/
#define IPU_RC_C5_H			(IPU_BASE+0x0073)	/* R/W,    0, Red cyan c5[8]   cofficoent		*/
#define IPU_RC_C6_L			(IPU_BASE+0x0074)	/* R/W,    0, Red cyan c6[7:0] cofficoent		*/
#define IPU_RC_C6_H			(IPU_BASE+0x0075)	/* R/W,    0, Red cyan c6[8]   cofficoent		*/
#define IPU_RC_K1_L			(IPU_BASE+0x0076)	/* R/W,    0, Red cyan k1[7:0] cofficoent		*/
#define IPU_RC_K1_H			(IPU_BASE+0x0077)	/* R/W,    0, Red cyan k1[8]   cofficoent		*/
#define IPU_RC_K2_L			(IPU_BASE+0x0078)	/* R/W,    0, Red cyan k2[7:0] cofficoent		*/
#define IPU_RC_K2_H			(IPU_BASE+0x0079)	/* R/W,    0, Red cyan k2[8]   cofficoent		*/
#define IPU_RC_K3_L			(IPU_BASE+0x007A)	/* R/W,    0, Red cyan k3[7:0] cofficoent		*/
#define IPU_RC_K3_H			(IPU_BASE+0x007B)	/* R/W,    0, Red cyan k3[8]   cofficoent		*/
#define IPU_CH0_JMP0			(IPU_BASE+0x007C)	/* R/W,    0, Channel0 addres jump 7~0			*/
#define IPU_CH0_JMP1			(IPU_BASE+0x007D)	/* R/W,    0, Channel0 addres jump 15~8			*/
#define IPU_CH0_JMP2			(IPU_BASE+0x007E)	/* R/W,    0, Channel0 addres jump 23~16		*/
#define IPU_CH1_JMP0			(IPU_BASE+0x007F)	/* R/W,    0, Channel1 addres jump 7~0			*/
#define IPU_CH1_JMP1			(IPU_BASE+0x0080)	/* R/W,    0, Channel1 addres jump 15~8			*/
#define IPU_CH1_JMP2			(IPU_BASE+0x0081)	/* R/W,    0, Channel1 addres jump 23~16		*/


/*
 * Structure Definition
 */
struct ipuctrl {
	// sensor interface
	unsigned short	width;
	unsigned short	height;
	unsigned short	crop;
	unsigned char	lstart;
	unsigned char	lend;
	
	// memory interface
	unsigned long	fb1;
	unsigned long	fb2;
	unsigned long	fb3;
	unsigned long	jmp;

	// control
	unsigned short	overlap;

	union {
		unsigned char	a;
		struct {
			unsigned char	scan	: 1;	// 0 = progressive, 1 = interlaced
			unsigned char	rsv0	: 1;	// reserve
			unsigned char	format	: 1;	// 0 = raw8/yuv,    1 = raw10
			unsigned char	rsv1	: 1;	// reserve
			unsigned char	online	: 1;	// 0 = off-line,    1 = on-line
			unsigned char	rsv2	: 1;	// reserve
			unsigned char	rsv3	: 1;	// reserve
			unsigned char	rsv4	: 1;	// reserve
		} b;
	} cf1;
	union {
		unsigned char	a;
		struct {
			unsigned char	ext	: 4;
			unsigned char	sync	: 2;	// 0 = , 1 = , 2 = , 3 =
			unsigned char	sedge	: 1;	// 0 = rising-edge, 1 = falling-edge
			unsigned char	hmode	: 1;	// 0 = H-SYNC,      1 = HREF
		} b;
	} cf2;
};







#endif /* __REGS_IPU_H__ */
