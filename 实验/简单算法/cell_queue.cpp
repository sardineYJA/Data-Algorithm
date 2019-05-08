#include <stdio.h>
#include <malloc.h>
#define MaxQueueSize 100

typedef struct cell{
	char type;        // type of cell. '1' for wall, '0' for road, '*' for path
	int x, y;         // 当前x, y 坐标
	int visited;      // 1 for visited, 0 for not visited
	int preX, preY;   // 当前点的前一点坐标
}Cell;
typedef Cell DataType;

#include "SeqQueue.h"

int main(void){
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
			maze[i][j].preX = 0;
			maze[i][j].preY = 0;
		}


	///////////////////////// 输出迷宫
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

	sx = 1; sy = 2;
	ex = 8; ey = 8;
	printf("Start point:%d,%d\n",sx, sy);
	printf("End point:%d,%d\n",ex, ey);
	Cell current;
	SeqCQueue q;
	int prex = -1, prey = -1;
	QueueInitiate(&q);

	/////////////////////// 队列非递归寻找路径
	QueueAppend(&q, maze[sx][sy]);
	maze[sx][sy].visited = 1;
	maze[sx][sy].preX = -1;
	maze[sx][sy].preY = -1;
	while(QueueNotEmpty(q)){
		QueueDelete(&q, &current);

		//////////////////////////////// 找到路径，输出路径
		if(current.x==ex && current.y==ey){
			printf("Find the path:\n");
			while(current.preX!=-1 && current.preY!=-1){
				maze[current.x][current.y].type = '*';
				printf("(%d,%d)<-",current.x,current.y);
				current = maze[current.preX][current.preY];
			}
			maze[current.x][current.y].type = '*';
			printf("(%d,%d)<-\n",current.x,current.y);
			break;
		} 

		else {
			if(maze[current.x][current.y+1].type=='0' && maze[current.x][current.y+1].visited==0){
				maze[current.x][current.y+1].preX = current.x;
				maze[current.x][current.y+1].preY = current.y;
				QueueAppend(&q, maze[current.x][current.y+1]);
				maze[current.x][current.y+1].visited = 1;
			}
			if(maze[current.x-1][current.y].type=='0' && maze[current.x-1][current.y].visited==0){
				maze[current.x-1][current.y].preX = current.x;
				maze[current.x-1][current.y].preY = current.y;
				QueueAppend(&q, maze[current.x-1][current.y]);
				maze[current.x-1][current.y].visited = 1;
			}
			if(maze[current.x][current.y-1].type=='0' && maze[current.x][current.y-1].visited==0){
				maze[current.x][current.y-1].preX = current.x;
				maze[current.x][current.y-1].preY = current.y;
				QueueAppend(&q, maze[current.x][current.y-1]);
				maze[current.x][current.y-1].visited = 1;
			}
			if(maze[current.x+1][current.y].type=='0' && maze[current.x+1][current.y].visited==0){
				maze[current.x+1][current.y].preX = current.x;
				maze[current.x+1][current.y].preY = current.y;
				QueueAppend(&q, maze[current.x+1][current.y]);
				maze[current.x+1][current.y].visited = 1;
			}

		}
	}

	///////////////////////// 输出迷宫
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
