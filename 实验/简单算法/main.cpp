#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 52       // 扑克牌52张
#define M 8        // 杨辉三角层数

// 扑克牌随机生成
void poker()
{
	int poker[N + 1];
	int i, j, tmp, remain;

	//初始化列阵
	for(i = 0; i <= N; i++)
		poker[i] = i;

	//time(0)是得到当前时,时间值用1970.1.1至今的秒数，初始化随机数种子
	srand((unsigned int)time(0));

	//洗牌
	for (i = 0; i <= N; i++)
	{
		j = rand() % 52 + 1;  // 生成 1-52 的数

		//两个值位置互换
		tmp = poker[i];
		poker[i] = poker[j];
		poker[j] = tmp;
	}

	for (i = 1; i <= N; i++)
	{
		//判断花色
		switch ((poker[i]-1) / 13)
		{
		case 0:
			printf("黑桃");
			break;
		case 1:
			printf("红心");
			break;
		case 2:
			printf("方块");
			break;
		case 3:
			printf("梅花");
			break;
		}

		// 扑克牌数字
		remain = poker[i] % 13;
		switch((remain))
		{
		case 0:
			printf("K ");
			break;
		case 12:
			printf("Q ");
			break;
		case 11:
			printf("J ");
			break;
		default:
			printf("%d ",remain);
			break;
		}
		if(i % 13 == 0)
			printf("\n");
	}
}




// 有一个梵塔，塔内有三个座A、B、C，A座上有诺干个盘子，盘子大小不等，大的在下，小的在上
// 把这些个盘子从A座移到C座，中间可以借用B座但每次只能允许移动一个盘子，并且在移动过程中
// 3个座上的盘子始终保持大盘在下，小盘在上

// n 盘子数
void hanoi(int n, int a = 1, int b = 2, int c = 3)
{
	if ( n == 1 )
		printf("%d->%d ", a, c);   // 将直接从 a 到 c
	else
	{ 
	     hanoi( n-1, a, c, b);    // 将除了最后一个 n 以外的上面的全部当成一个整体
		                          // 通过 c 做跳板，从 a 到 b
		 printf("%d->%d ", a, c);
		 hanoi(n-1, b, a, c);     // 最后一个 a 到 c 后，将上面的那部分移到 c
	}
}



// 杨辉三角
void Triangle()
{
	int i, j, a[M][M];
	for (i = 0; i < M; i++)
	{
	   a[i][0] = 1;             // 每行首个为 1
	   a[i][i] = 1;             // 每行尾巴为 1
    }

	for (i = 2; i < M; i++)         // 第三行开始
		for (j = 1; j < i; j++)     // 每行第二个开始
			a[i][j] = a[i-1][j-1] + a[i-1][j];

	// 输出界面
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M-i-1; j++)     // 每行之前的空格数
			printf("  ");
	    for (j = 0; j <= i; j++)        // 每行的个数 == 所在的行数
			printf("%4d", a[i][j]);
	    printf("\n");
	}
}



// 折半查找
// 在有序数组 a[low]-a[high] 中查找 == x 返回下标 可惜只能找到一个
int BSearch(int a[], int x, int low, int high)
{
	int mid;
	if (low > high )
		return -1;       // 查找不成功
	
	mid = (low + high) / 2;
	if (x == a[mid])
		return mid;      // 查找成功

	else if(x < a[mid])
		BSearch(a, x, low, mid-1);    // 在前半区递归寻找
	else
		BSearch(a, x, mid+1, high);   // 在后半区递归寻找
}



// 递归计算 整数X 的 n 次方
// 思路:
// ①结束 n=0 , x 的 0 次方等于 1
// ②如果 n 为偶数，则 x 的 n 次方 ===== x 的 n/2 次方的平方
// ③如果 n 为奇数，则 x 的 n 次方 ===== x 的 n/2 次方的平方 * x
int power(int x, int n)
{
	int y;          // 计算结果
	if (n == 0)
	{
		y = 1;
	}
	else
	{
		y = power(x, n/2);         // 递归
		if (n%2 == 1)      // 如果 n 为奇数
		{
			y  = y * y * x;
		}
		else               // 如果 n 为偶数
		{
			y = y * y;
		}
	}
	return y;
}



// 累加
int add(int n)
{
	if (n == 1)
		return 1;   // 递归出口
	else 
		return n + add(n-1);
}
// 数组累加
int addArray(int a[], int n)
{
	if (n == 1)
		return a[n-1];
	else
		return a[n-1] + addArray(a, n-1);
}
// 阶乘
int factor(int n)
{
	if (n == 1)
		return 1;
	else
		return n * factor(n-1);
}
// 数组阶乘
int factorialArray(int a[], int n)
{
	if (n == 1)
		return a[n-1];
	else
		return a[n-1] * factorialArray(a, n-1);
}
// 数组中找最大
int maxArray(int a[], int n)
{
	int x;
	if (n == 1)
		return a[n-1];
	else
	{
		x = maxArray(a, n-1);    // 直接递归到数组第一个，return 第一个开始比较
		if (x > a[n-1])
			return x;
		else
			return a[n-1];
	}
}

// 递归求两个最大公约数
int gcd(int a, int b)
{
	int max = a > b ? a : b;
	int min = max == a ? b : a;
	if (min == 0) 
		return max;    // 表示找到了
	else
		return gcd(min, max % min);
}


/********************************************************************
魔幻方阵：
一个 n 阶的幻方由 1, 2, 3,....n^2组成，
方阵的每行上的整数和，每列上的整数和，两条对角线的整数和等于一个整数 s.

         8  1  6  
3 阶 ==  3  5  7
         4  9  2

1）将 1 放在第一行的中间
2）其余的整数沿着当前放置整数的斜向右上方：
		1.如果要放置的数字处于第一行的上面，则将它放置于最低行的对应位置
		2.如果要放置的数字处于最右一列的右侧，则将它放置于最左一列的对应位置
		3.如果要放置的数字的位置已被占用，则放在上一个放置好的数字的正下方

*********************************************************************/





/**************************************************************************
循环移位：
将数组分成为前后两部分，a 和 b ，原数组为 ab ，移位后变成 ba ,
线性代数：（a的逆 · b的逆）的逆 = ba
***************************************************************************/
void reverse(int *a, int start, int end) 
{
	int mid = (end - start) /2;
	int temp;
	for (int i = start, j = end; i < j; i++, j--)
	{
		temp = a[i];    // 对称翻转
		a[i] = a[j];
		a[j] = temp;
	}
}
void shift_reverse(int * a, int len, int num)  // 左移 num 位，相当于右移 len-num 位
{
	reverse(a, 0, num-1);
	reverse(a, num, len-1);
	reverse(a, 0, len-1);
}



void main()
{
	/*
	int a[] = {1,2,3,4};
	int n = factorialArray(a,4);
	int m = maxArray(a, 4);


	printf("%d  ", n);
	printf("%d  ", m);

	printf("%d  ", gcd(7, 55));
	*/

	int arrayInt[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arrayLen = 10;
	int move = 3;

	shift_reverse(arrayInt, arrayLen, move);   // 测试循环移位
	for (int i = 0; i < arrayLen; i++)
		printf("%d  ", arrayInt[i]);

}
