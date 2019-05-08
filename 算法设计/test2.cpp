#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 20            // �����������ָ���
#define MaxStackSize 20   // ˳���ջ�����Ԫ�ظ���
typedef int DataType;     // ��ջ�洢����

typedef struct
{
	DataType stack[MaxStackSize];
	int top;
}SeqStack;

// ��ʼ��
void StackInitiate(SeqStack *S)
{
	S->top = 0;
}

// �ǿշ�
int StackNotEmpty(SeqStack S)
{
	if (S.top <= 0)
		return 0;
	else
		return 1;
}

// ��ջ
int StackPush(SeqStack *S, DataType x)
{
	if (S->top >= MaxStackSize)
	{
		printf("��ջ�������޷����룡\n");
		return 0;
	}
	else
	{
		S->stack[S->top] = x;
		S->top++;
		return 1;
	}
}

// ��ջ
int StackPop(SeqStack *S, DataType *d)
{
	if (S->top <= 0)
	{
		printf("��ջ�ѿգ��޷���ջ��\n");
		return 0;
	}
	else
	{
		S->top--;
		*d = S->stack[S->top];
		return 1;
	}
}


// ȡջ��Ԫ�أ���ջ������
int StackTop(SeqStack S, DataType *d)
{
	if (S.top <= 0)
	{
		printf("��ջ�ѿգ�\n");
		return 0;
	}
	else
	{
		*d = S.stack[S.top - 1];
		return 1;
	}
}


// �ж�����һ�������Ƿ��������ǰ���ĳ���ض���˳���ջ
int require(DataType num[], int n)
{
	// �ж������Ƿ�� 1 �� n ������
	for (int i = 0; i < n; i++)
	{
		if (num[i] < 1 || num[i] > n)
		{
			printf("���벻����Ҫ��\n");
			return 0;
		}

		for (int j = 0; j < n; j++)
		{
			if (j != i && num[j] == num[i])
			{
				printf("��������ͬ�����֣�������Ҫ��\n");
				return 0;
			}
		}
	}

	// �ж��Ƿ��������ǰ���ĳ���ض���˳���ջ
	// ÿһ��Ԫ�� i ����� i С�Ķ��ǽ���
	for (int i = 0; i < n; i++)
	{
		DataType temp = num[i];
		for (int j = i+1; j < n; j++)
		{
			if (num[i] > num[j])
			{
				if (temp < num[j])
				{
					printf("�ô����ֲ��ܰ���ĳ���ض���˳���ջ\n");
					return 0;
				}	
				temp = num[j];
			}
		}
	}
	return 1;
}

// �������岽��õ�����
int resultStack(DataType num[], int n)
{
	SeqStack myStack;
	StackInitiate(&myStack);    	// ��ʼ��

	printf("���岽�����£�\n");
	int start = 1;                  // ˳��� 1 ��ʼ�� n ��ʼ��ջ
	for (int j = 0; j < n; )
	{
		while (start <= num[j] && start <= n)
		{
			// �����ǰ������С������Ԫ�أ�����������ֱ����ջ
			if (num[j] != start)
			{
				printf("%d ��ջ\n", start);
				StackPush(&myStack, start);  
			}
			// �����ǰ��������������Ԫ�أ�����������ֱ����ջ����ջ
			else 
			{
				printf("%d ��ջ����ջ\n", start);
				j++;     // ��һ������Ԫ��
			}

			start++;     // ��һ��������
		}

		// �����ǰ��������������Ԫ�أ����ջ�����������бȽ�
		while (start > num[j] && start <= n)
		{
			DataType temp;
			StackPop(&myStack, &temp);
			
			if (temp == num[j])
			{
				printf ("%d ��ջ\n", temp);
				j++;    // �����������һ��
			}
			else
			{
				return 0;
			}
		}

		// ��ʱ 1 - n �Ѿ���ɱ��������� for
		if (start > n)
			break;  
	}

	// ������ջ����������ȫ����ջ
	while ( StackNotEmpty(myStack) )
	{
		DataType temp;
		StackPop(&myStack, &temp); 
		printf ("%d ��ջ\n", temp);
	}
	return 1;
}

void test2()
{
	DataType num[MAX];  // ���ִ�
	int n = 0;          // ���ִ��ĸ���

	printf("����һ�� 1-n ����(������0����)��");
	for (n = 0; ; n++)
	{
		scanf("%d", &num[n]);
		if (num[n] == 0 || n >= MAX-1)
			break;
	}

	printf("����������֣�");
	for (int j = 0; j < n; j++)
		printf("%d ", num[j]);
	printf("\n");

	// �������Ҫ��������õ������еľ��岽��
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