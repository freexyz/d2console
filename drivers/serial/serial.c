/*
 * driver/serial/serial.c -- 
 *
 * Copyright 2010-2011 ZealTek CO., LTD.
 *
 *
 * History:
 *	2011.11.14	T.C. Chiu <tc.chiu@zealtek.com.tw>
 */

#include <configs.h>
#include <common.h>
#include <serial.h>

#if (CONFIG_SERIAL)
/*
 * Serial Port Initialization

 * If  Timer 1 is used:
 *	Baud Rate = K กั fsclk / (32 กั 2 กั (256 - TH1)) for all values of  TH1.
 *
 * If  Timer 2 is used:
 *	Baud Rate = Timer2 Overflow rate / 16
 *	          = fosc / (32 กั (65536 กV RCP2H.RCP2L))
 *		where fosc = fsclk if Timer2 is being clocked internally.
 */
void serial_init(void)
{

#if (CONFIG_UART_CLKSRC == CONFIG_UART_USE_T1)
	/*
	 * Use Timer1
	 *	TH1 = 256 กV  (K กั fsclk) / (32 กั  2 กั baud rate)
	 */
	TH1	= (unsigned char) (256UL - (CONFIG_FSCLK / (32UL * 2UL * CONFIG_BAUDRATE)));
	TL1	= TH1;
	TMOD	= (TMOD & 0x0F) | 0x20;
	TF1	= 0;
	TR1	= 1;

#elif (CONFIG_UART_CLKSRC == CONFIG_UART_USE_T2)
	/*
	 * Use Timer2
	 *	RCP2H.RCP2L = 65536 - (fosc / (32 กั baud rate))
	 */
	RCAP2L	= (unsigned char)  ((65536UL - (CONFIG_FOSC / (32UL * CONFIG_BAUDRATE))) & 0x00FF);
	RCAP2H	= (unsigned char) (((65536UL - (CONFIG_FOSC / (32UL * CONFIG_BAUDRATE))) & 0xFF00) >> 8);
	TH2	= RCAP2H;
	TL2	= RCAP2L;
	T2CON	= 0x34;
#else
#error Please define UART clock source 'CONFIG_UART_CLKSRC'
#endif

	SCON	= 0x52;
}


/*
 * Input/Output Function
 */
unsigned char serial_getc(void)
{
	unsigned char	c;
	
	while (!RI)
		;	/* wait RI = 1 */

	c  = SBUF;
	RI = 0;
	return c;
}

void serial_putc(unsigned char c)
{
repeat:
	while (!TI)
		;	/* wait TI = 1 */

	TI   = 0;
	SBUF = c;

	/* If \n, also do \r */
	if (c == '\n') {
		c = '\r';
		goto repeat;
	}
}


void serial_putcx(unsigned char c)
{
	while (!TI)
		;	/* wait TI = 1 */

	TI   = 0;
	SBUF = c;
}


void serial_puts(const char *s)
{
	while (*s != '\0') {
		serial_putc(*s++);
	}
}

unsigned char serial_tstc(unsigned short msec)
{
	if (msec == 0)
		return (unsigned char) RI;

	/* with delay */
	TMOD	= (TMOD & 0xF0) | 0x01;
	do {
		TL0 = (unsigned char)  ((65536UL - ((CONFIG_FOSC / 1000UL) >> 1)) & 0x00FF);
		TH0 = (unsigned char) (((65536UL - ((CONFIG_FOSC / 1000UL) >> 1)) & 0xFF00) >> 8);
		TF0 = 0;
		TR0 = 1;
		while (!TF0) {
			if (RI)
				return 1;
		}
	} while (--msec);

	/* time-out */
	return 0;
}

#else

void serial_init(void)
{
}

unsigned char serial_getc(void)
{
	return 0x43;
}

void serial_putc(unsigned char c)
{
	c = c;
}


void serial_putcx(unsigned char c)
{
	c = c;
}


void serial_puts(const char *s)
{
	s = s;
}

unsigned char serial_tstc(unsigned short msec)
{
	msec = msec;

	return 1;
}

#endif /* CONFIG_SERIAL */

