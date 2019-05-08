#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DString.h"

/*
 Brute-Force �㷨
�������� S �� start ��ʼ���Ӵ� T���ɹ����� T �� S �е����ַ�λ��

���ƣ��������
ȱ�㣺���������Ӵ������൱����ַ��Ƚ���ͬ������£���һ����ͬ����Ч�ʲ���

��������һ��ƥ�䣬�Ƚϴ���Ϊ�Ӵ��ĳ��� m , ʱ�临�Ӷ� O(m)
������ÿ�αȽ��Ӵ���m-1�Σ����һ���ַ���ͬ���Ƚϴ���m*(n-m+1)��ʱ�临�Ӷ� O(n*m)
*/
int BFIndex(DString S, int start, DString T)
{
	int i = start;
	int j = 0;
	int v;                  // �������ַ���λ��

	while (i < S.length && j < T.length)
	{
		if (S.str[i] == T.str[j])
		{
			i++;
			j++;    // ��ͬ��Ƚ���һ��
		}
		else
		{
			// ��ͬ���ȥԭ���ĵط����ټ� 1����һ���ַ���ʼ�Ƚ�
			i = i - j + 1;
			j = 0;
		}
	}

	// ����ҵ����� j == T.length��������ѭ��������
	if (j == T.length)
		v = i - T.length;
	else
		v = -1;
	return v;
}


/*
KMP�㷨
��Ҫ�ص㣺����Brute-Force�㷨�������Ƚ�λ�����൱����ַ��Ƚ���Ⱥ�
		  ֻҪ��һ���ַ��Ƚϲ���ȱ����ȱ��
�Ƚϴ��� m+n�� ʱ�临�Ӷȣ�O(m+n)
*/

// �������� S �� start ��ʼ���Ӵ� T, �ɹ��򷵻� T �� S �е����ַ��±꣬ʧ���򷵻�-1
// ���� next �д����ģʽ�� T �� next[j] ֵ
int KMPIndex(DString S, int start, DString T, int next[])
{
	int i = start;     // �������±� 
	int j = 0;         // �Ӵ����±�
	int v;             // ����ֵ

	while (i < S.length && j < T.length)
	{
		if (S.str[i] == T.str[j])  // ��ͬ����һ���ַ�
		{
			i++;
			j++;
		}
		else if (j == 0)           // �Ӵ��ĵ�һ�ַ���ͬ����������һ��
			i++;
		else
			j = next[j];
	}
	if (j == T.length)             // ����Ӵ�ȫ��ƥ���꣬�򷵻����������ַ����±�
		v = i - T.length;
	else
		v = -1;

	return v;
}

// ���Ӵ� T �� next[j] ֵ
void GetNext(DString T, int next[])
{
	int j = 1;
	int k = 0;

	next[0] = -1;
	next[1] = 0;

	while (j < T.length -1)
	{
		if (T.str[j] == T.str[k])
		{
			next[j+1] = k + 1;
			j++;
			k++;
		}
		else if (k == 0)
		{
			next[j+1] = 0;
			j++;
		}
		else
			k = next[k];
	}

}



void main()
{

}