#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int DataType;
typedef struct Node
{
	DataType data;       // ϵ��
	DataType exponent;   // ָ��
	struct Node *next;
}SLNode;

// ��ʼ����ͷ
void SListInitiate( SLNode **head)
{
	*head = (SLNode *)malloc(sizeof(SLNode));
	(*head)->next = NULL;
}


// ��������
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
		printf("����ϵ�������д�\n");
		return 0;
	}
	s = (SLNode *)malloc(sizeof(SLNode));
	s->data = x;
	s->exponent = i;
	s->next = p->next;
	p->next = s;

	return 1;
}

// ȡ������Ԫ��
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
		printf("ϵ�����㲹0��\n");
		*x = 0;
		return 0;
	}

	*x = p->data;
	return 1;
}

// ɾ�����
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
	// ���������ɾ��0�ᱨ��
	if (head->next == NULL && i == 0)
	{
		*x = 0;  
		return 0;
	}
	// ������� i �����Ϊ����
	if (j != i-1 )
	{
		*x = 0;
		return 0;
	}
	s = p->next;
	*x = s->data;             // ����ɾ��������
	                          // p �ڵ� i-1 �Ľ��
	p->next = p->next->next;  // ֱ�Ӹ�����һ��ɾ��
	free(s);                  // �ͷ��ڴ�ռ�
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


// �������ʽ���
void print(SLNode *result)
{
	SLNode *p;
	p = result->next;
	printf("����ʽR(X) = ");
	while (p != NULL)
	{
		if (p->data != 0)
		{
			printf("%dX^%d ", p->data, p->exponent);
			if (p->next != NULL && p->next->data >= 0)
				printf("+");
		}
			
		p = p->next;
		
	}
	printf("\n\n");
}

// ָ������ʽ�� X ��������
DataType calculateResult(SLNode *result, DataType x)
{
	SLNode *p;
	p = result->next;
	DataType sum = 0;
	while (p != NULL)
	{
		sum = sum + p->data * (DataType)pow((double)x, p->exponent);
		p = p->next;
	}
	return sum;
}

// �Զ���ʽ head1 �� head2 ���мӷ����㣬������浽 result
// flag = 1  ���мӷ�
// flag = -1 ���м���
void add(SLNode *head1, SLNode *head2, SLNode *result, int flag)
{
	SLNode *p1 = head1->next;
	SLNode *p2 = head2->next;
	DataType exponent = 0;    // ��ʼ��ָ��0

	// ����������ʽ����Ϊ�գ�ָ����ͬ���������
	while (p1 != NULL && p2 != NULL)
	{
		SListInsert(result, exponent, p1->data + flag*p2->data);
		exponent++;
		p1 = p1->next;
		p2 = p2->next;
	}
	// ��� p2 ��Ϊ�գ��� p1 �Ķ���ʽֱ�Ӵ洢��ָ��λ��
	while (p1 != NULL)
	{
		SListInsert(result, exponent, p1->data);
		exponent++;
		p1 = p1->next;
	}
	// ��� p1 ��Ϊ�գ��� p2 �Ķ���ʽֱ�Ӵ洢��ָ��λ��
	while (p2 != NULL)
	{
		SListInsert(result, exponent, flag*p2->data);
		exponent++;
		p2 = p2->next;
	}
}

// �Զ���ʽ head1 �� head2 ���г˷����㣬������浽 result
void multiply(SLNode *head1, SLNode *head2, SLNode *result)
{
	// �˷�
	SLNode *p1;
	SLNode *p2;

	p1 = head1->next;
	p2 = head2->next;

	DataType data;           // Ҫ�����ϵ��
	DataType exponent = 0;   // Ҫ�����ָ��
	DataType pre_data = 0;   // ԭ������ϵ��

	while (p2 != NULL)
	{
		p1 = head1->next;
		while (p1 != NULL)
		{
			data = p1->data * p2->data;              // Ҫ�����ϵ��
			exponent = p1->exponent + p2->exponent;  // Ҫ�����ָ��
			
			// ��ʱӦ��ɾ����ָ���Ľ�㣬�����²����ָ���Ľ��
			// ��ȡ��ԭ����ϵ����û����ȡ�� 0
			SListDelete(result, exponent,  &pre_data);
			data = data + pre_data;
			SListInsert(result, exponent, data);
			p1 = p1->next;  //  p1 ��һ��� p1 ��������� p2 �ĵ�һ��
			
		}
		p2 = p2->next;
	}
}


// �������ʽ
void input(SLNode * head)
{
	DataType num;
	int n;
	printf("�����������������ָ�� n ��");
	scanf("%d", &n);
	printf ("����ʽP(x) = ������ÿ��ϵ�� a0, a1, a2, ..... an��\n");
	for (int i = 0; i < n+1; i++)
	{
		scanf("%d", &num);
		SListInsert(head, i, num);
	}
}

void main()
{
	SLNode *head1;
	SLNode *head2;
	SLNode *result;

	// ��ʼ��
	SListInitiate(&head1);
	SListInitiate(&head2);
	SListInitiate(&result);

	printf("*--------------------------------\n");
	printf("*       1.ָ�� X �Զ���ʽ��ֵ   *\n");
	printf("*       2.��������ʽ���        *\n");
	printf("*       3.��������ʽ���        *\n");
	printf("*       4.��������ʽ���        *\n");
	printf("*--------------------------------\n");
	
	int choose = 0;
	int x;
	int sum;
	printf("��������Ҫ�Ĺ��ܣ�");
	scanf("%d", &choose);
	switch(choose)
	{
		// ָ�� X �Զ���ʽ��ֵ
	case 1:
		printf("������ x :");
		scanf("%d", &x);
		input(head1);
		sum = calculateResult(head1, x);
		print(head1);
		printf("�����%d \n\n", sum);
		break;

		// ��������ʽ���
	case 2:
		input(head1);
		input(head2);
		add(head1, head2, result, 1);
		print(result);
		break;

		// ��������ʽ���
	case 3:
		input(head1);
		input(head2);
		add(head1, head2, result, -1);
		print(result);
		break;

		// ��������ʽ��� 
	case 4:
		input(head1);
		input(head2);
		multiply(head1, head2, result);
		print(result);
		break;

	default :
		printf("ѡ�����\n");
		break;
	}
}