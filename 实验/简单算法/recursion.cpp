#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>


////////////////////////////////////////////////////////////////////
// 输出 0或1 排好的数组， length 数组长度 
void printCode(int *a, int length)
{
	int i;
	for (i = 0; i < length; i++)
		printf("%d", a[i]);
	printf("\n");
}


// a[] 数组，n 数组的长度
void code(int *a, int n, int k)
{
    // k 是从 0 开始的
	if (k == n)
	{
		printCode(a, n);
	}
	else
	{
		a[k] = 0;
		code(a, n, k+1);
		a[k] = 1;
		code(a, n, k+1);
	}

	// a[k] 是从 n-1 个开始赋值的
	//if (k == -1)
	//{
	//	printCode(a, n);
	//}
	//else
	//{
	//	a[k] = 0;
	//	code(a, n, k-1);
	//	a[k] = 1;
	//	code(a, n, k-1);
	//}
}
////////////////////////////////////////////////////////////////////////////////////////////


// 从 n 个人中抽出 k （k<=n）个人，共有几种组合
/*
 思路：
 第一部分：第一个人包括在 k 个人中      -->   从 n-1 个人中抽 k-1 个人
 第二部分：第一个人不包括在 k 个人中    -->   从 n-1 个人中抽 k 个人
 */
int comm(int n, int k)
{
	if (n < 1 || k < 0 || k > n)
		return 0;                // 参数出错

	if (k == 0)
		return 1;
	if (n == k)
		return 1;               // 递归出口

	return comm(n-1, k-1) + comm(n-1, k);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

