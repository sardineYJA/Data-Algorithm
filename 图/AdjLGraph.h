
//////////////////////////////// �ڽӱ�  �洢�ṹ��ͼ���� /////////
/*
ÿ��������һ������ 

0 a --> 1 e1(��) --> 3 e4 ^null(adjͷ�������)
1 b --> ����
2 c --> ����

*/



//#define MaxVertices 100

typedef struct Node 
{
	int dest;            // �ڽӱߵĻ�ͷ�������
	struct Node *next;   // ���������һ�����ָ��
} Edge;    // �ڽӱߵ�����Ľ��ṹ��

typedef struct
{
	int data;          // ����Ԫ��
	int source;        // �ڽӱߵĻ�β�������
	Edge * adj;        // �ڽӱߵ�ͷָ��
} AdjLHeight;     // ���������Ԫ�����ͽṹ��

typedef struct
{
	AdjLHeight a[MaxVertices];    // �ڽӱ�����
	int numOfVerts;               // �������
	int numOfEdges;               // �߸���
} AdjLGraph;    // �ڽӱ�ṹ��


// ��ʼ��
void AdjInitiate(AdjLGraph *G)
{
	G->numOfVerts = 0;   // ����Ϊ0
	G->numOfEdges = 0;   // ����Ϊ0
	for (int i = 0; i < MaxVertices; i++)
	{
		G->a[i].source = i;           // ���ڽӱߵĻ�ͷ�������
		G->a[i].adj = NULL;           // ���ڽӱߵ�����ͷָ���ֵ
	}
}


// ���붥��
// ��ͼG �еĵ� i ��λ�ò��붥������ vertex
void InsertVertex(AdjLGraph *G, int i, int vertex)
{
	if (i >= 0 && i < MaxVertices)
	{
		G->a[i].data = vertex;          // �洢��������Ԫ��vertex
		G->numOfVerts++;                // ���������1
	}
	else
		printf("����Խ�磡");
}


// �����
// ��ͼG �м����<v1, v2>
void InsertEdge(AdjLGraph *G, int v1, int v2)
{
	Edge *p;
	if (v1 < 0 || v1 >= G->numOfVerts || v2 < 0 || v2 >= G->numOfVerts)
	{
		printf("���� v1 �� v2 Խ�����\n");
		return;
	}
	p = (Edge *)malloc(sizeof(Edge));   // �����ڽӱߵ�������ռ�
	p->dest = v2;                       // ���ڽӱ߻�ͷ���
	p->next = G->a[v1].adj;             // �½����뵥����ı�ͷ
	G->a[v1].adj = p;                   // ͷָ��ָ���µĵ������ͷ
	G->numOfEdges++; // ������1
}

// ɾ��ͼ G �ı�<v1, v2>
void DeleteEdge(AdjLGraph * G, int v1, int v2)
{
	Edge *curr, *pre;
	if (v1 < 0 || v1 >= G->numOfVerts || v2 < 0 || v2 >= G->numOfVerts)
	{
		printf("���� v1 �� v2 Խ�����\n");
		return;
	}
	
	pre = NULL;
	curr = G->a[v1].adj;

	// ��v1 ������ڽӱߵ����в��� v2 ���� 
	while (curr != NULL &&curr->dest != v2)
	{
		pre = curr;
		curr = curr->next;
	}

	// ɾ���ڱ�<v1, v2>
	if (curr != NULL && curr->dest == v2 && pre == NULL)
	// ���ڽӱ�<v1, v2>�Ľ���ǵ�����ĵ�һ�����ʱ
	{
		G->a[v1].adj = curr->next;
		free(curr);
		G->numOfEdges--;
	} 
	else if (curr != NULL && curr->dest == v2 && pre != NULL)
	// ���ڽӱ�<v1, v2>�Ľ�㲻�ǵ�����ĵ�һ�����ʱ
	{
		pre->next = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else  // ���߲�����ʱ
		printf("��<v1, v2>������");
}


// ȡͼ G �ж��� v �ĵ�һ���ڽӶ���
// ��ȡ�����򷵻ظ��ڽӶ���Ķ�Ӧ��ţ����򷵻�-1
int GetFirstVex(AdjLGraph G, int v)
{
	Edge *p;
	if (v < 0 || v >= G.numOfVerts)
	{
		printf("���� v1 �� v2 Խ�����\n");
		return -1;
	}
	p = G.a[v].adj;
	if (p != NULL)
		return p->dest;    // ���ظ��ڽӶ���Ķ�Ӧ���
	else
		return -1;
}



// ȡͼ G �ж��� v1 ���ڽӶ��� v2 ����һ���ڽӶ���
// ��ȡ�����򷵻ظ��ڽӶ���Ķ�Ӧ��ţ����򷵻�-1
int GetNextVex(AdjLGraph G, int v1, const int v2)
{
	Edge *p;
	if (v1 < 0 || v1 >= G.numOfVerts || v2 < 0 || v2 >= G.numOfVerts)
	{
		printf("���� v1 �� v2 Խ�����\n");
		return -1;
	}

	p = G.a[v1].adj;
	while (p != NULL)
	{
		if (p->dest != v2)
		{
			p = p->next;
			continue;
		}
		else 
			break;
	}

	p = p->next;      // p ָ���ڽӶ��� v2 ����һ���ڽӶ���
	if (p != NULL)
		return p->dest;   // ���ظ��ڽӶ���Ķ�Ӧ���
	else 
		return -1;
}


// ����ͼ G �е����е�����ռ�õĴ洢�ռ�
void AdjLDestory(AdjLGraph * G)
{
	Edge *p, *q;
	for (int i = 0; i < G->numOfVerts; i++)
	{
		p = G->a[i].adj;
		while (p != NULL)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
}