



/*
线索二叉树:
既可以从前向后分步遍历二叉树，又可以从后向前分步遍历二叉树
分类：前序，中序，后序

如果leftThread == 0, leftChild 指向结点的左孩子
如果leftThread == 1, leftChild 指向结点的前驱结点(即上一个结点：父亲结点)

如果rightThread == 0, rightChild 指向结点的左孩子
如果rightThread == 1, rightChild 指向结点的后继结点（即下一个结点：孩子结点）

结点的存储结构：
leftThread  leftChild  data  rightChild  rightThread
*/


/*

//////////////// 中序线索二叉树

typedef char DataType;

typedef struct ThreadNode 
{
	DataType data;               // 数据域
	int leftThread;              // 左线索
	int rightThread;             // 右线索
	struct ThreadNode * leftChild;     // 左指针
	struct ThreadNode * rightChild;    // 右指针
} ThreadBiNode;


// 中序线索化二叉树
// current 为当前结点指针，pre为当前结点的中序前驱结点指针
void InThread(ThreadBiNode *current, ThreadBiNode ** pre)
{
	if (current != NULL)
	{
		InThread(current->leftChild, pre);  // 中序线索化左子树
		if (current->leftChild == NULL)     // 左为空，当前左指针指向父亲结点
		{
			current->leftThread = 1;        // 建立左线索标记
			current->leftChild = *pre;      // 建立左线索指针（前驱：下一个）
		}
		else
			current->leftThread = 0;

		if (current->rightChild != NULL)
			current->rightThread = 0;
		else
			current->rightThread = 1;

		if ((*pre)->rightChild == NULL)    // 右为空，则上一个结点右指针指向孩子结点
		{
			(*pre)->rightThread = 1;       // 建立右线索标记
			(*pre)->rightChild = current;  // 建立右线索指针（后继）
		}
		else
			current->rightThread = 0;

		*pre = current;                       // 前序结点指针等于当前结点指针
		InThread(current->rightChild, pre);   // 中序线索化右子树
	}
}

// 创建中序线索化二叉树tree
void CreatInThread(ThreadBiNode ** root)
{
	ThreadBiNode *t = *root;          // 保存原二叉树根结点指针
	ThreadBiNode *current;
	ThreadBiNode *pre = *root;
	// 建立头结点
	*root = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));

	// 如果树为空
	if (t == NULL)
	{
		(*root)->leftThread = 0;
		(*root)->rightThread = 1;
		(*root)->leftChild = *root;
		(*root)->rightChild = *root;
	}
	else
	{
		current = t;
		(*root)->leftChild = t;        // 置头结点的左指针
		(*root)->leftThread = 0;       // 置头结点的左线索

		InThread(current, &pre);       // 线索化二叉树

		pre->rightChild = *root;       // 置最后一个结点的右指针
		pre->rightThread = 1;          // 置最后一个结点的右线索

		(*root)->rightChild = pre;     // 置头结点的右指针
		(*root)->rightThread = 1;      // 置头结点的右线索
	}
}


typedef struct
{
	ThreadBiNode * root;        // 头指针
	ThreadBiNode * current;     // 当前结点指针
	int nextComplete;           // 遍历结束标记
} ThreadBiTree;


// 初始化中序线索二叉树
void ThreadInitiate(ThreadBiTree *tree, ThreadBiNode * root)
{
	tree->root = root;
	tree->current = root;
	if (root == NULL)
		tree->nextComplete = 1;
	else
		tree->nextComplete = 0;
}

// 使中序线索二叉树 tree 的当前结点指针指向中序遍历的第一个结点
void First(ThreadBiTree *tree)
{
	tree->current = tree->root;              // 定位根结点
	while (tree->current->leftThread == 0)   // 找到最左子树结点
		tree->current = tree->current->leftChild;

	if (tree->current == tree->root)
		tree->nextComplete = 1;
	else
		tree->nextComplete = 0;
}

// 使中序线索二叉树tree的当前结点指针指向中序遍历的下一个结点
void Next(ThreadBiTree *tree)
{
	ThreadBiNode * p = tree->current->rightChild;
	if (tree->nextComplete == 1)
		return;

	if (tree->current->rightThread == 0)  // 若有右孩子结点则找到最左子树结点
		while (p->leftThread ==0)
			p = p->leftChild;

	tree->current = p;
	if (tree->current == tree->root)
		tree->nextComplete = 1;
}

// 判断是否已到中序线索二叉树tree的尾部
// nextComplete = 1 表示已到，否则未到
int EndOfNext(ThreadBiTree * tree)
{
	return tree->nextComplete;
}


*/