
#include <stdio.h>

#define N 8

int a[N][N] = 
{
	{5, 5, 3, 8, 0, 7, 7, 3},
	{6, 2, 4, 8, 9, 4, 0, 2},
	{0, 1, 2, 5, 2, 4, 3, 1},
	{2, 5, 9, 9, 6, 3, 7, 4},
	{0, 8, 6, 0, 7, 7, 6, 1},
	{0, 9, 6, 4, 8, 6, 1, 9},
	{9, 3, 0, 6, 9, 3, 5, 6},
	{9, 5, 9, 9, 0, 9, 6, 9}
};
int num = 0;  // ��·������
int max = 0;  // �������

void getMaxGold(int i, int j, int sum = 0)
{
	sum = sum + a[i][j];

	// ��ʱ�ѵ����յ�
	if (i == N-1 && j == N-1)
	{
		//printf("%4d", sum);
		num++;

		// �������������
		if (sum > max)
			max = sum;
	}

	// û�е����յ���ݹ����ң����µ�·��
	else if (i < N-1 && j < N-1)
	{
		getMaxGold(i+1, j, sum);
		getMaxGold(i, j+1, sum);
	}
	// ���������ƶ����������ƶ�
	else if (i == N-1)
	{
		getMaxGold(i, j+1, sum);
	}
	// ���������ƶ����������ƶ�
	else if (j == N-1)
	{
		getMaxGold(i+1, j, sum);
	}
}

void main()
{
	getMaxGold(0, 0, 0);
	printf("\n\n��·��������%d\n����Ҹ�����%d\n\n", num, max);
}
