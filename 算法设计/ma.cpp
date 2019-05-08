//#define _CRT_SECURE_NO_WARNINGS
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//#include "SeqList.h"         // 存放顶点的顺序表
//#include "SeqCQueue.h"       // 广度遍历
//
//#include "AdjMGraph.h"       // 邻接矩阵
//#include "AdjMGraphCreate.h" // 创建图
//
//#include "DepthSearch.h"     // 深度遍历
//#include "BroadSearch.h"     // 广度遍历
//
///*
//
//8 □ ■ □ ■ □ ■ □ ■
//7 ■ □ ■ □ ■ □ ■ □
//6 □ ■ □ ■ □ ■ □ ■
//5 ■ □ ■ □ ■ □ ■ □
//4 □ ■ □ ■ □ ■ □ ■
//3 ■ □ ■ □ ■ □ ■ □
//2 □ ■ □ ■ □ ■ □ ■
//1 ■ □ ■ □ ■ □ ■ □
//  a  b  c  d  e  f  g  h
//
//
//*/
//
//void Visit(int item)
//{
//	printf("%d  ", item);
//}
//
//
//
////// 狄克斯特拉Dijkstra算法——找特定某个点到其他点的最短路径
///*
//集合 S 存放已经找到最短路径的顶点
//集合 T 存放当前还未找到最短路径的顶点
//
//初始状态，集合只包含 v0,
//集合 S 中每加一个新的顶点 u, 都要修改 v0 到集合 T 中剩余顶点的当前最短路径长度值
//集合 T 中各顶点新的当前最短路径长度值 ＝ min（原来的当前最短路径长度值， 从源点 v0 经过顶点 u 到达该顶点的路径长度）
//循环，直至集合 T 中的顶点全部加入到集合 S 中
//*/
//
//// 带权图 G 从下标 v0 顶点到其他顶点的最短距离 distance 和 最短路径下标 path
//
//// path[j] = u;   // j 就是下一个的点，而用值(即u)来保存它，已达到路径的连接
//
//void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
//{
//	int *s = (int *)malloc(sizeof(int) * 89); // 集合 S
//	int minDis, u;
//
//	// 初始化
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <= 8; j++)
//		{
//			distance[i+j] = G.edge[v0][i+j];
//			s[i+j] = 0;                         // 标记顶点 i 未从集合 T 加入到集合 S 中
//
//			if ((i+j) != v0 && distance[i+j] < MaxWeight)
//				path[i+j] = v0;
//			else 
//				path[i+j] = -1;
//		}
//	}
//
//	s[v0] = 1; // 标记顶点 v0 已从集合 T 加入到集合 S 中
//
//	// 在当前还未找到最短路径的顶点集中选取具有最短距离的顶点 u
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <= 8; j++)
//		{
//			minDis = MaxWeight;
//			for (int x = 80; x >= 10; x=x-10)
//			{
//				for (int y = 1; y <= 8; y++)
//				{
//					if (s[x+y] == 0 && distance[x+y] < minDis)
//					{
//						u = x+y;
//						minDis = distance[x+y];
//					}
//				}
//			}
//
//			// 当已不再存在路径时，算法结束。此语句对非连通图是必须的
//			if (minDis == MaxWeight) 
//				return;
//			s[u] = 1;    // 标记顶点 u 已从集合 T 加入到集合 S 中
//
//			// 修改从 v0 到其他顶点的最短距离和最短路径
//			for (int x = 80; x >= 10; x=x-10)
//			{
//				for (int y = 1; y <= 8; y++)
//				{
//					if (s[x+y] == 0 && G.edge[u][x+y] < MaxWeight && distance[u] + G.edge[u][x+y] < distance[x+y])
//					{
//						// 顶点 v0 经顶点 u 到其他顶点的最短距离和最短路径
//						distance[x+y] = distance[u] + G.edge[u][x+y];
//						path[x+y] = u;
//					}
//				}
//			}
//		}
//	}
//}
//
//
//void maind()
//{
//	AdjMGraph g;   
//
//	///////////////////////////////// 共 8*8 个点
//	int n = 64;        
//	int v[] = 
//	{
//		81, 82, 83, 84, 85, 86, 87, 88,
//		71, 72, 73, 74, 75, 76, 77, 78,
//		61, 62, 63, 64, 65, 66, 67, 68,
//		51, 52, 53, 54, 55, 56, 57, 58,
//		41, 42, 43, 44, 45, 46, 47, 48,
//		31, 32, 33, 34, 35, 36, 37, 38,
//		21, 22, 23, 24, 25, 26, 27, 28,
//		11, 12, 13, 14, 15, 16, 17, 18
//	};
//
//	///////////////////////////////// 64个点每个点最多8条边，无向图双向边
//	RowColWeight rcw[64*8*2];    
//	int edge_num = 0; // 边数
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <=8; j++)
//		{
//			// 首先是 i+j 点 的边
//			for (int x = 80; x >= 10; x=x-10)
//			{
//				for (int y = 1; y <= 8; y++)
//				{
//					// 根据马走日建立边
//					if ( (i != x)&& (j != y) && ((abs(i-x)/10 + abs(j-y)) == 3) )
//					{
//						// 以i+j为建立与他相连的点
//						
//						rcw[edge_num].col = i+j;  // 行下标
//						rcw[edge_num].row = x+y;  // 列下标
//						rcw[edge_num].weight = 1; // 权值 
//						edge_num++;
//				
//						rcw[edge_num].col = x+y;  // 行下标
//						rcw[edge_num].row = i+j;  // 列下标				
//						rcw[edge_num].weight = 1; // 权值 
//						edge_num++;
//					}
//				}
//			}
//		}
//	}
//	//printf("无向图边数：%d \n", edge_num);
//
//
//	/////////////////////////////////// 建立无向图
//	CreateGraph(&g, v, n, rcw, edge_num); 
//
//
//	//printf("顶点数：%d\n", g.Vertices.size);
//	//printf("顶点集合为：");
//	//for (int i = 0; i < g.Vertices.size; i++)
//	//	printf("%3d", g.Vertices.list[i]);
//	//printf("\n");
//	//printf("点45的权值集合为：\n");
//	//for (int i = 80; i >= 10; i=i-10)
//	//{
//	//	for (int j = 1; j <= 8; j++)
//	//		printf("%4d", g.edge[45][i+j]);
//	//	printf("\n");
//	//}
//	//printf("\n深度优先遍历：");
//	//DepthFirstSearch(g, Visit);
//	//printf("\n广度优先遍历：");
//	//BroadFirstSearch(g, Visit);
//
//
//	int distance[100];
//	int path[100];
//	int v0;
//	int v1;
//	printf("输入v0：");
//	scanf("%d", &v0);
//	printf("输入v1：");
//	scanf("%d", &v1);
//
//	Dijkstra(g, v0, distance, path);  
//	printf("\n顶点 %d 到 %d 之间的步数：%d \n", v0, v1, distance[v1]);
//	printf("路径：");
//	
//	int temp = v1;
//	printf("%d", v1);
//	while (temp != v0)
//	{
//		printf(" <-- %d", path[temp]);
//		temp = path[temp];
//	}
//
//}
//
