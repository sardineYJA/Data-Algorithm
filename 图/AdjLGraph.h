
//////////////////////////////// 邻接表  存储结构下图操作 /////////
/*
每个顶点是一个链表 

0 a --> 1 e1(边) --> 3 e4 ^null(adj头结点在这)
1 b --> ……
2 c --> ……

*/



//#define MaxVertices 100

typedef struct Node 
{
	int dest;            // 邻接边的弧头顶点序号
	struct Node *next;   // 单链表的下一个结点指针
} Edge;    // 邻接边单链表的结点结构体

typedef struct
{
	int data;          // 顶点元素
	int source;        // 邻接边的弧尾顶点序号
	Edge * adj;        // 邻接边的头指针
} AdjLHeight;     // 数组的数据元素类型结构体

typedef struct
{
	AdjLHeight a[MaxVertices];    // 邻接表数组
	int numOfVerts;               // 顶点个数
	int numOfEdges;               // 边个数
} AdjLGraph;    // 邻接表结构体


// 初始化
void AdjInitiate(AdjLGraph *G)
{
	G->numOfVerts = 0;   // 顶点为0
	G->numOfEdges = 0;   // 边数为0
	for (int i = 0; i < MaxVertices; i++)
	{
		G->a[i].source = i;           // 置邻接边的弧头顶点序号
		G->a[i].adj = NULL;           // 置邻接边单链表头指针初值
	}
}


// 插入顶点
// 在图G 中的第 i 个位置插入顶点数据 vertex
void InsertVertex(AdjLGraph *G, int i, int vertex)
{
	if (i >= 0 && i < MaxVertices)
	{
		G->a[i].data = vertex;          // 存储顶点数据元素vertex
		G->numOfVerts++;                // 顶点个数加1
	}
	else
		printf("顶点越界！");
}


// 插入边
// 在图G 中加入边<v1, v2>
void InsertEdge(AdjLGraph *G, int v1, int v2)
{
	Edge *p;
	if (v1 < 0 || v1 >= G->numOfVerts || v2 < 0 || v2 >= G->numOfVerts)
	{
		printf("参数 v1 或 v2 越界出错！\n");
		return;
	}
	p = (Edge *)malloc(sizeof(Edge));   // 申请邻接边单链表结点空间
	p->dest = v2;                       // 置邻接边弧头序号
	p->next = G->a[v1].adj;             // 新结点插入单链表的表头
	G->a[v1].adj = p;                   // 头指针指向新的单链表表头
	G->numOfEdges++; // 边数加1
}

// 删除图 G 的边<v1, v2>
void DeleteEdge(AdjLGraph * G, int v1, int v2)
{
	Edge *curr, *pre;
	if (v1 < 0 || v1 >= G->numOfVerts || v2 < 0 || v2 >= G->numOfVerts)
	{
		printf("参数 v1 或 v2 越界出错！\n");
		return;
	}
	
	pre = NULL;
	curr = G->a[v1].adj;

	// 在v1 顶点的邻接边单链中查找 v2 顶点 
	while (curr != NULL &&curr->dest != v2)
	{
		pre = curr;
		curr = curr->next;
	}

	// 删除邻边<v1, v2>
	if (curr != NULL && curr->dest == v2 && pre == NULL)
	// 当邻接边<v1, v2>的结点是单链表的第一个结点时
	{
		G->a[v1].adj = curr->next;
		free(curr);
		G->numOfEdges--;
	} 
	else if (curr != NULL && curr->dest == v2 && pre != NULL)
	// 当邻接边<v1, v2>的结点不是单链表的第一个结点时
	{
		pre->next = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else  // 当边不存在时
		printf("边<v1, v2>不存在");
}


// 取图 G 中顶点 v 的第一个邻接顶点
// 若取到，则返回该邻接顶点的对应序号，否则返回-1
int GetFirstVex(AdjLGraph G, int v)
{
	Edge *p;
	if (v < 0 || v >= G.numOfVerts)
	{
		printf("参数 v1 或 v2 越界出错！\n");
		return -1;
	}
	p = G.a[v].adj;
	if (p != NULL)
		return p->dest;    // 返回该邻接顶点的对应序号
	else
		return -1;
}



// 取图 G 中顶点 v1 的邻接顶点 v2 的下一个邻接顶点
// 若取到，则返回该邻接顶点的对应序号，否则返回-1
int GetNextVex(AdjLGraph G, int v1, const int v2)
{
	Edge *p;
	if (v1 < 0 || v1 >= G.numOfVerts || v2 < 0 || v2 >= G.numOfVerts)
	{
		printf("参数 v1 或 v2 越界出错！\n");
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

	p = p->next;      // p 指向邻接顶点 v2 的下一个邻接顶点
	if (p != NULL)
		return p->dest;   // 返回该邻接顶点的对应序号
	else 
		return -1;
}


// 撤销图 G 中的所有单链表占用的存储空间
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