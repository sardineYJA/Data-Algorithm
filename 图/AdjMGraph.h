
///////////////////// 邻接矩阵  存储结构下图操作 /////////////////////////

#define MaxVertices 10         // 定义顶点的最大值
#define MaxWeight 100          // 定义最大权值

typedef struct
{
	SeqList Vertices;                       // 存放顶点的顺序表
	int edge[MaxVertices][MaxVertices];     // 存放边的邻接矩阵，两个值为顶点，数组值为边的权值
	int numOfEdges;                         // 边的条数
} AdjMGraph;


// 初始化有n个顶点的顺序表和邻接矩阵
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

	G->numOfEdges = 0;               // 边数
	ListInitiate(&G->Vertices);      // 顺序表初始化
}


// 插入顶点vertex
void InsertVertex(AdjMGraph * G, int vertex)
{
	ListInsert(&G->Vertices, G->Vertices.size, vertex);    // 在顺序表尾插入顶点
}

// 插入一条有向边，对于增加一条无向边，可通过增加两条有向边完成
void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
{
	if (v1 < 0 || v1 >= G->Vertices.size || v2 < 0 || v2 >= G->Vertices.size)
	{
		printf ("参数v1或v2越界出错！\n");
		return;
	}
	G->edge[v1][v2] = weight;
	G->numOfEdges++;
}


// 取消一条有向边，对于取消一条无向边，可通过取消两次
void DeleteEdge(AdjMGraph * G, int v1, int v2)
{
	if (v1 < 0 || v1 >= G->Vertices.size || v2 <0 || v2 >= G->Vertices.size || v1 == v2)
	{
		printf("参数v1或v2出错！\n");
		return;
	}
	if (G->edge[v1][v2] == MaxWeight || v1 == v2)
	{
		printf("该边不存在！\n");
		return;
	}
	G->edge[v1][v2] = MaxWeight;
	G->numOfEdges--;
}



// 在图G 中寻找序号为v 的顶点的第一个邻接顶点
// 如果这样的邻接顶点存在，则返回该邻接顶点的序号：否则返回-1
int GetFirstVex(AdjMGraph G, int v)
{
	if (v < 0 || v >= G.Vertices.size)
	{
		printf("参数 v1 越界出错！\n");
		return -1;
	}
	for (int col = 0; col < G.Vertices.size; col++)
		if (G.edge[v][col] > 0 && G.edge[v][col] < MaxWeight)
			return col;
	return -1;
}

// 在图G 中寻找v1 顶点的邻接顶点v2 的下一个邻接顶点
// 如果这样的邻接顶点存在，则返回该邻接顶点的序号，否则返回-1
// v1 和 v2 都是相应顶点的序号
int GetNextVex(AdjMGraph G, int v1, int v2)
{
	if (v1 < 0 || v1 >= G.Vertices.size || v2 < 0 || v2 >= G.Vertices.size)
	{
		printf("参数v1或v2越界出错！\n");
		return -1;
	}
	for (int col = v2+1; col < G.Vertices.size; col++)
		if (G.edge[v1][col] > 0 && G.edge[v1][col] < MaxWeight)
			return col;
	return -1;
}






