#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "spi.h"
#include "lcd.h"

int main(void)
{
	long Target_Value, Ambient_Value; //��ȣ �ִ� 2byte ����
	//Port_init(); // PORT �ʱ�ȭ
	//LCD_init(); // LCD �ʱ�ȭ
	//EN_HIGH; // CS idle High
	//SPI_init(); // SPI �ʱ�ȭ

	while(1)
	{
		SPI_Write(0xA0);

		SPI_Write(0xA1);

	}

	return 0;
}
