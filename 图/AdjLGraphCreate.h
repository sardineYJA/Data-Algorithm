
typedef struct
{
	int row;  // 行下标 
	int col;  // 列下标
} RowCol;     // 边信息结构体


// 创建有 n 个顶点 e 条边的图 G 
// 顶点信息存在数组 v 中，边信息存放在数组 d 中
void CreateGraph(AdjLGraph * G, int v[], int n, RowCol d[], int e)
{
	AdjInitiate(G);
	for (int i = 0; i < n; i++)
		InsertVertex(G, i , v[i]);         // 插入顶点
	for (int k = 0; k < e; k++)
		InsertEdge(G, d[k].row, d[k].col); // 插入边
}



