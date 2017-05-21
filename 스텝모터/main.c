#include <avr/io.h>
#include <util/delay.h>

// PORTC 0, 1, 2, 3  ==  A, B, /A, /B
char Step[4] = {0x09, 0x03, 0x06, 0x0C};

int main(void)
{
	int i = 0;			// ��� �޽� ����
	int cnt = 0;		// ��� �޽� ���� count
	DDRC = 0x0F;		// PORTC ���� 4��Ʈ �������
	
	
	while(1)
	{
		for(cnt = 0; cnt < 212; cnt++)	// �ð���� 1���� ȸ��
		{
			PORTC = Step[i];
			_delay_ms(50);

			i++;
			if(i > 3)
			{
				i = 0;
			}
		}
		_delay_ms(1000);

		for(cnt = 0; cnt < (int)((60/1.7)+0.5); cnt++)	// �ݽð���� 60�� ȸ��
		{
			PORTC = Step[i];
			_delay_ms(50);

			i--;
			if(i < 0)
			{
				i = 3;
			}
		} 

		_delay_ms(1000);
	}

	return 0;
}

