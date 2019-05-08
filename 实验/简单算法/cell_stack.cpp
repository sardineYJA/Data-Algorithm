
#include <stdio.h>
#include <malloc.h>
#define MaxStackSize 100

typedef struct cell{
	char type;       // type of cell. '1' for wall, '0' for road, '*' for path
	int x, y;        // ��ǰx, y ����
	int visited;     // 1 for visited, 0 for not visited
	int preX, preY;  // û�õ�
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

	/////////////////////////// ����Թ�
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){

			if (maze[i][j].type == '1')
				printf("��");
			if (maze[i][j].type == '0')
				printf("��");
			if (maze[i][j].type == '*')
				printf("��");

		}
		printf("\n");
	}

	////////////////////////
	sx = 8; sy = 8;       // ���
	ex = 1; ey = 2;       // �յ�
	printf("Start point:%d,%d\n",sx, sy);
	printf("End point:%d,%d\n",ex, ey);
	Cell top;
	SeqStack s;
	StackInitiate(&s);

	StackPush(&s, maze[sx][sy]);
	maze[sx][sy].visited = 1;

	////////////////////// �ǵݹ���ʽѰ��·��
	while(StackNotEmpty(s)) {
		StackTop(s, &top);  // ÿ����ȡջ��Ԫ�س���

		////////////////////////////////// �ҵ�·��
		if(top.x==ex && top.y==ey){
			printf("Find the path:\n");

			//////////////// ��·�����
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
			// ���ĸ�����Ѱ��
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
				StackPop(&s, &top);   // û��·���򷵻���һ��
			}
		}
	}

	/////////////////////////// ����Թ�
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (maze[i][j].type == '1')
				printf("��");
			if (maze[i][j].type == '0')
				printf("��");
			if (maze[i][j].type == '*')
				printf("��");
		}
		printf("\n");
	}


}
