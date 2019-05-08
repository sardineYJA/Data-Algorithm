



/*
����������:
�ȿ��Դ�ǰ���ֲ��������������ֿ��ԴӺ���ǰ�ֲ�����������
���ࣺǰ�����򣬺���

���leftThread == 0, leftChild ָ���������
���leftThread == 1, leftChild ָ�����ǰ�����(����һ����㣺���׽��)

���rightThread == 0, rightChild ָ���������
���rightThread == 1, rightChild ָ����ĺ�̽�㣨����һ����㣺���ӽ�㣩

���Ĵ洢�ṹ��
leftThread  leftChild  data  rightChild  rightThread
*/


/*

//////////////// ��������������

typedef char DataType;

typedef struct ThreadNode 
{
	DataType data;               // ������
	int leftThread;              // ������
	int rightThread;             // ������
	struct ThreadNode * leftChild;     // ��ָ��
	struct ThreadNode * rightChild;    // ��ָ��
} ThreadBiNode;


// ����������������
// current Ϊ��ǰ���ָ�룬preΪ��ǰ��������ǰ�����ָ��
void InThread(ThreadBiNode *current, ThreadBiNode ** pre)
{
	if (current != NULL)
	{
		InThread(current->leftChild, pre);  // ����������������
		if (current->leftChild == NULL)     // ��Ϊ�գ���ǰ��ָ��ָ���׽��
		{
			current->leftThread = 1;        // �������������
			current->leftChild = *pre;      // ����������ָ�루ǰ������һ����
		}
		else
			current->leftThread = 0;

		if (current->rightChild != NULL)
			current->rightThread = 0;
		else
			current->rightThread = 1;

		if ((*pre)->rightChild == NULL)    // ��Ϊ�գ�����һ�������ָ��ָ���ӽ��
		{
			(*pre)->rightThread = 1;       // �������������
			(*pre)->rightChild = current;  // ����������ָ�루��̣�
		}
		else
			current->rightThread = 0;

		*pre = current;                       // ǰ����ָ����ڵ�ǰ���ָ��
		InThread(current->rightChild, pre);   // ����������������
	}
}

// ��������������������tree
void CreatInThread(ThreadBiNode ** root)
{
	ThreadBiNode *t = *root;          // ����ԭ�����������ָ��
	ThreadBiNode *current;
	ThreadBiNode *pre = *root;
	// ����ͷ���
	*root = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));

	// �����Ϊ��
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
		(*root)->leftChild = t;        // ��ͷ������ָ��
		(*root)->leftThread = 0;       // ��ͷ����������

		InThread(current, &pre);       // ������������

		pre->rightChild = *root;       // �����һ��������ָ��
		pre->rightThread = 1;          // �����һ������������

		(*root)->rightChild = pre;     // ��ͷ������ָ��
		(*root)->rightThread = 1;      // ��ͷ����������
	}
}


typedef struct
{
	ThreadBiNode * root;        // ͷָ��
	ThreadBiNode * current;     // ��ǰ���ָ��
	int nextComplete;           // �����������
} ThreadBiTree;


// ��ʼ����������������
void ThreadInitiate(ThreadBiTree *tree, ThreadBiNode * root)
{
	tree->root = root;
	tree->current = root;
	if (root == NULL)
		tree->nextComplete = 1;
	else
		tree->nextComplete = 0;
}

// ʹ�������������� tree �ĵ�ǰ���ָ��ָ����������ĵ�һ�����
void First(ThreadBiTree *tree)
{
	tree->current = tree->root;              // ��λ�����
	while (tree->current->leftThread == 0)   // �ҵ������������
		tree->current = tree->current->leftChild;

	if (tree->current == tree->root)
		tree->nextComplete = 1;
	else
		tree->nextComplete = 0;
}

// ʹ��������������tree�ĵ�ǰ���ָ��ָ�������������һ�����
void Next(ThreadBiTree *tree)
{
	ThreadBiNode * p = tree->current->rightChild;
	if (tree->nextComplete == 1)
		return;

	if (tree->current->rightThread == 0)  // �����Һ��ӽ�����ҵ������������
		while (p->leftThread ==0)
			p = p->leftChild;

	tree->current = p;
	if (tree->current == tree->root)
		tree->nextComplete = 1;
}

// �ж��Ƿ��ѵ���������������tree��β��
// nextComplete = 1 ��ʾ�ѵ�������δ��
int EndOfNext(ThreadBiTree * tree)
{
	return tree->nextComplete;
}


*/