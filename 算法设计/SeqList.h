

//#define MaxSize 100
//
//typedef struct
//{
//	int list[MaxSize];
//	int size;          // ����
//} SeqList;
//
//
//// ��ʼ��
//void ListInitiate(SeqList * L)
//{
//	L->size = 0;
//}
//
//// ��Ԫ�ظ���
//int ListLength(SeqList L)
//{
//	return L.size;
//}
//
//// ����Ԫ�� x
//int ListInsert(SeqList * L, int i, int x)
//{
//	if (L->size >= MaxSize)
//	{
//		printf("˳��������޷�����!\n");
//		return 0;
//	}
//	else if (i < 0 || i> L->size)
//	{
//		printf("���� i ���Ϸ���\n");
//		return 0;
//	}
//	else
//	{
//		// �Ӻ���ǰ���κ������ݣ�Ϊ������׼��
//		for (int j = L->size; j > i; j--)
//			L->list[j] = L->list[j-1];
//		L->list[i] = x;
//		L->size++;
//		return 1;
//	}
//}
//
//
//// ɾ������
//int ListDelete(SeqList *L, int i, int *x)
//{
//	if (L->size <= 0)
//	{
//		printf("˳�����Ϊ�գ������ݿ�ɾ����\n");
//		return 0;
//	}
//	else if (i < 0 || i > L->size-1)
//	{
//		printf("���� i ���Ϸ���\n");
//		return 0;
//	}
//	else
//	{
//		*x = L->list[i];    // ����Ҫɾ��Ԫ��
//
//		// ��ǰ�������ǰ��
//		for (int j = i+1; j <= L->size-1; j++)
//			L->list[j-1] = L->list[j];
//		L->size--;
//		return 1;
//	}
//}
//
//
//// ȡ������
//int ListGet(SeqList L, int i, int *x)
//{
//	if (i < 0 || i > L.size-1)
//	{
//		printf("���� i ���Ϸ���\n");
//		return 0;
//	}
//	else
//	{
//		*x = L.list[i];   
//		return 1;
//	}
//}
//
//
