#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"
#include "SeqCQueue.h"
#include "InThreadIterator.h"



// �������Ĳ�α�����ͬһ����������
// ��Ҫʹ�ö���
void LevelOrder(BiTreeNode *root)
{
	BiTreeNode *p = root;

    // ��ʼ������  
    SeqCQueue queue;
	QueueInitiate(&queue);

    //���ڵ����  
    QueueAppend(&queue, *p);  // �Ե�ַ��ֵ�������޸ģ����Ի�Ӱ�� root ָ��

    //���в���ѭ��  
    while (QueueNotEmpty(queue)) 
	{  
        //��ͷԪ�س���
		//�˳�����  
		QueueDelete(&queue, p);

        //����pָ��Ľ��  
        printf("%c ",p->data);  

        //���������գ������������  
		if(p->leftChild != NULL){  
			QueueAppend(&queue, *p->leftChild);
        }  
        //���������գ������������  
		if(p->rightChild != NULL){  
			QueueAppend(&queue, *p->rightChild); 
        }
	}
}


// �ж��Ƿ�Ϊ��ȫ������
// ��α��������������������ҽڵ�����С�
// �������еĽ��Ϊ�գ����Ժ�����еĽ�㶼Ϊ�գ�1 ��Ϊ��ȫ������������ 0 ����
int CompleteBiTree(BiTreeNode * root)
{
	BiTreeNode *p = root;
	int flag = 1;

    // ��ʼ������  
    SeqCQueue queue;
	QueueInitiate(&queue);

    //���ڵ����  
    QueueAppend(&queue, *p);   // �Ե�ַ��ֵ�������޸ģ����Ի�Ӱ�� root ָ��

    //���в���ѭ��  
    while (QueueNotEmpty(queue)) 
	{  
        //��ͷԪ�س���
		//�˳�����  
		QueueDelete(&queue, p);

        //���������գ������������  
		if(p->leftChild != NULL) {  
			QueueAppend(&queue, *p->leftChild);
			if (flag == 0)
				return 0;
        }
		else 
			flag = 0;  // ����Ժ�����еĽ���������������Ϊ��

        //���������գ������������  
		if(p->rightChild != NULL) {  
			QueueAppend(&queue, *p->rightChild);
			if (flag == 0)
				return 0;
        }
		else
			flag = 0;  // ����Ժ�����еĽ���������������Ϊ��
	}
	return 1;
}




////////////// ��ס���ĸ����� root ���� root->leftChild ///////////////////
void main()
{
	BiTreeNode *root, *p, *find;
	char x = 'T';
	Initiate(&root);

	p = InsertLeftNode(root, 'A');
	p = InsertLeftNode(p, 'B');
	InsertRightNode(p, 'W');
	p = InsertLeftNode(p, 'D');
	
	InsertRightNode(p, 'G');
	InsertLeftNode(p, 'T');

	p = InsertRightNode(root->leftChild, 'C');
	InsertLeftNode(p, 'E');
	InsertRightNode(p, 'F');
	
	// ��ʱ��90�ȴ�ӡ������
	PrintBiTree(root, 0);


	printf("ǰ�������");
	PreOrder(root->leftChild, visit);
	
	printf("\n���������");
	InOrder(root->leftChild, visit);
	
	printf("\n���������");
	PostOrder(root->leftChild, visit);

	// ��α�����Ӱ�� root ��λ�� ������������
	printf("\n��α���: ");
	//LevelOrder(root->leftChild);



	find = Search(root->leftChild, x);
	if (find != NULL)
		printf("\n\n����Ԫ��%c�ڶ�������\n", x);
	else 
		printf("\n\n����Ԫ��%c���ڶ�������\n", x);

	
	printf ("��������㣺%d\n\n", NumOfNodes(root->leftChild));

	printf ("����������ȣ�%d\n\n", HeightBiTree(root->leftChild) - 1);

	// ��α�����Ӱ�� root ��λ�� ������������
	printf ("�Ƿ�����ȫ��������%d\n\n", CompleteBiTree(root->leftChild));

	Destroy(&root);
}



/////////////////////////////////////////////////////////////////////
/////////////// �����������Ĳ���

/*

// �������������
ThreadBiNode * GetTreeNode (DataType item, ThreadBiNode *left, ThreadBiNode * right)
{
	ThreadBiNode *p;
	p = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));
	p->data = item;
	p->leftChild = left;
	p->rightChild = right;
	return p;
}

// �����õ��������
void InOrder_ThreadBiNode(ThreadBiNode *root, void visit(int item))
{
	if (root != NULL)
	{
		InOrder_ThreadBiNode(root->leftChild, visit);
		visit(root->data);
		InOrder_ThreadBiNode(root->rightChild, visit);
	}
}
// ����������
void MakeCharTree(ThreadBiNode ** root)
{
	ThreadBiNode *b, *c, *d, *e, *f, *g;
	g = GetTreeNode('G', NULL, NULL);
	d = GetTreeNode('D', NULL, g);
	b = GetTreeNode('B', d, NULL);
	e = GetTreeNode('E', NULL, NULL);
	f = GetTreeNode('F', NULL, NULL);
	c = GetTreeNode('C', e, f);
	*root = GetTreeNode('A', b, c);
	//
	//              A(root)
	//         	B       C
    //        D	      E   F   
    //           G	
	//     
	printf("����������������������Ƿ񴴽��ɹ���");
	InOrder_ThreadBiNode(*root,  visit);
	printf("\n");
}

void mainj()
{
	ThreadBiNode *root;
	ThreadBiTree tree;
	MakeCharTree(&root);
	CreatInThread(&root);
	printf("���������������������Ϊ��");
	ThreadInitiate(&tree, root);
	for (First(&tree); !EndOfNext(&tree); Next(&tree))
		printf("%c, ", tree.current->data);
}


*/