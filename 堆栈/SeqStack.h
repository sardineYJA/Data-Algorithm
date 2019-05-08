
/*
时间复杂度：都是 O(1)
*/

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
