

/////////////////////////////////// ���ȼ����� /////////////////////////////////             
// �����Ƕ����ȼ���ߵĿ�ʼ������ж�
// ���жԺ󣬺��������Ԫ�ػ�ǰ��һ��
// ��ֵԽС�����ȼ�Խ��
typedef struct
{
	int priority;     // ���ȼ�
	ElemType data;         // ��������
}PriorityData;

typedef struct
{
	PriorityData queue[MaxQueueSize];  // ��������
	int size;                          // Ԫ�ظ���
}SeqPQueue;


// ��ʼ�� 
void PQueueInitiate(SeqPQueue *Q)
{
	Q->size = 0;    // ��ʼ��Ԫ�ظ���
}

// �ǿ�
int PQueueNotEmpty(SeqPQueue Q)
{
	if (Q.size <= 0)
		return 0;
	else 
		return 1;
}

// ���
int PQueueAppend(SeqPQueue *Q, PriorityData x)
{
	if (Q->size >= MaxQueueSize)
	{
		printf("����������\n");
		return 0;
	}
	else
	{
		Q->queue[Q->size] = x;
		Q->size++;                   // ������ 1 
		return 1;
	}
}


// ɾ�����ȼ���ߵ�Ԫ��
int PQueueDelete(SeqPQueue *Q, PriorityData *d)
{
	PriorityData min;
	int minIndex;           // ���ȼ���ߵ�Ԫ���±�

	if (Q->size <= 0)
	{
		printf("�����ѿգ�\n");
		return 0;
	}
	else
	{
		min = Q->queue[0];           // ��ʼѡ�� queue[0] Ϊ���ȼ���ߵ�Ԫ��
		minIndex = 0;

		for (int i = 1; i < Q->size; i++)
		{
			if (Q->queue[i].priority < min.priority)  // ѭ���ҵ�������ȼ�����
			{
				min = Q->queue[i];
				minIndex = i;
			}
		}

		*d = Q->queue[minIndex];    // ���ȼ���ߵ�Ԫ��

		for (int i = minIndex; i < Q->size; i++)
		{
			Q->queue[i-1] = Q->queue[i];  // Ԫ������ǰ��
		}

		Q->size--;
		return 1;
	}
}


// �������ȼ���ߵ�
int PQueueGet(SeqPQueue *Q, PriorityData *d)
{
	PriorityData min;
	int minIndex;           // ���ȼ���ߵ�Ԫ���±�
	int i;

	if (Q->size <= 0)
	{
		printf("�����ѿգ�\n");
		return 0;
	}
	else
	{
		min = Q->queue[0];           // ��ʼѡ�� queue[0] Ϊ���ȼ���ߵ�Ԫ��
		minIndex = 0;

		for (i = 1; i < Q->size; i++)
		{
			if (Q->queue[i].priority < min.priority)
			{
				min = Q->queue[i];
				minIndex = i;
			}
		}

		*d = Q->queue[minIndex];    // ���ȼ���ߵ�Ԫ��
		return 1;
	}
}

