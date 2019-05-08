#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxVertices 100         // 定义顶点的最大值
#define MaxWeight 100           // 定义最大权值
#define MaxSize 100             // 顺序表最大值

////////////////////////////////// 顺序表的存储和操作//////////////////////////////////////
typedef struct
{
	int list[MaxSize];
	int size;     
} SeqList;

// 初始化
void ListInitiate(SeqList * L)
{
	L->size = 0;
}

// 求元素个数
int ListLength(SeqList L)
{
	return L.size;
}

// 插入元素 x
int ListInsert(SeqList * L, int i, int x)
{
	if (L->size >= MaxSize)
	{
		printf("顺序表已满无法插入!\n");
		return 0;
	}
	else if (i < 0 || i> L->size)
	{
		printf("参数 i 不合法！\n");
		return 0;
	}
	else
	{
		// 从后向前依次后移数据，为插入做准备
		for (int j = L->size; j > i; j--)
			L->list[j] = L->list[j-1];
		L->list[i] = x;
		L->size++;
		return 1;
	}
}

// 取出数据
int ListGet(SeqList L, int i, int *x)
{
	if (i < 0 || i > L.size-1)
	{
		printf("参数 i 不合法！\n");
		return 0;
	}
	else
	{
		*x = L.list[i];   
		return 1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////// 图的存储结构和操作//////////////////////////////////////
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
	for (i = 1; i <= 88; i++)
		for (j = 1; j <= 88; j++)
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

// 插入一条有向边
void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
{
	G->edge[v1][v2] = weight;
	G->numOfEdges++;
}

// 得到第一个邻接点的值
int GetFirstVex(AdjMGraph G, int v)
{
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j<= 8; j++)
		if (G.edge[v][i+j] > 0 && G.edge[v][i+j] < MaxWeight)
			return i+j;
	}
	return -1;
}

// 得到下一个邻接的值
int GetNextVex(AdjMGraph G, int v1, int v2)
{
	int x = v2/10;
	int y = v2%10;

	for (int i = x*10; i >= 10; i=i-10)
	{
		for (int j = y+1; j<= 8; j++)
		{
			if (G.edge[v1][i+j] > 0 && G.edge[v1][i+j] < MaxWeight)
			return i+j;
		}
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// 创建无向图 ///////////////////////////////////
typedef struct 
{
	int row;       // 行下标
	int col;       // 列下标
	int weight;    // 权值
} RowColWeight;    // 边信息结构体定义

// 在图 G 中插入 n 个顶点信息 V 和 e 条边信息 E
void CreateGraph(AdjMGraph * G, int V[], int n, RowColWeight E[], int e)
{
	Initiate(G, n);      // 顶点顺序表初始化
	for (int i = 0; i < n; i++)
		InsertVertex(G, V[i]);    // 插入顶点

	for (int k = 0; k < e; k++)
		InsertEdge(G, E[k].row, E[k].col, E[k].weight);  // 插入边
}
//////////////////////////////////////////////////////////////////////////////////

// 输出元素函数
void Visit(int item)
{
	printf("%d  ", item);
}

// 狄克斯特拉Dijkstra算法
void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
{
	int *s = (int *)malloc(sizeof(int) * 89); // 集合 S
	int minDis, u;

	// 初始化
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j <= 8; j++)
		{
			distance[i+j] = G.edge[v0][i+j];
			s[i+j] = 0;    // 标记顶点 i 未从集合 T 加入到集合 S 中

			if ((i+j) != v0 && distance[i+j] < MaxWeight)
				path[i+j] = v0;
			else 
				path[i+j] = -1;
		}
	}

	s[v0] = 1; // 标记顶点 v0 已从集合 T 加入到集合 S 中

	// 在当前还未找到最短路径的顶点集中选取具有最短距离的顶点 u
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j <= 8; j++)
		{
			minDis = MaxWeight;
			for (int x = 80; x >= 10; x=x-10)
			{
				for (int y = 1; y <= 8; y++)
				{
					if (s[x+y] == 0 && distance[x+y] < minDis)
					{
						u = x+y;
						minDis = distance[x+y];
					}
				}
			}

			// 当已不再存在路径时，算法结束。此语句对非连通图是必须的
			if (minDis == MaxWeight) 
				return;
			s[u] = 1;    // 标记顶点 u 已从集合 T 加入到集合 S 中

			// 修改从 v0 到其他顶点的最短距离和最短路径
			for (int x = 80; x >= 10; x=x-10)
			{
				for (int y = 1; y <= 8; y++)
				{
					if (s[x+y] == 0 && G.edge[u][x+y] < MaxWeight && 
						distance[u] + G.edge[u][x+y] < distance[x+y])
					{
						// 顶点 v0 经顶点 u 到其他顶点的最短距离和最短路径
						distance[x+y] = distance[u] + G.edge[u][x+y];
						path[x+y] = u;
					}
				}
			}
		}
	}
}

// 将数字转换成字符串
void IntToChar(char * ch, int n)
{
	ch[0] = (char)(n%10 + 96);
	ch[1] = (char)(n/10 + 48);
	ch[2] = '\0';
}

void main()
{
	AdjMGraph g;   
	//////// 共 8*8 个点
	int n = 64;        
	int v[] = 
	{
		81, 82, 83, 84, 85, 86, 87, 88,
		71, 72, 73, 74, 75, 76, 77, 78,
		61, 62, 63, 64, 65, 66, 67, 68,
		51, 52, 53, 54, 55, 56, 57, 58,
		41, 42, 43, 44, 45, 46, 47, 48,
		31, 32, 33, 34, 35, 36, 37, 38,
		21, 22, 23, 24, 25, 26, 27, 28,
		11, 12, 13, 14, 15, 16, 17, 18
	};

	//////// 64个点每个点最多8条边，无向图双向边
	RowColWeight rcw[64*8*2];    
	int edge_num = 0; // 边数
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j <=8; j++)
		{
			// 首先是 i+j 点 的边
			for (int x = 80; x >= 10; x=x-10)
			{
				for (int y = 1; y <= 8; y++)
				{
					// 根据马走日建立边
					if ( (i != x)&& (j != y) &&
						((abs(i-x)/10 + abs(j-y)) == 3) )
					{
						// 以i+j为建立与他相连的点
						
						rcw[edge_num].col = i+j;  // 行下标
						rcw[edge_num].row = x+y;  // 列下标
						rcw[edge_num].weight = 1; // 权值 
						edge_num++;
				
						rcw[edge_num].col = x+y;  // 行下标
						rcw[edge_num].row = i+j;  // 列下标				
						rcw[edge_num].weight = 1; // 权值 
						edge_num++;
					}
				}
			}
		}
	}

	// 建立无向图
	CreateGraph(&g, v, n, rcw, edge_num); 
	int distance[100];
	int path[100];
	int start = 11;
	int end = 88;
	char v0[10];    // 起点
	char v1[10];    // 终点

	printf("输入起点(如：a1)：");
	scanf("%s", &v0);
	printf("输入重点(如：b1)：");
	scanf("%s", &v1);

	if (97 <= v0[0] && v0[0]<= 104 && 97 <= v1[0] && v1[0]<= 104
		&& 49 <= v0[1] && v0[1]<= 56 && 49 <= v1[1] && v1[1]<= 56 
		&& v0[2]=='\0' && v1[2] == '\0')
	{
		// 将字符串转为数字
		start = (v0[0]-96) + (v0[1]-48)*10;
		end = (v1[0]-96) + (v1[1]-48)*10;
	}
	else
	{
		printf("输入不符合要求!\n");
		return;
	}

	Dijkstra(g, start, distance, path);  
	// 输出路径
	printf("\n顶点 %s 到 %s 之间的步数：%d \n", v0, v1, distance[end]);
	printf("路径：");
	int temp = end;
	char ch[3];
	printf("%s", v1);
	while (temp != start)
	{
		IntToChar(ch, path[temp]);
		printf(" <-- %s", ch);
		temp = path[temp];
	}
	printf("\n\n");
}
