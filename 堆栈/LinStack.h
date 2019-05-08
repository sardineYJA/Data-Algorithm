
////////////////////////// 带头结点的链式堆栈 //////////

/*
时间复杂度：都是 O(1)
*/

typedef struct snode
{
	DataType data;
	struct snode *next;
}LSNode;


// 初始化
void LStackInitiate(LSNode **head)
{
	*head = (LSNode *)malloc(sizeof(LSNode));
	(*head)->next = NULL;
}


// 非空否
int LStackNotEmpty(LSNode *head)
{
	if (head->next == NULL)
		return 0;
	else
		return 1;
}


// 入栈，将数据元素 x 插入 head 的栈顶作为新的栈顶
void LStackPush(LSNode *head, DataType x)
{
	LSNode *p;
	p = (LSNode *)malloc(sizeof(LSNode));

	p->data = x;

	p->next = head->next;   // 新结点链入栈顶
	head->next = p;         // 新结点成新的栈顶
}


// 出栈
int LStackPop(LSNode *head, DataType *d)
{
	LSNode *p = head->next;
	if (p == NULL)
	{
		printf("堆栈已空！\n");
		return 0;
	}

	head->next = p->next;      // 删除结点 p
	*d = p->data;

	free(p);
	return 1;
}


// 取栈顶
int LStackTop(LSNode *head, DataType *d)
{
	LSNode *p = head->next;
	if (p == NULL)
	{
		printf("堆栈已空！\n");
		return 0;
	}

	*d = p->data;
	return 1;
}


// 释放内存
void LStackDestroy(LSNode *head)
{
	LSNode *p;
	LSNode *q;   // 要释放的结点

	p = head;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

