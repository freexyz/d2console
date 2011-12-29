/*
 * include/i2c.h -- 
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

#if !defined(__I2C_H__)
#define __I2C_H__


struct i2c_dev {
	unsigned char	hsn;	// 1 = host sensor, 0 = pio
	unsigned char	scl;
	unsigned char	sda;	
};



extern struct i2c_dev		i2cdev[];


extern void			i2c_gpio_init(void);
extern void			i2c_write_byte(struct i2c_dev *dev, unsigned char slave, unsigned char reg, unsigned char val);
extern unsigned char		i2c_read_byte(struct i2c_dev *dev, unsigned char slave, unsigned char reg);
extern void			i2c_write_byte16(struct i2c_dev *dev, unsigned char slave, unsigned short reg, unsigned char val);
extern unsigned char		i2c_read_byte16(struct i2c_dev *dev, unsigned char slave, unsigned short reg);



#endif	/* __I2C_H__ */
