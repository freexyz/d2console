/*
 * common/cmd_mem.c --
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */
#include <stdio.h>
#include <stdlib.h>
#include <absacc.h>

#include <configs.h>
#include <command.h>

#include <regs_sys.h>
#include <dvt.h>


#if (CONFIG_MEM)
/*
 *****************************************************************************
 *
 * Memory Dump
 *
 *****************************************************************************
 */
void cmd_imem_dump(int argc, const char *argv[])
{
	unsigned char	dst;
	unsigned char	len;

	if (argc != 3) {
		printf("invalid 'mdi' command: too few(many) arguments\n");
		return;
	}

	/* read */
	dst = (unsigned char) strtoul(argv[1], NULL, 16);
	len = (unsigned char) strtoul(argv[2], NULL, 16);

	hex_dump((char __data *) dst, (unsigned short) len);
}

command_t	cmd_imem_dump_t = {
	"mdi",
	cmd_imem_dump,
	"mdi <addr8> <len8> \t\t\t-- display data memory"
};


void cmd_xmem_dump(int argc, const char *argv[])
{
	unsigned short	dst;
	unsigned short	len;

	if (argc != 3) {
		printf("invalid 'mdx' command: too few(many) arguments\n");
		return;
	}

	/* read */
	dst = (unsigned short) strtoul(argv[1], NULL, 16);
	len = (unsigned short) strtoul(argv[2], NULL, 16);

	hex_dump((char __xdata *) dst, (unsigned short) len);
}

command_t	cmd_xmem_dump_t = {
	"mdx",
	cmd_xmem_dump,
	"mdx <addr16> <len16> \t\t-- display xdata memory"
};


void cmd_dump_mem(int argc, const char *argv[])
{
	unsigned long	dst;
	unsigned long	len;

	if (argc != 3) {
		printf("invalid 'dm' command: too few(many) arguments\n");
		return;
	}

	/* read */
	dst = strtoul(argv[1], NULL, 16);
	len = strtoul(argv[2], NULL, 16);
	hex_dump_linear(dst, len);
}

command_t	cmd_dump_mem_t = {
	"dm",
	cmd_dump_mem,
	"dm <addr32> <len32> \t\t\t-- display xdata memory (linear)"
};


/*
 *****************************************************************************
 * DATA Read/Write
 *
 * mov   @Ri, a	; write
 * mov   a, @Ri	; read
 *****************************************************************************
 */
void cmd_mov_rd(int argc, const char *argv[])
{
	unsigned char	dst;
	unsigned char	val;

	if (argc != 2) {
		printf("invalid 'movr' command: too few(many) arguments\n");
		return;
	}

	/* read */
	dst = (unsigned char) strtoul(argv[1], NULL, 16);
	val = DBYTE[dst];
	printf("Ri=%02x, a=%02x\t\t;mov\ta, @Ri\n", (int) dst, (int) val);
}

command_t	cmd_mov_rd_t = {
	"movr",
	cmd_mov_rd,
	"movr <addr8> \t\t\t-- mov    a, @Ri"
};


void cmd_mov_wr(int argc, const char *argv[])
{
	unsigned char 	dst;
	unsigned char	val;


	if (argc != 3) {
		printf("invalid 'movw' command: too few(many) arguments\n");
		return;
	}

	/* write */
	dst = (unsigned char) strtoul(argv[1], NULL, 16);
	val = (unsigned char) strtoul(argv[2], NULL, 16);
	DBYTE[dst] = val;
	printf("Ri=%02x, a=%02x\t\t;mov\t@Ri, a\n", (int) dst, (int) val);
}

command_t	cmd_mov_wr_t = {
	"movw",
	cmd_mov_wr,
	"movw <addr8> <val8> \t\t\t-- mov    @Ri, a"
};


/*
 *****************************************************************************
 * XDATA Read/Write
 *
 * movx   @dptr, a	; write
 * movx   a, @dptr	; read
 *****************************************************************************
 */
void cmd_movx_rd(int argc, const char *argv[])
{
	unsigned short	dst;
	unsigned char	val;

	if (argc != 2) {
		printf("invalid 'movxr' command: too few(many) arguments\n");
		return;
	}

	/* read */
	dst = (unsigned short) strtoul(argv[1], NULL, 16);
	val = XBYTE[dst];
	printf("dptr=%04x, a=%02x\t\t;movx\ta, @dptr\n", dst, (int) val);
}

command_t	cmd_movx_rd_t = {
	"movxr",
	cmd_movx_rd,
	"movxr <addr16> \t\t\t-- movx   a, @dptr"
};


void cmd_movx_wr(int argc, const char *argv[])
{
	unsigned short	dst;
	unsigned char	val;

	if (argc != 3) {
		printf("invalid 'movxw' command: too few(many) arguments\n");
		return;
	}
	/* write */
	dst = (unsigned short) strtoul(argv[1], NULL, 16);
	val = (unsigned char)  strtoul(argv[2], NULL, 16);
	XBYTE[dst] = val;
	printf("dptr=%04x, a=%02x\t\t;movx\t@dptr, a\n", dst, (int) val);
}

command_t	cmd_movx_wr_t = {
	"movxw",
	cmd_movx_wr,
	"movxw <addr16> <val8> \t\t-- movx   @dptr, a"
};


/*
 *****************************************************************************
 * DRAM Space Read/Write with Bank Register
 *
 * memset, memcmp, swbank
 *****************************************************************************
 */
void cmd_swbank(int argc, const char *argv[])
{
	unsigned short	bank;

	if (argc != 2) {
		printf("invalid 'swbank' command: too few(many) arguments\n");
		return;
	}
	bank = (unsigned short) strtoul(argv[1], NULL, 16);
	if ((bank & 0xFE00) != 0) {
		printf("Over the range, 0 <= bank <= 511\n");
		return;
	}
	printf("switch to DRAM bannk=%04x\n", bank);
	__iow16(HADDRL, bank);
}

command_t	cmd_swbank_t = {
	"swbank",
	cmd_swbank,
	"swbank <bank9> \t\t\t-- switch DRAM bank"
};


void cmd_memcmp(int argc, const char *argv[])
{
	unsigned long	a1;
	unsigned long	a2;
	unsigned long	num;
	long		state;

	if (argc != 4) {
		printf("invalid 'memcmp' command: too few(many) arguments\n");
		return;
	}
	a1  = strtoul(argv[1], NULL, 16);
	a2  = strtoul(argv[2], NULL, 16);
	num = strtoul(argv[3], NULL, 16);

	state = d2Bmemcmp(a1, a2, num);
	if (state == (-1)){
		printf("no different\n");
	} else {
		printf("data different at = %08lx\n", state);	
	}
}

command_t	cmd_memcmp_t = {
	"memcmp",
	cmd_memcmp,
	"memcmp <addr24> <addr24> <num32> \t-- memory compare (linear)"
};


void cmd_msetb(int argc, const char *argv[])
{
	unsigned long	addr;
	unsigned long	num;
	char		c;

	if (argc != 4) {
		printf("invalid 'msetb' command: too few(many) arguments\n");
		return;
	}
	addr = strtoul(argv[1], NULL, 16);
	c    = (char) strtoul(argv[2], NULL, 16);
	num  = strtoul(argv[3], NULL, 16);

	d2Bmemset(addr, c, num);
}

command_t	cmd_msetb_t = {
	"msetb",
	cmd_msetb,
	"msetb <addr24> <val8> <num32> \t-- memory set (byte) (linear)"
};


void cmd_msetw(int argc, const char *argv[])
{
	unsigned long	addr;
	unsigned long	num;
	unsigned short	c;

	if (argc != 4) {
		printf("invalid 'msetw' command: too few(many) arguments\n");
		return;
	}
	addr = strtoul(argv[1], NULL, 16);
	c    = (unsigned short) strtoul(argv[2], NULL, 16);
	num  = strtoul(argv[3], NULL, 16);

	d2Wmemset(addr, c, num);
}

command_t	cmd_msetw_t = {
	"msetw",
	cmd_msetw,
	"msetw <addr24> <val16> <num32> \t-- memory set (word) (linear)"
};


void cmd_msetdw(int argc, const char *argv[])
{
	unsigned long	addr;
	unsigned long	num;
	unsigned long	c;

	if (argc != 4) {
		printf("invalid 'msetdw' command: too few(many) arguments\n");
		return;
	}
	addr = strtoul(argv[1], NULL, 16);
	c    = strtoul(argv[2], NULL, 16);
	num  = strtoul(argv[3], NULL, 16);

	d2Dmemset(addr, c, num);
}

command_t	cmd_msetdw_t = {
	"msetdw",
	cmd_msetdw,
	"msetdw <addr24> <val32> <num32> \t-- memory set (double word) (linear)"
};


#endif /* CONFIG_MEM */

#if (CONFIG_DVT_MEM)
/*
 *****************************************************************************
 * Memory Read/Write Test
 *
 * memset, memcmp, swbank
 *****************************************************************************
 */
void cmd_memtst(int argc, const char *argv[])
{
	argc    = argc;
	argv    = argv;
	argv[1] = NULL;

	if (argc != 1) {
		printf("invalid 'memtst' command: too few(many) arguments\n");
		return;
	}
	printf("\nDRAM read/write test\n");
	if (dvt_sdram() != 0)
		return;

	printf("\n2K SRAM read/write test\n");
	if (dvt_2ksram() != 0)
		return;

	printf("\nInternal RAM read/write test\n");
	if (dvt_iram() != 0)
		return;
}

command_t	cmd_memtst_t = {
	"memtst",
	cmd_memtst,
	"memtst \t\t\t\t-- memory read/write test (linear)"
};

#endif /* CONFIG_DVT_MEM */



