#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int DataType;
typedef struct Node
{
	DataType data;       // 系数
	DataType exponent;   // 指数
	struct Node *next;
}SLNode;

// 初始化链头
void SListInitiate( SLNode **head)
{
	*head = (SLNode *)malloc(sizeof(SLNode));
	(*head)->next = NULL;
}


// 插入链表
int SListInsert(SLNode *head, int i, DataType x)
{
	SLNode *p;   // 暂时处理的链表
	SLNode *s;   // 保存传进的数据结点
	int j;
	p = head;
	j = -1;

	while (p->next != NULL && j < i-1)
	{
		p = p->next;
		j++;
	}
	// 当输入的 i 过大或为负数
	if (j != i-1)
	{
		printf("插入系数参数有错！\n");
		return 0;
	}
	s = (SLNode *)malloc(sizeof(SLNode));
	s->data = x;
	s->exponent = i;
	s->next = p->next;
	p->next = s;

	return 1;
}

// 取出数据元素
int SListGet(SLNode* head, int i, DataType *x)
{
	SLNode *p;
	int j;

	p = head;
	j = -1;

	while (p->next != NULL && j < i)
	{
		p = p->next;
		j++;
	}

	if ( j != i)
	{
		printf("系数不足补0！\n");
		*x = 0;
		return 0;
	}

	*x = p->data;
	return 1;
}

// 删除结点
int SListDelete(SLNode *head, int i, DataType *x)
{
	SLNode *p;   // 暂时处理的链表
	SLNode *s;   // 保存要删除的结点
	int j;
	p = head;
	j = -1;

	// 带头结点首个不放数据，要删除的是 p->next;
	while (p->next != NULL && p->next->next != NULL && j < i-1)
	{
		p = p->next;
		j++;
	}
	// 好像空链表，删除0会报错
	if (head->next == NULL && i == 0)
	{
		*x = 0;  
		return 0;
	}
	// 当输入的 i 过大或为负数
	if (j != i-1 )
	{
		*x = 0;
		return 0;
	}
	s = p->next;
	*x = s->data;             // 返回删除的数据
	                          // p 在第 i-1 的结点
	p->next = p->next->next;  // 直接覆盖上一个删除
	free(s);                  // 释放内存空间
	return 1;
}

// 释放链表
void SListDestroy(SLNode **head)
{
	SLNode *p;  // 暂时处理的链表
	SLNode *s;  // 释放的结点

	p = *head;
	while (p != NULL)
	{
		s = p;
		p = p->next;
		free(s);
	}

	*head = NULL;
}


// 输出多项式结果
void print(SLNode *result)
{
	SLNode *p;
	p = result->next;
	printf("多项式R(X) = ");
	while (p != NULL)
	{
		if (p->data != 0)
		{
			printf("%dX^%d ", p->data, p->exponent);
			if (p->next != NULL && p->next->data >= 0)
				printf("+");
		}
			
		p = p->next;
		
	}
	printf("\n\n");
}

// 指定多项式的 X ，计算结果
DataType calculateResult(SLNode *result, DataType x)
{
	SLNode *p;
	p = result->next;
	DataType sum = 0;
	while (p != NULL)
	{
		sum = sum + p->data * (DataType)pow((double)x, p->exponent);
		p = p->next;
	}
	return sum;
}

// 对多项式 head1 和 head2 进行加法运算，结果保存到 result
// flag = 1  进行加法
// flag = -1 进行减法
void add(SLNode *head1, SLNode *head2, SLNode *result, int flag)
{
	SLNode *p1 = head1->next;
	SLNode *p2 = head2->next;
	DataType exponent = 0;    // 初始化指数0

	// 当两个多项式都不为空，指数相同的两项相加
	while (p1 != NULL && p2 != NULL)
	{
		SListInsert(result, exponent, p1->data + flag*p2->data);
		exponent++;
		p1 = p1->next;
		p2 = p2->next;
	}
	// 如果 p2 已为空，将 p1 的多项式直接存储到指定位置
	while (p1 != NULL)
	{
		SListInsert(result, exponent, p1->data);
		exponent++;
		p1 = p1->next;
	}
	// 如果 p1 已为空，将 p2 的多项式直接存储到指定位置
	while (p2 != NULL)
	{
		SListInsert(result, exponent, flag*p2->data);
		exponent++;
		p2 = p2->next;
	}
}

// 对多项式 head1 和 head2 进行乘法运算，结果保存到 result
void multiply(SLNode *head1, SLNode *head2, SLNode *result)
{
	// 乘法
	SLNode *p1;
	SLNode *p2;

	p1 = head1->next;
	p2 = head2->next;

	DataType data;           // 要插入的系数
	DataType exponent = 0;   // 要插入的指数
	DataType pre_data = 0;   // 原来结点的系数

	while (p2 != NULL)
	{
		p1 = head1->next;
		while (p1 != NULL)
		{
			data = p1->data * p2->data;              // 要插入的系数
			exponent = p1->exponent + p2->exponent;  // 要插入的指数
			
			// 此时应该删除该指数的结点，再重新插入该指数的结点
			// 先取出原来的系数，没有则取出 0
			SListDelete(result, exponent,  &pre_data);
			data = data + pre_data;
			SListInsert(result, exponent, data);
			p1 = p1->next;  //  p1 下一项，将 p1 所有项都乘于 p2 的第一项
			
		}
		p2 = p2->next;
	}
}


// 输入多项式
void input(SLNode * head)
{
	DataType num;
	int n;
	printf("请输入所有项中最大指数 n ：");
	scanf("%d", &n);
	printf ("多项式P(x) = 请输入每项系数 a0, a1, a2, ..... an：\n");
	for (int i = 0; i < n+1; i++)
	{
		scanf("%d", &num);
		SListInsert(head, i, num);
	}
}

void main()
{
	SLNode *head1;
	SLNode *head2;
	SLNode *result;

	// 初始化
	SListInitiate(&head1);
	SListInitiate(&head2);
	SListInitiate(&result);

	printf("*--------------------------------\n");
	printf("*       1.指定 X 对多项式求值   *\n");
	printf("*       2.两个多项式相加        *\n");
	printf("*       3.两个多项式相减        *\n");
	printf("*       4.两个多项式想乘        *\n");
	printf("*--------------------------------\n");
	
	int choose = 0;
	int x;
	int sum;
	printf("输入你想要的功能：");
	scanf("%d", &choose);
	switch(choose)
	{
		// 指定 X 对多项式求值
	case 1:
		printf("请输入 x :");
		scanf("%d", &x);
		input(head1);
		sum = calculateResult(head1, x);
		print(head1);
		printf("结果：%d \n\n", sum);
		break;

		// 两个多项式相加
	case 2:
		input(head1);
		input(head2);
		add(head1, head2, result, 1);
		print(result);
		break;

		// 两个多项式相减
	case 3:
		input(head1);
		input(head2);
		add(head1, head2, result, -1);
		print(result);
		break;

		// 两个多项式想乘 
	case 4:
		input(head1);
		input(head2);
		multiply(head1, head2, result);
		print(result);
		break;

	default :
		printf("选择错误！\n");
		break;
	}
}