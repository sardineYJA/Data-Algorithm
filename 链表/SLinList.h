

//////////////////////////////// 线性表的链式操作 //////////////////////////////

/*
时间复杂度：
插入和删除平均时间复杂度为 O(n)
求元素个数和撤销链表时间复杂度为 O(n)
其余为 O(1)

优点：不需要预先确定数据元素的最大个数
缺点：内存空间单元利用效率不高，算法较复杂
*/

/*
将单链表修改成循环单链表（环状）
1.在初始化函数中，(*head)->next = NULL; 修改成 (*head)->next = *head;
2.循环判断条件 p->next != NULL, p->next->next != NULL; 修改成 
	p->next != head, p->next->next != head;
*/

typedef struct Node
{
	DataType data;
	struct Node *next;
}SLNode;


// 带头结点的单链存储结构


// 初始化链头
// 为什么要两个 * ，如果只有一个好像 main() 函数里 ListInitiate（&）就不能传进 head 的地址
void SListInitiate( SLNode **head)
{
	*head = (SLNode *)malloc(sizeof(SLNode));
	(*head)->next = NULL;
}


// 求当前数据元素个数
int SListLength( SLNode *head)
{
	SLNode *p = head;
	int size = 0;       // 个数

	while (p->next != NULL)
	{
		p = p->next;
		size++;
	}
	return size;
}


// 插入链表
// i (0<=i<size)  要插入的位置
// x 要插入的数据
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
		printf("插入元素位置参数有错！\n");
		return 0;
	}

	s = (SLNode *)malloc(sizeof(SLNode));
	s->data = x;

	// p 在第 i-1 个结点
	// 插入步骤，s 插到 p 后
	s->next = p->next;
	p->next = s;

	return 1;

}



// 删除结点
// i (0<=i<size-1) 要删除的结点位置
// *x 传出删除结点的数据
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

	// 当输入的 i 过大或为负数
	if (j != i-1)
	{
		printf("删除元素位置参数有错！\n");
		return 0;
	}

	s = p->next;
	*x = s->data;  // 返回删除的数据

	// p 在第 i-1 的结点
	p->next = p->next->next;  // 直接覆盖上一个删除

	free(s);      // 释放内存空间
	return 1;
}


// 取出数据元素
// i (0<=i<size-1) 要的结点位置
// *x 传出结点的数据
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
		printf("取出元素位置参数有错！\n");
		return 0;
	}

	*x = p->data;
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


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// 将链表中的全部值为 x 删除
int SListDataDelete(SLNode *head, DataType x)
{
	SLNode *p;   // 暂时处理的链表
	SLNode *s;   // 保存要删除的结点
	int tag = 0; // 标记是否有删过数据

	p = head;

	// 带头结点首个不放数据，要删除的是 p->next;
	while (p->next != NULL)
	{
		if (p->next->data == x)
		{
			s = p->next;           
			p->next = p->next->next;  // 直接覆盖上一个删除
			free(s);                  // 释放内存空间
			tag = 1;
		}
		else
		{
			p = p->next;  // 保证两个相邻的 x 可以正确删除
		}
	}

	return tag;
}


// 将 x 插入到递增单链中,保持有序
void SListDataInsert(SLNode *head, DataType x)
{
	SLNode *curr;
	SLNode *pre;
	SLNode *q;

	curr = head->next;
	pre = head;

	// 定位插入位置，退出循环，pre 指针指向要插入结点的位置
	while (curr != NULL && curr->data <= x)
	{
		pre = curr;
		curr = curr->next;
	}

	q  = (SLNode *)malloc(sizeof(SLNode));
	q->data = x;

	// 将去插入pre 结点的后面
	q->next = pre->next;
	pre->next = q;
}


// 链表递增排序
void SListSort(SLNode* head)
{
	SLNode *curr;
	SLNode *pre;
	SLNode *p;
	SLNode *q;

	p = head->next;           // 要逐个取出作为插入结点
	head->next = NULL;        // head 指针带头结点，初始为空链
	                          // 将结点重新连接，全过程不会产生结点
	while (p != NULL)
	{
		curr = head->next;
		pre = head;

		// 定位，pre 指针指向要插入的结点位置
		while (curr != NULL && curr->data <= p->data)
		{
			pre = curr;
			curr = curr->next;
		}

		q = p;                   // q 指向要插入的结点
		p = p->next;             // q 指向下一个结点

		// 把 q 指针所指结点插入 pre 指针后
		q->next = pre->next;
		pre->next = q;
	}
}



// 递增排序
void SListBubbleSort(SLNode *head)
{
	SLNode *p;
	SLNode *q;
	int temp;

	for ( p = head->next; p != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next )
		{
			if (p->data > q->data)
			{
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
		}
	}
}


// 带头结点的链表数据逆置
void SListConverse(SLNode *head)
{
	SLNode *p;    // 链表
	SLNode *q;    // q 一个要连接到 head 后的结点

	p = head->next;
	head->next = NULL;     // 新的链表，将结点重新连接上去

	while (p != NULL)
	{
		q = p;
		p = p->next;

		// 每次将 q 连接到 head 的后面，达到逆置的效果
		q->next = head->next;
		head->next = q;
	}
}


// 设带头结点的单链表 L1 和 L2 中分别存放着两个数据元素集合，
// 判断集合 L1 中的数据元素是否都是集合 L2 中的数据元素，
// （L1 是 L2 的子集）
// 直接从 L1 的数据开始在 L2 中找 
int SSubset(SLNode *head1, SLNode *head2)
{
	SLNode *p1;
	SLNode *p2;
	int flag = 0;
	p1 = head1->next;
	
	if (SListLength(head1) > SListLength(head2))
	{
		return flag;   // L1 元素个数大于 L2 的
	}

	while (p1 != NULL)
	{
		p2 = head2->next;             // 每个 p1 的数据都要从 p2 的第一个开始找
		flag = 0;                     // 下一次搜索，标志重新为 0

		while (p2 != NULL)
		{
			if (p1->data == p2->data)
			{
				flag = 1;
				break;        // 跳出第一个循环
			}

			p2 = p2->next;
		}

		if (flag == 0)
		{
			return flag;          // 如果 p1 的元素在 p2 中找不到
		}

		p1 = p1->next;
	}

	return flag;
}


// 判断单链表是否有环
// p 前进两个节点，q 前进一个节点
// p 追上 q，则存在环； p 先为 null，则没有环
bool isCircle(SLNode * head) 
{
	SLNode *p = head, *q = head;
	do 
	{
		p = p->next->next;
		q = q->next;
	} while (p && p != q);

	if (p && p ==q )
		return true;
	else 
		return false;

}

