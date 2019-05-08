#include <stdlib.h>
#include <stdio.h>
#define MaxBit 8         // 初始设定的最大编码位数
#define MaxValue 100     // 初始设定的权值最大
typedef struct
{
	int weight;     // 权值
	int flag;       // 标记  1已加入树中，0未加入
	int parent;     // 双亲结点下标
	int leftChild;  // 左孩子
	int rightChild; // 右孩子
} HuffNode;              // 哈夫曼树的结点结构

typedef struct
{
	int bit[MaxBit];    // 编码数组 如：01101110
	int start;          // 编码的起始下标
	int weight;         // 字符的权值
} Code;                       // 哈夫曼编码的结构


// 建立叶结点个数为 n，权值数组为weight的 huffTree
void Huffman(int weight[], int n, HuffNode huffTree[])
{
	int i, j, m1, m2, x1, x2;
	// 哈夫曼树 huffTree初始化， n 个叶结点的二叉树共有 2n-1 个结点
	for (i = 0; i < 2*n - 1; i++)
	{
		if (i < n)
			huffTree[i].weight =weight[i];    // 分别将 n 个权值赋给前 n 个结点
		else
			huffTree[i].weight = 0;           // 其余结点权值为 0
		huffTree[i].parent = -1;
		huffTree[i].flag = 0;
		huffTree[i].leftChild = -1;
		huffTree[i].rightChild = -1;
	}

	// 构造哈夫曼树 huffTree 的 n-1 个非叶结点
	for (i = 0; i < n-1; i++)
	{
		m1 = m2 = MaxValue;      // 保存最小和次小的权值，MaxValue 为权值中最大的
		x1 = x2 = 0;             // 保存最小和次小的下标

		// 找出权值最小和次小的子树
		for (j = 0; j < n+i; j++)  // i 表示此轮循环共有多少的合并点加入，加入到 huffTree[n+i].....               
		{
			if (huffTree[j].weight < m1 && huffTree[j].flag == 0)     // 找到最小的，如果找到更小的则将保存到m1，原来的保存到m2
			{
				m2 = m1;
				x2 = x1;
				m1 = huffTree[j].weight;
				x1 = j;
			}
			else if (huffTree[j].weight < m2 && huffTree[j].flag == 0) // 找到次小的
			{
				m2 = huffTree[j].weight;
				x2 = j;
			}
		}

		// 将找出的两棵权值最小和次小的子树合并一棵子树
		huffTree[x1].parent = n+i;
		huffTree[x2].parent = n+i;
		huffTree[x1].flag = 1;
		huffTree[x2].flag = 1;
		huffTree[n+i].weight = huffTree[x1].weight + huffTree[x2].weight;
		huffTree[n+i].leftChild = x1;
		huffTree[n+i].rightChild = x2;
	}
}


// 由 n 个叶结点的哈夫曼树 huffTree 构造哈夫曼编码 huffCode
void HuffmanCode(HuffNode huffTree[], int n, Code huffCode[])
{
	Code *cd = (Code *)malloc(sizeof(Code));
	int i, j, child, parent;

	// 求 n 个叶节点的哈夫曼编码
	for (i = 0; i < n; i++)         // 构建哈夫曼树时，已经将叶子结点下标从 0 到 n-1 开始的
	{
		cd->start = n-1;                   // 不等长编码的最后一位为 n-1，虽然其他没有这么长
		cd->weight = huffTree[i].weight;   // 获取编码对应的权值
		child = i;
		parent = huffTree[child].parent;

		// 由一个叶节点向上直到根节点，得到编码
		while (parent != -1)  
		{
			if (huffTree[parent].leftChild == child)
				cd->bit[cd->start] = 0;         // 左孩子分支编码 0
			else
				cd->bit[cd->start] = 1;         // 右孩子分支编码 1
			cd->start--;
			child = parent;
			parent = huffTree[child].parent;
		}
		for (j = cd->start+1; j < n; j++)         // 加1 是因为前面-1，此时指针指向空的数组[start]，所以需要减一
			huffCode[i].bit[j] = cd->bit[j];      // 保存每个叶结点的编码
		huffCode[i].start = cd->start + 1;        // 保存叶结点编码的起始位
		huffCode[i].weight = cd->weight;          // 保存编码对应的权值
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

	// 输出每个叶结点的哈夫曼编码
	for (i = 0; i < n; i++)
	{
		printf("Weight = %d  Code = ", myHuffCode[i].weight);
		for (j = myHuffCode[i].start; j < n; j++)        // 逆置输出
			printf("%d", myHuffCode[i].bit[j]);
		printf("\n");
	}
}
