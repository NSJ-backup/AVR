#ifndef 	__USART_H__
#define 	__USART_H__

#include "smart2560.h"
												// ���ڰ� �߸����ʵ��� �ϱ����� unsigned long���� Ȯ��
#define	F_OSC	((unsigned long)(F_CPU))			// F_CPU�� Makefile�� define��
#define	BAUD	9600
#define	UBRR_H	( (unsigned long) ( ( F_OSC/ (16.0*BAUD) )-0.5 )>>8)	// �񵿱� ��� , normal mode
#define	UBRR_L	( (unsigned long) ((F_OSC/(16.0*BAUD))-0.5) )

void Usart0_Init(void);
void Usart1_Init(void);

void USART0_Tx( unsigned char);
void USART1_Tx( unsigned char);

void Usart_Print(const unsigned char *);

unsigned char USART0_Rx(void);
unsigned char USART1_Rx(void);

#endif	/* __USART_H__ */
