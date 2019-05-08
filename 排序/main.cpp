#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#define MaxStackSize 18000 // ˳���ջ�����Ԫ�ظ���
typedef  int KeyType;

typedef struct
{
	KeyType key;
} DataType;

#include "LinQuene.h"  // ��������
#include "SeqStack_Sort.h"
///////////////////// �������� ///////////////////////////////////////
/*
ֱ�Ӳ�������

�㷨˼�룺
���ϵذ��µ�����Ԫ�ز��뵽�����������Ӽ��ϵĺ���λ��

�ռ临�Ӷȣ�O(1)
ʱ�临�Ӷȣ�O(n) - O(n2)֮��
�㷨�ȶ�
*/
void InsertSort(DataType a[], int n)
// �� a[0] �� a[n-1] ����
{
	int j;
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		temp = a[i+1];
		j = i;
		while (j > -1 && temp.key < a[j].key)
		{
			a[j+1] = a[j];  // ǰ��ϴ�����ֺ���
			j--;
		}
		a[j+1] = temp;
	}
}




/*
ϣ�����򣨲�������

�㷨˼�룺
�Ѵ���������Ԫ�طֳ����ɸ�С�飬��ͬһС���ڵ�����Ԫ����ֱ�Ӳ�������
С��ĸ����𽥼�С���������������Ԫ�ض���һ�����ڵ�����󣬽�����

�ռ临�Ӷȣ�O��1��
ʱ�临�Ӷȣ�O�� n*(lbn)2 ��
�㷨���ȶ�
*/
void ShellSort(DataType a[], int n, int d[], int numOfD)
// d[0] �� d[numOfD-1] Ϊϣ������ֵ
{
	int j;
	int span;                          // ÿ�����ӵ���
	DataType temp;

	for (int m = 0; m < numOfD; m++)   // ��ѭ��numOfD�Σ�������d�ĸ��� 
	{
		span = d[m];                   // ȡ�����ε�����ֵ
		for (int k = 0; k < span; k++) // ÿ��С��span��Ԫ�أ���Ƚϴ���Ϊspan��
		{
			// ������ֱ�Ӳ������������ǣ�ÿ�β�����1������span
			for (int i = k; i < n-span; i = i+span)  // ����ֳ���n-span���飬ÿ�����span��
			{                                        
				temp = a[i+span];                    // ÿ�αȽϵ��ǣ�һ���i������һ��ĵ�i���Ƚϣ�while��ȫ����ĵ�i��
				j = i;

				while (j > -1 && temp.key < a[j].key )
				{
					a[j+span] = a[j];
					j = j - span;
				}
				a[j+span] = temp;
			}
		}
	}
}



//////////////////////////// ѡ������ //////////////////////////////////////////////////
/*
ֱ��ѡ������

�㷨˼�룺
ÿ�δӴ����������Ԫ�ؼ�����ѡ��ؼ�����С������󣩵�����Ԫ�ص�
����Ԫ�ؼ��ϵ���ǰ�棨������棩������Ԫ�ؼ��ϲ�����С

�ռ临�Ӷȣ�O��1��
ʱ�临�Ӷȣ�O��n2��
�㷨���ȶ�
*/
void SelectSort(DataType a[], int n)
{
	int small;     // �ؼ�����С���±�
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		small = i;                      // ���i������Ԫ�عؼ�����С
		for (int j = i+1; j< n; j++)    // Ѱ�ҹؼ�����С������Ԫ��
			if (a[j].key < a[small].key)
				small = j;              // ��ס��С�ؼ��ֵ��±�

		if (small != i)      // ����СԪ�ص��±겻Ϊiʱ������λ��
		{
			temp = a[i];
			a[i] = a[small];
			a[small] = temp;
		}
	}
}


/*
ʵ��ֱ��ѡ��������ȶ��㷨

�㷨˼�룺
��ѡ����С����Ԫ�غ󣬽���ǰ�����������Ԫ�����κ��ƣ�
Ȼ���ٽ���С����Ԫ�ط����������ĺ��档
*/
void SelectSort2(DataType a[], int n)
{
	int small;     // �ؼ�����С���±�
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		small = i;                      // ���i������Ԫ�عؼ�����С
		for (int j = i+1; j< n; j++)    // Ѱ�ҹؼ�����С������Ԫ��
			if (a[j].key < a[small].key)
				small = j;              // ��ס��С�ؼ��ֵ��±�

		if (small != i)      // ����СԪ�ص��±겻Ϊiʱ������λ��
		{
			temp = a[small]; 

			////////////////////////////////// ��ʱ��ǰ����������ݺ���
			for (int k = small-1; k >= i; k--)
				a[k+1] = a[k];

			a[i] = temp;
		}
	}
}




// ������Ҷ��� a[h] ʹ֮�������ѣ�n Ϊ���� a ��Ԫ�ظ���
// ����һ�κ���ֻ�ǽ�һ�����һֱ�����ų����ѣ���������÷�Ҷ�ӽ��������
void CreatHeap(DataType a[], int n, int h)
{
	int i, j;
	int flag;
	DataType temp;

	i = h;           // i ΪҪ���ѵĶ�����������±�
	j = 2*i+1;       // j Ϊ i �����ӽ����±�
	temp = a[i];
	flag = 0;        // ɸѡ�Ƿ����

	// �����Һ�����ֵ�ϴ����ظ�����ɸѡ
	while (j < n && flag != 1) 
	{
		// Ѱ�����Һ��ӽ���еĽϴ��ߣ�j Ϊ���±�
		if (j < n-1 && a[j].key < a[j+1].key)
			j++;

		if (temp.key > a[j].key)   // a[i].key > a[j].key
			flag = 1;              // ��ǽ���ɸѡ����
		else                       // �����a[j]����
		{
			a[i] = a[j];

			///////////////////////////// ��ʱ������һ�����ǶѱȽ�
			i = j;
			j = 2*i + 1;
		}
	}
	a[i] = temp;       // ������� a[i] �������� a[j]
}

/*
��ʼ���������ѵĹ��̾��Ǵӵ�һ����Ҷ���a[h](h = (n-2)/2)��ʼ��
�������a[0]Ϊֹ��ѭ������CreatHeap(a, n, h)
*/
// ������Ԫ�� a[0] - a[n-1] ��ʼ������Ϊ����
void InitCreatHeap(DataType a[], int n)
{
	for (int i = (n-2)/2; i >= 0; i--)
		CreatHeap(a, n, i);
}

/*
������

�㷨˼�룺
���Ȱ���n��Ԫ�ص�����a��ʼ������Ϊ���ѣ�Ȼ��ѭ��ִ�����£�ֱ������Ϊ��
1.�ѶѶ� a[0] Ԫ�أ�Ϊ���Ԫ�أ��͵�ǰ���ѵ����һ��Ԫ�ؽ�����
2.����Ԫ�ظ����� 1��
���ڵ�һ�������㲻���������ѵĶ��壬��˵��������ʹ֮��������

�ռ临�Ӷȣ�O(1)
ʱ�临�Ӷȣ�O(nlbn)
�㷨���ȶ�
*/
void HeapSort(DataType a[], int n)
{
	DataType temp;
	InitCreatHeap(a, n);            // ��ʼ��������

	for (int i = n-1; i > 0; i--)   // ��ǰ���Ѹ���ÿ�εݼ�1
	{
		// �ѶѶ� a[0] Ԫ�غ͵�ǰ���ѵ����һ��Ԫ�ؽ���
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		CreatHeap(a, i, 0);  // �����������������
		// ע�⣬��ʱ�Ӷ�����������±�Ϊ0���Ӷ�����������Ϊi
	}
}


///////////////////////////////// �������� ///////////////////////////////////////////
/*
ð������

�㷨˼�룺
ѭ��n-1�Σ�ÿ�ζ��Ǵ��±�0��ʼ���������ڵ�Ԫ�ؽ��бȽϣ�Ԫ�ش��ǰ��

�ռ临�Ӷȣ�O(1)
ʱ�临�Ӷȣ�O(n) - O(n2)
�㷨�ȶ�
*/
void BubbleSort(DataType a[], int n)
{
	int flag = 1;
	DataType temp;

	for (int i = 1; i < n && flag == 1; i++)
	{
		flag = 0;
		for (int j = 0; j < n-i; j++)        // n-i ÿ�ֻ������ȽϵĴ������٣��ϴ���ֵ�𽥷ŵ������
		{
			if (a[j].key > a[j+1].key)       // ÿ�ζ����������ڵ�Ԫ�ؽ��бȽ�
			{
				flag = 1;                    // ����й�������¼

				// �������ڵ�Ԫ�ؽ���λ��
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
/*
˫��ð������

�㷨˼�룺
�� i �� k �ֱ��¼�������еĿ�ʼλ�úͽ���λ�ã�
�ھ���һ������ð����������Ԫ�ر��������� k ��λ�ã�
��ʱ k ��ǰ��һ��λ�ã�Ȼ���ٽ���һ�˷���ð������
����СԪ�ؽ������� i ��λ�ã�i �����һ��λ�á�
��������ͷ�������У�ֱ�� i �� k ���Ϊֹ��
*/
void  BubbleSort2(DataType a[], int n)
{
	int flag = 1;    // �Ƿ�������
	DataType temp;
	
	int I = 0;       // �ʼ��Ԫ��
	int K = n-1;     // ����Ԫ��
	int i = I;
	int k = K;

	while (I < K && flag == 1)
	{
		flag = 0;          
		for (int j = I; j < K; j++)
		{
			if (a[j].key > a[j+1].key)   // ������Ԫ��������
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;

				k = j;// ��ʱ a[j] ��ǰ������Ƚ���Ԫ�����ģ���������и���ĵ���������
				// ������� a[k] ��ʼ
			}
		}

		K = k;

		for (int t = K; t > I; t--)
		{
			if (a[t].key < a[t-1].key)   // ����С��Ԫ��������
			{
				temp = a[t];
				a[t] = a[t-1];
				a[t-1] = temp;
				flag = 1;

				i = t;// ��ʱ a[i] �Ǻ�����ǰ�Ƚ���Ԫ����С�ģ�ǰ������и�С�ĵ���������
				// ������� a[i] ��ʼ
			}
		}

		I = i;

	}
}



/*
��������

�㷨˼�룺

�ռ临�Ӷȣ�O(n)
ʱ�临�Ӷȣ�O(nlbn)
�㷨���ȶ�
*/
void QuickSort(DataType a[], int low, int high)
{
	int i = low;
	int j = high;
	DataType temp = a[low];      // ��ŦԪ��

	while (i < j)
	{
		while (i < j && temp.key <= a[j].key)   // ��������Ҷ��ұ���ŦԪ��С����
			j--;

		if (i < j)
		{
			a[i] = a[j];
			i++;
		}

		while (i < j && a[i].key < temp.key)   // �����������ұ���ŦԪ�ش����
			i++;

		if (i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	// i == j ѭ������

	a[i] = temp;
	if (low < i)
		QuickSort(a, low, i-1);   

	if (i < high)
		QuickSort(a, j+1, high);
}
///// �ǵݹ�Ŀ��������㷨
void QuickSort2(KeyType a[], KeyType low, KeyType high)
{
	SeqStack s;
	StackInitiate(&s);

	StackPush(&s, low);
	StackPush(&s, high);
	
	while (StackNotEmpty(s)) 
	{
		KeyType lowTemp;
		KeyType highTemp;

		StackPop(&s, &highTemp);
		StackPop(&s, &lowTemp);          // �Ƚ����

		KeyType i = lowTemp;
		KeyType j = highTemp;
		KeyType temp = a[lowTemp];      // ��ŦԪ��

		while (i < j)
		{
			while (i < j && temp <= a[j])   // ��������Ҷ��ұ���ŦԪ��С����
				j--;

			if (i < j)
			{
				a[i] = a[j];
				i++;
			}

			while (i < j && a[i] < temp)   // �����������ұ���ŦԪ�ش����
				i++;

			if (i < j)
			{
				a[j] = a[i];
				j--;
			}
		}
		// i == j ѭ������

		a[i] = temp;
		if (lowTemp < i)
		{
			StackPush(&s, lowTemp);
			StackPush(&s, i-1);
		}
		if (i < highTemp)
		{
			StackPush(&s, j+1);
			StackPush(&s, highTemp);
		}
			
	}

}

/*
������ L �д����Ҫ����� int ��������
ʵ��ֱ�Ӳ�������

typedef struct Node
{
	int data;
	struct Node * next;
} SLNode;
// ��ͷ��㵥���� L ��ֱ�Ӳ�������
void LinkInSort(SLNode * L)
{
	SLNode * p, *q, *r;
	p = L->next;
	L->next = NULL;

	while (p != NULL)
	{
		r = p;
		p = p->next;
		q = L;

		while (q->next != NULL && q->next->data < r->next)
			q = q->next;

		r->next = q->next;
		q->next = r;
	}
}

ʵ��ð������
ʵ��ֱ��ѡ������
*/




///////////////////////////// �鲢���� ////////////////////////////////////////////
/*
�鲢����

�㷨˼�룺

�ռ临�Ӷȣ�O(n)
ʱ�临�Ӷȣ�O(nlbn)
�㷨�ȶ�
*/
// k Ϊ����������ĳ��ȣ�һ�ζ�·�鲢���������������д�������swap��
void Merge(DataType a[], int n, DataType swap[], int k)
{
	int m = 0;
	int U1, U2, i, j, L2;
	int L1 = 0;           // ��һ�������������½�Ϊ0

	while (L1+k <= n-1)
	{
		L2 = L1 + k;                         // ����ڶ��������������½�
		U1 = L2 - 1;                         // �����һ�������������Ͻ�
		U2 = (L2+k-1 <= n-1) ? L2+k-1 : n-1; // ����ڶ��������������Ͻ�

		// ��������������ϲ�
		for (i = L1, j = L2; i <= U1 && j <= U2; m++)
		{
			if (a[i].key <= a[j].key)
			{
				swap[m] = a[i];
				i++;
			}
			else
			{
				swap[m] = a[j];
				j++;
			}
		}

		// ������2�Ѿ��鲢�꣬��������1��ʣ���Ԫ�ش�ŵ�swap
		while (i <= U1)
		{
			swap[m] = a[i];
			m++;
			i++;
		}

		// ������2�Ѿ��鲢�꣬��������2��ʣ���Ԫ�ش�ŵ�swap
		while (j <= U2)
		{
			swap[m] = a[j];
			m++;
			j++;
		}

		L1 = U2 + 1;
	}

	// ��ԭʼ������ֻ��һ�������Ԫ��˳���ŵ�����swap��
	for (i = L1; i < n; i++, m++)
		swap[m] = a[i];
}

// ��·�鲢����
void MergeSort(DataType a[], int n)
{
	int k = 1;                   // �鲢���ȴ�1��ʼ
	DataType *swap;
	swap = (DataType *)malloc(sizeof(DataType) * n);

	while (k < n)
	{
		Merge(a, n, swap, k);
		for (int i = 0; i < n; i++)
			a[i] = swap[i];     // ��Ԫ�ش���ʱ����swap�Ż�����a��

		k = k * 2;              // �鲢���ȼӱ�       
	}
	free(swap);
}



///////////////////////////// �鲢���� ////////////////////////////////////////////

// �ϲ�����[p, q], [q+1, r]
void merge(DataType a[], int p, int q, int r)
{
	DataType *b = (DataType *)malloc(sizeof(DataType) * (r-p+1));
	int s = p;
	int t = q+1;
	int k = 0;

	// �ϲ�����[s, q], [t, r] �� b[]
	while (s <= q && t <= r)
	{
		if (a[s].key <= a[t].key)
			b[k++] = a[s++];
		else
			b[k++] = a[t++];
	}

	while (s <= q)            // ������1��ʣ���Ԫ�ش�ŵ�b[]
		b[k++] = a[s++];
	while (t <= r)            // ������2��ʣ���Ԫ�ش�ŵ�b[]
		b[k++] = a[t++];

	for (k = p; k <= r; k++)  // ��b[]��ֵ���θ���a[]
		a[k] = b[k-p];
	free(b);
}
// ��·�鲢����
void mergeSort(DataType a[], int low, int high)
{
	int mid;
	if (low < high) 
	{
		mid = (low+high) / 2;
		mergeSort(a, low, mid);
		mergeSort(a, mid+1, high);
		merge(a, low, mid, high);
	}
}


///////////////////////////// �������� ////////////////////////////////////////////
/*
��������Ͱ����

�ؼ���Ϊ��������

�㷨˼�룺
�ؼ���Ϊ m λ d ���Ƶ�����
���� d ��Ͱ�����0,1��2.����d-1
���Ȱ��ؼ������λ����ֵ���ΰѸ������ŵ���Ӧ��Ͱ�У�
Ȼ����Ͱ�Ŵ�С����ͽ���Ͱ�����ݵ��Ⱥ�����ռ������ڸ�Ͱ�е�����Ԫ�ء�

�ռ临�Ӷȣ�O(n)
ʱ�临�Ӷȣ�O(nm)
�㷨�ȶ�
*/

// ������Ԫ��a[0] - a[n-1]���йؼ���Ϊ m λ d ��������ֵ�Ļ�������
// Ͱ������ʽ���У��Ƚ��ȳ���
void RadixSort(DataType a[], int n, int m, int d)
{
	LQueue *tub;
	int k, power;

	// �� d �����ж���Ϊ��̬����
	tub = (LQueue *)malloc(sizeof(LQueue) * d);
	for (int i = 0; i < d; i++)
		LQueueInitiate(&tub[i]);    // ��ʼ��d ������

	// ���� m �ηź���
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
			power = 1;            // ��һ�λ���Ϊ 1
		else 
			power = power * d;    // ��2,3������Ϊ10,100����

		// �� n ������Ԫ�ذ��չؼ��ֵ� k λ����ֵ�ŵ���Ӧ�Ķ�����
		for (int j = 0; j < n; j++)
		{
			k = a[j].key/power - (a[j].key / (power*d)) * d;   // ������ӦͰ�ı��
			LQueueAppend(&tub[k], a[j]);                       // ��a[j]�Ž�tub[k]
		}

		// ˳����ո��ж��е�����Ԫ�������� a ��
		k = 0;
		for (int j = 0; j < d; j++)
			while (LQueueNotEmpty(tub[j]) != 0)
			{
				LQueueDelete(&tub[j], &a[k]);   // �Ӹ��жӻ���
				k++;
			}
	}
}


////////////////////////////// �������� ////////////////////////////////////////////
void CountingSort(DataType a[], int n) 
{
	DataType max = a[0];
	DataType min = a[0];
	for (int i = 1; i < n; i++)       // �ҳ������Сֵ 
	{
		if (a[i].key > max.key)
			max = a[i];
		else if (a[i].key < min.key)
			min = a[i];
	}

	int k = max.key - min.key + 1;    // ���� B �ĳ���
	DataType *b = (DataType *)malloc(sizeof(DataType) * k); // ��������B
	
	for (int i = 0; i < k; i++)    // ��ʼ������B
		b[i].key = 0;

	for (int i = 0; i < n; i++)    // ͳ��ÿ��Ԫ�صĸ���
		b[a[i].key - min.key].key++;

	int dx = 0;       // �������Ŀ������ʱ��λ�ñ�־
	for (int i = 0; i < k; i++)    // �������Ŀ������
	{
		while (b[i].key-- > 0)
			a[dx++].key = i + min.key;
	}

	free(b);    // �ͷ����� B
}



#define N 18000
void main()
{
	// �������10000����0-999������
	int n = N;
	DataType test1[N];
	DataType test2[N];
	DataType test3[N];
	DataType test4[N];
	DataType test5[N];
	DataType test6[N];
	DataType test7[N];
	DataType test8[N];
	DataType test9[N];
	DataType test10[N];
	DataType test12[N];

	KeyType test11[N];

	time_t bDiff;
	timeb bStart, bEnd;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		
		test1[i].key = rand() % 999;
		test2[i] = test1[i];
		test3[i] = test1[i];
		test4[i] = test1[i];
		test5[i] = test1[i];
		test6[i] = test1[i];
		test7[i] = test1[i];
		test8[i] = test1[i];
		test9[i] = test1[i];
		test10[i] = test1[i];
		test12[i] = test1[i];
		test11[i] = test1[i].key;
		//printf("%d ", test11[i]);
	}
	

	ftime(&bStart);
	/////////////////////////////////////////////// ֱ�Ӳ�������
	InsertSort(test1, n);           
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("ֱ�Ӳ�������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// ϣ������
	int d[] = {5, 3, 1};
	int numOfD = 3;
	ShellSort(test2, n, d, numOfD);   
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    ϣ������%d ����\n", bDiff);

	ftime(&bStart);
	/////////////////////////////////////////////// ֱ��ѡ������
	SelectSort(test3, n);              
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("ֱ��ѡ������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// �ȶ���ѡ������
	SelectSort2(test4, n);              
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("�ȶ���ѡ������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// ������
	HeapSort(test5, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("      ������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// ð������
	BubbleSort(test6, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    ð������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// ˫��ð������
	BubbleSort2(test7, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("˫��ð������%d ����\n", bDiff);

	ftime(&bStart);
	/////////////////////////////////////////////// ��������
	QuickSort(test8, 0, n-1);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    ��������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// �鲢����
	//mergeSort(a, 0, 9);
	MergeSort(test9, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    �鲢����%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// ��������
	RadixSort(test10, n, 3, 10);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    ��������%d ����\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// �ǵݹ������������
	QuickSort2(test11, 0, n-1);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("�ǵݹ������������%d ����\n", bDiff);

	ftime(&bStart);
	//////////////////////////////////////////////// ��������
	CountingSort(test12, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("          ��������%d ����\n", bDiff);


	//for (int i = 0; i < n/4; i++)
		//printf("%d ", test12[i].key);
}

void main2()
{
	DataType a[10];
	int n = 10;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i].key = rand() % 999;
		printf("%d ", a[i].key);
	}
	printf("\n");


	//SelectSort2(a, n);             // �ȶ���ѡ������
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	//BubbleSort2(a, n);              // ˫��ð������
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	CountingSort(a, n);              // ��������
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	//////////////////////////////////////////////////////
	int b[10] = {2,14,6,38,0,61,3,5,97,9};
	QuickSort2(b, 0, 9);              // �ǵݹ�Ŀ�������
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
}