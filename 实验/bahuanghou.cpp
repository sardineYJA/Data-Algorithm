
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// a[] 已经决定的皇后位置，n 是第 n 个皇后的位置，a[n]
int Check(int a[],int n)  
{  
	// 与前面 n-1 个皇后位置矛盾，则返回 0 
    for(int i=1;i<n;i++)  
    {  
        if(abs(a[i]-a[n])==abs(i-n) || a[i]==a[n])
            return 0;  
    }  
    return 1;  
}  

int a[20];
int n = 8;  // 8 皇后
int i;
int t = 1;  // 第 t 种解法
  
void EightQueen(int i)     // 从第 i 行开始
{  
    int j;  
    for (j = 1; j <= n; j++)  
    {  
        a[i] = j;  
        if (Check(a, i))// 如果第j列不会与之前的皇后冲突  
        {  
            if (i < n)  // 如果i<n，即还没有找到八个皇后，继续递归  
                EightQueen(i + 1);  
            else        // 如果找到了一组解就输出  
            {  
                printf("第%d种解法：\n", t++);  
				for (i = 1; i <9; i++)
				{
					for (int j = 1; j < 9; j++)
					{
						if (a[i] == j)
							printf("■");
						else
							printf("□");
					}
					printf("\n");
				}
			}  
		} 
	}  
}  

/////////////////////////////////////////////////////////////////////////////////////

/*
设计函数，输出如下
1
2 2
3 3 3
.......
n n n n n ..... n

要求：
1.设计成递归函数
2.设计成循环结构函数
*/

// num 从 1 逐渐递增 到 n
int printN(int num, int n)
{   
	if (n == num-1)
		return  1;   // 递归出口
	else if (n < 0 || num > n )
	{
		return 0;    // 输入的参数有错
	}
	else 
	{
		for (int i = 1; i <= num; i++)
			printf("%d ", num);
		printf("\n");
		printN(num+1, n);     // 递归
	}

}

/*
设 a 是有n 个int 类型数据元素的数组，试试编写求a 中最大值的递归函数。
*/
// a数组有 n 个元素
int MaxArray(int *a, int n) 
{
	int x;
	if (n == 1)
		return a[n-1];
	else
	{
		// 直接递归到数组第一个，return 第一个开始比较
		x = MaxArray(a, n-1);  
		if (x > a[n-1])
			return x;
		else
			return a[n-1];
	}
}

void main()
{
	printN(1,5);
	printf("\n");
	printN(3,9);
}

