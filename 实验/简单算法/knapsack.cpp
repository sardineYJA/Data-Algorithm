#include <iostream>
using namespace std;

// 背包问题  
// s 背包所承受重量，w[] 是 n 个物品的质量数组
// s 减去其中一个背包质量，直到等于 0
/*
 递归思路：每个背包分两个支路
 第一部分：第 n 个物品包括在中      -->   s 减去第 n 个背包的质量，剩下 n-1 个
 第二部分：第 n 个物品不包括在中    -->   n 减去 1 ， s 不变
 */
void knapsack(int s, int w[], int n, int *solution)
{
	if (s == 0)       // 递归出口
	{
		for (int i = 0; i < 7; i++)
			if (solution[i] == 1)
				printf("%d ", w[i]);
		printf("\n");
	}
	else if (s > 0 && n >= 1)   // 还有剩余物件数，则递归
	{
		solution[n-1] = 1;
		knapsack(s-w[n-1], w, n-1, solution);    // 第 n 个物品放进背包

		                                         // ???? 两个位置不能换，否则是错误的
		solution[n-1] = 0;
		knapsack(s, w, n-1, solution);           // 第 n 个物品不放进背包
	}
}





/// w 每个物品的质量， n 物品个数， t 背包容量， solution 怎么放， k 目前遍历的次数
void subset(int* w, int n, int t, int* solution, int k) 
{
	if ( k == n)
	{                
		int sum = 0;
		for (int i = 0; i < k; i++)
			sum += solution[i] * w[i];

		// 输出的结果
		if ( sum == t ){
			for (int i = 0; i < k; i++)
				if (solution[i] == 1)
					printf("%d ", w[i]);
			printf("\n");
		}
	}

	else 
	{
		solution[k] = 1;
		subset(w, n, t, solution, k + 1);

		solution[k] = 0;
		subset(w, n, t, solution, k + 1);
	}
}


/**********************************************
动态规划求出满足最大载重量的最大价值

n：物品个数
m：背包载重量
w：重量数组
v：价值数组
c：是否被选中数组

返回值：最大价值

背包装入的量从 0 开始逐渐加 1 增大，（即 j++ ）

***********************************************/
int getMaxValue(int n, int m, int *w, int *v, int *c) 
{
	int row = n+1;
	int col = m+1;

	// value[i][j] 表示前 i 个物品能装入载重量为 j 的背包中的物品的最大价值
	int **value = (int **)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		value[i] = (int *)malloc(sizeof(int) * col);

	// 初始化第0行，第0列
	for (int j = 0; j < col; j++)
		value[0][j] = 0;
	for (int i = 0; i < row; i++)
		value[i][0] = 0;

	// 计算
	/*
	下面计算有点乱
	v, w, c, 数组是从0 开始的，所以要减1

	*/
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++) 
		{
			// w[i] > j，第 i 个物品不装入背包
			value[i][j] = value[i-1][j];        // 首先每个容量的价值都先等于前一个容量的价值

			// w[i] <= j，且第 i 个物品装入背包后价值 > value[i-1][j]，则记录当前最大价值
			int temp = value[i-1][j-w[i-1]] + v[i-1];
			if (w[i-1] <= j && temp > value[i][j])
				value[i][j] = temp;
		}
	}

	// 逆推求装入的物品
	int j = m;
	for (int i = row-1; i > 0; i--)
	{
		if (value[i][j] > value[i-1][j])
		{
			c[i-1] = 1;
			j = j - w[i-1];
		}
	}

	// 最大价值
	int nMaxValue = value[row-1][col-1];

	// 释放内存
	for (int i = 0; i < row; i++)
		free(value[i]);
	free(value);

	return nMaxValue;
}


///////////////////////////////////////////////////////////////////////////////////////////


void maindfg()
{
	/*
	int allWeight = 10;
	int weight[] = {1,2,3,4,5,6,7};
	int n = 7;
	int solution[] = {0, 0, 0, 0, 0, 0, 0};
	knapsack(allWeight, weight, n, solution);
	printf("\n");
	subset(weight, n, allWeight, solution, 0);
	*/


	int n = 5;             // 物品个数
	int m = 10;            // 背包最大载重量
	int w[] = {2, 3, 4, 5, 6};     // 每个物品的重量
	int v[] = {4, 15, 7, 8, 9};   // 每个物品的价值
	int c[] = {0, 0, 0, 0, 0};     // 是否被选中

	int maxValue = getMaxValue(n, m, w, v, c);
	for (int i = 0; i < n; i++)
		printf("%d  ", c[i]);

	printf("%d   \n", maxValue);

}