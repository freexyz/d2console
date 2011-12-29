/* common/cmd_i2c.c --
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
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include <configs.h>
#include <command.h>

#include <i2c.h>

/* 8 bit register address */
void cmd_i2crd(int argc, const char *argv[])
{
	unsigned char	dev;
	unsigned char	slave;
	unsigned char	reg;
	unsigned char	val;

	if (argc != 4) {
		printf("invalid 'i2crd' command: too few(many) arguments\n");
		return;
	}

	dev   = (unsigned char) strtoul(argv[1], NULL, 16);
	slave = (unsigned char) strtoul(argv[2], NULL, 16);
	reg   = (unsigned char) strtoul(argv[3], NULL, 16);

	val = i2c_read_byte(&i2cdev[dev], slave, reg);
	printf("i2c<%02x>: slave=%02x, reg<%02x>=%02x\n", (int) dev, (int) slave, (int) reg, (int) val);
}

command_t	cmd_i2crd_t = {
	"i2crd",
	cmd_i2crd,
	"i2crd <dev> <slv8> <reg8> \t\t-- I2C read"
};


void cmd_i2cwe(int argc, const char *argv[])
{
	unsigned char	dev;
	unsigned char	slave;
	unsigned char	reg;
	unsigned char	val;

	if (argc != 5) {
		printf("invalid 'i2crd' command: too few(many) arguments\n");
		return;
	}

	dev   = (unsigned char) strtoul(argv[1], NULL, 16);
	slave = (unsigned char) strtoul(argv[2], NULL, 16);
	reg   = (unsigned char) strtoul(argv[3], NULL, 16);
	val   = (unsigned char) strtoul(argv[4], NULL, 16);

	i2c_write_byte(&i2cdev[dev], slave, reg, val);
}

command_t	cmd_i2cwe_t = {
	"i2cwe",
	cmd_i2cwe,
	"i2cwe <dev> <slv8> <reg8> <val8> \t-- I2C write"
};


/* 16 bit register address */
void cmd_i2crd16(int argc, const char *argv[])
{
	unsigned char	dev;
	unsigned char	slave;
	unsigned short	reg;
	unsigned char	val;

	if (argc != 4) {
		printf("invalid 'i2crd16' command: too few(many) arguments\n");
		return;
	}

	dev   = (unsigned char)  strtoul(argv[1], NULL, 16);
	slave = (unsigned char)  strtoul(argv[2], NULL, 16);
	reg   = (unsigned short) strtoul(argv[3], NULL, 16);

	val = i2c_read_byte16(&i2cdev[dev], slave, reg);
	printf("i2c<%02x>: slave=%02x, reg<%04x>=%02x\n", (int) dev, (int) slave, (int) reg, (int) val);
}

command_t	cmd_i2crd16_t = {
	"i2crd16",
	cmd_i2crd16,
	"i2crd16 <dev> <slv8> <reg16> \t-- I2C read (16bit address)"
};


void cmd_i2cwe16(int argc, const char *argv[])
{
	unsigned char	dev;
	unsigned char	slave;
	unsigned short	reg;
	unsigned char	val;

	if (argc != 5) {
		printf("invalid 'i2crd16' command: too few(many) arguments\n");
		return;
	}

	dev   = (unsigned char)  strtoul(argv[1], NULL, 16);
	slave = (unsigned char)  strtoul(argv[2], NULL, 16);
	reg   = (unsigned short) strtoul(argv[3], NULL, 16);
	val   = (unsigned char)  strtoul(argv[4], NULL, 16);

	i2c_write_byte16(&i2cdev[dev], slave, reg, val);
}

command_t	cmd_i2cwe16_t = {
	"i2cwe16",
	cmd_i2cwe16,
	"i2cwe16 <dev> <slv8> <reg16> <val8> \t-- I2C write (16bit address)"
};


static __code const unsigned char	bitmap[8][8] = {
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 },
	{ 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01 },
	{ 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02 },
	{ 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04 },
	{ 0x10, 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08 },
	{ 0x20, 0x40, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10 },
	{ 0x40, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 },
	{ 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 }
};

static __code const unsigned short	regmap[] = {
	0x0334, 0x0337, 0x033a, 0x033d, 0x0340, 0x0343, 0x0349, 0x034c
};

void cmd_hsntst(int argc, const char *argv[])
{
	unsigned short	reg;
	unsigned char	val;
	unsigned char	i, j, k;

	argv[1] = NULL;
	if (argc != 1) {
		printf("invalid 'hsntst' command: too few(many) arguments\n");
		return;
	}

	for (k=0; k<1; k++) {
		// test register file
		printf("test register file...\n");
		for (j=0; j<(sizeof(regmap)/sizeof(unsigned short)); j++) {
			printf("   write register file\n");
			for (i=0; i<(sizeof(regmap)/sizeof(unsigned short)); i++) {
				i2c_write_byte16(&i2cdev[0], 0x04, regmap[i], bitmap[j][i]);
			}
			printf("   read & verify register file\n");
			for (i=0; i<(sizeof(regmap)/sizeof(unsigned short)); i++) {
				val = i2c_read_byte16(&i2cdev[0], 0x04, regmap[i]);
				if (val != bitmap[j][i]) {
					printf("      [Fail], reg[%04x] != %02x\n", regmap[i], (int) bitmap[j][i]);
				}
			}
		}

		// test internal 2K SRAM
		printf("test inetrnal 2K SRAM...\n");
		printf("   write 2K SRAM\n");
		reg = 0x7400;
		for (i=0; i<128; i++) {
			i2c_write_byte16(&i2cdev[0], 0x04, reg+i, bitmap[i/8][i%8]);
		}
		printf("   read & verify 2K SRAM\n");
		for (i=0; i<128; i++) {
			val = i2c_read_byte16(&i2cdev[0], 0x04, reg+i);
			if (val != bitmap[i/8][i%8]) {
				printf("      [Fail], 2KRAM[%04x] == %02x\n", reg+i, (int) bitmap[i/8][i%8]);
			}
		}

		// test DRAM
		printf("test DRAM...\n");
		printf("   write DRAM\n");
		reg = 0xFE00;
		for (i=0; i<128; i++) {
			i2c_write_byte16(&i2cdev[0], 0x04, reg+i, bitmap[i/8][i%8]);
		}
		printf("   read & verify DRAM\n");
		for (i=0; i<128; i++) {
			val = i2c_read_byte16(&i2cdev[0], 0x04, reg+i);
			if (val != bitmap[i/8][i%8]) {
				printf("      [Fail], DRAM[%04x] == %02x\n", reg+i, (int) bitmap[i/8][i%8]);
			}
		}
	}

}

command_t	cmd_hsntst_t = {
	"hsntst",
	cmd_hsntst,
	"hsntst \t\t\t\t-- host sensor interface test"
};