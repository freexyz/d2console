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
extern int		dvt_lpbk_stop(void);
extern int		dvt_lpbk_raw8(void);
extern int		dvt_lpbk_ccir656i(void);
extern int		dvt_lpbk_ccir656p(void);
extern int		dvt_lpbk_multich(unsigned char edge);
extern int		dvt_accurate(void);
extern int		dvt_align(void);


#endif /* __DVT_H__ */
