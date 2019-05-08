//
/////////////////////// 邻接矩阵  存储结构下图操作 /////////////////////////
//
//#define MaxVertices 100         // 定义顶点的最大值
//#define MaxWeight 100           // 定义最大权值
//
//typedef struct
//{
//	SeqList Vertices;                       // 存放顶点的顺序表
//	int edge[MaxVertices][MaxVertices];     // 存放边的邻接矩阵，两个值为顶点，数组值为边的权值
//	int numOfEdges;                         // 边的条数
//} AdjMGraph;
//
//
//// 初始化有n个顶点的顺序表和邻接矩阵
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
//	G->numOfEdges = 0;               // 边数
//	ListInitiate(&G->Vertices);      // 顺序表初始化
//}
//
//
//// 插入顶点vertex
//void InsertVertex(AdjMGraph * G, int vertex)
//{
//	ListInsert(&G->Vertices, G->Vertices.size, vertex);    // 在顺序表尾插入顶点
//}
//
//// 插入一条有向边，对于增加一条无向边，可通过增加两条有向边完成
//void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
//{
//	G->edge[v1][v2] = weight;
//	G->numOfEdges++;
//}
//
//// v是值
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
//// v是值
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
