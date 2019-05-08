#include <stdlib.h>
#include <stdio.h>
#define MaxBit 8         // ��ʼ�趨��������λ��
#define MaxValue 100     // ��ʼ�趨��Ȩֵ���
typedef struct
{
	int weight;     // Ȩֵ
	int flag;       // ���  1�Ѽ������У�0δ����
	int parent;     // ˫�׽���±�
	int leftChild;  // ����
	int rightChild; // �Һ���
} HuffNode;              // ���������Ľ��ṹ

typedef struct
{
	int bit[MaxBit];    // �������� �磺01101110
	int start;          // �������ʼ�±�
	int weight;         // �ַ���Ȩֵ
} Code;                       // ����������Ľṹ


// ����Ҷ������Ϊ n��Ȩֵ����Ϊweight�� huffTree
void Huffman(int weight[], int n, HuffNode huffTree[])
{
	int i, j, m1, m2, x1, x2;
	// �������� huffTree��ʼ���� n ��Ҷ���Ķ��������� 2n-1 �����
	for (i = 0; i < 2*n - 1; i++)
	{
		if (i < n)
			huffTree[i].weight =weight[i];    // �ֱ� n ��Ȩֵ����ǰ n �����
		else
			huffTree[i].weight = 0;           // ������ȨֵΪ 0
		huffTree[i].parent = -1;
		huffTree[i].flag = 0;
		huffTree[i].leftChild = -1;
		huffTree[i].rightChild = -1;
	}

	// ����������� huffTree �� n-1 ����Ҷ���
	for (i = 0; i < n-1; i++)
	{
		m1 = m2 = MaxValue;      // ������С�ʹ�С��Ȩֵ��MaxValue ΪȨֵ������
		x1 = x2 = 0;             // ������С�ʹ�С���±�

		// �ҳ�Ȩֵ��С�ʹ�С������
		for (j = 0; j < n+i; j++)  // i ��ʾ����ѭ�����ж��ٵĺϲ�����룬���뵽 huffTree[n+i].....               
		{
			if (huffTree[j].weight < m1 && huffTree[j].flag == 0)     // �ҵ���С�ģ�����ҵ���С���򽫱��浽m1��ԭ���ı��浽m2
			{
				m2 = m1;
				x2 = x1;
				m1 = huffTree[j].weight;
				x1 = j;
			}
			else if (huffTree[j].weight < m2 && huffTree[j].flag == 0) // �ҵ���С��
			{
				m2 = huffTree[j].weight;
				x2 = j;
			}
		}

		// ���ҳ�������Ȩֵ��С�ʹ�С�������ϲ�һ������
		huffTree[x1].parent = n+i;
		huffTree[x2].parent = n+i;
		huffTree[x1].flag = 1;
		huffTree[x2].flag = 1;
		huffTree[n+i].weight = huffTree[x1].weight + huffTree[x2].weight;
		huffTree[n+i].leftChild = x1;
		huffTree[n+i].rightChild = x2;
	}
}


// �� n ��Ҷ���Ĺ������� huffTree ������������� huffCode
void HuffmanCode(HuffNode huffTree[], int n, Code huffCode[])
{
	Code *cd = (Code *)malloc(sizeof(Code));
	int i, j, child, parent;

	// �� n ��Ҷ�ڵ�Ĺ���������
	for (i = 0; i < n; i++)         // ������������ʱ���Ѿ���Ҷ�ӽ���±�� 0 �� n-1 ��ʼ��
	{
		cd->start = n-1;                   // ���ȳ���������һλΪ n-1����Ȼ����û����ô��
		cd->weight = huffTree[i].weight;   // ��ȡ�����Ӧ��Ȩֵ
		child = i;
		parent = huffTree[child].parent;

		// ��һ��Ҷ�ڵ�����ֱ�����ڵ㣬�õ�����
		while (parent != -1)  
		{
			if (huffTree[parent].leftChild == child)
				cd->bit[cd->start] = 0;         // ���ӷ�֧���� 0
			else
				cd->bit[cd->start] = 1;         // �Һ��ӷ�֧���� 1
			cd->start--;
			child = parent;
			parent = huffTree[child].parent;
		}
		for (j = cd->start+1; j < n; j++)         // ��1 ����Ϊǰ��-1����ʱָ��ָ��յ�����[start]��������Ҫ��һ
			huffCode[i].bit[j] = cd->bit[j];      // ����ÿ��Ҷ���ı���
		huffCode[i].start = cd->start + 1;        // ����Ҷ���������ʼλ
		huffCode[i].weight = cd->weight;          // ��������Ӧ��Ȩֵ
	}
}

void maineea()
{
	int i, j, n = 4;
	int weight[] = {1,3,5,7};
	HuffNode *myHuffTree = (HuffNode *)malloc(sizeof(HuffNode) * (2*n - 1));
	Code *myHuffCode = (Code *)malloc(sizeof(Code) * n);
	
	Huffman(weight, n, myHuffTree);
	HuffmanCode(myHuffTree, n, myHuffCode);

	// ���ÿ��Ҷ���Ĺ���������
	for (i = 0; i < n; i++)
	{
		printf("Weight = %d  Code = ", myHuffCode[i].weight);
		for (j = myHuffCode[i].start; j < n; j++)        // �������
			printf("%d", myHuffCode[i].bit[j]);
		printf("\n");
	}
}
