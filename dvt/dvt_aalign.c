/* dvt_aalign.c -- Design Verification Test for Auto Align module
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 */
#include <intrins.h>

#include <configs.h>
#include <regs_align.h>
#include <dvt.h>

#if (CONFIG_AALIGN)

static __code const struct amv_object		default_val[] = {
	{ AUTO_ALIGN_CFG,			AUTO_ALIGN_TRIGGER,	0 },
	{ RAM_PORT_EN, 				RAM_PORT_ENB,		0 },
	{ RAM_PORT_ADDR,			0x3F,			0 },
	{ AUTO_ALIGN_CFG2,			(AUTO_ALIGN_CH_ID | AUTO_ALIGN_RAW_MODE | AUTO_ALIGN_SAMPLE_X4), 0x02 },
	{ AUTO_ALIGN_SCALE,			AALIGN_SCALE_FACTOR4,	0 },
	{ AUTO_ALIGN_REG_UPDATE,		AUTO_ALIGN_UPDATE,	0 },
	{ AUTO_ALIGN_64X64_PANNING_X_0,		0xFF,			0 },
	{ AUTO_ALIGN_64X64_PANNING_X_1,		0x1F,			0 },
	{ AUTO_ALIGN_64X64_PANNING_Y_0,		0xFF,			0 },
	{ AUTO_ALIGN_64X64_PANNING_Y_1,		0x0F,			0 },
	{ AUTO_ALIGN_128X64_PANNING_X_0,	0xFF,			0 },
	{ AUTO_ALIGN_128X64_PANNING_X_1,	0x1F,			0 },
	{ AUTO_ALIGN_128X64_PANNING_Y_0,	0xFF,			0 },
	{ AUTO_ALIGN_128X64_PANNING_Y_1,	0x0F,			0 },
	{ AUTO_ALIGN_STATUS,			AUTO_ALIGN_BUSY,	0 },
};


static __code const struct amv_object		rdwr_val[] = {
	{ AUTO_ALIGN_64X64_PANNING_X_0,		0xFF,			0x5A },
	{ AUTO_ALIGN_64X64_PANNING_X_1,		0x1F,			0x15 },
	{ AUTO_ALIGN_64X64_PANNING_Y_0,		0xFF,			0xAA },
	{ AUTO_ALIGN_64X64_PANNING_Y_1,		0x0F,			0x05 },
	{ AUTO_ALIGN_128X64_PANNING_X_0,	0xFF,			0xAA },
	{ AUTO_ALIGN_128X64_PANNING_X_1,	0x1F,			0x15 },
	{ AUTO_ALIGN_128X64_PANNING_Y_0,	0xFF,			0x5A },
	{ AUTO_ALIGN_128X64_PANNING_Y_1,	0x0F,			0x05 },
	{ AUTO_ALIGN_SCALE,			AALIGN_SCALE_FACTOR4,	0x03 },
	{ AUTO_ALIGN_CFG2,			(AUTO_ALIGN_CH_ID | AUTO_ALIGN_RAW_MODE | AUTO_ALIGN_SAMPLE_X4), 0x05 },
	{ RAM_PORT_ADDR,			0x3F,			0x2A },
	{ RAM_PORT_EN, 				RAM_PORT_ENB,		0x01 },
	{ AUTO_ALIGN_REG_UPDATE,		AUTO_ALIGN_UPDATE,	0x01 },
	{ AUTO_ALIGN_CFG,			AUTO_ALIGN_TRIGGER,	0x01 },
};


static __code const struct amv_object		normal_func[] = {
	{ RAM_PORT_EN, 				RAM_PORT_ENB,		0x00 },
	{ AUTO_ALIGN_CFG2,			(AUTO_ALIGN_CH_ID | AUTO_ALIGN_RAW_MODE | AUTO_ALIGN_SAMPLE_X4), 0x02 },
	{ AUTO_ALIGN_SCALE,			AALIGN_SCALE_FACTOR4,	0x00 },
	{ AUTO_ALIGN_64X64_PANNING_X_0,		0xFF,			0x00 },
	{ AUTO_ALIGN_64X64_PANNING_X_1,		0x1F,			0x00 },
	{ AUTO_ALIGN_64X64_PANNING_Y_0,		0xFF,			0x00 },
	{ AUTO_ALIGN_64X64_PANNING_Y_1,		0x0F,			0x00 },
	{ AUTO_ALIGN_128X64_PANNING_X_0,	0xFF,			0x00 },
	{ AUTO_ALIGN_128X64_PANNING_X_1,	0x1F,			0x00 },
	{ AUTO_ALIGN_128X64_PANNING_Y_0,	0xFF,			0x00 },
	{ AUTO_ALIGN_128X64_PANNING_Y_1,	0x0F,			0x00 },
	{ AUTO_ALIGN_REG_UPDATE,		AUTO_ALIGN_UPDATE,	0x00 },
	{ AUTO_ALIGN_CFG,			AUTO_ALIGN_TRIGGER,	0x00 },
};


void dvt_aalign(void)
{
	unsigned char	loop;
	unsigned char	i;


	/*
	 * default value test
	 */
	loop = sizeof(default_val) / sizeof(struct amv_object);
	for (i=0; i<loop; i++) {
		if ((__ior8(default_val[i].address) & default_val[i].mask) != default_val[i].value)
			goto fail_default_val;
	}


	/*
	 * read/write test
	 */
	loop = sizeof(rdwr_val) / sizeof(struct amv_object);
	/* write */
	for (i=0; i<loop; i++) {
		__iow8(rdwr_val[i].address, rdwr_val[i].value);
	}
	/* read */
	for (i=0; i<loop; i++) {
		if ((__ior8(rdwr_val[i].address) & rdwr_val[i].mask) != rdwr_val[i].value)
			goto fail_read_write;
	}


	/*
	 * normal function test
	 */
	loop = sizeof(normal_func) / sizeof(struct amv_object);
	for (i=0; i<loop; i++) {
		__iow8(normal_func[i].address, normal_func[i].value);
	}

	while (__ior8(AUTO_ALIGN_STATUS) & AUTO_ALIGN_BUSY) {
		_nop_();
	}

	/* pass */
pass:
	return;

	/* fail */
fail_default_val:
	goto fail_default_val;

fail_read_write:
	goto fail_read_write;

fail_normal_func:
	goto fail_normal_func;

}


#endif /* CONFIG_AALIGN */
