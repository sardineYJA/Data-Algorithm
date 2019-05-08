#include<stdio.h>
#include<stdlib.h>
#define MaxStackSize 100

typedef struct
{
	int stack[MaxStackSize];
	int top;
}SeqStack;




////////////////////////    堆栈   //////////////////////////////
// 初始化
void StackInitiate(SeqStack *S)
{
	S->top = 0;
}


// 非空否
int StackNotEmpty(SeqStack S)
{
	if (S.top <= 0)
		return 0;
	else
		return 1;
}


// 入栈
int StackPush(SeqStack *S, int x)
{
	if (S->top >= MaxStackSize)
	{
		printf("堆栈已满，无法插入！\n");
		return 0;
	}
	else
	{
		S->stack[S->top] = x;
		S->top++;
		return 1;
	}
}


// 出栈
int StackPop(SeqStack *S, int *d)
{
	if (S->top <= 0)
	{
		printf("堆栈已空，无法出栈！\n");
		return 0;
	}
	else
	{
		S->top--;
		*d = S->stack[S->top];
		return 1;
	}
}


// 取栈顶元素，但栈顶不变
int StackTop(SeqStack S, int *d)
{
	if (S.top <= 0)
	{
		printf("堆栈已空！\n");
		return 0;
	}
	else
	{
		*d = S.stack[S.top - 1];
		return 1;
	}
}
/////////////////////////////////////////////////////////////////

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
void visit(int i,int j, SeqStack S)
{
	int m, n;
	maze[i][j] = 1; // 全部空路变为◇ 

	// 二维坐标入栈
	StackPush(&S, j);
	StackPush(&S, i);

	// 结束，并且显示路径
	if (i == endI && j == endJ )        // 当满足此两条件，则已经找好出口
	{
		// 接下的只是显示二维数组
		printf("\n显示路径:\n");

		///////////////////////////// 将栈里的坐标显示出来
		int flag = 1;
		while (StackNotEmpty(S))  
		{
			StackPop(&S, &n);
			if (flag%2 == 1)
			{
				printf("第%2d个坐标：（%d, ", flag/2+1, n);
			}
			else 
			{
				printf("%d）\n", n);
			}
			flag++;
		}
		printf("\n");
		/////////////////////////////////////////////////
		/////////////////// 已方块图片的形式显示出来/////
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

	//递归不同方向得出不同路径
	if (maze[i][j+1] == 0)//向左方走
		visit(i, j+1, S);

	if (maze[i+1][j] == 0)//向下方走
		visit(i+1, j, S);

	if (maze[i][j-1] == 0)//向右方走
		visit(i, j-1, S);

	if (maze[i-1][j] == 0)//向上方走
		visit(i-1, j, S);

	maze[i][j] = 0;   // 没有输出路径，则变回空路
}


// 随机产生二维数组迷宫




void mainww()
{
	SeqStack S;
	StackInitiate(&S);

	//开始递归
	visit(startI, startJ, S);

}


