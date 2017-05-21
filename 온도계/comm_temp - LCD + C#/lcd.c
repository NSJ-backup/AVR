#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "lcd.h"

void Lcd_Avr_Pin_Init(void)
{
	LCD_BUS_DDR = 0xFF;		// ��� ��¸���
	LCD_CTL_DDR |= (1<<LCD_PIN_RS)|(1<<LCD_PIN_RW)|(1<<LCD_PIN_EN);	// LCD�� �����ɵ��� ��¸��� (0x07�� ����)

	return;
}

void Lcd_Init(void)
{
	Lcd_Avr_Pin_Init();			// AVR pin �ʱ�ȭ

	_delay_ms(100);				// LCD booting�� ��ٸ���

	Lcd_Inst(LCD_INST_FUNC);	// LCD ��ɵ� �ʱ�ȭ
	Lcd_Inst(LCD_INST_DSP);
	Lcd_Inst(LCD_INST_ENT);
	Lcd_Inst(LCD_INST_CUR);
	Lcd_Inst(LCD_INST_CLR);
	Lcd_Inst(LCD_INST_HOME);

	_delay_ms(5);

	return;
}

void Lcd_Inst(unsigned char ucInst)	// LCD�� ����� ����, lcd.c������ ȣ�Ⱑ��
{
	LCD_BUS = ucInst;

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);
	
	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	_delay_us(50);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	return;
}

void Lcd_Data(unsigned char ucData)	// LCD�� Data�� ����
{
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	_delay_us(50);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

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
	Lcd_Inst( 0x80 | ucAddr );	// Ŀ�� ��ġ�� �����Ѵ�
	
	return;
}

void Lcd_Cursor(unsigned char x, unsigned char y)
{
	unsigned char ucAddr;

	ucAddr = (0x40*y) + x;

	Lcd_Inst( 0x80 | ucAddr );	// Ŀ�� ��ġ�� �����Ѵ�

	return;
}

void Lcd_LineClear(unsigned char line)
{
	char * clear = "                ";
	
	Lcd_SetAddr( (line*0x40) );
	Lcd_Print(clear);
}

void Lcd_CGRAM_Init(void)
{	
	unsigned char NO[8] 	= {0x1F, 0x15, 0x15, 0x1B, 0x15, 0x15, 0x1F, 0x1F};
	unsigned char OK[8] 	= {0x1F, 0x1B, 0x15, 0x15, 0x15, 0x15, 0x1B, 0x1F};
	
	Lcd_CGRAM_Set(0, NO);		
	Lcd_CGRAM_Set(1, OK);

	Lcd_SetAddr(0);	

	return;
}

void Lcd_CGRAM_Data(unsigned char ucData)
{
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN Ȱ��ȭ
	_delay_us(50);													// (�ּ� 150ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram�� �� ��
	_delay_us(10);													// (�ּ� 40ns �ʿ�)LCD�� ����� �����ϱ����� �����ð�

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

