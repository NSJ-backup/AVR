#include <avr/io.h>
#include "usart.h"

void Usart0_Init(void)
{
	UBRR0H = 0;
	UBRR0L = 8;	// 115200

	UCSR0A = (0<<U2X)|(0<<MPCM);
	UCSR0B = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
	UCSR0C = (0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);

	return;
}

void Usart1_Init(void)
{
	UBRR1H = 0;
	UBRR1L = 0;		// 1M

	UCSR1A = (0<<U2X)|(0<<MPCM);
	UCSR1B = (1<<TXEN);
	//UCSR1B = (1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
	UCSR1C = (0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);

	return;
}

void USART0_Tx( unsigned char ucData )
{
	// Wait for empty transmit buffer (empty UDR)
	// UCSR0A�� (1<<UDRE)�� MASK���Ѽ� UCSR0A�� UDRE�ڸ��� ��Ʈ�� ����
	// UCSR0A�� UDRE��Ʈ�� 1�̸� ���ѷ����� ����
	// UCSR0A�� UDRE��Ʈ�� 0�̸� ������ ���� ���� �ڵ�� ������
	// Polling: ���ͷ�Ʈ������ CPU�ڿ����� �����
	while ( 0 == ( UCSR0A & (1<<UDRE)) );


	// Put data into buffer, sends the data 
	UDR0 = ucData;

	return;
}

void USART1_Tx( unsigned char ucData )
{
	while ( 0 == ( UCSR1A & (1<<UDRE)) );

	UDR1 = ucData;

	return;
}

void Usart_Print(const char * ucString)
{
	while( 0 != *ucString )
	{
		USART0_Tx(*ucString);
		++ucString;
	}

	return;
}

unsigned char USART0_Rx( void )
{
	// Wait for data to be received 	
	while ( !( UCSR0A  &  (1<<RXC) ) )	;	//	UCSRA: Datasheet 184p 	
										//	Polling ���(UCSRA�� ���ſϷ��Ʈ RXC�� 1�� ���嶧���� wait)

	// Get and return received data from buffer 
	return UDR0;		// ���ŵ� �����͸� �Լ��� ȣ���� ���� �����Ѵ�
}

unsigned char USART1_Rx( void )
{
	// Wait for data to be received 
	while ( !( UCSR1A  &  (1<<RXC) ) )	;

	// Get and return received data from buffer 
	return UDR1;
}

