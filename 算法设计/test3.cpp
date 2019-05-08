#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxVertices 100         // ���嶥������ֵ
#define MaxWeight 100           // �������Ȩֵ
#define MaxSize 100             // ˳������ֵ

////////////////////////////////// ˳���Ĵ洢�Ͳ���//////////////////////////////////////
typedef struct
{
	int list[MaxSize];
	int size;     
} SeqList;

// ��ʼ��
void ListInitiate(SeqList * L)
{
	L->size = 0;
}

// ��Ԫ�ظ���
int ListLength(SeqList L)
{
	return L.size;
}

// ����Ԫ�� x
int ListInsert(SeqList * L, int i, int x)
{
	if (L->size >= MaxSize)
	{
		printf("˳��������޷�����!\n");
		return 0;
	}
	else if (i < 0 || i> L->size)
	{
		printf("���� i ���Ϸ���\n");
		return 0;
	}
	else
	{
		// �Ӻ���ǰ���κ������ݣ�Ϊ������׼��
		for (int j = L->size; j > i; j--)
			L->list[j] = L->list[j-1];
		L->list[i] = x;
		L->size++;
		return 1;
	}
}

// ȡ������
int ListGet(SeqList L, int i, int *x)
{
	if (i < 0 || i > L.size-1)
	{
		printf("���� i ���Ϸ���\n");
		return 0;
	}
	else
	{
		*x = L.list[i];   
		return 1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////// ͼ�Ĵ洢�ṹ�Ͳ���//////////////////////////////////////
typedef struct
{
	SeqList Vertices;                       // ��Ŷ����˳���
	int edge[MaxVertices][MaxVertices];     // ��űߵ��ڽӾ�������ֵΪ���㣬����ֵΪ�ߵ�Ȩֵ
	int numOfEdges;                         // �ߵ�����
} AdjMGraph;


// ��ʼ����n�������˳�����ڽӾ���
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

	G->numOfEdges = 0;               // ����
	ListInitiate(&G->Vertices);      // ˳����ʼ��
}

// ���붥��vertex
void InsertVertex(AdjMGraph * G, int vertex)
{
	ListInsert(&G->Vertices, G->Vertices.size, vertex);    // ��˳���β���붥��
}

// ����һ�������
void InsertEdge(AdjMGraph * G, int v1, int v2, int weight)
{
	G->edge[v1][v2] = weight;
	G->numOfEdges++;
}

// �õ���һ���ڽӵ��ֵ
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

// �õ���һ���ڽӵ�ֵ
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


//////////////////////////////////// ��������ͼ ///////////////////////////////////
typedef struct 
{
	int row;       // ���±�
	int col;       // ���±�
	int weight;    // Ȩֵ
} RowColWeight;    // ����Ϣ�ṹ�嶨��

// ��ͼ G �в��� n ��������Ϣ V �� e ������Ϣ E
void CreateGraph(AdjMGraph * G, int V[], int n, RowColWeight E[], int e)
{
	Initiate(G, n);      // ����˳����ʼ��
	for (int i = 0; i < n; i++)
		InsertVertex(G, V[i]);    // ���붥��

	for (int k = 0; k < e; k++)
		InsertEdge(G, E[k].row, E[k].col, E[k].weight);  // �����
}
//////////////////////////////////////////////////////////////////////////////////

// ���Ԫ�غ���
void Visit(int item)
{
	printf("%d  ", item);
}

// �ҿ�˹����Dijkstra�㷨
void Dijkstra(AdjMGraph G, int v0, int distance[], int path[])
{
	int *s = (int *)malloc(sizeof(int) * 89); // ���� S
	int minDis, u;

	// ��ʼ��
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j <= 8; j++)
		{
			distance[i+j] = G.edge[v0][i+j];
			s[i+j] = 0;    // ��Ƕ��� i δ�Ӽ��� T ���뵽���� S ��

			if ((i+j) != v0 && distance[i+j] < MaxWeight)
				path[i+j] = v0;
			else 
				path[i+j] = -1;
		}
	}

	s[v0] = 1; // ��Ƕ��� v0 �ѴӼ��� T ���뵽���� S ��

	// �ڵ�ǰ��δ�ҵ����·���Ķ��㼯��ѡȡ������̾���Ķ��� u
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

			// ���Ѳ��ٴ���·��ʱ���㷨�����������Է���ͨͼ�Ǳ����
			if (minDis == MaxWeight) 
				return;
			s[u] = 1;    // ��Ƕ��� u �ѴӼ��� T ���뵽���� S ��

			// �޸Ĵ� v0 �������������̾�������·��
			for (int x = 80; x >= 10; x=x-10)
			{
				for (int y = 1; y <= 8; y++)
				{
					if (s[x+y] == 0 && G.edge[u][x+y] < MaxWeight && 
						distance[u] + G.edge[u][x+y] < distance[x+y])
					{
						// ���� v0 ������ u �������������̾�������·��
						distance[x+y] = distance[u] + G.edge[u][x+y];
						path[x+y] = u;
					}
				}
			}
		}
	}
}

// ������ת�����ַ���
void IntToChar(char * ch, int n)
{
	ch[0] = (char)(n%10 + 96);
	ch[1] = (char)(n/10 + 48);
	ch[2] = '\0';
}

void main()
{
	AdjMGraph g;   
	//////// �� 8*8 ����
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

	//////// 64����ÿ�������8���ߣ�����ͼ˫���
	RowColWeight rcw[64*8*2];    
	int edge_num = 0; // ����
	for (int i = 80; i >= 10; i=i-10)
	{
		for (int j = 1; j <=8; j++)
		{
			// ������ i+j �� �ı�
			for (int x = 80; x >= 10; x=x-10)
			{
				for (int y = 1; y <= 8; y++)
				{
					// ���������ս�����
					if ( (i != x)&& (j != y) &&
						((abs(i-x)/10 + abs(j-y)) == 3) )
					{
						// ��i+jΪ�������������ĵ�
						
						rcw[edge_num].col = i+j;  // ���±�
						rcw[edge_num].row = x+y;  // ���±�
						rcw[edge_num].weight = 1; // Ȩֵ 
						edge_num++;
				
						rcw[edge_num].col = x+y;  // ���±�
						rcw[edge_num].row = i+j;  // ���±�				
						rcw[edge_num].weight = 1; // Ȩֵ 
						edge_num++;
					}
				}
			}
		}
	}

	// ��������ͼ
	CreateGraph(&g, v, n, rcw, edge_num); 
	int distance[100];
	int path[100];
	int start = 11;
	int end = 88;
	char v0[10];    // ���
	char v1[10];    // �յ�

	printf("�������(�磺a1)��");
	scanf("%s", &v0);
	printf("�����ص�(�磺b1)��");
	scanf("%s", &v1);

	if (97 <= v0[0] && v0[0]<= 104 && 97 <= v1[0] && v1[0]<= 104
		&& 49 <= v0[1] && v0[1]<= 56 && 49 <= v1[1] && v1[1]<= 56 
		&& v0[2]=='\0' && v1[2] == '\0')
	{
		// ���ַ���תΪ����
		start = (v0[0]-96) + (v0[1]-48)*10;
		end = (v1[0]-96) + (v1[1]-48)*10;
	}
	else
	{
		printf("���벻����Ҫ��!\n");
		return;
	}

	Dijkstra(g, start, distance, path);  
	// ���·��
	printf("\n���� %s �� %s ֮��Ĳ�����%d \n", v0, v1, distance[end]);
	printf("·����");
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
