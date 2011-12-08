/*
 * include/dvt.h -- Design Verification Test
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#if !defined(__DVT_H__)
#define __DVT_H__

/*
 * Macro Definition
 */
struct amv_object {
	unsigned short	address;
	unsigned char	mask;
	unsigned char	value;
};

struct regs_object {
	unsigned short	address;
	unsigned char	value;
};


extern int		dvt_iram(void);
extern int		dvt_2ksram(void);
extern int		dvt_sdram(void);


#endif /* __DVT_H__ */