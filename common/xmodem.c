/*
 * common/xmodem.c -- base on Georges Menie source code
 *
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.18	T.C. Chiu <tc.chiu@zealtek.com.tw>
 *		- First implementation
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <absacc.h>

#include <configs.h>
#include <command.h>
#include <serial.h>

#include <regs_sys.h>



#if (CONFIG_XMODEM)

#define USE_1K_XMODEM		1	 /* 1 for use 1k_xmodem, 0 for xmodem */

#if (USE_1K_XMODEM)
// 1K xmodem protocol
# define PACKET_SZ		1024
# define SOH			0x02
#else
// xmodem protocol
# define PACKET_SZ		128
# define SOH			0x01
#endif


/*
 * XMODEM Protocol
 *
 * Xmodem    Frame form: <SOH><blk><255-blk><-- 128 data bytes--><CRC hi><CRC lo>
 * 1K-Xmodem Frame form: <SOH><blk><255-blk><--1024 data bytes--><CRC hi><CRC lo>
 */
//#define SOH			0x01
//#define STX			0x02
#define EOT			0x04
#define ACK			0x06
#define NAK			0x15
#define CAN			0x18
#define CTRLZ			0x1A

#define DLY_1S			1000


static unsigned char		packetno;
static unsigned short		pktcnt;
static unsigned short		crc;
static unsigned short		paddr;


// Table of CRC constants - implements x^16+x^12+x^5+1
static __code const unsigned short	crc16tab[] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

enum rx_state {
	RX_INIT,
	RX_PACKET,
	RX_REPEAT,
	RX_EOT
};

enum tx_state {
	TX_INIT,
	TX_PACKET,
	TX_REPEAT,
	TX_EOT
};


static char packet_recv(unsigned long dst)
{
	int		i;
	unsigned char	c;

	crc   = 0;
	paddr = __ior16(HADDRL) & 0x01FF;	// keep current memory bank register
	for (i=0; i<PACKET_SZ; i++) {
		c = getc();
		crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ c) & 0x00FF];
#if (CONFIG_LINEAR_DRAM == 0)
		XBYTE[dst + i] = c;
#else
		__iow16(HADDRL, HIWORD(dst << 1));
		XBYTE[0x8000+(LOWORD(dst) & 0x7FFF)] = c;
#endif
		dst++;
	}
	__iow16(HADDRL, paddr);			// restore memory bank register

	c = getc();				// CRC high order
	if (c != ((crc >> 8) & 0x00FF))
		return 0;

	c = getc();				// CRC low order
	if (c != (crc & 0x00FF))
		return 0;

	return 1;
}

static int xmodem_rx(unsigned long dst)
{
	enum rx_state	state;
	unsigned char	c;
	unsigned char	retry;

	retry    = 0;
	pktcnt   = 1;
	packetno = 1;
	state    = RX_INIT;

	while (1) {
		switch (state) {
		case RX_INIT:
			putcx('C');				// send poll char
			if (tstc(DLY_1S * 2)) {
				c = getc();			// an SOH byte
				if (c == SOH) {
					state = RX_PACKET;
				}
			}
			break;

		case RX_REPEAT:
			c = getc();				// an SOH byte
			if (c == SOH) {
				state = RX_PACKET;
			} else if (c == EOT) {			// end-of-transmission (EOT)
				state = RX_EOT;
				putcx(ACK);			// ACK
				return pktcnt - 1;
			} else if (c == CAN) {			// cancel
				return -2;
			}
			break;

		case RX_PACKET:
			c = getc();				// the packet number
			if (c != packetno) {
				// incorrect packet number, cancel
rx_cancel:
				putcx(CAN);
				putcx(CAN);
				putcx(CAN);
				putcx(CAN);
				return -1;
			}
			c = getc();				// the 1's complement of the packet number
			if (~c == packetno) {
				if (packet_recv(dst)) {
					putcx(ACK);		// ACK
					state = RX_REPEAT;	// next transmission
					retry = 0;
					dst  += PACKET_SZ;
					packetno++;
					pktcnt++;
					break;
				}
			}
			putcx(NAK);				// requested retransmission
			state = RX_REPEAT;
			if (++retry > 10) {
				goto rx_cancel;
			}
			break;

		default:
			break;
		}
	}
}


static int xmodem_tx(unsigned long src, unsigned long sz)
{
	enum tx_state	state;
	unsigned char	c;
	unsigned char	retry;
	unsigned short	i;

	retry    = 0;
	pktcnt   = 1;
	packetno = 1;
	state    = TX_INIT;

	while (1) {
		switch (state) {
		case TX_INIT:
			if (getc() == 'C') {			// wait poll char
				state = TX_PACKET;
			}
			break;

		case TX_PACKET:
			putcx(SOH);				// an SOH byte
			putcx(packetno);			// the packet number
			putcx(~packetno);			// the 1's complement of the packet number
			crc   = 0;
			paddr = __ior16(HADDRL) & 0x01FF;	// keep current memory bank register
			for (i=0; i<PACKET_SZ; i++) {
				if (sz) {
#if (CONFIG_LINEAR_DRAM == 0)
					c = XBYTE[src + i];
#else
					__iow16(HADDRL, HIWORD((src + i) << 1));
					c = XBYTE[0x8000+(LOWORD(src + i) & 0x7FFF)];
#endif
					sz--;
				} else {
					c = 0x1A;
				}
				crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ c) & 0x00FF];
				putcx(c);
			}
			__iow16(HADDRL, paddr);			// restore memory bank register
			putcx((unsigned char) (crc >> 8));	// CRC high order
			putcx((unsigned char)  crc);		// CRC low order
			state = TX_REPEAT;
			break;

		case TX_REPEAT:
			c = getc();
			if (c == ACK) {
				if (sz) {
					pktcnt++;
					packetno++;
					retry = 0;
					state = TX_PACKET;
					src  += PACKET_SZ;
				} else {
					state = TX_EOT;
				}
			} else if (c == NAK) {
				state = TX_PACKET;
				if (++retry > 10) {
					goto tx_cancel;
				}
			} else if (c == CAN) {
				goto tx_cancel;
			}
			break;

		case TX_EOT:
			putcx(EOT);				// end-of-transmission (EOT)
			if (getc() == ACK) {
				return pktcnt;
			}

		default:
tx_cancel:
			putcx(CAN);
			putcx(CAN);
			putcx(CAN);
			putcx(CAN);
			return -1;
		}
	}
}


/*
 *****************************************************************************
 *
 * XMODEM Command
 *
 *****************************************************************************
 */
void cmd_xmodem_send(int argc, const char *argv[])
{
	unsigned long	src;
	unsigned long	len;
	int		st;

	if (argc != 3) {
		printf("invalid 'xsend' command: too few(many) arguments\n");
		return;
	}

	printf("Receive data using the xmodem protocol from your terminal emulator now...\n");

	src = strtoul(argv[1], NULL, 16);
	len = strtoul(argv[2], NULL, 16);
	st  = xmodem_tx(src, len);
	if (st < 0) {
		printf("\nXmodem transmit error: status: %d\n", st);
	} else {
		printf("\nXmodem successfully transmitted %d packets\n", st);
	}
}

command_t	cmd_xmodem_send_t = {
	"xsend",
	cmd_xmodem_send,
#if (CONFIG_LINEAR_DRAM)
	"xsend <addr24> <len32> \t\t-- xmodem send (linear)"
#else
	"xsend <addr24> <len32> \t\t-- xmodem send"
#endif
};


void cmd_xmodem_receive(int argc, const char *argv[])
{
	unsigned long	dst;
	int		st;

	if (argc != 2) {
		printf("invalid 'xrecv' command: too few(many) arguments\n");
		return;
	}

	printf("Send data using the xmodem protocol from your terminal emulator now...\n");

	dst = strtoul(argv[1], NULL, 16);
	st  = xmodem_rx(dst);
	if (st < 0) {
		printf("\nXmodem receive error: status: %d\n", st);
	} else {
		printf("\nXmodem successfully received %d packets\n", st);
	}
}

command_t	cmd_xmodem_receive_t = {
	"xrecv",
	cmd_xmodem_receive,
#if (CONFIG_LINEAR_DRAM)
	"xrecv <addr24> \t\t\t-- xmodem receive (linear)"
#else
	"xrecv <addr24> \t\t\t-- xmodem receive"
#endif
};

#endif /* CONFIG_XMODEM */

