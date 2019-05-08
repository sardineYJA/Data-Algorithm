

//////////////////////////////////// ����ͷ��������� /////////////////////          
// �������ƣ��ɿ�����ͷָ����βָ��������Ҷ�����ָ�������ݵ��׸�����β����㣬����һ��Ȧ

/*
ʱ�临�Ӷȣ������������� O(n)������ O(1)
*/

typedef struct qnode
{
	DataType data;
	struct qnode *next;

}LQNode;

typedef struct
{
	LQNode *front;   // ��ͷָ�룬ɾ��
	LQNode *rear;    // ��βָ�룬����
}LQueue;


// û��ͷ��������
// ��ʼ��
void LQueueInitiate(LQueue *Q)
{
	Q->front = NULL;               // ��Ԫ��ʱ������ָ�붼ָ�������ݵĽ�㣬���ǿյĽ��
	Q->rear = NULL;
}


// �ǿշ�
int LQueueNotEmpty(LQueue Q)
{
	if (Q.front == NULL)
		return 0;
	else
		return 1;
}


// �����
void LQueueAppend(LQueue *Q, DataType x)
{
	LQNode *p;
	p = (LQNode *)malloc(sizeof(LQNode));
	p->data = x;
	p->next = NULL;

	if (Q->rear != NULL)
	{
		Q->rear->next = p;  // ����ԭ���ǿ�ʱ��β���½��
	}

	Q->rear = p;            // �޸Ķ�βָ�룬��β���Ƶ� p

	if (Q->front == NULL)
	{
		Q->front = p;       // ����ԭ��Ϊ��ʱ�޸Ķ�ͷָ��
	}
}


// ���ж�
int LQueueDelete(LQueue *Q, DataType *d)
{
	LQNode *p;
	if (Q->front == NULL)
	{
		printf("����Ϊ�գ�\n");
		return 0;
	}
	else
	{
		*d = Q->front->data;
		p = Q->front;
		Q->front = Q->front->next;    // ���������ֱ�Ӹ���

		if (Q->front == NULL)
			Q->rear = NULL;          // ɾ������Ѹ���㣬Ҫ��βָ��Ϊ��

		free(p);
		return 1;
	}
}


// ȡ����ͷ����
int LQueueGet(LQueue Q, DataType *d)
{
	if (Q.front == NULL)
	{
		printf("�����ѿգ�\n");
		return 0;
	}
	else
	{
		*d = Q.front->data;
		return 1;
	}
}


// �ͷ��ڴ� 
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

