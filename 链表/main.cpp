#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

#include "SLinList.h"
#include "DLinList.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void main()
{
	SLNode *head1;
	SLNode *head2;
	int i;
	int x;
	int num;    // ���������

	// ��ʼ��
	SListInitiate(&head1);
	SListInitiate(&head2);

	SListDelete(head1, 0, &x);

	// ��������
	for (i = 0; i <2; i++)
	{
		printf("�����%d������", i+1);
		scanf("%d", &num);
		SListInsert(head1, i, num);
	}

	for (i = 0; i <5; i++)
	{
		printf("�����%d������", i+1);
		scanf("%d", &num);
		SListInsert(head2, i, num);
	}

	// �ж� head1 �Ƿ�Ϊ head2 ���Ӽ�
	x = SSubset(head1, head2);
	printf("\n  %d \n", x);


	// ɾ��2��Ԫ��
	SListDelete(head1, 2, &x);
	printf("  ɾ�� i=2 ��Ԫ�أ�");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListBubbleSort(head1);   // ð������
	// ListSort(head1);       // ����
	printf("             ����");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListDataInsert(head1, 3);  // ���������в���8
	printf("��������8��������");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListDataDelete(head1, 3);  // ɾ������3
	printf("    ɾ��ȫ������3��");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListConverse(head1);     // ��������
	printf("         �������ã�");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	// �ͷ��ڴ�
	SListDestroy(&head1);
	SListDestroy(&head2);

}



