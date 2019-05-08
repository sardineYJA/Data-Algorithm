
typedef int VerT;            // ���嶥�����������Ϊ int

typedef struct
{
	VerT vertex;   // ������С������ÿ���ߵĻ�ͷ��������
	int weight;   // ������С�����������Ӧ�ߵ�Ȩֵ
} MinSpanTree;


// ������Ȩͼ G ����С������ closeVertex
void Prim(AdjMGraph G, MinSpanTree closeVertex[])
{
	VerT x;
	int n = G.Vertices.size;   // �������
	int minCost;

	int *lowCost = (int *)malloc(sizeof(int) * n);  // ��ʱ����

	for (int i = 1; i < n; i++)
		lowCost[i] = G.edge[0][i];      // ��ʼ��

	// �Ӷ���0����������С������
	ListGet(G.Vertices, 0, &x);     // ȡ���� 0
	closeVertex[0].vertex = x;      // ���涥��
	lowCost[0] = -1;                // ��Ƕ���

	int k;
	for (int i = 1; i < n; i++)
	{
		// Ѱ�ҵ�ǰ��СȨֵ�ı�����Ӧ�Ļ�ͷ���� k
		minCost = MaxWeight;
		for (int j = 1; j < n; j++)
		{
			if (lowCost[j] < minCost && lowCost[j] > 0)
			{
				minCost = lowCost[j];
				k = j;
			}
		}
		ListGet(G.Vertices, k, &x);     // ȡ��ͷ���� k
		closeVertex[i].vertex = x;      // ���满ͷ���� k 
		closeVertex[i].weight = minCost;// ������Ӧ��Ȩֵ
		lowCost[k] = -1;                // ��Ƕ��� k

		// ���ݼ��뼯�� U �Ķ��� k �޸� lowCost �е���ֵ
		for (int j = 1; j < n; j++)
		{
			if (G.edge[k][j] < lowCost[j])
				lowCost[j] = G.edge[k][j];
		}
	}
}
