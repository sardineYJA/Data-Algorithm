#include<stdio.h>
#include<stdlib.h>


//2为围墙，1表示路径，0为空路
int maze[9][9] = {
	{2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,2},
	{2,0,2,2,0,2,2,0,2},
	{2,0,2,0,0,2,0,0,2},
	{2,0,2,0,2,0,2,0,2},
	{2,0,0,0,0,0,2,0,2},
	{2,2,0,2,2,0,2,2,2},
	{2,0,0,0,0,0,0,0,2},
	{2,2,2,2,2,2,2,2,2},
};

int startI = 1, startJ = 1;  //入口数组maze[startI][startJ]
int endI = 7, endJ = 7;      //出口数组maze[endI][endJ]


// 传入二维数组的下标a[i][j]
void visit(int i,int j)
{
	int m, n;
	maze[i][j] = 1; // 全部空路变为◇ 

	// 结束，并且显示路径
	if (i == endI && j == endJ )        // 当满足此两条件，则已经找好出口
	{
		// 接下的只是显示二维数组
		printf("\n显示路径:\n");
		for (m = 0; m < 9; m++)
		{
			for (n = 0; n < 9; n++)
			{
				if (maze[m][n] == 2)
					printf("■");
				else if (maze[m][n] == 1)
					printf("◇");
				else
					printf("  ");
			}
			printf("\n");
		}
	}

	//递归不同方向（逆时针）得出不同路径
	if (maze[i-1][j] == 0)//向上方走
		visit(i-1, j);

	if (maze[i][j+1] == 0)//向左方走
		visit(i, j+1);

	if (maze[i+1][j] == 0)//向下方走
		visit(i+1, j);

	if (maze[i][j-1] == 0)//向右方走
		visit(i, j-1);

	

	maze[i][j] = 0;   // 没有输出路径，则变回空路
	
}


// 随机产生二维数组迷宫



void main()
{
	//开始递归
	visit(startI, startJ); 

}

