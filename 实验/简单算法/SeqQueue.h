
//////////////////////// ˳��ѭ���ж� ////////////////////////

/*
ʱ�临�Ӷȣ����� O(1)
*/

typedef struct
{
	DataType queue[MaxQueueSize];   // ��������� 99���ͻ�ص� 0  ���γ�һ��Ȧ
	int rear;            // ��βָ�룬���룬ָ��ĩβ���ݵĺ�һ�����ǿյ�
	int front;           // ��ͷָ�룬ɾ����ָ������׸������ݵ�
	int count;           // ������
}SeqCQueue;


// ��ʼ��
void QueueInitiate(SeqCQueue *Q)
{
	Q->rear = 0;                // �����ʼ��βָ���±�ֵ
	Q->front = 0;               // �����ʼ��ͷָ���±�ֵ
	Q->count = 0;               // �����ʼ������
}


// �ǿշ�
int QueueNotEmpty(SeqCQueue Q)
{
	if (Q.count != 0)
		return 1;
	else 
		return 0;
}


// ���ж�
int QueueAppend(SeqCQueue *Q, DataType x)
{
	if (Q->count > 0 && Q->rear == Q->front)
	{
		printf("�ж�������\n");
		return 0;
	}

	else
	{
		Q->queue[Q->rear] = x;                    // x �����β
		Q->rear = (Q->rear + 1) % MaxQueueSize;   // ��βָʾ���� 1���γɻ�״
		Q->count++;                               // �������� 1
		return 1;
	}
}


// ������
int QueueDelete(SeqCQueue *Q, DataType *d)
{
	if (Q->count == 0)
	{
		printf("�����ѿգ�\n");
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

// ȡ��ͷ����
int QueueGet(SeqCQueue Q, DataType *d)
{
	if (Q.count == 0)
	{
		printf("�����ѿգ�\n");
		return 0;
	}
	else
	{
		*d = Q.queue[Q.front];
		return 1;
	}
}


