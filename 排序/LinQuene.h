

//////////////////////////////////// 不带头的链表队列 /////////////////////          
// 下面的设计，可看成有头指针有尾指针的链表，且都各自指向有数据的首个结点和尾个结点，不是一个圈

/*
时间复杂度：除撤销链表是 O(n)，都是 O(1)
*/

typedef struct qnode
{
	DataType data;
	struct qnode *next;

}LQNode;

typedef struct
{
	LQNode *front;   // 队头指针，删除
	LQNode *rear;    // 队尾指针，插入
}LQueue;


// 没有头结点的链表
// 初始化
void LQueueInitiate(LQueue *Q)
{
	Q->front = NULL;               // 有元素时，两个指针都指向有数据的结点，不是空的结点
	Q->rear = NULL;
}


// 非空否
int LQueueNotEmpty(LQueue Q)
{
	if (Q.front == NULL)
		return 0;
	else
		return 1;
}


// 入队列
void LQueueAppend(LQueue *Q, DataType x)
{
	LQNode *p;
	p = (LQNode *)malloc(sizeof(LQNode));
	p->data = x;
	p->next = NULL;

	if (Q->rear != NULL)
	{
		Q->rear->next = p;  // 队列原来非空时队尾加新结点
	}

	Q->rear = p;            // 修改队尾指针，队尾后移到 p

	if (Q->front == NULL)
	{
		Q->front = p;       // 队列原来为空时修改队头指针
	}
}


// 出列队
int LQueueDelete(LQueue *Q, DataType *d)
{
	LQNode *p;
	if (Q->front == NULL)
	{
		printf("队列为空！\n");
		return 0;
	}
	else
	{
		*d = Q->front->data;
		p = Q->front;
		Q->front = Q->front->next;    // 结点脱链，直接覆盖

		if (Q->front == NULL)
			Q->rear = NULL;          // 删除最后已给结点，要队尾指针为空

		free(p);
		return 1;
	}
}


// 取出队头数据
int LQueueGet(LQueue Q, DataType *d)
{
	if (Q.front == NULL)
	{
		printf("队列已空！\n");
		return 0;
	}
	else
	{
		*d = Q.front->data;
		return 1;
	}
}


// 释放内存 
void LQueueDestroy(LQueue Q)
{
	LQNode *p;
	LQNode *q;

	p = Q.front;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

