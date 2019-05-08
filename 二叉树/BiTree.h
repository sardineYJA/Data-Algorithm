
//////////////////////////////////////////// ������
// ���
typedef struct Node
{
	int data;                   // ������
	struct Node *leftChild;     // ������ָ��
	struct Node *rightChild;    // ������ָ�� 
} BiTreeNode;


// ��ʼ������ͷ���ģ���root �ǿյ�
void Initiate(BiTreeNode **root)
{
	*root = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	(*root)->leftChild = NULL;
	(*root)->rightChild = NULL;
}


// �������
// ��ǰ��� curr �ǿգ����� curr ������������Ԫ��ֵΪ x ���½��
// ԭ curr ��ָ������������Ϊ�²������������
// ������ɹ����򷵻��²������ָ�룬���򷵻ؿ�ָ��
BiTreeNode * InsertLeftNode(BiTreeNode * curr, int x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)
		return NULL;   // ��ǰ��� curr ��

	t = curr->leftChild;       // ����ԭ curr ��ָ�����������ָ��
	
	s = (BiTreeNode *)malloc(sizeof(BiTreeNode));   // �½��
	s->data = x;
	s->leftChild = t;                  // �²������������Ϊԭ curr ��������
	s->rightChild = NULL;

	curr->leftChild = s;               // �½���Ϊ curr ��������

	return curr->leftChild;            // �����²������ָ��
}



// �Ҳ�����
// ��ǰ��� curr �ǿգ����� curr ������������Ԫ��ֵΪ x ���½��
// ԭ curr ��ָ������������Ϊ�²������������
// ������ɹ����򷵻��²������ָ�룬���򷵻ؿ�ָ��
BiTreeNode * InsertRightNode(BiTreeNode * curr, int x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)
		return NULL;   // ��ǰ��� curr ��

	t = curr->rightChild;       // ����ԭ curr ��ָ�����������ָ��
	
	s = (BiTreeNode *)malloc(sizeof(BiTreeNode));   // �½��
	s->data = x;
	s->rightChild = t;                  // �²������������Ϊԭ curr ��������
	s->leftChild = NULL;

	curr->rightChild = s;               // �½���Ϊ curr ��������

	return curr->rightChild;            // �����²������ָ��
}


//////////////////////////////////////////////////////////////////////////// ����

void visit(int item)
{
	printf("%c  ", item);
}

// ǰ���������-��-��
void PreOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		visit(root->data);
		PreOrder(root->leftChild, visit);
		PreOrder(root->rightChild, visit);
	}
}

// �����������-��-��
void InOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		InOrder(root->leftChild, visit);
		visit(root->data);
		InOrder(root->rightChild, visit);
	}
}

// �����������-��-��
void PostOrder(BiTreeNode *root, void visit(int item))
{
	if (root != NULL)
	{
		PostOrder(root->leftChild, visit);
		PostOrder(root->rightChild, visit);
		visit(root->data);
	}
}


// ����������
void Destroy(BiTreeNode **root)
{
	if ((*root) != NULL && (*root)->leftChild != NULL)
		Destroy(&(*root)->leftChild);
	if ((*root) != NULL && (*root)->rightChild != NULL)
		Destroy(&(*root)->rightChild);
	free(*root);
}
//////////////////////////////////////////////////////////////////////////// ��������


// ��ɾ������
// �� curr �ǿգ���ɾ�� curr ��ָ�����������
// ��ɾ���ɹ����򷵻�ɾ������˫�׽��ָ�룬���򷵻ؿ�ָ��
BiTreeNode * DeleteLeftTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->leftChild == NULL)
		return NULL;

	Destroy(&curr->leftChild);
	curr->leftChild = NULL;
	return curr;
}


// ��ɾ������
// �� curr �ǿգ���ɾ�� curr ��ָ�����������
// ��ɾ���ɹ����򷵻�ɾ������˫�׽��ָ�룬���򷵻ؿ�ָ��
BiTreeNode * DeleteRightTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->rightChild == NULL)
		return NULL;

	Destroy(&curr->rightChild);
	curr->rightChild = NULL;
	return curr;
}


// ��ӡ������
// ��ʱ����ת90�ȴ�ӡ������ root, n Ϊ������������ʼֵΪ0
void PrintBiTree(BiTreeNode *root, int n = 0)
{
	if (root == NULL)
		return;        // �ݹ����

	PrintBiTree(root->rightChild, n+1);   // ������ӡ������

	// ���ʸ����
	for (int i = 0; i < n-1; i++)
		printf("   ");
	if (n > 0)
	{
		printf("---");
		printf("%c\n", root->data);
	}
	PrintBiTree(root->leftChild, n+1);   // ������ӡ������
}

// ��������Ԫ�� x �Ƿ��ڶ����� root��
// �У����ؽ��ָ�룬�ޣ����ؿ�ָ��
BiTreeNode *Search(BiTreeNode *root, int x)
{
	BiTreeNode *find = NULL;      // ��ʼ�����
	if (root != NULL)
	{
		if (root->data == x)
		{
			find = root;          // ��ǲ��ҳɹ�
		}
		else
		{
			find = Search(root->leftChild, x);  // ����������
			if (find == NULL)
				find = Search(root->rightChild, x); // ����������
		}
	}
	return find;
}


// ����������Ľ����
int NumOfNodes(BiTreeNode *root)
{
	if (root == NULL)
		return 0;
	else 
		return NumOfNodes(root->leftChild)
			+ NumOfNodes(root->rightChild) + 1;
}



// ������������
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


