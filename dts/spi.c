#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

void Spi_Init(void)
{
	// B0 : /SS, B1 : SCK, B2 : MOSI, B3 : MISO
	DDRB = 0xF7;	// SPI�� ����ϴ� ��

	SPCR = 0x3D;	// MSB first, CPOL=1, CPHA=1, SCK=Fosc/16
	SPSR = 0x00;

	return;
}

void SPI_Write(unsigned char byte)
{
	// /CS = 0

	// SPDR 
	// Delay 10ms
	// Data ����
	// Delay 10ms
	// Data ����

	// Delay 50ms

	// Data ����
	// Delay 10ms
	// Data ����
	// Delay 10ms
	// Data ����

	// /CS = 1

	return;
}

/*
long Check_Temp(unsigned char datum) // Sonix �����Ϸ����� Long �� 2byte �Դϴ�.
{
	long temp_bank=0;

	SIOB = datum; // Buffer �������Ϳ� ����
	NOP(1);
	EN_LOW; // Enable Low
	delay_us(10); // 10us delay
	FSTART = 1; // SPI ���� ����
	while(FSTART==1); // ���� �Ϸ� flag check
	buffer2=SIOB; // dummy

	SIOB = 0x22; // 0x22 or 0x00 �����մϴ�.
	delay_ms(10); // 10ms delay
	FSTART = 1; // SPI ���� ����
	while(FSTART==1); // ���� �Ϸ� flag check
	buffer=SIOB; // ���� Byte ����

	SIOB = 0x22; // 0x22 or 0x00 �����մϴ�.
	delay_ms(10); // 10ms delay
	FSTART = 1; // SPI ���� ����
	while(FSTART==1); // ���� �Ϸ� flag check
	buffer1=SIOB; // ���� Byte ����

	EN_HIGH; // Enable High
	temp_bank=(buffer1*256)+buffer; // ����, ���� Byte �µ� ����.

	// temp_bank : ���� �µ�
	return temp_bank;
}
*/
