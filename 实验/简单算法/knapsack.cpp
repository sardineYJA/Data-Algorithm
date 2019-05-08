#include <iostream>
using namespace std;

// ��������  
// s ����������������w[] �� n ����Ʒ����������
// s ��ȥ����һ������������ֱ������ 0
/*
 �ݹ�˼·��ÿ������������֧·
 ��һ���֣��� n ����Ʒ��������      -->   s ��ȥ�� n ��������������ʣ�� n-1 ��
 �ڶ����֣��� n ����Ʒ����������    -->   n ��ȥ 1 �� s ����
 */
void knapsack(int s, int w[], int n, int *solution)
{
	if (s == 0)       // �ݹ����
	{
		for (int i = 0; i < 7; i++)
			if (solution[i] == 1)
				printf("%d ", w[i]);
		printf("\n");
	}
	else if (s > 0 && n >= 1)   // ����ʣ�����������ݹ�
	{
		solution[n-1] = 1;
		knapsack(s-w[n-1], w, n-1, solution);    // �� n ����Ʒ�Ž�����

		                                         // ???? ����λ�ò��ܻ��������Ǵ����
		solution[n-1] = 0;
		knapsack(s, w, n-1, solution);           // �� n ����Ʒ���Ž�����
	}
}





/// w ÿ����Ʒ�������� n ��Ʒ������ t ���������� solution ��ô�ţ� k Ŀǰ�����Ĵ���
void subset(int* w, int n, int t, int* solution, int k) 
{
	if ( k == n)
	{                
		int sum = 0;
		for (int i = 0; i < k; i++)
			sum += solution[i] * w[i];

		// ����Ľ��
		if ( sum == t ){
			for (int i = 0; i < k; i++)
				if (solution[i] == 1)
					printf("%d ", w[i]);
			printf("\n");
		}
	}

	else 
	{
		solution[k] = 1;
		subset(w, n, t, solution, k + 1);

		solution[k] = 0;
		subset(w, n, t, solution, k + 1);
	}
}


/**********************************************
��̬�滮����������������������ֵ

n����Ʒ����
m������������
w����������
v����ֵ����
c���Ƿ�ѡ������

����ֵ������ֵ

����װ������� 0 ��ʼ�𽥼� 1 ���󣬣��� j++ ��

***********************************************/
int getMaxValue(int n, int m, int *w, int *v, int *c) 
{
	int row = n+1;
	int col = m+1;

	// value[i][j] ��ʾǰ i ����Ʒ��װ��������Ϊ j �ı����е���Ʒ������ֵ
	int **value = (int **)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		value[i] = (int *)malloc(sizeof(int) * col);

	// ��ʼ����0�У���0��
	for (int j = 0; j < col; j++)
		value[0][j] = 0;
	for (int i = 0; i < row; i++)
		value[i][0] = 0;

	// ����
	/*
	��������е���
	v, w, c, �����Ǵ�0 ��ʼ�ģ�����Ҫ��1

	*/
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++) 
		{
			// w[i] > j���� i ����Ʒ��װ�뱳��
			value[i][j] = value[i-1][j];        // ����ÿ�������ļ�ֵ���ȵ���ǰһ�������ļ�ֵ

			// w[i] <= j���ҵ� i ����Ʒװ�뱳�����ֵ > value[i-1][j]�����¼��ǰ����ֵ
			int temp = value[i-1][j-w[i-1]] + v[i-1];
			if (w[i-1] <= j && temp > value[i][j])
				value[i][j] = temp;
		}
	}

	// ������װ�����Ʒ
	int j = m;
	for (int i = row-1; i > 0; i--)
	{
		if (value[i][j] > value[i-1][j])
		{
			c[i-1] = 1;
			j = j - w[i-1];
		}
	}

	// ����ֵ
	int nMaxValue = value[row-1][col-1];

	// �ͷ��ڴ�
	for (int i = 0; i < row; i++)
		free(value[i]);
	free(value);

	return nMaxValue;
}


///////////////////////////////////////////////////////////////////////////////////////////


void maindfg()
{
	/*
	int allWeight = 10;
	int weight[] = {1,2,3,4,5,6,7};
	int n = 7;
	int solution[] = {0, 0, 0, 0, 0, 0, 0};
	knapsack(allWeight, weight, n, solution);
	printf("\n");
	subset(weight, n, allWeight, solution, 0);
	*/


	int n = 5;             // ��Ʒ����
	int m = 10;            // �������������
	int w[] = {2, 3, 4, 5, 6};     // ÿ����Ʒ������
	int v[] = {4, 15, 7, 8, 9};   // ÿ����Ʒ�ļ�ֵ
	int c[] = {0, 0, 0, 0, 0};     // �Ƿ�ѡ��

	int maxValue = getMaxValue(n, m, w, v, c);
	for (int i = 0; i < n; i++)
		printf("%d  ", c[i]);

	printf("%d   \n", maxValue);

}