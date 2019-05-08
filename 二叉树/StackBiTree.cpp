//
//#include "BiTree.h"
//#include "SeqStack.h"
//
//#include "SeqCQueue.h"
//
//
//void visit(int item) {
//	printf("%c ", item);
//}
//
///*  先序遍历
//（1）初始化设置一个堆栈；
//（2）把根结点指针入栈；
//（3）当堆栈非空时，循环执行步骤（3.a）到步骤（3.c）
//    （3.a）取栈顶，访问该结点；
//    （3.b）若该结点的右子树非空，则右子树根结点入栈；
//    （3.c）若该结点的左子树非空，则左子树根结点入栈；
//（4）结束。
//
//*/
//void Pre_Order(BiTreeNode *t, void visit(int item)){
///*使用visit()函数非递归前序遍历二叉树t*/
//	SeqStack s;
//	BiTreeNode *p = NULL;
//
//	if (t == NULL) 
//		return;
//	StackInitiate(&s);
//	StackPush(&s, *t);
//	while (StackNotEmpty(s)) {
//		StackPop(&s, p);
//		visit(p->data);
//		if (p->rightChild != NULL)
//			StackPush(&s, *p->rightChild);
//		if (p->leftChild != NULL)
//			StackPush(&s, *p->leftChild);
//	}
//}
//
//void In_Order(BiTreeNode *t, void visit(int item)){
///*使用visit()函数非递归中序遍历二叉树t*/
//    SeqStack s;
//    BiTreeNode *p=t;
//
//    if(t==NULL) return;
//
//	StackInitiate(&s);
//	while (p != NULL || StackNotEmpty(s)) {
//		while (p != NULL) { /*一直向左走*/
//			StackPush(&s, *p); /*将根结点入栈*/
//			p = p->leftChild;
//		}
//		if (StackNotEmpty(s)) {
//			StackPop(&s, p); /*取出栈顶根结点访问*/
//			visit(p->data);
//			p = p->rightChild; /*转向根的右子树进行遍历*/
//		}
//	}
//}
//
//void Post_Order(BiTreeNode *t, void visit(int item)){
///*使用visit()函数非递归后序遍历二叉树t*/
//    SeqStack s;
//    BiTreeNode *p=t, *q;
//
//    if(t==NULL) return;
//
//	StackInitiate(&s);
//	while (p != NULL || StackNotEmpty(s)) {
//		while (p != NULL){ /*先左后右不断深入*/
//			StackPush(&s, *p); /*将根结点入栈*/
//			if (p->leftChild != NULL)
//				p = p->leftChild;
//			else
//				p = p->rightChild;
//		}
//		if (StackNotEmpty(s)) {
//			StackPop(&s, p); /*取出栈顶根结点访问*/
//			visit(p->data);
//		}
//		while (StackNotEmpty(s) && StackTop(s, q) && p == q->rightChild){  ////////////////////////////////////// ?????????????q
//		/*条件满足时，说明栈顶根结点的右子树已遍历，应取出栈顶访问*/
//			StackPop(&s, p);
//			visit(p->data);
//		}
//		/*转向栈顶结点的右子树继续后序遍历*/
//		if (StackNotEmpty(s)) {
//			StackTop(s, q);
//			p = q->rightChild;
//		} else
//			p = NULL;
//	}
//}
//
//
///*
//（1）初始化设置一个队列；
//（2）把根结点指针入队列；
//（3）当队列非空时，循环执行步骤（3.a）到步骤（3.c）；
//    （3.a）出队列取得一个结点指针，访问该结点；
//    （3.b）若该结点的左子树非空，则将该结点的左子树指针入队列；
//    （3.c）若该结点的右子树非空，则将该结点的右子树指针入队列；
//（4）结束。
//*/
//
//
//void LevelOrder(BiTreeNode *t, void visit(int item)){
///*按层遍历*/
//
//
//}
//
//BiTreeNode* search(BiTreeNode *t, int x) {
//	BiTreeNode *p = NULL;
//	if (t == NULL)
//		return NULL;
//	/*如果是根结点，返回根*/
//	if (t->data == x)
//		return t;
//	/*否则在左子树中找*/
//	p = search(t->leftChild, x);
//	/*没找到，在右子树中找*/
//	if (p == NULL)
//		p = search(t->rightChild, x);
//	return p;
//}
//
//
//
//int NumofNodes(BiTreeNode *t) {
//	if (t == NULL)
//		return 0;
//	else
//		return NumofNodes(t->leftChild) + NumofNodes(t->rightChild) + 1;
//}
//
//int Height(BiTreeNode *t) {
//
//	return -1;
//}
//
//int Leafs(BiTreeNode *t) {
//	return -1;
//}
//
//int main(void)
//{
//    BiTreeNode *root, *p, *pp;
//    char x='Z';
//
//    Initiate(&root);
//    p = InsertLeftNode(root, 'A');
//    p = InsertLeftNode(p, 'B');
//    p = InsertLeftNode(p, 'D');
//    p = InsertRightNode(p, 'G');
//    p = InsertRightNode(root->leftChild, 'C');
//    pp = p;
//    InsertLeftNode(p, 'E');
//    InsertRightNode(pp, 'F');
//
//   
//    printf("\nPre_Order :");
//    Pre_Order(root->leftChild, visit);
//    printf("\n");
//
//    printf("\nIn_Order  :");
//    In_Order(root->leftChild, visit);
//    printf("\n");
//
//    printf("\nPost_Order:");
//    Post_Order(root->leftChild, visit);
//    printf("\n");
//
//    printf("\nLevelOrder:");
//    LevelOrder(root->leftChild, visit);
//    printf("\n");
//
//    p = search(root->leftChild,x);
//    if(p!=NULL) printf("\n%c \n", p->data);
//    else printf("\n%c is not found in the tree! \n",x);
//
//    printf("\nNumber of nodes:%d \n", NumofNodes(root->leftChild));
//    printf("\nThe height of tree is:%d \n", Height(root->leftChild));
//    printf("\nNumber of leafs:%d \n", Leafs(root->leftChild));
//
//    Destroy(&root);
//    return 1;
//}
