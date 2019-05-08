//
//typedef struct 
//{
//	int row;       // 行下标
//	int col;       // 列下标
//	int weight;    // 权值
//} RowColWeight;    // 边信息结构体定义
//
//
//// 在图 G 中插入 n 个顶点信息 V 和 e 条边信息 E
//void CreateGraph(AdjMGraph * G, int V[], int n, RowColWeight E[], int e)
//{
//	Initiate(G, n);      // 顶点顺序表初始化
//	for (int i = 0; i < n; i++)
//		InsertVertex(G, V[i]);    // 插入顶点
//
//	for (int k = 0; k < e; k++)
//		InsertEdge(G, E[k].row, E[k].col, E[k].weight);  // 插入边
//}
//
