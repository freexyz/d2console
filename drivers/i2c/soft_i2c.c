/*
 * drivers/i2c/i2c.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <intrins.h>
#include <configs.h>

#if (CONFIG_SOFT_I2C)

sbit P1_0	= P1 ^ 0;
sbit P1_1	= P1 ^ 1;


/*
 * Pins function define
 */
#define I2C_SDA		P1_0
#define I2C_SCL		P1_1

#if !defined(I2C_SDA)
#error Please define 'I2C_SDA'
#endif
#if !defined(I2C_SCL)
#error Please define 'I2C_SCL'
#endif

/*
 * i2c_wait -- wait for some time to get proper I2c timing
 */
static void i2c_wait(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/*
 * i2c_wait2 -- wait for some time to get proper I2c timing
 */
static void i2c_wait2(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}


/*
 * i2c_start -- I2C start signal
 *
 *  SCL _________
 *               \________
 *  SDA _____
 *           \____________
 */
void i2c_start(void)
{
	/* for second start signal on i2c_read */
	I2C_SDA = HIGH;
	I2C_SCL = HIGH;
	i2c_wait();

	/* send start signal*/
	I2C_SDA = LOW;
	i2c_wait2();
	I2C_SCL = LOW;
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
void i2c_stop(void)
{
	i2c_wait2();
	I2C_SDA = LOW;
	i2c_wait2();
	I2C_SCL = HIGH;
	i2c_wait2();
	I2C_SDA = HIGH;
}

/*
 * i2c_write -- I2C write command
 *
 * I2C_SCL = LOW,  data change
 * I2C_SCL = HIGH, data stable
 */
bit i2c_write(unsigned char value)
{
	char	i = 9;
	bit	ack;

	while (--i) {
        	/* upload data */
        	i2c_wait2();
        	I2C_SDA = (value & 0x80) ? HIGH : LOW;
        	i2c_wait2();
        	/* send data */
        	I2C_SCL = HIGH;
        	i2c_wait();
        	value <<= 1;
        	I2C_SCL = LOW;
	}

	/* get acknowledgement */
	i2c_wait2();
	I2C_SDA = HIGH;
	i2c_wait2();
	I2C_SCL = HIGH;
	i2c_wait2();
	ack = I2C_SDA;
	i2c_wait2();
	I2C_SCL = LOW;
	return ack;
}

/*
 * i2c_read -- I2C read command
 *
 * I2C_SCL = LOW,  data change
 * I2C_SCL = HIGH, data stable
 */
unsigned char i2c_read(bit acknowledge)
{
	unsigned char	value = 0;
	char		i = 9;

	/* read data */
	while (--i) {
		/* download data */
		value <<= 1;
		i2c_wait();
		/* get data */
		I2C_SCL = HIGH;
		i2c_wait2();
		value |= I2C_SDA;
		i2c_wait2();
		I2C_SCL = LOW;
	}

	/* send acknowledge */
	i2c_wait2();
	I2C_SDA = acknowledge;
	i2c_wait2();
	I2C_SCL = HIGH;
	i2c_wait();
	I2C_SCL = LOW;

	/* return data */
	return value;
}

/*
 * i2c_write_byte -- write one byte
 */
void i2c_write_byte(unsigned char slave_addr, unsigned char reg_addr, unsigned char value)
{
	char	i = 10;

	while (--i) {
		i2c_start();				/* start I2C */
		if (i2c_write(slave_addr)) continue;	/* slave address */
		if (i2c_write(reg_addr))  continue;	/* register address */
		if (i2c_write(value))     continue;	/* send data */
		i2c_stop();				/* stop I2C */
		break;
	}
}

/*
 * i2c_read_byte -- read one byte
 */
unsigned char i2c_read_byte(unsigned char slave_addr, unsigned char reg_addr)
{
	char		i = 10;
	unsigned char	value = 0;

	while (--i) {
		/* send register address */
		i2c_start();					/* start I2C */
		if (i2c_write(slave_addr & 0xfe)) continue;	/* slave address */
		if (i2c_write(reg_addr)) continue;		/* register address */
		/* read data */
		i2c_start();					/* restart I2C */
		if (i2c_write(slave_addr | 1)) continue;	/* slave address */
		value = i2c_read(1);				/* read data */
		i2c_stop();					/* stop I2C */
		break;
	}

	return value;
}


#endif /* CONFIG_SOFT_I2C */

