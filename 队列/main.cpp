#include <stdio.h>
#include <stdlib.h>

#define MaxQueueSize 100  // 顺序队列最大元素个数
typedef int DataType;
typedef int ElemType;

#include "SeqQueue.h"
#include "SeqPQueue.h"
#include "LinQuene.h"


void main()
{
	int children = 15;     // 15 人围成一个圈
	int k = 4;               // 每次数到 k 则踢一个人
	int i, x;
	SeqCQueue myQueue;
	QueueInitiate(&myQueue);     // 初始化队列

	// 将n个孩子入队；将队头的孩子出队并从1开始计数，计数小于k的孩子重新入队，
	// 计数为k的孩子退出,然后重新从1计数；直到最后一个小孩。
	for(i = 0; i < children; i++)
		QueueAppend(&myQueue, i + 1);   // 分别赋值1,2,3,,,,,15

	while (QueueNotEmpty(myQueue))      // 直到最后一个队列元素出队，借宿循环
	{
		for (i = 1; i < k; i++)
		{
			QueueDelete(&myQueue, &x);   // 删掉头

			QueueAppend(&myQueue, x);    // 将头重新放到尾
		}

		//  此时i == k ，第 i 个人
		QueueDelete(&myQueue, &x);  // 每次数到 k 则踢一个人
		printf("%4d exit\n", x);
	}

	getchar();
}