

//////////////////////////////// ���Ա����ʽ���� //////////////////////////////

/*
ʱ�临�Ӷȣ�
�����ɾ��ƽ��ʱ�临�Ӷ�Ϊ O(n)
��Ԫ�ظ����ͳ�������ʱ�临�Ӷ�Ϊ O(n)
����Ϊ O(1)

�ŵ㣺����ҪԤ��ȷ������Ԫ�ص�������
ȱ�㣺�ڴ�ռ䵥Ԫ����Ч�ʲ��ߣ��㷨�ϸ���
*/

/*
���������޸ĳ�ѭ����������״��
1.�ڳ�ʼ�������У�(*head)->next = NULL; �޸ĳ� (*head)->next = *head;
2.ѭ���ж����� p->next != NULL, p->next->next != NULL; �޸ĳ� 
	p->next != head, p->next->next != head;
*/

typedef struct Node
{
	DataType data;
	struct Node *next;
}SLNode;


// ��ͷ���ĵ����洢�ṹ


// ��ʼ����ͷ
// ΪʲôҪ���� * �����ֻ��һ������ main() ������ ListInitiate��&���Ͳ��ܴ��� head �ĵ�ַ
void SListInitiate( SLNode **head)
{
	*head = (SLNode *)malloc(sizeof(SLNode));
	(*head)->next = NULL;
}


// ��ǰ����Ԫ�ظ���
int SListLength( SLNode *head)
{
	SLNode *p = head;
	int size = 0;       // ����

	while (p->next != NULL)
	{
		p = p->next;
		size++;
	}
	return size;
}


// ��������
// i (0<=i<size)  Ҫ�����λ��
// x Ҫ���������
int SListInsert(SLNode *head, int i, DataType x)
{
	SLNode *p;   // ��ʱ���������
	SLNode *s;   // ���洫�������ݽ��
	int j;

	p = head;
	j = -1;

	while (p->next != NULL && j < i-1)
	{
		p = p->next;
		j++;
	}

	// ������� i �����Ϊ����
	if (j != i-1)
	{
		printf("����Ԫ��λ�ò����д�\n");
		return 0;
	}

	s = (SLNode *)malloc(sizeof(SLNode));
	s->data = x;

	// p �ڵ� i-1 �����
	// ���벽�裬s �嵽 p ��
	s->next = p->next;
	p->next = s;

	return 1;

}



// ɾ�����
// i (0<=i<size-1) Ҫɾ���Ľ��λ��
// *x ����ɾ����������
int SListDelete(SLNode *head, int i, DataType *x)
{
	SLNode *p;   // ��ʱ���������
	SLNode *s;   // ����Ҫɾ���Ľ��
	int j;

	p = head;
	j = -1;


	// ��ͷ����׸��������ݣ�Ҫɾ������ p->next;
	while (p->next != NULL && p->next->next != NULL && j < i-1)
	{
		p = p->next;
		j++;
	}

	// ������� i �����Ϊ����
	if (j != i-1)
	{
		printf("ɾ��Ԫ��λ�ò����д�\n");
		return 0;
	}

	s = p->next;
	*x = s->data;  // ����ɾ��������

	// p �ڵ� i-1 �Ľ��
	p->next = p->next->next;  // ֱ�Ӹ�����һ��ɾ��

	free(s);      // �ͷ��ڴ�ռ�
	return 1;
}


// ȡ������Ԫ��
// i (0<=i<size-1) Ҫ�Ľ��λ��
// *x ������������
int SListGet(SLNode* head, int i, DataType *x)
{
	SLNode *p;
	int j;

	p = head;
	j = -1;

	while (p->next != NULL && j < i)
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



// �ͷ�����
void SListDestroy(SLNode **head)
{
	SLNode *p;  // ��ʱ���������
	SLNode *s;  // �ͷŵĽ��

	p = *head;
	while (p != NULL)
	{
		s = p;
		p = p->next;
		free(s);
	}

	*head = NULL;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// �������е�ȫ��ֵΪ x ɾ��
int SListDataDelete(SLNode *head, DataType x)
{
	SLNode *p;   // ��ʱ���������
	SLNode *s;   // ����Ҫɾ���Ľ��
	int tag = 0; // ����Ƿ���ɾ������

	p = head;

	// ��ͷ����׸��������ݣ�Ҫɾ������ p->next;
	while (p->next != NULL)
	{
		if (p->next->data == x)
		{
			s = p->next;           
			p->next = p->next->next;  // ֱ�Ӹ�����һ��ɾ��
			free(s);                  // �ͷ��ڴ�ռ�
			tag = 1;
		}
		else
		{
			p = p->next;  // ��֤�������ڵ� x ������ȷɾ��
		}
	}

	return tag;
}


// �� x ���뵽����������,��������
void SListDataInsert(SLNode *head, DataType x)
{
	SLNode *curr;
	SLNode *pre;
	SLNode *q;

	curr = head->next;
	pre = head;

	// ��λ����λ�ã��˳�ѭ����pre ָ��ָ��Ҫ�������λ��
	while (curr != NULL && curr->data <= x)
	{
		pre = curr;
		curr = curr->next;
	}

	q  = (SLNode *)malloc(sizeof(SLNode));
	q->data = x;

	// ��ȥ����pre ���ĺ���
	q->next = pre->next;
	pre->next = q;
}


// �����������
void SListSort(SLNode* head)
{
	SLNode *curr;
	SLNode *pre;
	SLNode *p;
	SLNode *q;

	p = head->next;           // Ҫ���ȡ����Ϊ������
	head->next = NULL;        // head ָ���ͷ��㣬��ʼΪ����
	                          // ������������ӣ�ȫ���̲���������
	while (p != NULL)
	{
		curr = head->next;
		pre = head;

		// ��λ��pre ָ��ָ��Ҫ����Ľ��λ��
		while (curr != NULL && curr->data <= p->data)
		{
			pre = curr;
			curr = curr->next;
		}

		q = p;                   // q ָ��Ҫ����Ľ��
		p = p->next;             // q ָ����һ�����

		// �� q ָ����ָ������ pre ָ���
		q->next = pre->next;
		pre->next = q;
	}
}



// ��������
void SListBubbleSort(SLNode *head)
{
	SLNode *p;
	SLNode *q;
	int temp;

	for ( p = head->next; p != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next )
		{
			if (p->data > q->data)
			{
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
		}
	}
}


// ��ͷ����������������
void SListConverse(SLNode *head)
{
	SLNode *p;    // ����
	SLNode *q;    // q һ��Ҫ���ӵ� head ��Ľ��

	p = head->next;
	head->next = NULL;     // �µ��������������������ȥ

	while (p != NULL)
	{
		q = p;
		p = p->next;

		// ÿ�ν� q ���ӵ� head �ĺ��棬�ﵽ���õ�Ч��
		q->next = head->next;
		head->next = q;
	}
}


// ���ͷ���ĵ����� L1 �� L2 �зֱ�������������Ԫ�ؼ��ϣ�
// �жϼ��� L1 �е�����Ԫ���Ƿ��Ǽ��� L2 �е�����Ԫ�أ�
// ��L1 �� L2 ���Ӽ���
// ֱ�Ӵ� L1 �����ݿ�ʼ�� L2 ���� 
int SSubset(SLNode *head1, SLNode *head2)
{
	SLNode *p1;
	SLNode *p2;
	int flag = 0;
	p1 = head1->next;
	
	if (SListLength(head1) > SListLength(head2))
	{
		return flag;   // L1 Ԫ�ظ������� L2 ��
	}

	while (p1 != NULL)
	{
		p2 = head2->next;             // ÿ�� p1 �����ݶ�Ҫ�� p2 �ĵ�һ����ʼ��
		flag = 0;                     // ��һ����������־����Ϊ 0

		while (p2 != NULL)
		{
			if (p1->data == p2->data)
			{
				flag = 1;
				break;        // ������һ��ѭ��
			}

			p2 = p2->next;
		}

		if (flag == 0)
		{
			return flag;          // ��� p1 ��Ԫ���� p2 ���Ҳ���
		}

		p1 = p1->next;
	}

	return flag;
}


// �жϵ������Ƿ��л�
// p ǰ�������ڵ㣬q ǰ��һ���ڵ�
// p ׷�� q������ڻ��� p ��Ϊ null����û�л�
bool isCircle(SLNode * head) 
{
	SLNode *p = head, *q = head;
	do 
	{
		p = p->next->next;
		q = q->next;
	} while (p && p != q);

	if (p && p ==q )
		return true;
	else 
		return false;

}

