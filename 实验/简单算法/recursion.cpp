#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>


////////////////////////////////////////////////////////////////////
// ��� 0��1 �źõ����飬 length ���鳤�� 
void printCode(int *a, int length)
{
	int i;
	for (i = 0; i < length; i++)
		printf("%d", a[i]);
	printf("\n");
}


// a[] ���飬n ����ĳ���
void code(int *a, int n, int k)
{
    // k �Ǵ� 0 ��ʼ��
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

	// a[k] �Ǵ� n-1 ����ʼ��ֵ��
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


// �� n �����г�� k ��k<=n�����ˣ����м������
/*
 ˼·��
 ��һ���֣���һ���˰����� k ������      -->   �� n-1 �����г� k-1 ����
 �ڶ����֣���һ���˲������� k ������    -->   �� n-1 �����г� k ����
 */
int comm(int n, int k)
{
	if (n < 1 || k < 0 || k > n)
		return 0;                // ��������

	if (k == 0)
		return 1;
	if (n == k)
		return 1;               // �ݹ����

	return comm(n-1, k-1) + comm(n-1, k);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

