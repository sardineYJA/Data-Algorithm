

/////////////////////////////////// 优先级队列 /////////////////////////////////             
// 操作是对优先级最高的开始，如出列队
// 出列对后，后面的数组元素会前移一个
// 数值越小，优先级越高
typedef struct
{
	int priority;     // 优先级
	ElemType data;         // 其他内容
}PriorityData;

typedef struct
{
	PriorityData queue[MaxQueueSize];  // 队列数组
	int size;                          // 元素个数
}SeqPQueue;


// 初始化 
void PQueueInitiate(SeqPQueue *Q)
{
	Q->size = 0;    // 初始化元素个数
}

// 非空
int PQueueNotEmpty(SeqPQueue Q)
{
	if (Q.size <= 0)
		return 0;
	else 
		return 1;
}

// 添加
int PQueueAppend(SeqPQueue *Q, PriorityData x)
{
	if (Q->size >= MaxQueueSize)
	{
		printf("队列已满！\n");
		return 0;
	}
	else
	{
		Q->queue[Q->size] = x;
		Q->size++;                   // 个数加 1 
		return 1;
	}
}


// 删除优先级最高的元素
int PQueueDelete(SeqPQueue *Q, PriorityData *d)
{
	PriorityData min;
	int minIndex;           // 优先级最高的元素下标

	if (Q->size <= 0)
	{
		printf("队列已空！\n");
		return 0;
	}
	else
	{
		min = Q->queue[0];           // 初始选定 queue[0] 为优先级最高的元素
		minIndex = 0;

		for (int i = 1; i < Q->size; i++)
		{
			if (Q->queue[i].priority < min.priority)  // 循环找到最高优先级数据
			{
				min = Q->queue[i];
				minIndex = i;
			}
		}

		*d = Q->queue[minIndex];    // 优先级最高的元素

		for (int i = minIndex; i < Q->size; i++)
		{
			Q->queue[i-1] = Q->queue[i];  // 元素依次前移
		}

		Q->size--;
		return 1;
	}
}


// 返回优先级最高的
int PQueueGet(SeqPQueue *Q, PriorityData *d)
{
	PriorityData min;
	int minIndex;           // 优先级最高的元素下标
	int i;

	if (Q->size <= 0)
	{
		printf("队列已空！\n");
		return 0;
	}
	else
	{
		min = Q->queue[0];           // 初始选定 queue[0] 为优先级最高的元素
		minIndex = 0;

		for (i = 1; i < Q->size; i++)
		{
			if (Q->queue[i].priority < min.priority)
			{
				min = Q->queue[i];
				minIndex = i;
			}
		}

		*d = Q->queue[minIndex];    // 优先级最高的元素
		return 1;
	}
}

