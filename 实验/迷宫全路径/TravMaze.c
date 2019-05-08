#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
迷宫图
                    终点
 ___       ___       
| 4 |     | 5 |    | 7 |
|   |     |   |    |   |
|   -------   ------   |
|_3_______ 2   ______6_|   
         |    |
		 | 1  |
		 起点


6                    // 路口个数
0 2 0                // 每一行表示每个路口的情况，如：只能中路去 2
3 5 6                // 左去 3 ， 右去 6 ， 中去 5 
0 0 4
0 0 0
0 0 0
7 0 0
7                    // 出口为路口7
*/

// 路口的结构体定义
typedef struct
{
	int left;      // 向左方向
	int forward;   // 向前方向
	int rigth;     // 向右方向
} InterSection;

// 迷宫的结构体定义
typedef struct
{
	int mazeSize;           // 路口个数
	InterSection *intSec;   // 路口集合
	int Exit;               // 出口
} Maze;


// 用回溯算法搜素迷宫 m 的所有分支，输入 currSetValue 为当前所处的路口
// intSec[currSetValue] 记载了第 currSetValue 行的左右中路情况
int TravMaze(Maze *m, int currSetValue)
{
	// currSetValue > 0 表示路径存在，可以继续搜索发现一条路径
	if (currSetValue > 0)
	{
		if (currSetValue == m->Exit)           // 递归出口
		{
			printf("%d <== ", currSetValue);   // 输出路口号 
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].left) == 1)      // 向左
		{
			// 只有探索成功，即返回值为 1 ，才执行以下语句
			printf("%d <== ", currSetValue);                          // 输出路口号
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].forward) == 1)   // 向前
		{
			// 只有探索成功，即返回值为 1 ，才执行以下语句
			printf("%d <== ", currSetValue);                          // 输出路口号
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].rigth) == 1)     // 向右
		{
			// 只有探索成功，即返回值为 1 ，才执行以下语句
			printf("%d <== ", currSetValue);                          // 输出路口号
			return 1;
		}
	}

	return 0;       // currSetValue = 0 表示无路径存在，返回0
}


// 按文件 Filename 中存放的数据创建迷宫 m
void CreateMaze(char *fileName, Maze *m)
{
	FILE *fp;
	int i;

	fp = fopen(fileName, "r");     // 只读方式打开文件
	if (!fp)
	{
		printf("数据文件无法打开！");
		return;
	}

	fscanf(fp, "%d", &m->mazeSize);    // 读入路口个数

	// 建立 mazeSize + 1 个元素的数组        为毛要加 1 ？？？？？？？？？
	m->intSec = (InterSection *)malloc(sizeof(InterSection) * (m->mazeSize+1));

	for (i = 1; i <= m->mazeSize; i++)
	{
		// 读入全部路口的结构体数值
		fscanf(fp, "%d%d%d", &m->intSec[i].left, &m->intSec[i].forward, &m->intSec[i].rigth);
	}

	fscanf(fp, "%d%d%d", &m->Exit);    // 读入出口数值

	fclose(fp); 
}


void maind()
{
	Maze m;
	int start = 1;
	CreateMaze("Maze.txt", &m);
	if (TravMaze(&m, start))
		printf("\n迷宫的一条路：");
	else
		printf("\n无路");
}

