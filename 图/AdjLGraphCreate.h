
typedef struct
{
	int row;  // ���±� 
	int col;  // ���±�
} RowCol;     // ����Ϣ�ṹ��


// ������ n ������ e ���ߵ�ͼ G 
// ������Ϣ�������� v �У�����Ϣ��������� d ��
void CreateGraph(AdjLGraph * G, int v[], int n, RowCol d[], int e)
{
	AdjInitiate(G);
	for (int i = 0; i < n; i++)
		InsertVertex(G, i , v[i]);         // ���붥��
	for (int k = 0; k < e; k++)
		InsertEdge(G, d[k].row, d[k].col); // �����
}



