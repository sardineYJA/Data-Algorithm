#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DString.h"

/*
 Brute-Force 算法
查找主串 S 从 start 开始的子串 T，成功返回 T 在 S 中的首字符位置

优势：易于理解
缺点：在主串和子串已有相当多个字符比较相同的情况下，有一个不同，则效率不高

最好情况：一次匹配，比较次数为子串的长度 m , 时间复杂度 O(m)
最坏情况：每次比较子串的m-1次，最后一个字符不同，比较次数m*(n-m+1)，时间复杂度 O(n*m)
*/
int BFIndex(DString S, int start, DString T)
{
	int i = start;
	int j = 0;
	int v;                  // 返回首字符的位置

	while (i < S.length && j < T.length)
	{
		if (S.str[i] == T.str[j])
		{
			i++;
			j++;    // 相同则比较下一个
		}
		else
		{
			// 不同则回去原来的地方，再加 1，下一个字符开始比较
			i = i - j + 1;
			j = 0;
		}
	}

	// 如果找到，则 j == T.length，不满足循环则跳出
	if (j == T.length)
		v = i - T.length;
	else
		v = -1;
	return v;
}


/*
KMP算法
主要特点：消除Brute-Force算法的主串比较位置在相当多个字符比较相等后
		  只要有一个字符比较不相等便回退缺点
比较次数 m+n， 时间复杂度：O(m+n)
*/

// 查找主串 S 从 start 开始的子串 T, 成功则返回 T 在 S 中的首字符下标，失败则返回-1
// 数组 next 中存放有模式串 T 的 next[j] 值
int KMPIndex(DString S, int start, DString T, int next[])
{
	int i = start;     // 主串的下标 
	int j = 0;         // 子串的下标
	int v;             // 返回值

	while (i < S.length && j < T.length)
	{
		if (S.str[i] == T.str[j])  // 相同则下一个字符
		{
			i++;
			j++;
		}
		else if (j == 0)           // 子串的第一字符不同，则主串下一个
			i++;
		else
			j = next[j];
	}
	if (j == T.length)             // 如果子串全部匹配完，则返回在主串首字符的下标
		v = i - T.length;
	else
		v = -1;

	return v;
}

// 求子串 T 的 next[j] 值
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