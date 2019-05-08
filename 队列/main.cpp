#include <stdio.h>
#include <stdlib.h>

#define MaxQueueSize 100  // ˳��������Ԫ�ظ���
typedef int DataType;
typedef int ElemType;

#include "SeqQueue.h"
#include "SeqPQueue.h"
#include "LinQuene.h"


void main()
{
	int children = 15;     // 15 ��Χ��һ��Ȧ
	int k = 4;               // ÿ������ k ����һ����
	int i, x;
	SeqCQueue myQueue;
	QueueInitiate(&myQueue);     // ��ʼ������

	// ��n��������ӣ�����ͷ�ĺ��ӳ��Ӳ���1��ʼ����������С��k�ĺ���������ӣ�
	// ����Ϊk�ĺ����˳�,Ȼ�����´�1������ֱ�����һ��С����
	for(i = 0; i < children; i++)
		QueueAppend(&myQueue, i + 1);   // �ֱ�ֵ1,2,3,,,,,15

	while (QueueNotEmpty(myQueue))      // ֱ�����һ������Ԫ�س��ӣ�����ѭ��
	{
		for (i = 1; i < k; i++)
		{
			QueueDelete(&myQueue, &x);   // ɾ��ͷ

			QueueAppend(&myQueue, x);    // ��ͷ���·ŵ�β
		}

		//  ��ʱi == k ���� i ����
		QueueDelete(&myQueue, &x);  // ÿ������ k ����һ����
		printf("%4d exit\n", x);
	}

	getchar();
}