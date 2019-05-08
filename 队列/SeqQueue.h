
//////////////////////// 顺序循环列队 ////////////////////////

/*
时间复杂度：都是 O(1)
*/

typedef struct
{
	DataType queue[MaxQueueSize];   // 如果超过了 99，就会回到 0  ，形成一个圈
	int rear;            // 队尾指针，插入，指向末尾数据的后一个，是空的
	int front;           // 队头指针，删除，指向的是首个有数据的
	int count;           // 计数器
}SeqCQueue;


// 初始化
void QueueInitiate(SeqCQueue *Q)
{
	Q->rear = 0;                // 定义初始队尾指针下标值
	Q->front = 0;               // 定义初始队头指针下标值
	Q->count = 0;               // 定义初始计数器
}


// 非空否
int QueueNotEmpty(SeqCQueue Q)
{
	if (Q.count != 0)
		return 1;
	else 
		return 0;
}


// 入列队
int QueueAppend(SeqCQueue *Q, DataType x)
{
	if (Q->count > 0 && Q->rear == Q->front)
	{
		printf("列队已满！\n");
		return 0;
	}

	else
	{
		Q->queue[Q->rear] = x;                    // x 插入队尾
		Q->rear = (Q->rear + 1) % MaxQueueSize;   // 队尾指示器加 1，形成环状
		Q->count++;                               // 计数器加 1
		return 1;
	}
}


// 出队列
int QueueDelete(SeqCQueue *Q, DataType *d)
{
	if (Q->count == 0)
	{
		printf("队列已空！\n");
		return 0;
	}

	else
	{
		*d = Q->queue[Q->front];
		Q->front = (Q->front +1) % MaxQueueSize;
		Q->count--;
		return 1;
	}
}

// 取队头数据
int QueueGet(SeqCQueue Q, DataType *d)
{
	if (Q.count == 0)
	{
		printf("队列已空！\n");
		return 0;
	}
	else
	{
		*d = Q.queue[Q.front];
		return 1;
	}
}


