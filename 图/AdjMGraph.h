
///////////////////// �ڽӾ���  �洢�ṹ��ͼ���� /////////////////////////

#define MaxVertices 10         // ���嶥������ֵ
#define MaxWeight 100          // �������Ȩֵ

typedef struct
{
	SeqList Vertices;                       // ��Ŷ����˳���
	int edge[MaxVertices][MaxVertices];     // ��űߵ��ڽӾ�������ֵΪ���㣬����ֵΪ�ߵ�Ȩֵ
	int numOfEdges;                         // �ߵ�����
} AdjMGraph;


// ��ʼ����n�������˳�����ڽӾ���
void Initiate(AdjMGraph * G, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (i == j)
				G->edge[i][j] = 0;
			else
				G->edge[i][j] = MaxWeight;
		}

	G->numOfEdges = 0;               // ����
	ListInitiate(&G->Vertices);      // ˳����ʼ��
}


// ���붥��vertex
void InsertVertex(AdjMGraph * G, int vertex)
{
	ListInsert(&G->Vertices, G->Vertices.size, vertex);    // ��˳���β���붥��
}

// ����һ������ߣ���������һ������ߣ���ͨ������������������
void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
{
	if (v1 < 0 || v1 >= G->Vertices.size || v2 < 0 || v2 >= G->Vertices.size)
	{
		printf ("����v1��v2Խ�����\n");
		return;
	}
	G->edge[v1][v2] = weight;
	G->numOfEdges++;
}


// ȡ��һ������ߣ�����ȡ��һ������ߣ���ͨ��ȡ������
void DeleteEdge(AdjMGraph * G, int v1, int v2)
{
	if (v1 < 0 || v1 >= G->Vertices.size || v2 <0 || v2 >= G->Vertices.size || v1 == v2)
	{
		printf("����v1��v2����\n");
		return;
	}
	if (G->edge[v1][v2] == MaxWeight || v1 == v2)
	{
		printf("�ñ߲����ڣ�\n");
		return;
	}
	G->edge[v1][v2] = MaxWeight;
	G->numOfEdges--;
}



// ��ͼG ��Ѱ�����Ϊv �Ķ���ĵ�һ���ڽӶ���
// ����������ڽӶ�����ڣ��򷵻ظ��ڽӶ������ţ����򷵻�-1
int GetFirstVex(AdjMGraph G, int v)
{
	if (v < 0 || v >= G.Vertices.size)
	{
		printf("���� v1 Խ�����\n");
		return -1;
	}
	for (int col = 0; col < G.Vertices.size; col++)
		if (G.edge[v][col] > 0 && G.edge[v][col] < MaxWeight)
			return col;
	return -1;
}

// ��ͼG ��Ѱ��v1 ������ڽӶ���v2 ����һ���ڽӶ���
// ����������ڽӶ�����ڣ��򷵻ظ��ڽӶ������ţ����򷵻�-1
// v1 �� v2 ������Ӧ��������
int GetNextVex(AdjMGraph G, int v1, int v2)
{
	if (v1 < 0 || v1 >= G.Vertices.size || v2 < 0 || v2 >= G.Vertices.size)
	{
		printf("����v1��v2Խ�����\n");
		return -1;
	}
	for (int col = v2+1; col < G.Vertices.size; col++)
		if (G.edge[v1][col] > 0 && G.edge[v1][col] < MaxWeight)
			return col;
	return -1;
}






