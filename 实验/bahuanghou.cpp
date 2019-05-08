
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// a[] �Ѿ������Ļʺ�λ�ã�n �ǵ� n ���ʺ��λ�ã�a[n]
int Check(int a[],int n)  
{  
	// ��ǰ�� n-1 ���ʺ�λ��ì�ܣ��򷵻� 0 
    for(int i=1;i<n;i++)  
    {  
        if(abs(a[i]-a[n])==abs(i-n) || a[i]==a[n])
            return 0;  
    }  
    return 1;  
}  

int a[20];
int n = 8;  // 8 �ʺ�
int i;
int t = 1;  // �� t �ֽⷨ
  
void EightQueen(int i)     // �ӵ� i �п�ʼ
{  
    int j;  
    for (j = 1; j <= n; j++)  
    {  
        a[i] = j;  
        if (Check(a, i))// �����j�в�����֮ǰ�Ļʺ��ͻ  
        {  
            if (i < n)  // ���i<n������û���ҵ��˸��ʺ󣬼����ݹ�  
                EightQueen(i + 1);  
            else        // ����ҵ���һ�������  
            {  
                printf("��%d�ֽⷨ��\n", t++);  
				for (i = 1; i <9; i++)
				{
					for (int j = 1; j < 9; j++)
					{
						if (a[i] == j)
							printf("��");
						else
							printf("��");
					}
					printf("\n");
				}
			}  
		} 
	}  
}  

/////////////////////////////////////////////////////////////////////////////////////

/*
��ƺ������������
1
2 2
3 3 3
.......
n n n n n ..... n

Ҫ��
1.��Ƴɵݹ麯��
2.��Ƴ�ѭ���ṹ����
*/

// num �� 1 �𽥵��� �� n
int printN(int num, int n)
{   
	if (n == num-1)
		return  1;   // �ݹ����
	else if (n < 0 || num > n )
	{
		return 0;    // ����Ĳ����д�
	}
	else 
	{
		for (int i = 1; i <= num; i++)
			printf("%d ", num);
		printf("\n");
		printN(num+1, n);     // �ݹ�
	}

}

/*
�� a ����n ��int ��������Ԫ�ص����飬���Ա�д��a �����ֵ�ĵݹ麯����
*/
// a������ n ��Ԫ��
int MaxArray(int *a, int n) 
{
	int x;
	if (n == 1)
		return a[n-1];
	else
	{
		// ֱ�ӵݹ鵽�����һ����return ��һ����ʼ�Ƚ�
		x = MaxArray(a, n-1);  
		if (x > a[n-1])
			return x;
		else
			return a[n-1];
	}
}

void main()
{
	printN(1,5);
	printf("\n");
	printN(3,9);
}

