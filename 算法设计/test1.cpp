#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 80
void test1()
{
	char str[MAX];
	printf("������һ����O��X��ɵ��ַ��������Ȳ�����80����");
	scanf("%s", str);
	int i = 0;               // �ַ�������
	int sum = 0;             // ����ܷ�
	int numO = 0;            // ��¼����O�Ĵ���

	while (str[i] != '\0')   
	{
		if (str[i] != 'O' || str[i] != 'X'){}  // ���в�����Ҫ����ַ�
		if (str[i] == 'O')
		{
			numO++;
			sum += numO;
		}

		if (str[i] == 'X')
		{
			numO = 0;   // O �����ж�
		}

		i++;           // ��һ���ַ�
	}
	printf("���÷֣�%d\n\n", sum);
}

void main()
{
	while(1)
		test1();
}