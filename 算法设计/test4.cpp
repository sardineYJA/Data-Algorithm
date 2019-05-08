
#include <stdio.h>

#define N 8

int a[N][N] = 
{
	{5, 5, 3, 8, 0, 7, 7, 3},
	{6, 2, 4, 8, 9, 4, 0, 2},
	{0, 1, 2, 5, 2, 4, 3, 1},
	{2, 5, 9, 9, 6, 3, 7, 4},
	{0, 8, 6, 0, 7, 7, 6, 1},
	{0, 9, 6, 4, 8, 6, 1, 9},
	{9, 3, 0, 6, 9, 3, 5, 6},
	{9, 5, 9, 9, 0, 9, 6, 9}
};
int num = 0;  // 总路线条数
int max = 0;  // 最多金币数

void getMaxGold(int i, int j, int sum = 0)
{
	sum = sum + a[i][j];

	// 此时已到达终点
	if (i == N-1 && j == N-1)
	{
		//printf("%4d", sum);
		num++;

		// 保存最多金币数量
		if (sum > max)
			max = sum;
	}

	// 没有到达终点则递归向右，向下的路线
	else if (i < N-1 && j < N-1)
	{
		getMaxGold(i+1, j, sum);
		getMaxGold(i, j+1, sum);
	}
	// 不能向下移动，则向右移动
	else if (i == N-1)
	{
		getMaxGold(i, j+1, sum);
	}
	// 不能向右移动，则向下移动
	else if (j == N-1)
	{
		getMaxGold(i+1, j, sum);
	}
}

void main()
{
	getMaxGold(0, 0, 0);
	printf("\n\n总路线条数：%d\n最多金币个数：%d\n\n", num, max);
}
