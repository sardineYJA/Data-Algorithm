#include<stdio.h>
#include<stdlib.h>


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
void visit(int i,int j)
{
	int m, n;
	maze[i][j] = 1; // ȫ����·��Ϊ�� 

	// ������������ʾ·��
	if (i == endI && j == endJ )        // ������������������Ѿ��Һó���
	{
		// ���µ�ֻ����ʾ��ά����
		printf("\n��ʾ·��:\n");
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

	//�ݹ鲻ͬ������ʱ�룩�ó���ͬ·��
	if (maze[i-1][j] == 0)//���Ϸ���
		visit(i-1, j);

	if (maze[i][j+1] == 0)//������
		visit(i, j+1);

	if (maze[i+1][j] == 0)//���·���
		visit(i+1, j);

	if (maze[i][j-1] == 0)//���ҷ���
		visit(i, j-1);

	

	maze[i][j] = 0;   // û�����·�������ؿ�·
	
}


// ���������ά�����Թ�



void main()
{
	//��ʼ�ݹ�
	visit(startI, startJ); 

}

