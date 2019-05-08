#include<stdio.h>
#include<stdlib.h>
#define MaxStackSize 100

typedef struct
{
	int stack[MaxStackSize];
	int top;
}SeqStack;




////////////////////////    ��ջ   //////////////////////////////
// ��ʼ��
void StackInitiate(SeqStack *S)
{
	S->top = 0;
}


// �ǿշ�
int StackNotEmpty(SeqStack S)
{
	if (S.top <= 0)
		return 0;
	else
		return 1;
}


// ��ջ
int StackPush(SeqStack *S, int x)
{
	if (S->top >= MaxStackSize)
	{
		printf("��ջ�������޷����룡\n");
		return 0;
	}
	else
	{
		S->stack[S->top] = x;
		S->top++;
		return 1;
	}
}


// ��ջ
int StackPop(SeqStack *S, int *d)
{
	if (S->top <= 0)
	{
		printf("��ջ�ѿգ��޷���ջ��\n");
		return 0;
	}
	else
	{
		S->top--;
		*d = S->stack[S->top];
		return 1;
	}
}


// ȡջ��Ԫ�أ���ջ������
int StackTop(SeqStack S, int *d)
{
	if (S.top <= 0)
	{
		printf("��ջ�ѿգ�\n");
		return 0;
	}
	else
	{
		*d = S.stack[S.top - 1];
		return 1;
	}
}
/////////////////////////////////////////////////////////////////

//2ΪΧǽ��1��ʾ·����0Ϊ��·
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

int startI = 1, startJ = 1;  //�������maze[startI][startJ]
int endI = 7, endJ = 7;      //��������maze[endI][endJ]


// �����ά������±�a[i][j]
void visit(int i,int j, SeqStack S)
{
	int m, n;
	maze[i][j] = 1; // ȫ����·��Ϊ�� 

	// ��ά������ջ
	StackPush(&S, j);
	StackPush(&S, i);

	// ������������ʾ·��
	if (i == endI && j == endJ )        // ������������������Ѿ��Һó���
	{
		// ���µ�ֻ����ʾ��ά����
		printf("\n��ʾ·��:\n");

		///////////////////////////// ��ջ���������ʾ����
		int flag = 1;
		while (StackNotEmpty(S))  
		{
			StackPop(&S, &n);
			if (flag%2 == 1)
			{
				printf("��%2d�����꣺��%d, ", flag/2+1, n);
			}
			else 
			{
				printf("%d��\n", n);
			}
			flag++;
		}
		printf("\n");
		/////////////////////////////////////////////////
		/////////////////// �ѷ���ͼƬ����ʽ��ʾ����/////
		for (m = 0; m < 9; m++)
		{
			for (n = 0; n < 9; n++)
			{
				if (maze[m][n] == 2)
					printf("��");
				else if (maze[m][n] == 1)
					printf("��");
				else
					printf("  ");
			}
			printf("\n");
		}
	}

	//�ݹ鲻ͬ����ó���ͬ·��
	if (maze[i][j+1] == 0)//������
		visit(i, j+1, S);

	if (maze[i+1][j] == 0)//���·���
		visit(i+1, j, S);

	if (maze[i][j-1] == 0)//���ҷ���
		visit(i, j-1, S);

	if (maze[i-1][j] == 0)//���Ϸ���
		visit(i-1, j, S);

	maze[i][j] = 0;   // û�����·�������ؿ�·
}


// ���������ά�����Թ�




void mainww()
{
	SeqStack S;
	StackInitiate(&S);

	//��ʼ�ݹ�
	visit(startI, startJ, S);

}


