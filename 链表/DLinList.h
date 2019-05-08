
//////////////////////////// 双向带头结点链表 /////////////////////

// 用于频繁查找当前结点的后继结点和前驱结点

typedef struct DNode
{
	DataType data;
	struct DNode *next;           
	struct DNode *prior;
}DLNode;



// 带头结点的双向链表

// 初始化
void DListInitiate(DLNode **head)
{
	*head = (DLNode *)malloc(sizeof(DLNode));
	(*head)->prior = *head;          // 构成前驱指针循环链表
	(*head)->next = *head;           // 构成后继指针循环链表
}


// 求元素个数
int DListLength(DLNode *head)
{
	DLNode *p = head;
	int size = 0;
	 
	while (p->next != head)
	{
		p = p->next;
		size++;
	}

	return size;
}



// 获取结点数据
int DListGet(DLNode* head, int i, DataType *x)
{
	DLNode *p;
	int j;

	p = head;
	j = -1;

	while (p->next != head && j < i)
	{
		p = p->next;
		j++;
	}

	if ( j != i)
	{
		printf("取出元素位置参数有错！\n");
		return 0;
	}

	*x = p->data;
	return 1;
}


// 插入元素
int DListInsert(DLNode *head, int i, DataType x)
{
	DLNode *p;
	DLNode *s;
	int j;

	p = head->next;
	j = 0;

	while (p != head && j < i)
	{
		p = p->next;
		j++;
	}

	if (j != i)
	{
		printf("插入元素位置参数有错！\n");
		return 0;
	}

	s = (DLNode *)malloc(sizeof(DLNode));
	s->data = x;

	// p 在第 i 个结点
	s->prior = p->prior;   // 前一个的关系
	p->prior->next = s;

	s->next = p;           // 后一个的关系
	p->prior = s;

	return 1;
}


// 删除结点
int DListDelete(DLNode *head, int i, DataType *x)
{
	DLNode *p;
	int j;

	p = head->next;
	j = 0;

	while (p->next != head && j < i)
	{
		p = p->next;
		j++;
	}

	if (j != i)
	{
		printf("删除元素位置参数有错！\n");
		return 0;
	}

	*x = p->data;

	// p 在第 i 个结点
	p->prior->next = p->next;        // 前一个的关系
	p->next->prior = p->prior;       // 后一个的关系

	free(p);
	return 1;
}




// 释放内存
void DListDestroy(DLNode **head)
{
	DLNode *p;
	DLNode *s;
	int i;
	int n;

	n = DListLength(*head);  // 结点个数
	p = *head;

	for (i = 0; i <= n; i++)
	{
		s = p;
		p = p->next;
		free(s);
	}

	*head = NULL;
}


