#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 52       // �˿���52��
#define M 8        // ������ǲ���

// �˿����������
void poker()
{
	int poker[N + 1];
	int i, j, tmp, remain;

	//��ʼ������
	for(i = 0; i <= N; i++)
		poker[i] = i;

	//time(0)�ǵõ���ǰʱ,ʱ��ֵ��1970.1.1�������������ʼ�����������
	srand((unsigned int)time(0));

	//ϴ��
	for (i = 0; i <= N; i++)
	{
		j = rand() % 52 + 1;  // ���� 1-52 ����

		//����ֵλ�û���
		tmp = poker[i];
		poker[i] = poker[j];
		poker[j] = tmp;
	}

	for (i = 1; i <= N; i++)
	{
		//�жϻ�ɫ
		switch ((poker[i]-1) / 13)
		{
		case 0:
			printf("����");
			break;
		case 1:
			printf("����");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("÷��");
			break;
		}

		// �˿�������
		remain = poker[i] % 13;
		switch((remain))
		{
		case 0:
			printf("K ");
			break;
		case 12:
			printf("Q ");
			break;
		case 11:
			printf("J ");
			break;
		default:
			printf("%d ",remain);
			break;
		}
		if(i % 13 == 0)
			printf("\n");
	}
}




// ��һ��������������������A��B��C��A������ŵ�ɸ����ӣ����Ӵ�С���ȣ�������£�С������
// ����Щ�����Ӵ�A���Ƶ�C�����м���Խ���B����ÿ��ֻ�������ƶ�һ�����ӣ��������ƶ�������
// 3�����ϵ�����ʼ�ձ��ִ������£�С������

// n ������
void hanoi(int n, int a = 1, int b = 2, int c = 3)
{
	if ( n == 1 )
		printf("%d->%d ", a, c);   // ��ֱ�Ӵ� a �� c
	else
	{ 
	     hanoi( n-1, a, c, b);    // ���������һ�� n ����������ȫ������һ������
		                          // ͨ�� c �����壬�� a �� b
		 printf("%d->%d ", a, c);
		 hanoi(n-1, b, a, c);     // ���һ�� a �� c �󣬽�������ǲ����Ƶ� c
	}
}



// �������
void Triangle()
{
	int i, j, a[M][M];
	for (i = 0; i < M; i++)
	{
	   a[i][0] = 1;             // ÿ���׸�Ϊ 1
	   a[i][i] = 1;             // ÿ��β��Ϊ 1
    }

	for (i = 2; i < M; i++)         // �����п�ʼ
		for (j = 1; j < i; j++)     // ÿ�еڶ�����ʼ
			a[i][j] = a[i-1][j-1] + a[i-1][j];

	// �������
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M-i-1; j++)     // ÿ��֮ǰ�Ŀո���
			printf("  ");
	    for (j = 0; j <= i; j++)        // ÿ�еĸ��� == ���ڵ�����
			printf("%4d", a[i][j]);
	    printf("\n");
	}
}



// �۰����
// ���������� a[low]-a[high] �в��� == x �����±� ��ϧֻ���ҵ�һ��
int BSearch(int a[], int x, int low, int high)
{
	int mid;
	if (low > high )
		return -1;       // ���Ҳ��ɹ�
	
	mid = (low + high) / 2;
	if (x == a[mid])
		return mid;      // ���ҳɹ�

	else if(x < a[mid])
		BSearch(a, x, low, mid-1);    // ��ǰ�����ݹ�Ѱ��
	else
		BSearch(a, x, mid+1, high);   // �ں�����ݹ�Ѱ��
}



// �ݹ���� ����X �� n �η�
// ˼·:
// �ٽ��� n=0 , x �� 0 �η����� 1
// ����� n Ϊż������ x �� n �η� ===== x �� n/2 �η���ƽ��
// ����� n Ϊ�������� x �� n �η� ===== x �� n/2 �η���ƽ�� * x
int power(int x, int n)
{
	int y;          // ������
	if (n == 0)
	{
		y = 1;
	}
	else
	{
		y = power(x, n/2);         // �ݹ�
		if (n%2 == 1)      // ��� n Ϊ����
		{
			y  = y * y * x;
		}
		else               // ��� n Ϊż��
		{
			y = y * y;
		}
	}
	return y;
}



// �ۼ�
int add(int n)
{
	if (n == 1)
		return 1;   // �ݹ����
	else 
		return n + add(n-1);
}
// �����ۼ�
int addArray(int a[], int n)
{
	if (n == 1)
		return a[n-1];
	else
		return a[n-1] + addArray(a, n-1);
}
// �׳�
int factor(int n)
{
	if (n == 1)
		return 1;
	else
		return n * factor(n-1);
}
// ����׳�
int factorialArray(int a[], int n)
{
	if (n == 1)
		return a[n-1];
	else
		return a[n-1] * factorialArray(a, n-1);
}
// �����������
int maxArray(int a[], int n)
{
	int x;
	if (n == 1)
		return a[n-1];
	else
	{
		x = maxArray(a, n-1);    // ֱ�ӵݹ鵽�����һ����return ��һ����ʼ�Ƚ�
		if (x > a[n-1])
			return x;
		else
			return a[n-1];
	}
}

// �ݹ����������Լ��
int gcd(int a, int b)
{
	int max = a > b ? a : b;
	int min = max == a ? b : a;
	if (min == 0) 
		return max;    // ��ʾ�ҵ���
	else
		return gcd(min, max % min);
}


/********************************************************************
ħ�÷���
һ�� n �׵Ļ÷��� 1, 2, 3,....n^2��ɣ�
�����ÿ���ϵ������ͣ�ÿ���ϵ������ͣ������Խ��ߵ������͵���һ������ s.

         8  1  6  
3 �� ==  3  5  7
         4  9  2

1���� 1 ���ڵ�һ�е��м�
2��������������ŵ�ǰ����������б�����Ϸ���
		1.���Ҫ���õ����ִ��ڵ�һ�е����棬��������������еĶ�Ӧλ��
		2.���Ҫ���õ����ִ�������һ�е��Ҳ࣬��������������һ�еĶ�Ӧλ��
		3.���Ҫ���õ����ֵ�λ���ѱ�ռ�ã��������һ�����úõ����ֵ����·�

*********************************************************************/





/**************************************************************************
ѭ����λ��
������ֳ�Ϊǰ�������֣�a �� b ��ԭ����Ϊ ab ����λ���� ba ,
���Դ�������a���� �� b���棩���� = ba
***************************************************************************/
void reverse(int *a, int start, int end) 
{
	int mid = (end - start) /2;
	int temp;
	for (int i = start, j = end; i < j; i++, j--)
	{
		temp = a[i];    // �ԳƷ�ת
		a[i] = a[j];
		a[j] = temp;
	}
}
void shift_reverse(int * a, int len, int num)  // ���� num λ���൱������ len-num λ
{
	reverse(a, 0, num-1);
	reverse(a, num, len-1);
	reverse(a, 0, len-1);
}



void main()
{
	/*
	int a[] = {1,2,3,4};
	int n = factorialArray(a,4);
	int m = maxArray(a, 4);


	printf("%d  ", n);
	printf("%d  ", m);

	printf("%d  ", gcd(7, 55));
	*/

	int arrayInt[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arrayLen = 10;
	int move = 3;

	shift_reverse(arrayInt, arrayLen, move);   // ����ѭ����λ
	for (int i = 0; i < arrayLen; i++)
		printf("%d  ", arrayInt[i]);

}
