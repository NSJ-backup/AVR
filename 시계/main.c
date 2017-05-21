#include "smart2560.h"
#include "lcd.h"

volatile unsigned int tdSec = 0;		// 0.01s ���� ī��Ʈ
volatile unsigned int tSec = 0;		// 1s ���� ī��Ʈ
volatile unsigned char tFlag = 0;	// �ð� ���� �÷���

int main(void)
{
	SREG &= 0x7F;				// global interrupt disable(register setting ���� ������ ����)

	Lcd_Init();		// LCD �ʱ�ȭ
	TCCR1A = 0x00;	// CTC mode
	TCCR1B = 0x0C;	// CTC mode, 256 ����
	TCCR1C = 0x00;	// ����� ����
	TCNT1 = 0x0000;	// ī���� �ʱ�ȭ
	TIMSK1 = 0x02;	// timer interrupt enable
	OCR1A = 624;		// 0.01 sec ���� Ÿ�̸�

	EICRB = 0x0A;		// falling edge interrupt
	EIMSK = 0x30;	// INT4, INT5 enable

	SREG |= 0x80;				// global interrupt enable

	Lcd_Print("Time= ");
	tFlag = 1;
	
	while(1)
	{
		if(tFlag)		// Ÿ�̸� ���ͷ�Ʈ�� �߻�
		{
			Lcd_SetAddr(6);				// �ð� ǥ�� �ڸ� ����
			Lcd_Data(((tSec/60)/10)+'0');
			Lcd_Data(((tSec/60)%10)+'0');
			Lcd_Data(':');
			Lcd_Data(((tSec%60)/10)+'0');
			Lcd_Data(((tSec%60)%10)+'0');
			Lcd_Data(':');
			Lcd_Data(tdSec/10+'0');
			Lcd_Data(tdSec%10+'0');

			tFlag = 0;
		}
	}
	return 0;
}

void __vector_17(void)		// 0.01s timer interrupt
{
	tdSec++;				// 10ms ������ ����
	
	if(tdSec == 100)
	{
		tSec++;				// 1s ������ ����
		if(tSec >= 3600) tSec = 0;		// 1�ð� �̻� ī���͸� ����

		tdSec = 0;
	}
	
	tFlag = 1;				// LCD display
}

void __vector_5(void)		// INT4: Timer on/off
{
	// Timer Interrupt ����
	
	SREG &= 0x7F;				// global interrupt disable
	
	TIMSK1 ^= 0b00000010;		// compare match A interrupt enable/disable

	SREG |= 0x80;				// global interrupt enable
}

void __vector_6(void)		// INT5: Timer reset
{
	// Timer �ʱ�ȭ
	if( !(TIMSK1 & 0x02))		// Ÿ�̸Ӱ� ���۾��ϴ� ���¿���
	{
		tdSec = 0;			// �ʱ�ȭ
		tSec = 0;
		tFlag = 1;			// �ʱ�ȭ�� ���� LCD ǥ��
	}
}

