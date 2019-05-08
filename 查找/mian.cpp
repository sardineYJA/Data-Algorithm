#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct 
{
	KeyType key;
} DataType;
#define MaxSize 100

#include "SeqList.h"

////////////////////////////////////////////////////////////////////// ��̬����
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

// ������ASL = (n+1)/2
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


// �������۰���ң�ѭ���ṹ���������±�
// ASL = lbn
int BinarySearch(SeqList S, DataType x)
{
	int low = 0;
	int high = S.size -1;
	int mid;

	while (low <= high) 
	{
		mid = (low + high) / 2;              // ȷ����������
		if (S.list[mid].key == x.key)
			return mid;                      // �ҵ������±�
		else if (S.list[mid].key < x.key)
			low = mid + 1;                   // �ڽϴ�һ����Ѱ��
		else if (S.list[mid].key > x.key)
			high = mid - 1;                  // �ڽ�Сһ����Ѱ��
	}

	return -1;                               // ����ʧ��
}



///////////////////////////////////////////////////////////////////////// ��̬����

/*
������������
�����������գ��������������н��Ĺؼ���ֵ��С�ڸ����Ĺؼ���ֵ
�����������գ��������������н��Ĺؼ���ֵ�����ڻ���ڸ����Ĺؼ���ֵ
*/

// �������洢�ṹ
typedef struct node
{
	DataType data;
	struct node * leftChild;
	struct node * rightChild;
} BiTreeNode;


// ѭ���ṹ���ң��и�������
// ���ҳɹ����� 1�� ʧ�ܷ��� 0
int Search(BiTreeNode * root, DataType item)
{
	BiTreeNode * p;
	if (root != NULL)
	{
		////////////////////// ѭ���ṹ
		p = root;
		while (p != NULL)
		{
			if (p->data.key == item.key)
				return 1;                // ���ҳɹ�

			if (item.key > p->data.key)
				p = p->rightChild;
			else
				p = p->leftChild;
		}

		/*
		//////////////////// �ݹ�ṹ
		if (p->data.key == item.key)
			return 1;             

		if (item.key > root->data.key)
			return Search(root->rightChild, item);
		else
			return Search(root->leftChild, item);
		*/
	}
	return 0;  // ����ʧ��
}


/*
�����㷨��
���Ȳ�������Ԫ���Ƿ����ڶ����������ϣ������ڣ��򲻲���
�������ڣ��������Ԫ�ز��뵽�ڶ�������������ʧ��ʱ�������ӻ��Һ�����

�������򷵻� 0 
���򣬲����㲢���� 1
*/

int Insert(BiTreeNode ** root, DataType item)
{
	BiTreeNode * current = *root;
	BiTreeNode * parent = NULL;
	BiTreeNode * p;

	while (current != NULL)
	{
		if (current->data.key == item.key)
			return 0;                       // �����Ѵ���

		parent = current;
		if (current->data.key < item.key)
			current = current->rightChild;
		else
			current = current->leftChild;
	}

	// �����½��
	p = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	p->data = item;
	p->leftChild = NULL;
	p->rightChild = NULL;

	if (parent == NULL)
		*root = p;                         // �µĸ����
	else if (item.key < parent->data.key)
		parent->leftChild = p;             // ��Ϊ������
	else
		parent->rightChild = p;            // ��Ϊ������
	return 1;
}


// �������������root, ���ڱ�������������������Ԫ��ֵ
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

////////////////////////////////////////////////// ���Զ�̬����
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
		printf("����%d���ڣ�\n", x.key);
	else
		printf("����%d�����ڣ�\n", x.key);

}


//////////////////////////////////////////////// ���Ծ�̬����
void mainqq()
{
	SeqList S;
	ListInitiate(&S);                        // ��ʼ��

	DataType data;
	for (int i = 0; i < 20; i++)
	{
		data.key = i*i;
		ListInsert(&S, i, data);             // ��������
	}

	data.key = 35;
	int address = BinarySearch(S, data);
	if (address == -1)
		printf("�Ҳ���\n");
	else
		printf("�±꣺%d����ֵ��%d \n", address, S.list[address].key);
}



