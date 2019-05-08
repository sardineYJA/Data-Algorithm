

#include <stdio.h>
#include <stdlib.h>

#include "SeqList.h"
#include "SeqStack.h"       // �ǵݹ����ȱ���
#include "SeqCQueue.h"      // ��ȱ���

#include "AdjMGraph.h"             // �ڽӾ���
#include "AdjMGraphCreate.h" 

#include "AdjLGraph.h"             // �ڽӱ�
#include "AdjLGraphCreate.h"

#include "DepthSearch.h"     // ��ȱ���
#include "BroadSearch.h"     // ��ȱ���

#include "Prim.h"     // ��С��������Prim�㷨

void Visit(int item)
{
	printf("%c  ", item);
}


// �ڽӾ���
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


	printf("���㼯��Ϊ��");
	for (int i = 0; i < g.Vertices.size; i++)
		printf("%c ", g.Vertices.list[i]);
	printf("\n");

	printf("Ȩֵ����Ϊ��\n");
	for (int i = 0; i < g.Vertices.size; i++)
	{
		for (int j = 0; j < g.Vertices.size; j++)
			printf("%5d   ", g.edge[i][j]);
		printf("\n");
	}

	printf("\n������ȱ�����");
	DepthFirstSearch(g, Visit);
	printf("\n");

	printf("\n������ȱ�����");
	BroadFirstSearch(g, Visit);
	printf("\n");

	printf("\n��ȱ�����������ĳ��Ⱥ���ȣ�\n");
	BroadFirstSearchDegree(g);
	printf("\n");

	printf("�ж� v1 �� v2 �Ƿ����·����\n");
	DepthFirstSearchPath(g, 0, 2);
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////


// �ڽӱ�
void mainLLLLLLLLL()
{
	AdjLGraph g;
	int a[] = { 'L', 'M', 'N', 'O', 'P'};
	RowCol rc[] = {{1,2}, {2,3}, {2,4}, {3,2}, {3,4}};
	int n = 5, e = 5;
	CreateGraph(&g, a, n, rc, e);

	printf("���㼯��Ϊ��");
	for (int i = 0; i < g.numOfVerts; i++)
		printf("%c ", g.a[i].data);
	printf("\n");

	printf("Ȩֵ����Ϊ��\n");
	for (int i = 0; i < g.numOfVerts; i++)
	{
		
	}
}
//////////////////////////////////////////////////////////////////////////////////////



// ��С������
void maintttt()
{
	AdjMGraph g;
	int a[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

	RowColWeight rcw[] = {{0,1,50}, {1,0,50}, {0,2,60}, {2,0,60}, {1,3,65}, {3,1,65}, 
						  {1,4,40}, {4,1,40}, {2,3,52}, {3,2,52}, {2,6,45}, {6,2,45}, 
	                      {3,4,50}, {4,3,50}, {3,5,30}, {5,3,30}, {3,6,42}, {6,3,42},
	                      {4,5,70}, {5,4,70}};

	int n = 7;     // 7������
	int e = 20;    // 20����
	MinSpanTree closeVertex[7];     // ���屣����С������������
	CreateGraph(&g, a, n, rcw, e);  // ����ͼ
	Prim(g, closeVertex);

	// �����С�������Ķ������к�Ȩֵ����
	printf("��ʼ���� = %c\n", closeVertex[0].vertex);
	for (int i = 1; i < n; i++)
		printf("���� = %c �ߵ�Ȩֵ = %d\n", closeVertex[i].vertex, closeVertex[i].weight);
}
/////////////////////////////////////////////////////////////////////////////////////////////




//// �ҿ�˹����Dijkstra�㷨�������ض�ĳ���㵽����������·��
/*
���� S ����Ѿ��ҵ����·���Ķ���
���� T ��ŵ�ǰ��δ�ҵ����·���Ķ���

��ʼ״̬������ֻ���� v0,
���� S ��ÿ��һ���µĶ��� u, ��Ҫ�޸� v0 ������ T ��ʣ�ඥ��ĵ�ǰ���·������ֵ
���� T �и������µĵ�ǰ���·������ֵ �� min��ԭ���ĵ�ǰ���·������ֵ�� ��Դ�� v0 �������� u ����ö����·�����ȣ�
ѭ����ֱ������ T �еĶ���ȫ�����뵽���� S ��
*/

// ��Ȩͼ G ���±� v0 ���㵽�����������̾��� distance �� ���·���±� path

// path[j] = u;   // j ������һ���ĵ㣬����ֵ(��u)�����������Ѵﵽ·��������

void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
{
	int n = G.Vertices.size;
	int *s = (int *)malloc(sizeof(int) * n); // ���� S
	int minDis, u;

	// ��ʼ��
	for (int i = 0; i < n; i++)
	{
		distance[i] = G.edge[v0][i];
		s[i] = 0;
		if (i != v0 && distance[i] < MaxWeight)
			path[i] = v0;
		else 
			path[i] = -1;
	}

	s[v0] = 1; // ��Ƕ��� v0 �ѴӼ��� T ���뵽���� S ��

	// �ڵ�ǰ��δ�ҵ����·���Ķ��㼯��ѡȡ������̾���Ķ��� u
	for (int i = 1; i < n; i++)
	{
		minDis = MaxWeight;
		for (int j = 0; j < n; j++)
			if (s[j] == 0 && distance[j] < minDis)
			{
				u = j;
				minDis = distance[j];
			}

		// ���Ѳ��ٴ���·��ʱ���㷨�����������Է���ͨͼ�Ǳ����
		if (minDis == MaxWeight) 
			return;
		s[u] = 1;    // ��Ƕ��� u �ѴӼ��� T ���뵽���� S ��

		// �޸Ĵ� v0 �������������̾�������·��
		for (int j = 0; j < n; j++)
			if (s[j] == 0 && G.edge[u][j] < MaxWeight && distance[u] + G.edge[u][j] < distance[j])
			{
				// ���� v0 ������ u �������������̾�������·��
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
	int n = 6;  // �������
	int e = 9;  // ������

	int distance[6];
	int path[6];
	CreateGraph(&g, a, n, rcw, e);

	/////////// Dijkstra�㷨�����·��
	Dijkstra(g, 0, distance, path);  

	printf("�Ӷ��� %c ��������������·��Ϊ��\n", g.Vertices.list[0]);
	for (int i = 0; i  < n; i++)
		printf("������ %c �����·��Ϊ %d \n", g.Vertices.list[i], distance[i]);

	printf("�Ӷ��� %c ���������������·����ǰһ����Ϊ��\n", g.Vertices.list[0]);
	for(int i = 0; i < n; i++)
		if (path[i] != -1)
			printf("������ %c ��ǰһ����Ϊ %c \n", g.Vertices.list[i], g.Vertices.list[path[i]]);
}
//////////////////////////////////////////////////////////////////////////////////////////


/*
�����㷨������ͼ�� 
  
A --> C    5
C --> B    15
C --> F    7
B --> A    2
B --> E    8
E --> D    4
F --> D    10
F --> E    18


*/


//// ��������Floyd�㷨�����ҵ�ÿ����֮�����̾���
/*
N : ͼ�Ķ������
cost[][N] �� ��Ŵ�ȨͼG��Ȩֵ
weight[i][j] : ����i �붥��j ֮�����·��(��ά�����ֵ)
path[i][j] = k : ���� i ������j ��·����ǰһ������ k (��ά�����ֵ)�����н�
*/
#define N 6
void Floyd(int cost[][N], int n, int weight[][N], int path[][N])
{
	// ��ʼ��
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			weight[i][j] = cost[i][j];
			path[i][j] = -1;
		}
	}

	// n �ε���
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (weight[i][j] > weight[i][k] + weight[k][j])   // k �����н�
				{
					// �õ��µ����·��������ֵ
					weight[i][j] = weight[i][k] + weight[k][j];
					// �õ������·���ľ����Ķ�������
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
	int n = 6;  // �������
	int e = 9;  // ������
	CreateGraph(&g, a, n, rcw, e);


	int weight[N][N];
	int path[N][N];
	int cost[N][N];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cost[i][j] = g.edge[i][j];
	

	////////////// Floyd�㷨�����·��
	Floyd(cost, n, weight, path);

	// ��ӡ�����
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




