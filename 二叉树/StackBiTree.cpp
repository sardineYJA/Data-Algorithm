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
///*  �������
//��1����ʼ������һ����ջ��
//��2���Ѹ����ָ����ջ��
//��3������ջ�ǿ�ʱ��ѭ��ִ�в��裨3.a�������裨3.c��
//    ��3.a��ȡջ�������ʸý�㣻
//    ��3.b�����ý����������ǿգ����������������ջ��
//    ��3.c�����ý����������ǿգ����������������ջ��
//��4��������
//
//*/
//void Pre_Order(BiTreeNode *t, void visit(int item)){
///*ʹ��visit()�����ǵݹ�ǰ�����������t*/
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
///*ʹ��visit()�����ǵݹ��������������t*/
//    SeqStack s;
//    BiTreeNode *p=t;
//
//    if(t==NULL) return;
//
//	StackInitiate(&s);
//	while (p != NULL || StackNotEmpty(s)) {
//		while (p != NULL) { /*һֱ������*/
//			StackPush(&s, *p); /*���������ջ*/
//			p = p->leftChild;
//		}
//		if (StackNotEmpty(s)) {
//			StackPop(&s, p); /*ȡ��ջ����������*/
//			visit(p->data);
//			p = p->rightChild; /*ת��������������б���*/
//		}
//	}
//}
//
//void Post_Order(BiTreeNode *t, void visit(int item)){
///*ʹ��visit()�����ǵݹ�������������t*/
//    SeqStack s;
//    BiTreeNode *p=t, *q;
//
//    if(t==NULL) return;
//
//	StackInitiate(&s);
//	while (p != NULL || StackNotEmpty(s)) {
//		while (p != NULL){ /*������Ҳ�������*/
//			StackPush(&s, *p); /*���������ջ*/
//			if (p->leftChild != NULL)
//				p = p->leftChild;
//			else
//				p = p->rightChild;
//		}
//		if (StackNotEmpty(s)) {
//			StackPop(&s, p); /*ȡ��ջ����������*/
//			visit(p->data);
//		}
//		while (StackNotEmpty(s) && StackTop(s, q) && p == q->rightChild){  ////////////////////////////////////// ?????????????q
//		/*��������ʱ��˵��ջ���������������ѱ�����Ӧȡ��ջ������*/
//			StackPop(&s, p);
//			visit(p->data);
//		}
//		/*ת��ջ�����������������������*/
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
//��1����ʼ������һ�����У�
//��2���Ѹ����ָ������У�
//��3�������зǿ�ʱ��ѭ��ִ�в��裨3.a�������裨3.c����
//    ��3.a��������ȡ��һ�����ָ�룬���ʸý�㣻
//    ��3.b�����ý����������ǿգ��򽫸ý���������ָ������У�
//    ��3.c�����ý����������ǿգ��򽫸ý���������ָ������У�
//��4��������
//*/
//
//
//void LevelOrder(BiTreeNode *t, void visit(int item)){
///*�������*/
//
//
//}
//
//BiTreeNode* search(BiTreeNode *t, int x) {
//	BiTreeNode *p = NULL;
//	if (t == NULL)
//		return NULL;
//	/*����Ǹ���㣬���ظ�*/
//	if (t->data == x)
//		return t;
//	/*����������������*/
//	p = search(t->leftChild, x);
//	/*û�ҵ���������������*/
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
