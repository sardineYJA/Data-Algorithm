#include <stdio.h>
#include <malloc.h>

// 动态数组

// 二维动态数组
int **Make2DArray(int row, int col)
{
	int **a;
	int i;

	// 动态申请 row 个 int 指针类型的内存空间
	a = (int **)calloc(row, sizeof(int *));

	// 循环 row 次，动态申请 col 个int 类型的内存空间
	for (i = 0; i < row; i++)
	{
		a[i] = (int *)calloc(col, sizeof(int));
	}
	return a;
}

// 释放内存
void Deliver2DArray(int **a, int row)
{
	int i;
	for (i = 0; i < row; i++)
		free(a[i]);       // 首先逐个释放a[i]

	free(a);
}

void main()
{

}




