#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 80
void test1()
{
	char str[MAX];
	printf("请输入一个由O或X组成的字符串（长度不超过80）：");
	scanf("%s", str);
	int i = 0;               // 字符串索引
	int sum = 0;             // 最后总分
	int numO = 0;            // 记录连续O的次数

	while (str[i] != '\0')   
	{
		if (str[i] != 'O' || str[i] != 'X'){}  // 含有不符合要求的字符
		if (str[i] == 'O')
		{
			numO++;
			sum += numO;
		}

		if (str[i] == 'X')
		{
			numO = 0;   // O 出现中断
		}

		i++;           // 下一个字符
	}
	printf("最后得分：%d\n\n", sum);
}

void main()
{
	while(1)
		test1();
}