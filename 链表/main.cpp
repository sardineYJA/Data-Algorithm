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
	int num;    // 输入的数据

	// 初始化
	SListInitiate(&head1);
	SListInitiate(&head2);

	SListDelete(head1, 0, &x);

	// 连续插入
	for (i = 0; i <2; i++)
	{
		printf("输入第%d个数：", i+1);
		scanf("%d", &num);
		SListInsert(head1, i, num);
	}

	for (i = 0; i <5; i++)
	{
		printf("输入第%d个数：", i+1);
		scanf("%d", &num);
		SListInsert(head2, i, num);
	}

	// 判断 head1 是否为 head2 的子集
	x = SSubset(head1, head2);
	printf("\n  %d \n", x);


	// 删除2号元素
	SListDelete(head1, 2, &x);
	printf("  删除 i=2 号元素：");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListBubbleSort(head1);   // 冒泡排序
	// ListSort(head1);       // 排序
	printf("             排序：");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListDataInsert(head1, 3);  // 有序链表中插入8
	printf("插入数据8保持排序：");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListDataDelete(head1, 3);  // 删除数据3
	printf("    删除全部数据3：");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	SListConverse(head1);     // 数据逆置
	printf("         数据逆置：");
	for(i = 0; i < SListLength(head1); i++)
	{
		SListGet(head1, i, &x);
		printf("%d   ", x);
	}
	printf("\n");


	// 释放内存
	SListDestroy(&head1);
	SListDestroy(&head2);

}



