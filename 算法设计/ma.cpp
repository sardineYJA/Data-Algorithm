//#define _CRT_SECURE_NO_WARNINGS
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//#include "SeqList.h"         // ��Ŷ����˳���
//#include "SeqCQueue.h"       // ��ȱ���
//
//#include "AdjMGraph.h"       // �ڽӾ���
//#include "AdjMGraphCreate.h" // ����ͼ
//
//#include "DepthSearch.h"     // ��ȱ���
//#include "BroadSearch.h"     // ��ȱ���
//
///*
//
//8 �� �� �� �� �� �� �� ��
//7 �� �� �� �� �� �� �� ��
//6 �� �� �� �� �� �� �� ��
//5 �� �� �� �� �� �� �� ��
//4 �� �� �� �� �� �� �� ��
//3 �� �� �� �� �� �� �� ��
//2 �� �� �� �� �� �� �� ��
//1 �� �� �� �� �� �� �� ��
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
////// �ҿ�˹����Dijkstra�㷨�������ض�ĳ���㵽����������·��
///*
//���� S ����Ѿ��ҵ����·���Ķ���
//���� T ��ŵ�ǰ��δ�ҵ����·���Ķ���
//
//��ʼ״̬������ֻ���� v0,
//���� S ��ÿ��һ���µĶ��� u, ��Ҫ�޸� v0 ������ T ��ʣ�ඥ��ĵ�ǰ���·������ֵ
//���� T �и������µĵ�ǰ���·������ֵ �� min��ԭ���ĵ�ǰ���·������ֵ�� ��Դ�� v0 �������� u ����ö����·�����ȣ�
//ѭ����ֱ������ T �еĶ���ȫ�����뵽���� S ��
//*/
//
//// ��Ȩͼ G ���±� v0 ���㵽�����������̾��� distance �� ���·���±� path
//
//// path[j] = u;   // j ������һ���ĵ㣬����ֵ(��u)�����������Ѵﵽ·��������
//
//void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
//{
//	int *s = (int *)malloc(sizeof(int) * 89); // ���� S
//	int minDis, u;
//
//	// ��ʼ��
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <= 8; j++)
//		{
//			distance[i+j] = G.edge[v0][i+j];
//			s[i+j] = 0;                         // ��Ƕ��� i δ�Ӽ��� T ���뵽���� S ��
//
//			if ((i+j) != v0 && distance[i+j] < MaxWeight)
//				path[i+j] = v0;
//			else 
//				path[i+j] = -1;
//		}
//	}
//
//	s[v0] = 1; // ��Ƕ��� v0 �ѴӼ��� T ���뵽���� S ��
//
//	// �ڵ�ǰ��δ�ҵ����·���Ķ��㼯��ѡȡ������̾���Ķ��� u
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
//			// ���Ѳ��ٴ���·��ʱ���㷨�����������Է���ͨͼ�Ǳ����
//			if (minDis == MaxWeight) 
//				return;
//			s[u] = 1;    // ��Ƕ��� u �ѴӼ��� T ���뵽���� S ��
//
//			// �޸Ĵ� v0 �������������̾�������·��
//			for (int x = 80; x >= 10; x=x-10)
//			{
//				for (int y = 1; y <= 8; y++)
//				{
//					if (s[x+y] == 0 && G.edge[u][x+y] < MaxWeight && distance[u] + G.edge[u][x+y] < distance[x+y])
//					{
//						// ���� v0 ������ u �������������̾�������·��
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
//	///////////////////////////////// �� 8*8 ����
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
//	///////////////////////////////// 64����ÿ�������8���ߣ�����ͼ˫���
//	RowColWeight rcw[64*8*2];    
//	int edge_num = 0; // ����
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <=8; j++)
//		{
//			// ������ i+j �� �ı�
//			for (int x = 80; x >= 10; x=x-10)
//			{
//				for (int y = 1; y <= 8; y++)
//				{
//					// ���������ս�����
//					if ( (i != x)&& (j != y) && ((abs(i-x)/10 + abs(j-y)) == 3) )
//					{
//						// ��i+jΪ�������������ĵ�
//						
//						rcw[edge_num].col = i+j;  // ���±�
//						rcw[edge_num].row = x+y;  // ���±�
//						rcw[edge_num].weight = 1; // Ȩֵ 
//						edge_num++;
//				
//						rcw[edge_num].col = x+y;  // ���±�
//						rcw[edge_num].row = i+j;  // ���±�				
//						rcw[edge_num].weight = 1; // Ȩֵ 
//						edge_num++;
//					}
//				}
//			}
//		}
//	}
//	//printf("����ͼ������%d \n", edge_num);
//
//
//	/////////////////////////////////// ��������ͼ
//	CreateGraph(&g, v, n, rcw, edge_num); 
//
//
//	//printf("��������%d\n", g.Vertices.size);
//	//printf("���㼯��Ϊ��");
//	//for (int i = 0; i < g.Vertices.size; i++)
//	//	printf("%3d", g.Vertices.list[i]);
//	//printf("\n");
//	//printf("��45��Ȩֵ����Ϊ��\n");
//	//for (int i = 80; i >= 10; i=i-10)
//	//{
//	//	for (int j = 1; j <= 8; j++)
//	//		printf("%4d", g.edge[45][i+j]);
//	//	printf("\n");
//	//}
//	//printf("\n������ȱ�����");
//	//DepthFirstSearch(g, Visit);
//	//printf("\n������ȱ�����");
//	//BroadFirstSearch(g, Visit);
//
//
//	int distance[100];
//	int path[100];
//	int v0;
//	int v1;
//	printf("����v0��");
//	scanf("%d", &v0);
//	printf("����v1��");
//	scanf("%d", &v1);
//
//	Dijkstra(g, v0, distance, path);  
//	printf("\n���� %d �� %d ֮��Ĳ�����%d \n", v0, v1, distance[v1]);
//	printf("·����");
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
