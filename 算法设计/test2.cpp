#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 20            // 输入最多的数字个数
#define MaxStackSize 20   // 顺序堆栈的最大元素个数
typedef int DataType;     // 堆栈存储类型

typedef struct
{
	DataType stack[MaxStackSize];
	int top;
}SeqStack;

// 初始化
void StackInitiate(SeqStack *S)
{
	S->top = 0;
}

// 非空否
int StackNotEmpty(SeqStack S)
{
	if (S.top <= 0)
		return 0;
	else
		return 1;
}

// 入栈
int StackPush(SeqStack *S, DataType x)
{
	if (S->top >= MaxStackSize)
	{
		printf("堆栈已满，无法插入！\n");
		return 0;
	}
	else
	{
		S->stack[S->top] = x;
		S->top++;
		return 1;
	}
}

// 出栈
int StackPop(SeqStack *S, DataType *d)
{
	if (S->top <= 0)
	{
		printf("堆栈已空，无法出栈！\n");
		return 0;
	}
	else
	{
		S->top--;
		*d = S->stack[S->top];
		return 1;
	}
}


// 取栈顶元素，但栈顶不变
int StackTop(SeqStack S, DataType *d)
{
	if (S.top <= 0)
	{
		printf("堆栈已空！\n");
		return 0;
	}
	else
	{
		*d = S.stack[S.top - 1];
		return 1;
	}
}


// 判断输入一串数字是否能让它们按照某种特定的顺序出栈
int require(DataType num[], int n)
{
	// 判断输入是否从 1 到 n 的乱序
	for (int i = 0; i < n; i++)
	{
		if (num[i] < 1 || num[i] > n)
		{
			printf("输入不符合要求\n");
			return 0;
		}

		for (int j = 0; j < n; j++)
		{
			if (j != i && num[j] == num[i])
			{
				printf("输入有相同的数字，不符合要求\n");
				return 0;
			}
		}
	}

	// 判断是否能让它们按照某种特定的顺序出栈
	// 每一个元素 i 后面比 i 小的都是降序
	for (int i = 0; i < n; i++)
	{
		DataType temp = num[i];
		for (int j = i+1; j < n; j++)
		{
			if (num[i] > num[j])
			{
				if (temp < num[j])
				{
					printf("该串数字不能按照某种特定的顺序出栈\n");
					return 0;
				}	
				temp = num[j];
			}
		}
	}
	return 1;
}

// 给出具体步骤得到序列
int resultStack(DataType num[], int n)
{
	SeqStack myStack;
	StackInitiate(&myStack);    	// 初始化

	printf("具体步骤如下：\n");
	int start = 1;                  // 顺序从 1 开始到 n 开始入栈
	for (int j = 0; j < n; )
	{
		while (start <= num[j] && start <= n)
		{
			// 如果当前序列数小于数组元素，将该序列数直接入栈
			if (num[j] != start)
			{
				printf("%d 入栈\n", start);
				StackPush(&myStack, start);  
			}
			// 如果当前序列数等于数组元素，将该序列数直接入栈，出栈
			else 
			{
				printf("%d 入栈，出栈\n", start);
				j++;     // 下一个数组元素
			}

			start++;     // 下一个序列数
		}

		// 如果当前序列数大于数组元素，则出栈序列数，进行比较
		while (start > num[j] && start <= n)
		{
			DataType temp;
			StackPop(&myStack, &temp);
			
			if (temp == num[j])
			{
				printf ("%d 出栈\n", temp);
				j++;    // 输入数组的下一个
			}
			else
			{
				return 0;
			}
		}

		// 此时 1 - n 已经完成遍历，跳出 for
		if (start > n)
			break;  
	}

	// 最后如果栈还有数字则全部出栈
	while ( StackNotEmpty(myStack) )
	{
		DataType temp;
		StackPop(&myStack, &temp); 
		printf ("%d 出栈\n", temp);
	}
	return 1;
}

void test2()
{
	DataType num[MAX];  // 数字串
	int n = 0;          // 数字串的个数

	printf("输入一串 1-n 数字(以数字0结束)：");
	for (n = 0; ; n++)
	{
		scanf("%d", &num[n]);
		if (num[n] == 0 || n >= MAX-1)
			break;
	}

	printf("你输入的数字：");
	for (int j = 0; j < n; j++)
		printf("%d ", num[j]);
	printf("\n");

	// 如果符合要求则输出得到该序列的具体步骤
	if (require(num, n))
		resultStack(num, n);
}

void main()
{
	while(1)
	{
		test2();
		printf("\n");
	}
}