#include <avr/io.h>
#include "lcd.h"

#define	DNUM1	120
#define	DNUM2	480
#define	DNUM3	120

static unsigned int uiCharCnt;

void Lcd_Avr_Pin_Init(void)
{
	LCD_BUS_DDR = 0xFF;		// ��� ��¸���
	LCD_CTL_DDR |= (1<<LCD_PIN_RS)|(1<<LCD_PIN_RW)|(1<<LCD_PIN_EN);	// LCD�� �����ɵ��� ��¸��� (0x07�� ����)

	return;
}

void Lcd_Inst(unsigned char ucInst)	// LCD�� ����� ����, lcd.c������ ȣ�Ⱑ��
{
	volatile unsigned int uiCnt;

	LCD_BUS = ucInst;

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM1);
	
	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	DELAY(DNUM2);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM3);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	return;
}

void Lcd_Data(unsigned char ucData)	// LCD�� Data�� ����
{
	volatile unsigned int uiCnt;

	if( 15 < uiCharCnt )				// �ּҰ� 15���� ũ��
	{
		if( 40 > uiCharCnt )			// �ּҰ� 40���� �۴ٸ�
		{
			uiCharCnt = 40;			// 2 ���� �� ��

			Lcd_SetAddr(uiCharCnt);	
		}
		else if( 55 < uiCharCnt )		// �ּҰ� 55���� ũ��
		{
			uiCharCnt = 0;			// ù ���� �� ��

			Lcd_SetAddr(uiCharCnt);	
		}
	}

	++uiCharCnt;

	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM1);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	DELAY(DNUM2);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM3);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	return;
}

void Lcd_Init(void)
{
	volatile unsigned int uiCnt;

	Lcd_Avr_Pin_Init();			// AVR pin �ʱ�ȭ

	DELAY(65000);				// LCD booting�� ��ٸ���

	Lcd_Inst(LCD_INST_FUNC);	// LCD ��ɵ� �ʱ�ȭ
	Lcd_Inst(LCD_INST_DSP);
	Lcd_Inst(LCD_INST_ENT);
	Lcd_Inst(LCD_INST_CUR);
	Lcd_Inst(LCD_INST_CLR);
	Lcd_Inst(LCD_INST_HOME);

	uiCharCnt = 0;

	return;
}

void Lcd_Print(const char * ucString)	// ���� ���ڿ��� ���������ʱ����ؼ� const�� ���δ�
{
	while( 0 != *ucString )
	{
		Lcd_Data(*ucString);
		++ucString;
	}

	return;
}


void Lcd_SetAddr(unsigned char ucAddr)
{
	if( 15 < ucAddr )				// �ּҰ� 15���� ũ��
	{
		if( 40 > ucAddr )			// �ּҰ� 40���� �۴ٸ�
		{
			ucAddr = 40;			// ���� ���� �� ��
		}
		else if( 55 < ucAddr )		// �ּҰ� 55���� ũ��
		{
			ucAddr = 0;			// ù ���� �� ��
		}
	}
	uiCharCnt = ucAddr;
	
	Lcd_Inst( 0x80 | ucAddr );	// Ŀ�� ��ġ�� �����Ѵ�
	
	return;
}

void Lcd_CGRAM_Init(void)
{	
	unsigned char Nam[8] 	= {0x12, 0x12, 0x13, 0x1E, 0x02, 0x1F, 0x11, 0x1F};
	unsigned char Su[8] 	= {0x04, 0x04, 0x0A, 0x11, 0x00, 0x1F, 0x04, 0x04};
	unsigned char Jin[8] 	= {0x1D, 0x09, 0x15, 0x15, 0x01, 0x10, 0x10, 0x1F};
	
	Lcd_CGRAM_Set(0, Nam);		
	Lcd_CGRAM_Set(1, Su);
	Lcd_CGRAM_Set(2, Jin);

	Lcd_SetAddr(uiCharCnt);	

	return;
}

void Lcd_CGRAM_Data(unsigned char ucData)
{
	volatile unsigned int uiCnt;
	
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM1);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	DELAY(DNUM2);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	DELAY(DNUM3);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	return;
}

void Lcd_CGRAM_Set(unsigned char ucAddr, const unsigned char * ucData)
{
	unsigned int uiCnt = 0;

	Lcd_Inst( 0x40 | (ucAddr<<3) );

	for( uiCnt = 0; uiCnt < 8; uiCnt++)
	{
		Lcd_CGRAM_Data(*ucData);
		ucData++;
	}
	
	return;
}

