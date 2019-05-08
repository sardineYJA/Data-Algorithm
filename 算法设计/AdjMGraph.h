//
/////////////////////// �ڽӾ���  �洢�ṹ��ͼ���� /////////////////////////
//
//#define MaxVertices 100         // ���嶥������ֵ
//#define MaxWeight 100           // �������Ȩֵ
//
//typedef struct
//{
//	SeqList Vertices;                       // ��Ŷ����˳���
//	int edge[MaxVertices][MaxVertices];     // ��űߵ��ڽӾ�������ֵΪ���㣬����ֵΪ�ߵ�Ȩֵ
//	int numOfEdges;                         // �ߵ�����
//} AdjMGraph;
//
//
//// ��ʼ����n�������˳�����ڽӾ���
//void Initiate(AdjMGraph * G, int n)
//{
//	int i, j;
//	for (i = 1; i <= 88; i++)
//		for (j = 1; j <= 88; j++)
//		{
//			if (i == j)
//				G->edge[i][j] = 0;
//			else
//				G->edge[i][j] = MaxWeight;
//		}
//
//	G->numOfEdges = 0;               // ����
//	ListInitiate(&G->Vertices);      // ˳����ʼ��
//}
//
//
//// ���붥��vertex
//void InsertVertex(AdjMGraph * G, int vertex)
//{
//	ListInsert(&G->Vertices, G->Vertices.size, vertex);    // ��˳���β���붥��
//}
//
//// ����һ������ߣ���������һ������ߣ���ͨ������������������
//void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
//{
//	G->edge[v1][v2] = weight;
//	G->numOfEdges++;
//}
//
//// v��ֵ
//int GetFirstVex(AdjMGraph G, int v)
//{
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j<= 8; j++)
//		if (G.edge[v][i+j] > 0 && G.edge[v][i+j] < MaxWeight)
//			return i+j;
//	}
//	return -1;
//}
//
//// v��ֵ
//int GetNextVex(AdjMGraph G, int v1, int v2)
//{
//	int x = v2/10;
//	int y = v2%10;
//
//	for (int i = x*10; i >= 10; i=i-10)
//	{
//		for (int j = y+1; j<= 8; j++)
//		{
//			if (G.edge[v1][i+j] > 0 && G.edge[v1][i+j] < MaxWeight)
//			return i+j;
//		}
//	}
//	return -1;
//}
