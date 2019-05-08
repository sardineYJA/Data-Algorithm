
////////////////////////// ��ͷ������ʽ��ջ //////////

/*
ʱ�临�Ӷȣ����� O(1)
*/

typedef struct snode
{
	DataType data;
	struct snode *next;
}LSNode;


// ��ʼ��
void LStackInitiate(LSNode **head)
{
	*head = (LSNode *)malloc(sizeof(LSNode));
	(*head)->next = NULL;
}


// �ǿշ�
int LStackNotEmpty(LSNode *head)
{
	if (head->next == NULL)
		return 0;
	else
		return 1;
}


// ��ջ��������Ԫ�� x ���� head ��ջ����Ϊ�µ�ջ��
void LStackPush(LSNode *head, DataType x)
{
	LSNode *p;
	p = (LSNode *)malloc(sizeof(LSNode));

	p->data = x;

	p->next = head->next;   // �½������ջ��
	head->next = p;         // �½����µ�ջ��
}


// ��ջ
int LStackPop(LSNode *head, DataType *d)
{
	LSNode *p = head->next;
	if (p == NULL)
	{
		printf("��ջ�ѿգ�\n");
		return 0;
	}

	head->next = p->next;      // ɾ����� p
	*d = p->data;

	free(p);
	return 1;
}


// ȡջ��
int LStackTop(LSNode *head, DataType *d)
{
	LSNode *p = head->next;
	if (p == NULL)
	{
		printf("��ջ�ѿգ�\n");
		return 0;
	}

	*d = p->data;
	return 1;
}


// �ͷ��ڴ�
void LStackDestroy(LSNode *head)
{
	LSNode *p;
	LSNode *q;   // Ҫ�ͷŵĽ��

	p = head;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

