//
//typedef struct 
//{
//	int row;       // ���±�
//	int col;       // ���±�
//	int weight;    // Ȩֵ
//} RowColWeight;    // ����Ϣ�ṹ�嶨��
//
//
//// ��ͼ G �в��� n ��������Ϣ V �� e ������Ϣ E
//void CreateGraph(AdjMGraph * G, int V[], int n, RowColWeight E[], int e)
//{
//	Initiate(G, n);      // ����˳����ʼ��
//	for (int i = 0; i < n; i++)
//		InsertVertex(G, V[i]);    // ���붥��
//
//	for (int k = 0; k < e; k++)
//		InsertEdge(G, E[k].row, E[k].col, E[k].weight);  // �����
//}
//
