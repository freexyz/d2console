/*
 * drivers/i2c/soft_i2c.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD. <http://www.zealtek.com.tw/>
 *		T.C. Chiu <tc.chiu@zealtek.com.tw>
 *
 *
 * THIS SOFTWARE IS PROVIDED UNDER LICENSE AND CONTAINS PROPRIETARY
 * AND CONFIDENTIAL MATERIAL WHICH IS THE PROPERTY OF SQ TECH.
 *
 * History:
 *	2011.12.27	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <intrins.h>
#include <configs.h>

#include <regs_sys.h>
#include <regs_pio.h>
#include <i2c.h>


#if (CONFIG_I2C_GPIO)


struct i2c_dev		i2cdev[] = {
	{ 1, CONFIG_HSN_SCL, CONFIG_HSN_SDA },
	{ 0, CONFIG_SN0_SCL, CONFIG_SN0_SDA },
	{ 0, CONFIG_SN1_SCL, CONFIG_SN1_SDA },
};


/*
 * i2c_wait -- wait for some time to get proper I2c timing
 */
static void i2c_wait(void)
{
	_nop_();
	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
}

/*
 * i2c_wait2 -- wait for some time to get proper I2c timing
 */
static void i2c_wait2(void)
{
	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
}

/*
 *
 */
static void i2c_hi(unsigned char gpio)
{
	// set to input
	pio[(gpio >> 3)].dir &= ~BIT(gpio & 0x07);
}

static void i2c_lo(unsigned char gpio)
{
	// driving '0'
	pio[(gpio >> 3)].dat &= ~BIT(gpio & 0x07);

	// set to output
	pio[(gpio >> 3)].dir |=  BIT(gpio & 0x07);
}

#define i2c_sda_hi(a)		   i2c_hi(a->sda)
#define i2c_sda_lo(a)		   i2c_lo(a->sda)

#define i2c_scl_hi(a)		   i2c_hi(a->scl)
#define i2c_scl_lo(a)		   i2c_lo(a->scl)


static void i2c_hsn_on(struct i2c_dev *dev)
{
	piomode[(dev->sda >> 3)] |=  BIT(dev->sda & 0x07);	// change to normal mode
}

static void i2c_hsn_off(struct i2c_dev *dev)
{
	piomode[(dev->sda >> 3)] &= ~BIT(dev->sda & 0x07);	// change to PIO mode
}

static unsigned char i2c_sda_read(struct i2c_dev *dev)
{
	unsigned char	value;

	// read port
	value   = pio[(dev->sda >> 3)].dat;
	value >>= (dev->sda & 0x07);
	return (value & 0x01);
}


/*
 *
 * I2C initialize
 *
 */
void i2c_gpio_init(void)
{
	char	i;

	for (i=0; i<(sizeof(i2cdev)/sizeof(struct i2c_dev)); i++) {
		// initial scl pin
		pio[(i2cdev[i].scl >> 3)].dat &= ~BIT(i2cdev[i].scl & 0x07);	// driving '0'
		pio[(i2cdev[i].scl >> 3)].dir &= ~BIT(i2cdev[i].scl & 0x07);	// set to input
		piomode[(i2cdev[i].scl >> 3)] &= ~BIT(i2cdev[i].scl & 0x07);	// change to PIO mode

		// initial sda pin
		pio[(i2cdev[i].sda >> 3)].dat &= ~BIT(i2cdev[i].sda & 0x07);	// driving '0'
		pio[(i2cdev[i].sda >> 3)].dir &= ~BIT(i2cdev[i].sda & 0x07);	// set to input
		piomode[(i2cdev[i].sda >> 3)] &= ~BIT(i2cdev[i].sda & 0x07);	// change to PIO mode
	}
}


/*
 * i2c_start -- I2C start signal
 *
 *  SCL _________
 *               \________
 *  SDA _____
 *           \____________
 */
void i2c_start(struct i2c_dev *dev)
{
	/* for second start signal on i2c_read */
	i2c_sda_hi(dev);
	i2c_scl_hi(dev);
	i2c_wait();

	/* send start signal*/
	i2c_sda_lo(dev);
	i2c_wait2();
	i2c_scl_lo(dev);
}

/*
 * i2c_stop - I2C stop signal
 *
 *             _____________
 *  SCL ______/
 *                 _________
 *  SDA __________/
 *
 * assume I2C_SCL = LOW, I2C_SDA = LOW
 */
void i2c_stop(struct i2c_dev *dev)
{
	i2c_wait2();
	i2c_sda_lo(dev);
	i2c_wait2();
	i2c_scl_hi(dev);
	i2c_wait2();
	i2c_sda_hi(dev);
}

/*
 * i2c_write -- I2C write command
 *
 * I2C_SCL = LOW,  data change
 * I2C_SCL = HIGH, data stable
 */
unsigned char i2c_write(struct i2c_dev *dev, unsigned char value)
{
	char		i = 9;
	unsigned char	ack;

	while (--i) {
		/* upload data */
		i2c_wait2();
		if (value & 0x80) {
			i2c_sda_hi(dev);
		} else {
			i2c_sda_lo(dev);
		}
		i2c_wait2();
		/* send data */
		i2c_scl_hi(dev);
		i2c_wait();
		value <<= 1;
		i2c_scl_lo(dev);
	}

	/* get acknowledgement */
	if (dev->hsn == 0) {
		i2c_wait2();
		i2c_sda_hi(dev);
		i2c_wait2();
		i2c_scl_hi(dev);
		i2c_wait2();
		ack = i2c_sda_read(dev);
		i2c_wait2();
		i2c_scl_lo(dev);
	} else {
		i2c_wait2();
		i2c_sda_hi(dev);
		i2c_hsn_on(dev);
		i2c_wait2();
		i2c_scl_hi(dev);
		i2c_wait2();
		ack = i2c_sda_read(dev);
		i2c_wait2();
		i2c_scl_lo(dev);
		i2c_hsn_off(dev);
	}
	return ack;
}

/*
 * i2c_read -- I2C read command
 *
 * I2C_SCL = LOW,  data change
 * I2C_SCL = HIGH, data stable
 */
unsigned char i2c_read(struct i2c_dev *dev, unsigned char acknowledge)
{
	unsigned char	value = 0;
	char		i = 9;

	/* read data */
	if (dev->hsn == 0) {
		while (--i) {
			/* download data */
			value <<= 1;
			i2c_wait();
			/* get data */
			i2c_scl_hi(dev);
			i2c_wait2();
			value |= i2c_sda_read(dev);
			i2c_wait2();
			i2c_scl_lo(dev);
		}
	} else {
		i2c_hsn_on(dev);
		while (--i) {
			/* download data */
			value <<= 1;
			i2c_wait();
			/* get data */
			i2c_scl_hi(dev);
			i2c_wait2();
			value |= i2c_sda_read(dev);
			i2c_wait2();
			i2c_scl_lo(dev);
		}
		i2c_hsn_off(dev);
	}

	/* send acknowledge */
	i2c_wait2();
	if (acknowledge) {
		i2c_sda_hi(dev);
	} else {
		i2c_sda_lo(dev);
	}
	i2c_wait2();
	i2c_scl_hi(dev);
	i2c_wait();
	i2c_scl_lo(dev);

	/* return data */
	return value;
}


/*
 *****************************************************************************
 *
 * Public Function
 *
 *****************************************************************************
 */
/* i2c_write_byte -- write one byte */
void i2c_write_byte(struct i2c_dev *dev, unsigned char slave, unsigned char reg, unsigned char val)
{
	char	retry = 10;

	while (--retry) {
		i2c_start(dev);				/* start I2C */
		if (i2c_write(dev, slave))
			continue;			/* slave address */
		if (i2c_write(dev, reg))
			continue;			/* register address */
		if (i2c_write(dev, val))
			continue;			/* send data */
//		i2c_stop(dev);				/* stop I2C, fixed no ACK bug */
		break;
	}
	i2c_stop(dev);					/* stop I2C */
}


/* i2c_read_byte -- read one byte */
unsigned char i2c_read_byte(struct i2c_dev *dev, unsigned char slave, unsigned char reg)
{
	char		retry = 10;
	unsigned char	value = 0;

	while (--retry) {
		/* send register address */
		i2c_start(dev);				/* start I2C */
		if (i2c_write(dev, slave & 0xfe))
			continue;			/* slave address */
		if (i2c_write(dev, reg))
			continue;			/* register address */
		/* read data */
		i2c_start(dev);				/* restart I2C */
		if (i2c_write(dev, slave | 1))
			continue;			/* slave address */
		value = i2c_read(dev, 1);		/* read data */
//		i2c_stop(dev);				/* stop I2C, fixed no ACK bug */
		break;
	}
	i2c_stop(dev);					/* stop I2C */
	return value;
}


/* i2c_write_byte16 -- write one byte */
void i2c_write_byte16(struct i2c_dev *dev, unsigned char slave, unsigned short reg, unsigned char val)
{
	char	retry = 10;

	while (--retry) {
		i2c_start(dev);				/* start I2C */
		if (i2c_write(dev, slave))
			continue;			/* slave address */
		if (i2c_write(dev, HIBYTE(reg)))
			continue;			/* hi byte register address */
		if (i2c_write(dev, LOBYTE(reg)))
			continue;			/* lo byte register address */
		if (i2c_write(dev, val))
			continue;			/* send data */
//		i2c_stop(dev);				/* stop I2C, fixed no ACK bug */
		break;
	}
	i2c_stop(dev);					/* stop I2C */
}


/* i2c_read_byte16 -- read one byte */
unsigned char i2c_read_byte16(struct i2c_dev *dev, unsigned char slave, unsigned short reg)
{
	char		retry = 10;
	unsigned char	value = 0;

	while (--retry) {
		/* send register address */
		i2c_start(dev);				/* start I2C */
		if (i2c_write(dev, slave & 0xfe))
			continue;			/* slave address */
		if (i2c_write(dev, HIBYTE(reg)))
			continue;			/* hi byte register address */
		if (i2c_write(dev, LOBYTE(reg)))
			continue;			/* lo byte register address */
		/* read data */
		i2c_start(dev);				/* restart I2C */
		if (i2c_write(dev, slave | 1))
			continue;			/* slave address */
		value = i2c_read(dev, 1);		/* read data */
//		i2c_stop(dev);				/* stop I2C, fixed no ACK bug */
		break;
	}
	i2c_stop(dev);					/* stop I2C */
	return value;
}

#endif /* CONFIG_I2C_GPIO */

