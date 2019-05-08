#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct 
{
	KeyType key;
} DataType;
#define MaxSize 100

#include "SeqList.h"

////////////////////////////////////////////////////////////////////// 静态查找
// ASL = (n+1)/2
int SeqSearch(SeqList S, DataType x)
{
	int i = 0;
	while (i < S.size && S.list[i].key != x.key)
		i++;
	if (S.list[i].key == x.key)
		return i;
	else
		return -1;
}

// （有序）ASL = (n+1)/2
int OrderSeqSearch(SeqList S, DataType x)
{
	int i = 0;
	while (i < S.size && S.list[i].key < x.key)
		i++;
	if (S.list[i].key == x.key)
		return i;
	else
		return -1;
}


// （有序）折半查找（循环结构），返回下标
// ASL = lbn
int BinarySearch(SeqList S, DataType x)
{
	int low = 0;
	int high = S.size -1;
	int mid;

	while (low <= high) 
	{
		mid = (low + high) / 2;              // 确定查找中心
		if (S.list[mid].key == x.key)
			return mid;                      // 找到返回下标
		else if (S.list[mid].key < x.key)
			low = mid + 1;                   // 在较大一部分寻找
		else if (S.list[mid].key > x.key)
			high = mid - 1;                  // 在较小一部分寻找
	}

	return -1;                               // 查找失败
}



///////////////////////////////////////////////////////////////////////// 动态查找

/*
二叉排序树：
若左子树不空，则左子树上所有结点的关键字值均小于根结点的关键字值
若右子树不空，则右子树上所有结点的关键字值均大于或等于根结点的关键字值
*/

// 二叉链存储结构
typedef struct node
{
	DataType data;
	struct node * leftChild;
	struct node * rightChild;
} BiTreeNode;


// 循环结构查找（中根遍历）
// 查找成功返回 1， 失败返回 0
int Search(BiTreeNode * root, DataType item)
{
	BiTreeNode * p;
	if (root != NULL)
	{
		////////////////////// 循环结构
		p = root;
		while (p != NULL)
		{
			if (p->data.key == item.key)
				return 1;                // 查找成功

			if (item.key > p->data.key)
				p = p->rightChild;
			else
				p = p->leftChild;
		}

		/*
		//////////////////// 递归结构
		if (p->data.key == item.key)
			return 1;             

		if (item.key > root->data.key)
			return Search(root->rightChild, item);
		else
			return Search(root->leftChild, item);
		*/
	}
	return 0;  // 查找失败
}


/*
插入算法：
首先查找数据元素是否已在二叉排序树上，若已在，则不插入
若不存在，则把数据元素插入到在二叉排序树查找失败时结点的左孩子或右孩子上

若存在则返回 0 
否则，插入结点并返回 1
*/

int Insert(BiTreeNode ** root, DataType item)
{
	BiTreeNode * current = *root;
	BiTreeNode * parent = NULL;
	BiTreeNode * p;

	while (current != NULL)
	{
		if (current->data.key == item.key)
			return 0;                       // 数据已存在

		parent = current;
		if (current->data.key < item.key)
			current = current->rightChild;
		else
			current = current->leftChild;
	}

	// 生成新结点
	p = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	p->data = item;
	p->leftChild = NULL;
	p->rightChild = NULL;

	if (parent == NULL)
		*root = p;                         // 新的根结点
	else if (item.key < parent->data.key)
		parent->leftChild = p;             // 作为左子树
	else
		parent->rightChild = p;            // 作为右子树
	return 1;
}


// 中序遍历二叉树root, 并在遍历过程中输出结点数据元素值
void InTraverse(BiTreeNode * root)
{
	if (root == NULL)
		return;

	if (root->leftChild != NULL)
		InTraverse(root->leftChild);
	printf("%d  ", root->data.key);

	if (root->rightChild != NULL)
		InTraverse(root->rightChild);
}

////////////////////////////////////////////////// 测试动态查找
void main()
{
	DataType test[] = {4, 5, 7, 2, 1, 9, 8, 6, 3};
	DataType x = {77};
	int n = 9;
	int s;

	BiTreeNode * root = NULL;
	for (int i = 0; i < n; i++)	
		Insert(&root, test[i]);
	InTraverse(root);
	s = Search(root, x);
	if (s == 1)
		printf("数据%d存在！\n", x.key);
	else
		printf("数据%d不存在！\n", x.key);

}


//////////////////////////////////////////////// 测试静态查找
void mainqq()
{
	SeqList S;
	ListInitiate(&S);                        // 初始化

	DataType data;
	for (int i = 0; i < 20; i++)
	{
		data.key = i*i;
		ListInsert(&S, i, data);             // 插入数据
	}

	data.key = 35;
	int address = BinarySearch(S, data);
	if (address == -1)
		printf("找不到\n");
	else
		printf("下标：%d，数值：%d \n", address, S.list[address].key);
}



