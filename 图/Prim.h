
typedef int VerT;            // 定义顶点的数据类型为 int

typedef struct
{
	VerT vertex;   // 保存最小生成树每条边的弧头顶点数据
	int weight;   // 保存最小生成树的相对应边的权值
} MinSpanTree;


// 建立带权图 G 的最小生成树 closeVertex
void Prim(AdjMGraph G, MinSpanTree closeVertex[])
{
	VerT x;
	int n = G.Vertices.size;   // 顶点个数
	int minCost;

	int *lowCost = (int *)malloc(sizeof(int) * n);  // 临时数组

	for (int i = 1; i < n; i++)
		lowCost[i] = G.edge[0][i];      // 初始化

	// 从顶点0出发构造最小生成树
	ListGet(G.Vertices, 0, &x);     // 取顶点 0
	closeVertex[0].vertex = x;      // 保存顶点
	lowCost[0] = -1;                // 标记顶点

	int k;
	for (int i = 1; i < n; i++)
	{
		// 寻找当前最小权值的边所对应的弧头顶点 k
		minCost = MaxWeight;
		for (int j = 1; j < n; j++)
		{
			if (lowCost[j] < minCost && lowCost[j] > 0)
			{
				minCost = lowCost[j];
				k = j;
			}
		}
		ListGet(G.Vertices, k, &x);     // 取弧头顶点 k
		closeVertex[i].vertex = x;      // 保存弧头顶点 k 
		closeVertex[i].weight = minCost;// 保存相应的权值
		lowCost[k] = -1;                // 标记顶点 k

		// 根据加入集合 U 的顶点 k 修改 lowCost 中的数值
		for (int j = 1; j < n; j++)
		{
			if (G.edge[k][j] < lowCost[j])
				lowCost[j] = G.edge[k][j];
		}
	}
}
