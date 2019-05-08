
//////////////////////////// ˫���ͷ������� /////////////////////

// ����Ƶ�����ҵ�ǰ���ĺ�̽���ǰ�����

typedef struct DNode
{
	DataType data;
	struct DNode *next;           
	struct DNode *prior;
}DLNode;



// ��ͷ����˫������

// ��ʼ��
void DListInitiate(DLNode **head)
{
	*head = (DLNode *)malloc(sizeof(DLNode));
	(*head)->prior = *head;          // ����ǰ��ָ��ѭ������
	(*head)->next = *head;           // ���ɺ��ָ��ѭ������
}


// ��Ԫ�ظ���
int DListLength(DLNode *head)
{
	DLNode *p = head;
	int size = 0;
	 
	while (p->next != head)
	{
		p = p->next;
		size++;
	}

	return size;
}



// ��ȡ�������
int DListGet(DLNode* head, int i, DataType *x)
{
	DLNode *p;
	int j;

	p = head;
	j = -1;

	while (p->next != head && j < i)
	{
		p = p->next;
		j++;
	}

	if ( j != i)
	{
		printf("ȡ��Ԫ��λ�ò����д�\n");
		return 0;
	}

	*x = p->data;
	return 1;
}


// ����Ԫ��
int DListInsert(DLNode *head, int i, DataType x)
{
	DLNode *p;
	DLNode *s;
	int j;

	p = head->next;
	j = 0;

	while (p != head && j < i)
	{
		p = p->next;
		j++;
	}

	if (j != i)
	{
		printf("����Ԫ��λ�ò����д�\n");
		return 0;
	}

	s = (DLNode *)malloc(sizeof(DLNode));
	s->data = x;

	// p �ڵ� i �����
	s->prior = p->prior;   // ǰһ���Ĺ�ϵ
	p->prior->next = s;

	s->next = p;           // ��һ���Ĺ�ϵ
	p->prior = s;

	return 1;
}


// ɾ�����
int DListDelete(DLNode *head, int i, DataType *x)
{
	DLNode *p;
	int j;

	p = head->next;
	j = 0;

	while (p->next != head && j < i)
	{
		p = p->next;
		j++;
	}

	if (j != i)
	{
		printf("ɾ��Ԫ��λ�ò����д�\n");
		return 0;
	}

	*x = p->data;

	// p �ڵ� i �����
	p->prior->next = p->next;        // ǰһ���Ĺ�ϵ
	p->next->prior = p->prior;       // ��һ���Ĺ�ϵ

	free(p);
	return 1;
}




// �ͷ��ڴ�
void DListDestroy(DLNode **head)
{
	DLNode *p;
	DLNode *s;
	int i;
	int n;

	n = DListLength(*head);  // ������
	p = *head;

	for (i = 0; i <= n; i++)
	{
		s = p;
		p = p->next;
		free(s);
	}

	*head = NULL;
}


