
/*
ʱ�临�Ӷȣ����� O(1)
*/

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
