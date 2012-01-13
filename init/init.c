/*
 * init/main.c
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.23	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stddef.h>
#include <stdio.h>
#include <configs.h>
#include <serial.h>

#include <regs_siu.h>
#include <regs_sou.h>
#include <regs_ipu.h>
#include <regs_sys.h>
#include <regs_pio.h>
#include <regs_align.h>

#include <dvt.h>
#include <i2c.h>

static unsigned long volatile __xdata		tmp;


#if (CONFIG_VLSI_SIMULATION)
static void d2_init(void)
{


//	dvt_lpbk_raw8();
//	dvt_lpbk_ccir656i();
	dvt_lpbk_ccir656p();
//	dvt_lpbk_multich(0);	// single
//	dvt_lpbk_multich(1);	// double
//	dvt_accurate();
//	dvt_fussy();
//	dvt_align();


}
#endif


void sys_init(void)
{
#if 0
# if (CONFIG_FOSC < 48000000UL)
	__iow8(CLKSEL, 0x04);
# else
	__iow8(CLKSEL, 0x00);
# endif
#endif

	serial_init();

// !!!! TEST TEST TEST !!!!
#if (CONFIG_VLSI_SIMULATION)
	d2_init();
#endif
// !!!! TEST TEST TEST !!!!


	i2c_gpio_init();
//	t515bm_init();


// !!!! TEST TEST TEST !!!!
#if 0
	souc->blinkval = __le32(0x11223344);	// write
	tmp            = souc->blinkval;	// read
#endif
// !!!! TEST TEST TEST !!!!
}

