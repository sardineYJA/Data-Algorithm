#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"
#include "SeqCQueue.h"
#include "InThreadIterator.h"



// 二叉树的层次遍历，同一层自左向右
// 需要使用队列
void LevelOrder(BiTreeNode *root)
{
	BiTreeNode *p = root;

    // 初始化队列  
    SeqCQueue queue;
	QueueInitiate(&queue);

    //根节点入队  
    QueueAppend(&queue, *p);  // 对地址的值进行了修改，所以会影响 root 指针

    //队列不空循环  
    while (QueueNotEmpty(queue)) 
	{  
        //对头元素出队
		//退出队列  
		QueueDelete(&queue, p);

        //访问p指向的结点  
        printf("%c ",p->data);  

        //左子树不空，将左子树入队  
		if(p->leftChild != NULL){  
			QueueAppend(&queue, *p->leftChild);
        }  
        //右子树不空，将右子树入队  
		if(p->rightChild != NULL){  
			QueueAppend(&queue, *p->rightChild); 
        }
	}
}


// 判断是否为完全二叉树
// 层次遍历二叉树，遍历的左右节点入队列。
// 若出队列的结点为空，则以后出队列的结点都为空，1 则为完全二叉树，否则 0 不是
int CompleteBiTree(BiTreeNode * root)
{
	BiTreeNode *p = root;
	int flag = 1;

    // 初始化队列  
    SeqCQueue queue;
	QueueInitiate(&queue);

    //根节点入队  
    QueueAppend(&queue, *p);   // 对地址的值进行了修改，所以会影响 root 指针

    //队列不空循环  
    while (QueueNotEmpty(queue)) 
	{  
        //对头元素出队
		//退出队列  
		QueueDelete(&queue, p);

        //左子树不空，将左子树入队  
		if(p->leftChild != NULL) {  
			QueueAppend(&queue, *p->leftChild);
			if (flag == 0)
				return 0;
        }
		else 
			flag = 0;  // 标记以后出队列的结点的左右子树必须为空

        //右子树不空，将右子树入队  
		if(p->rightChild != NULL) {  
			QueueAppend(&queue, *p->rightChild);
			if (flag == 0)
				return 0;
        }
		else
			flag = 0;  // 标记以后出队列的结点的左右子树必须为空
	}
	return 1;
}




////////////// 记住树的根不是 root 而是 root->leftChild ///////////////////
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
	
	// 逆时针90度打印二叉树
	PrintBiTree(root, 0);


	printf("前序遍历：");
	PreOrder(root->leftChild, visit);
	
	printf("\n中序遍历：");
	InOrder(root->leftChild, visit);
	
	printf("\n后序遍历：");
	PostOrder(root->leftChild, visit);

	// 层次遍历会影响 root 的位置 ？？？？？？
	printf("\n层次遍历: ");
	//LevelOrder(root->leftChild);



	find = Search(root->leftChild, x);
	if (find != NULL)
		printf("\n\n数据元素%c在二叉树中\n", x);
	else 
		printf("\n\n数据元素%c不在二叉树中\n", x);

	
	printf ("二叉树结点：%d\n\n", NumOfNodes(root->leftChild));

	printf ("二叉树的深度：%d\n\n", HeightBiTree(root->leftChild) - 1);

	// 层次遍历会影响 root 的位置 ？？？？？？
	printf ("是否是完全二叉树：%d\n\n", CompleteBiTree(root->leftChild));

	Destroy(&root);
}



/////////////////////////////////////////////////////////////////////
/////////////// 线索二叉树的测试

/*

// 创建二叉树结点
ThreadBiNode * GetTreeNode (DataType item, ThreadBiNode *left, ThreadBiNode * right)
{
	ThreadBiNode *p;
	p = (ThreadBiNode *)malloc(sizeof(ThreadBiNode));
	p->data = item;
	p->leftChild = left;
	p->rightChild = right;
	return p;
}

// 测试用的中序遍历
void InOrder_ThreadBiNode(ThreadBiNode *root, void visit(int item))
{
	if (root != NULL)
	{
		InOrder_ThreadBiNode(root->leftChild, visit);
		visit(root->data);
		InOrder_ThreadBiNode(root->rightChild, visit);
	}
}
// 创建二叉树
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
	printf("线索二叉树中序遍历测试是否创建成功：");
	InOrder_ThreadBiNode(*root,  visit);
	printf("\n");
}

void mainj()
{
	ThreadBiNode *root;
	ThreadBiTree tree;
	MakeCharTree(&root);
	CreatInThread(&root);
	printf("二叉树中序正向遍历序列为：");
	ThreadInitiate(&tree, root);
	for (First(&tree); !EndOfNext(&tree); Next(&tree))
		printf("%c, ", tree.current->data);
}


*/