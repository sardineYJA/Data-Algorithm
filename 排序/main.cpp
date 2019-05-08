#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#define MaxStackSize 18000 // 顺序堆栈的最大元素个数
typedef  int KeyType;

typedef struct
{
	KeyType key;
} DataType;

#include "LinQuene.h"  // 基数排序
#include "SeqStack_Sort.h"
///////////////////// 插入排序 ///////////////////////////////////////
/*
直接插入排序

算法思想：
不断地把新的数据元素插入到已排列有序子集合的合适位置

空间复杂度：O(1)
时间复杂度：O(n) - O(n2)之间
算法稳定
*/
void InsertSort(DataType a[], int n)
// 对 a[0] — a[n-1] 排序
{
	int j;
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		temp = a[i+1];
		j = i;
		while (j > -1 && temp.key < a[j].key)
		{
			a[j+1] = a[j];  // 前面较大的数字后移
			j--;
		}
		a[j+1] = temp;
	}
}




/*
希尔排序（插入排序）

算法思想：
把待排序数组元素分成若干个小组，对同一小组内的数据元素用直接插入排序，
小组的个数逐渐减小，当完成所有数组元素都在一个组内的排序后，结束。

空间复杂度：O（1）
时间复杂度：O（ n*(lbn)2 ）
算法不稳定
*/
void ShellSort(DataType a[], int n, int d[], int numOfD)
// d[0] — d[numOfD-1] 为希尔增量值
{
	int j;
	int span;                          // 每次增加的量
	DataType temp;

	for (int m = 0; m < numOfD; m++)   // 共循环numOfD次，即数组d的个数 
	{
		span = d[m];                   // 取出本次的增量值
		for (int k = 0; k < span; k++) // 每个小组span个元素，则比较次数为span次
		{
			// 组内是直接插入排序，区别是，每次不是增1而是增span
			for (int i = k; i < n-span; i = i+span)  // 数组分成了n-span个组，每组个数span，
			{                                        
				temp = a[i+span];                    // 每次比较的是：一组第i个与另一组的第i个比较，while了全部组的第i个
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



//////////////////////////// 选择排序 //////////////////////////////////////////////////
/*
直接选择排序

算法思想：
每次从待排序的数据元素集合中选择关键字最小（或最大）的数据元素到
数据元素集合的最前面（或最后面），数据元素集合不断缩小

空间复杂度：O（1）
时间复杂度：O（n2）
算法不稳定
*/
void SelectSort(DataType a[], int n)
{
	int small;     // 关键字最小的下标
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		small = i;                      // 设第i个数据元素关键字最小
		for (int j = i+1; j< n; j++)    // 寻找关键字最小的数据元素
			if (a[j].key < a[small].key)
				small = j;              // 记住最小关键字的下标

		if (small != i)      // 当最小元素的下标不为i时，交换位置
		{
			temp = a[i];
			a[i] = a[small];
			a[small] = temp;
		}
	}
}


/*
实现直接选择排序的稳定算法

算法思想：
在选出最小数据元素后，将他前面的无序数据元素依次后移，
然后再将最小数据元素放在有序区的后面。
*/
void SelectSort2(DataType a[], int n)
{
	int small;     // 关键字最小的下标
	DataType temp;
	for (int i = 0; i < n-1; i++)
	{
		small = i;                      // 设第i个数据元素关键字最小
		for (int j = i+1; j< n; j++)    // 寻找关键字最小的数据元素
			if (a[j].key < a[small].key)
				small = j;              // 记住最小关键字的下标

		if (small != i)      // 当最小元素的下标不为i时，交换位置
		{
			temp = a[small]; 

			////////////////////////////////// 此时将前面的无序数据后移
			for (int k = small-1; k >= i; k--)
				a[k+1] = a[k];

			a[i] = temp;
		}
	}
}




// 调整非叶结点 a[h] 使之满足最大堆，n 为数组 a 的元素个数
// 调用一次函数只是将一个结点一直向下排成最大堆，所以需调用非叶子结点数次数
void CreatHeap(DataType a[], int n, int h)
{
	int i, j;
	int flag;
	DataType temp;

	i = h;           // i 为要建堆的二叉树根结点下标
	j = 2*i+1;       // j 为 i 的左孩子结点的下标
	temp = a[i];
	flag = 0;        // 筛选是否结束

	// 沿左右孩子中值较大者重复向下筛选
	while (j < n && flag != 1) 
	{
		// 寻找左右孩子结点中的较大者，j 为其下标
		if (j < n-1 && a[j].key < a[j+1].key)
			j++;

		if (temp.key > a[j].key)   // a[i].key > a[j].key
			flag = 1;              // 标记结束筛选条件
		else                       // 否则把a[j]上移
		{
			a[i] = a[j];

			///////////////////////////// 此时进行下一个三角堆比较
			i = j;
			j = 2*i + 1;
		}
	}
	a[i] = temp;       // 把最初的 a[i] 赋予最后的 a[j]
}

/*
初始化创建最大堆的过程就是从第一个非叶结点a[h](h = (n-2)/2)开始，
到根结点a[0]为止的循环调用CreatHeap(a, n, h)
*/
// 把数组元素 a[0] - a[n-1] 初始化创建为最大堆
void InitCreatHeap(DataType a[], int n)
{
	for (int i = (n-2)/2; i >= 0; i--)
		CreatHeap(a, n, i);
}

/*
堆排序

算法思想：
首先把有n个元素的数组a初始化创建为最大堆，然后循环执行如下，直到数组为空
1.把堆顶 a[0] 元素（为最大元素）和当前最大堆的最后一个元素交换；
2.最大堆元素个数减 1；
由于第一步后根结点不再满足最大堆的定义，因此调整根结点使之满足最大堆

空间复杂度：O(1)
时间复杂度：O(nlbn)
算法不稳定
*/
void HeapSort(DataType a[], int n)
{
	DataType temp;
	InitCreatHeap(a, n);            // 初始创建最大堆

	for (int i = n-1; i > 0; i--)   // 当前最大堆个数每次递减1
	{
		// 把堆顶 a[0] 元素和当前最大堆的最后一个元素交换
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		CreatHeap(a, i, 0);  // 调整根结点满足最大堆
		// 注意，此时子二叉树根结点下标为0，子二叉树结点个数为i
	}
}


///////////////////////////////// 交换排序 ///////////////////////////////////////////
/*
冒泡排序

算法思想：
循环n-1次，每次都是从下标0开始，两个相邻的元素进行比较，元素大的前移

空间复杂度：O(1)
时间复杂度：O(n) - O(n2)
算法稳定
*/
void BubbleSort(DataType a[], int n)
{
	int flag = 1;
	DataType temp;

	for (int i = 1; i < n && flag == 1; i++)
	{
		flag = 0;
		for (int j = 0; j < n-i; j++)        // n-i 每轮回两两比较的次数减少，较大数值逐渐放到最后面
		{
			if (a[j].key > a[j+1].key)       // 每次都是两个相邻的元素进行比较
			{
				flag = 1;                    // 标记有过交换记录

				// 两个相邻的元素交换位置
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
/*
双向冒泡排序

算法思想：
用 i 和 k 分别记录无序序列的开始位置和结束位置，
在经过一趟正向冒泡排序后，最大元素被交换到第 k 个位置，
此时 k 向前移一个位置；然后再进行一趟反向冒泡排序，
将最小元素交换到第 i 个位置，i 向后移一个位置。
这样正向和反向交替进行，直到 i 与 k 相等为止。
*/
void  BubbleSort2(DataType a[], int n)
{
	int flag = 1;    // 是否发生交换
	DataType temp;
	
	int I = 0;       // 最开始的元素
	int K = n-1;     // 最后的元素
	int i = I;
	int k = K;

	while (I < K && flag == 1)
	{
		flag = 0;          
		for (int j = I; j < K; j++)
		{
			if (a[j].key > a[j+1].key)   // 将最大的元素往后移
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;

				k = j;// 此时 a[j] 是前面往后比较中元素最大的（后面或许有更大的但是已有序）
				// 反向则从 a[k] 开始
			}
		}

		K = k;

		for (int t = K; t > I; t--)
		{
			if (a[t].key < a[t-1].key)   // 将最小的元素往后移
			{
				temp = a[t];
				a[t] = a[t-1];
				a[t-1] = temp;
				flag = 1;

				i = t;// 此时 a[i] 是后面往前比较中元素最小的（前面获许有更小的但是已有序）
				// 正向则从 a[i] 开始
			}
		}

		I = i;

	}
}



/*
快速排序

算法思想：

空间复杂度：O(n)
时间复杂度：O(nlbn)
算法不稳定
*/
void QuickSort(DataType a[], int low, int high)
{
	int i = low;
	int j = high;
	DataType temp = a[low];      // 枢纽元素

	while (i < j)
	{
		while (i < j && temp.key <= a[j].key)   // 在数组的右端找比枢纽元素小的数
			j--;

		if (i < j)
		{
			a[i] = a[j];
			i++;
		}

		while (i < j && a[i].key < temp.key)   // 在数组的左端找比枢纽元素大的数
			i++;

		if (i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	// i == j 循环结束

	a[i] = temp;
	if (low < i)
		QuickSort(a, low, i-1);   

	if (i < high)
		QuickSort(a, j+1, high);
}
///// 非递归的快速排序算法
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
		StackPop(&s, &lowTemp);          // 先进后出

		KeyType i = lowTemp;
		KeyType j = highTemp;
		KeyType temp = a[lowTemp];      // 枢纽元素

		while (i < j)
		{
			while (i < j && temp <= a[j])   // 在数组的右端找比枢纽元素小的数
				j--;

			if (i < j)
			{
				a[i] = a[j];
				i++;
			}

			while (i < j && a[i] < temp)   // 在数组的左端找比枢纽元素大的数
				i++;

			if (i < j)
			{
				a[j] = a[i];
				j--;
			}
		}
		// i == j 循环结束

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
单链表 L 中存放着要排序的 int 类型数据
实现直接插入排序

typedef struct Node
{
	int data;
	struct Node * next;
} SLNode;
// 带头结点单链表 L 的直接插入排序
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

实现冒泡排序
实现直接选择排序
*/




///////////////////////////// 归并排序 ////////////////////////////////////////////
/*
归并排序

算法思想：

空间复杂度：O(n)
时间复杂度：O(nlbn)
算法稳定
*/
// k 为有序子数组的长度，一次二路归并排序后的有序子序列存于数组swap中
void Merge(DataType a[], int n, DataType swap[], int k)
{
	int m = 0;
	int U1, U2, i, j, L2;
	int L1 = 0;           // 第一个有序子数组下界为0

	while (L1+k <= n-1)
	{
		L2 = L1 + k;                         // 计算第二个有序子数组下界
		U1 = L2 - 1;                         // 计算第一个有序子数组上界
		U2 = (L2+k-1 <= n-1) ? L2+k-1 : n-1; // 计算第二个有序子数组上界

		// 两个有序子数组合并
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

		// 子数组2已经归并完，将子数组1中剩余的元素存放到swap
		while (i <= U1)
		{
			swap[m] = a[i];
			m++;
			i++;
		}

		// 子数组2已经归并完，将子数组2中剩余的元素存放到swap
		while (j <= U2)
		{
			swap[m] = a[j];
			m++;
			j++;
		}

		L1 = U2 + 1;
	}

	// 将原始数组中只够一组的数据元素顺序存放到数组swap中
	for (i = L1; i < n; i++, m++)
		swap[m] = a[i];
}

// 二路归并排序
void MergeSort(DataType a[], int n)
{
	int k = 1;                   // 归并长度从1开始
	DataType *swap;
	swap = (DataType *)malloc(sizeof(DataType) * n);

	while (k < n)
	{
		Merge(a, n, swap, k);
		for (int i = 0; i < n; i++)
			a[i] = swap[i];     // 将元素从临时数组swap放回数组a中

		k = k * 2;              // 归并长度加倍       
	}
	free(swap);
}



///////////////////////////// 归并排序 ////////////////////////////////////////////

// 合并区间[p, q], [q+1, r]
void merge(DataType a[], int p, int q, int r)
{
	DataType *b = (DataType *)malloc(sizeof(DataType) * (r-p+1));
	int s = p;
	int t = q+1;
	int k = 0;

	// 合并区间[s, q], [t, r] 到 b[]
	while (s <= q && t <= r)
	{
		if (a[s].key <= a[t].key)
			b[k++] = a[s++];
		else
			b[k++] = a[t++];
	}

	while (s <= q)            // 将数组1中剩余的元素存放到b[]
		b[k++] = a[s++];
	while (t <= r)            // 将数组2中剩余的元素存放到b[]
		b[k++] = a[t++];

	for (k = p; k <= r; k++)  // 将b[]数值依次赋给a[]
		a[k] = b[k-p];
	free(b);
}
// 二路归并排序
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


///////////////////////////// 基数排序 ////////////////////////////////////////////
/*
基数排序（桶排序）

关键字为整数类型

算法思想：
关键字为 m 位 d 进制的整数
设置 d 个桶，编号0,1，2.，，d-1
首先按关键字最低位的数值依次把各个数放到相应的桶中，
然后按照桶号从小到大和进入桶中数据的先后次序收集分配在各桶中的数据元素。

空间复杂度：O(n)
时间复杂度：O(nm)
算法稳定
*/

// 对数据元素a[0] - a[n-1]进行关键字为 m 位 d 进制整型值的基数排序
// 桶采用链式队列（先进先出）
void RadixSort(DataType a[], int n, int m, int d)
{
	LQueue *tub;
	int k, power;

	// 把 d 个队列定义为动态数组
	tub = (LQueue *)malloc(sizeof(LQueue) * d);
	for (int i = 0; i < d; i++)
		LQueueInitiate(&tub[i]);    // 初始化d 个队列

	// 进行 m 次放和收
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
			power = 1;            // 第一次回收为 1
		else 
			power = power * d;    // 第2,3，，，为10,100，，

		// 将 n 个数据元素按照关键字第 k 位的数值放到相应的队列中
		for (int j = 0; j < n; j++)
		{
			k = a[j].key/power - (a[j].key / (power*d)) * d;   // 计算相应桶的标号
			LQueueAppend(&tub[k], a[j]);                       // 把a[j]放进tub[k]
		}

		// 顺序回收各列队中的数据元素至数组 a 中
		k = 0;
		for (int j = 0; j < d; j++)
			while (LQueueNotEmpty(tub[j]) != 0)
			{
				LQueueDelete(&tub[j], &a[k]);   // 从各列队回收
				k++;
			}
	}
}


////////////////////////////// 计数排序 ////////////////////////////////////////////
void CountingSort(DataType a[], int n) 
{
	DataType max = a[0];
	DataType min = a[0];
	for (int i = 1; i < n; i++)       // 找出最大最小值 
	{
		if (a[i].key > max.key)
			max = a[i];
		else if (a[i].key < min.key)
			min = a[i];
	}

	int k = max.key - min.key + 1;    // 数组 B 的长度
	DataType *b = (DataType *)malloc(sizeof(DataType) * k); // 创建数组B
	
	for (int i = 0; i < k; i++)    // 初始化数组B
		b[i].key = 0;

	for (int i = 0; i < n; i++)    // 统计每个元素的个数
		b[a[i].key - min.key].key++;

	int dx = 0;       // 反向填充目标数组时的位置标志
	for (int i = 0; i < k; i++)    // 反向填充目标数组
	{
		while (b[i].key-- > 0)
			a[dx++].key = i + min.key;
	}

	free(b);    // 释放数组 B
}



#define N 18000
void main()
{
	// 随机产生10000个（0-999）的数
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
	/////////////////////////////////////////////// 直接插入排序
	InsertSort(test1, n);           
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("直接插入排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 希尔排序
	int d[] = {5, 3, 1};
	int numOfD = 3;
	ShellSort(test2, n, d, numOfD);   
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    希尔排序：%d 毫秒\n", bDiff);

	ftime(&bStart);
	/////////////////////////////////////////////// 直接选择排序
	SelectSort(test3, n);              
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("直接选择排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 稳定的选择排序
	SelectSort2(test4, n);              
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("稳定的选择排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 堆排序
	HeapSort(test5, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("      堆排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 冒泡排序
	BubbleSort(test6, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    冒泡排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 双向冒泡排序
	BubbleSort2(test7, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("双向冒泡排序：%d 毫秒\n", bDiff);

	ftime(&bStart);
	/////////////////////////////////////////////// 快速排序
	QuickSort(test8, 0, n-1);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    快速排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 归并排序
	//mergeSort(a, 0, 9);
	MergeSort(test9, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    归并排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 基数排序
	RadixSort(test10, n, 3, 10);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("    基数排序：%d 毫秒\n", bDiff);


	ftime(&bStart);
	/////////////////////////////////////////////// 非递归快速排序排序
	QuickSort2(test11, 0, n-1);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("非递归快速排序排序：%d 毫秒\n", bDiff);

	ftime(&bStart);
	//////////////////////////////////////////////// 计数排序
	CountingSort(test12, n);
	ftime(&bEnd);                     
	bDiff = bEnd.time * 1000 + bEnd.millitm -bStart.time*1000 - bStart.millitm;
	printf("          计数排序：%d 毫秒\n", bDiff);


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


	//SelectSort2(a, n);             // 稳定的选择排序
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	//BubbleSort2(a, n);              // 双向冒泡排序
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	CountingSort(a, n);              // 计数排序
	for (int i = 0; i < n; i++)
		printf("%d ", a[i].key);
	printf("\n");



	//////////////////////////////////////////////////////
	int b[10] = {2,14,6,38,0,61,3,5,97,9};
	QuickSort2(b, 0, 9);              // 非递归的快速排序
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
}