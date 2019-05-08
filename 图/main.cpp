

#include <stdio.h>
#include <stdlib.h>

#include "SeqList.h"
#include "SeqStack.h"       // 非递归的深度遍历
#include "SeqCQueue.h"      // 广度遍历

#include "AdjMGraph.h"             // 邻接矩阵
#include "AdjMGraphCreate.h" 

#include "AdjLGraph.h"             // 邻接表
#include "AdjLGraphCreate.h"

#include "DepthSearch.h"     // 深度遍历
#include "BroadSearch.h"     // 广度遍历

#include "Prim.h"     // 最小生成树的Prim算法

void Visit(int item)
{
	printf("%c  ", item);
}


// 邻接矩阵
void mainzzz()
{
	AdjMGraph g;
	int a[] = { 'A', 'B', 'C', 'D', 'E'};
	RowColWeight rcw[] = {{0,1,10}, {0,4,20}, {1,3,30}, {2,1,40}, {3,2,50}};

	int n = 5, e = 5;
	CreateGraph(&g, a, n, rcw, e);
	//DeleteEdge(&g, 0, 4);
	//DeleteEdge(&g, 1, 3);
	//InsertEdge(&g, 1, 0, 20);


	printf("顶点集合为：");
	for (int i = 0; i < g.Vertices.size; i++)
		printf("%c ", g.Vertices.list[i]);
	printf("\n");

	printf("权值集合为：\n");
	for (int i = 0; i < g.Vertices.size; i++)
	{
		for (int j = 0; j < g.Vertices.size; j++)
			printf("%5d   ", g.edge[i][j]);
		printf("\n");
	}

	printf("\n深度优先遍历：");
	DepthFirstSearch(g, Visit);
	printf("\n");

	printf("\n广度优先遍历：");
	BroadFirstSearch(g, Visit);
	printf("\n");

	printf("\n广度遍历各个顶点的出度和入度：\n");
	BroadFirstSearchDegree(g);
	printf("\n");

	printf("判断 v1 到 v2 是否存在路径：\n");
	DepthFirstSearchPath(g, 0, 2);
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////


// 邻接表
void mainLLLLLLLLL()
{
	AdjLGraph g;
	int a[] = { 'L', 'M', 'N', 'O', 'P'};
	RowCol rc[] = {{1,2}, {2,3}, {2,4}, {3,2}, {3,4}};
	int n = 5, e = 5;
	CreateGraph(&g, a, n, rc, e);

	printf("顶点集合为：");
	for (int i = 0; i < g.numOfVerts; i++)
		printf("%c ", g.a[i].data);
	printf("\n");

	printf("权值集合为：\n");
	for (int i = 0; i < g.numOfVerts; i++)
	{
		
	}
}
//////////////////////////////////////////////////////////////////////////////////////



// 最小生成树
void maintttt()
{
	AdjMGraph g;
	int a[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

	RowColWeight rcw[] = {{0,1,50}, {1,0,50}, {0,2,60}, {2,0,60}, {1,3,65}, {3,1,65}, 
						  {1,4,40}, {4,1,40}, {2,3,52}, {3,2,52}, {2,6,45}, {6,2,45}, 
	                      {3,4,50}, {4,3,50}, {3,5,30}, {5,3,30}, {3,6,42}, {6,3,42},
	                      {4,5,70}, {5,4,70}};

	int n = 7;     // 7个顶点
	int e = 20;    // 20条边
	MinSpanTree closeVertex[7];     // 定义保存最小生成树的数组
	CreateGraph(&g, a, n, rcw, e);  // 创建图
	Prim(g, closeVertex);

	// 输出最小生成树的顶点序列和权值序列
	printf("初始顶点 = %c\n", closeVertex[0].vertex);
	for (int i = 1; i < n; i++)
		printf("顶点 = %c 边的权值 = %d\n", closeVertex[i].vertex, closeVertex[i].weight);
}
/////////////////////////////////////////////////////////////////////////////////////////////




//// 狄克斯特拉Dijkstra算法——找特定某个点到其他点的最短路径
/*
集合 S 存放已经找到最短路径的顶点
集合 T 存放当前还未找到最短路径的顶点

初始状态，集合只包含 v0,
集合 S 中每加一个新的顶点 u, 都要修改 v0 到集合 T 中剩余顶点的当前最短路径长度值
集合 T 中各顶点新的当前最短路径长度值 ＝ min（原来的当前最短路径长度值， 从源点 v0 经过顶点 u 到达该顶点的路径长度）
循环，直至集合 T 中的顶点全部加入到集合 S 中
*/

// 带权图 G 从下标 v0 顶点到其他顶点的最短距离 distance 和 最短路径下标 path

// path[j] = u;   // j 就是下一个的点，而用值(即u)来保存它，已达到路径的连接

void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
{
	int n = G.Vertices.size;
	int *s = (int *)malloc(sizeof(int) * n); // 集合 S
	int minDis, u;

	// 初始化
	for (int i = 0; i < n; i++)
	{
		distance[i] = G.edge[v0][i];
		s[i] = 0;
		if (i != v0 && distance[i] < MaxWeight)
			path[i] = v0;
		else 
			path[i] = -1;
	}

	s[v0] = 1; // 标记顶点 v0 已从集合 T 加入到集合 S 中

	// 在当前还未找到最短路径的顶点集中选取具有最短距离的顶点 u
	for (int i = 1; i < n; i++)
	{
		minDis = MaxWeight;
		for (int j = 0; j < n; j++)
			if (s[j] == 0 && distance[j] < minDis)
			{
				u = j;
				minDis = distance[j];
			}

		// 当已不再存在路径时，算法结束。此语句对非连通图是必须的
		if (minDis == MaxWeight) 
			return;
		s[u] = 1;    // 标记顶点 u 已从集合 T 加入到集合 S 中

		// 修改从 v0 到其他顶点的最短距离和最短路径
		for (int j = 0; j < n; j++)
			if (s[j] == 0 && G.edge[u][j] < MaxWeight && distance[u] + G.edge[u][j] < distance[j])
			{
				// 顶点 v0 经顶点 u 到其他顶点的最短距离和最短路径
				distance[j] = distance[u] + G.edge[u][j];
				path[j] = u;
			}
	}
}

void main11()
{
	AdjMGraph g;
	int a[] = {'A', 'B', 'C', 'D', 'E', 'F'};

	RowColWeight rcw[] = {{0,2,5}, {0,3,30}, {1,0,2}, {1,4,8}, 
						{2,1,15}, {2,5,7}, {4,3,4}, {5,3,10}, {5,4,18}};
	int n = 6;  // 顶点个数
	int e = 9;  // 边条数

	int distance[6];
	int path[6];
	CreateGraph(&g, a, n, rcw, e);

	/////////// Dijkstra算法求最短路径
	Dijkstra(g, 0, distance, path);  

	printf("从顶点 %c 到其他顶点的最短路径为：\n", g.Vertices.list[0]);
	for (int i = 0; i  < n; i++)
		printf("到顶点 %c 的最短路径为 %d \n", g.Vertices.list[i], distance[i]);

	printf("从顶点 %c 到其他各顶点最短路径的前一顶点为：\n", g.Vertices.list[0]);
	for(int i = 0; i < n; i++)
		if (path[i] != -1)
			printf("到顶点 %c 的前一顶点为 %c \n", g.Vertices.list[i], g.Vertices.list[path[i]]);
}
//////////////////////////////////////////////////////////////////////////////////////////


/*
两个算法的有向图： 
  
A --> C    5
C --> B    15
C --> F    7
B --> A    2
B --> E    8
E --> D    4
F --> D    10
F --> E    18


*/


//// 弗洛伊德Floyd算法——找到每个点之间的最短距离
/*
N : 图的顶点个数
cost[][N] ： 存放带权图G的权值
weight[i][j] : 顶点i 与顶点j 之间最短路径(二维数组的值)
path[i][j] = k : 顶点 i 到顶点j 的路径的前一个顶点 k (二维数组的值)，即中介
*/
#define N 6
void Floyd(int cost[][N], int n, int weight[][N], int path[][N])
{
	// 初始化
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			weight[i][j] = cost[i][j];
			path[i][j] = -1;
		}
	}

	// n 次递推
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (weight[i][j] > weight[i][k] + weight[k][j])   // k 点做中介
				{
					// 得到新的最短路径长度数值
					weight[i][j] = weight[i][k] + weight[k][j];
					// 得到该最短路径的经过的顶点序列
					path[i][j] = k;
				}
			}
		}
	}
}


void mainrt()
{
	AdjMGraph g;
	int a[] = {'A', 'B', 'C', 'D', 'E', 'F'};

	RowColWeight rcw[] = {{0,2,5}, {0,3,30}, {1,0,2}, {1,4,8}, 
						{2,1,15}, {2,5,7}, {4,3,4}, {5,3,10}, {5,4,18}};
	int n = 6;  // 顶点个数
	int e = 9;  // 边条数
	CreateGraph(&g, a, n, rcw, e);


	int weight[N][N];
	int path[N][N];
	int cost[N][N];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cost[i][j] = g.edge[i][j];
	

	////////////// Floyd算法求最短路径
	Floyd(cost, n, weight, path);

	// 打印出结果
	printf("weight = \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5d", weight[i][j]);
		}
		printf("\n");
	}

	printf("\npath = \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5d", path[i][j]);
		}
		printf("\n");
	}
}
//////////////////////////////////////////////////////////////////////////////////




