
#include <stdio.h>
#include <malloc.h>
#define MaxStackSize 100

typedef struct cell{
	char type;       // type of cell. '1' for wall, '0' for road, '*' for path
	int x, y;        // 当前x, y 坐标
	int visited;     // 1 for visited, 0 for not visited
	int preX, preY;  // 没用到
}Cell;
typedef Cell DataType;


#include "SeqStack.h"

void mainqw(void){
	char m[10][10] = {{'1','1','1','1','1','1','1','1','1','1'},
			      	  {'1','0','0','1','1','1','0','0','1','1'},
					  {'1','0','0','1','1','0','0','1','0','1'},
					  {'1','0','0','0','0','0','0','1','0','1'},
					  {'1','0','0','0','0','1','1','0','0','1'},
					  {'1','0','0','1','1','1','0','0','0','1'},
					  {'1','0','0','0','0','1','0','1','0','1'},
					  {'1','0','1','1','0','0','0','1','0','1'},
					  {'1','1','0','0','0','0','1','0','0','1'},
					  {'1','1','1','1','1','1','1','1','1','1'}};
	int sx,sy,ex,ey;
	Cell maze[10][10];
	int i,j,row=10,col=10;
	for(i=0; i<row; i++)
		for(j=0; j<col; j++){
			maze[i][j].type = m[i][j];
			maze[i][j].visited = 0;
			maze[i][j].x = i;
			maze[i][j].y = j;
		}

	/////////////////////////// 输出迷宫
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){

			if (maze[i][j].type == '1')
				printf("■");
			if (maze[i][j].type == '0')
				printf("□");
			if (maze[i][j].type == '*')
				printf("√");

		}
		printf("\n");
	}

	////////////////////////
	sx = 8; sy = 8;       // 起点
	ex = 1; ey = 2;       // 终点
	printf("Start point:%d,%d\n",sx, sy);
	printf("End point:%d,%d\n",ex, ey);
	Cell top;
	SeqStack s;
	StackInitiate(&s);

	StackPush(&s, maze[sx][sy]);
	maze[sx][sy].visited = 1;

	////////////////////// 非递归形式寻找路径
	while(StackNotEmpty(s)) {
		StackTop(s, &top);  // 每次先取栈顶元素出来

		////////////////////////////////// 找到路径
		if(top.x==ex && top.y==ey){
			printf("Find the path:\n");

			//////////////// 将路径输出
			while(StackNotEmpty(s))
			{
				StackPop(&s, &top);
				maze[top.x][top.y].type = '*';
				printf("(%d,%d)<-",top.x,top.y);
			}
			printf("\n");
		} 
		
		else 
		{
			// 向四个方向寻找
			if(maze[top.x][top.y+1].type=='0' && maze[top.x][top.y+1].visited==0){
				StackPush(&s, maze[top.x][top.y+1]);
				maze[top.x][top.y+1].visited = 1;
			} 
			else if(maze[top.x-1][top.y].type=='0' && maze[top.x-1][top.y].visited==0){
				StackPush(&s, maze[top.x-1][top.y]);
				maze[top.x-1][top.y].visited = 1;
			} 
			else if(maze[top.x][top.y-1].type=='0' && maze[top.x][top.y-1].visited==0){
				StackPush(&s, maze[top.x][top.y-1]);
				maze[top.x][top.y-1].visited = 1;
			} 
			else if(maze[top.x+1][top.y].type=='0' && maze[top.x+1][top.y].visited==0){
				StackPush(&s, maze[top.x+1][top.y]);
				maze[top.x+1][top.y].visited = 1;
			}
			else{
				StackPop(&s, &top);   // 没有路径则返回上一点
			}
		}
	}

	/////////////////////////// 输出迷宫
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (maze[i][j].type == '1')
				printf("■");
			if (maze[i][j].type == '0')
				printf("□");
			if (maze[i][j].type == '*')
				printf("√");
		}
		printf("\n");
	}


}
