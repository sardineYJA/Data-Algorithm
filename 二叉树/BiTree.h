
//////////////////////////////////////////// 二叉树
// 结点
typedef struct Node
{
	int data;                   // 数据域
	struct Node *leftChild;     // 左子树指针
	struct Node *rightChild;    // 右子树指针 
} BiTreeNode;


// 初始化，带头结点的，即root 是空的
void Initiate(BiTreeNode **root)
{
	*root = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	(*root)->leftChild = NULL;
	(*root)->rightChild = NULL;
}


// 左插入结点
// 当前结点 curr 非空，则在 curr 的左子树插入元素值为 x 的新结点
// 原 curr 所指结点的左子树成为新插入结点的左子树
// 若插入成功，则返回新插入结点的指针，否则返回空指针
BiTreeNode * InsertLeftNode(BiTreeNode * curr, int x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)
		return NULL;   // 当前结点 curr 空

	t = curr->leftChild;       // 保存原 curr 所指向结点的左子树指针
	
	s = (BiTreeNode *)malloc(sizeof(BiTreeNode));   // 新结点
	s->data = x;
	s->leftChild = t;                  // 新插入结点的左子树为原 curr 的左子树
	s->rightChild = NULL;

	curr->leftChild = s;               // 新结点成为 curr 的左子树

	return curr->leftChild;            // 返回新插入结点的指针
}



// 右插入结点
// 当前结点 curr 非空，则在 curr 的右子树插入元素值为 x 的新结点
// 原 curr 所指结点的右子树成为新插入结点的右子树
// 若插入成功，则返回新插入结点的指针，否则返回空指针
BiTreeNode * InsertRightNode(BiTreeNode * curr, int x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)
		return NULL;   // 当前结点 curr 空

	t = curr->rightChild;       // 保存原 curr 所指向结点的右子树指针
	
	s = (BiTreeNode *)malloc(sizeof(BiTreeNode));   // 新结点
	s->data = x;
	s->rightChild = t;                  // 新插入结点的右子树为原 curr 的右子树
	s->leftChild = NULL;

	curr->rightChild = s;               // 新结点成为 curr 的右子树

	return curr->rightChild;            // 返回新插入结点的指针
}


//////////////////////////////////////////////////////////////////////////// 遍历

void visit(int item)
{
	printf("%c  ", item);
}

// 前序遍历，根-左-右
void PreOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		visit(root->data);
		PreOrder(root->leftChild, visit);
		PreOrder(root->rightChild, visit);
	}
}

// 中序遍历，左-根-右
void InOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		InOrder(root->leftChild, visit);
		visit(root->data);
		InOrder(root->rightChild, visit);
	}
}

// 后序遍历，左-右-根
void PostOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		PostOrder(root->leftChild, visit);
		PostOrder(root->rightChild, visit);
		visit(root->data);
	}
}


// 撤销二叉树
void Destroy(BiTreeNode **root)
{
	if ((*root) != NULL && (*root)->leftChild != NULL)
		Destroy(&(*root)->leftChild);
	if ((*root) != NULL && (*root)->rightChild != NULL)
		Destroy(&(*root)->rightChild);
	free(*root);
}
//////////////////////////////////////////////////////////////////////////// 遍历结束


// 左删除子树
// 若 curr 非空，则删除 curr 所指向结点的左子树
// 若删除成功，则返回删除结点的双亲结点指针，否则返回空指针
BiTreeNode * DeleteLeftTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->leftChild == NULL)
		return NULL;

	Destroy(&curr->leftChild);
	curr->leftChild = NULL;
	return curr;
}


// 右删除子树
// 若 curr 非空，则删除 curr 所指向结点的右子树
// 若删除成功，则返回删除结点的双亲结点指针，否则返回空指针
BiTreeNode * DeleteRightTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->rightChild == NULL)
		return NULL;

	Destroy(&curr->rightChild);
	curr->rightChild = NULL;
	return curr;
}


// 打印二叉树
// 逆时针旋转90度打印二叉树 root, n 为缩进层数，初始值为0
void PrintBiTree(BiTreeNode *root, int n = 0)
{
	if (root == NULL)
		return;        // 递归出口

	PrintBiTree(root->rightChild, n+1);   // 遍历打印右子树

	// 访问根结点
	for (int i = 0; i < n-1; i++)
		printf("   ");
	if (n > 0)
	{
		printf("---");
		printf("%c\n", root->data);
	}
	PrintBiTree(root->leftChild, n+1);   // 遍历打印左子树
}

// 查找数据元素 x 是否在二叉树 root中
// 有，返回结点指针，无，返回空指针
BiTreeNode *Search(BiTreeNode *root, int x)
{
	BiTreeNode *find = NULL;      // 初始化标记
	if (root != NULL)
	{
		if (root->data == x)
		{
			find = root;          // 标记查找成功
		}
		else
		{
			find = Search(root->leftChild, x);  // 在左子树找
			if (find == NULL)
				find = Search(root->rightChild, x); // 在右子树找
		}
	}
	return find;
}


// 计算二叉树的结点数
int NumOfNodes(BiTreeNode *root)
{
	if (root == NULL)
		return 0;
	else 
		return NumOfNodes(root->leftChild)
			+ NumOfNodes(root->rightChild) + 1;
}



// 求二叉树的深度
int HeightBiTree(BiTreeNode * root)
{
	int height;
	int left;
	int right;
	if (root == NULL)
		return 0;

	left = HeightBiTree(root->leftChild) + 1;
	right = HeightBiTree(root->rightChild) + 1;

	height = (left > right ? left : right); 
	return height;
}


