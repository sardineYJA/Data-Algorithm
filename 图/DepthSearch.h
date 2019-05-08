


////////////////// 连通图的深度优先遍历

// 连通图 G 以 v 为初始顶点的，访问操作为Visit()
// 数组visited 标记相应顶点是否已访问过（0表示未访问，1表示已访问）
void DepthFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
{
	int w;
	Visit(G.Vertices.list[v]);   // 访问顶点 v
	visited[v] = 1;              // 置已访问标记
	
	/*
	for (w = 0; w < G.Vertices.size; w++)
		if (G.edge[v][w] > 0 && G.edge[v][w] < MaxWeight && !visited[w])
			DepthFSearch(G, w, visited, Visit);
	*/

	w = GetFirstVex(G, v);       // 取第一个邻接顶点
	while (w != -1)
	{
		if (!visited[w])
			DepthFSearch(G, w, visited, Visit);  // 递归
		w = GetNextVex(G, v, w);                 // 取下一个邻接顶点
	}
}



////////////// 非连通图 的深度优先遍历
void DepthFirstSearch(AdjMGraph G, void Visit(int item))
{
	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);
	for (int i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;                       // 访问编辑初始均为0

	for (int i = 0; i < G.Vertices.size; i++)
		if (!visited[i])
			DepthFSearch(G, i, visited, Visit); // 以每个顶点为初始顶点进行调用
	free(visited);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

// 利用深度遍历，找到两个顶点之间的路径，可能是多条

int DepthFSearchPath(AdjMGraph G, int visited[], int v1, int v2)
{
	int w;
	int flag = 0;
	visited[v1] = 1;         // 置已访问标记
	w = GetFirstVex(G, v1);  // 取第一个邻接顶点

	while (w != -1)          // 主路线从这里开始直至尾点
	{
		if (w == v2)         // 如果找到路径
		{
			flag = 1;
			break;
		}

		if (!visited[w])
			if ((flag = DepthFSearchPath(G, visited, w, v2)) == 1)
				break;
		w = GetNextVex(G, v1, w);   // 取下一个邻接顶点
	}
	return flag;
}



/////////  判断是否存在下标为 v1 的顶点到下标为 v2 的顶点的路径
void DepthFirstSearchPath(AdjMGraph G, int v1, int v2)
{
	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);

	for (int i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;         // 访问编辑初始均为0		

	// 只需要从v1 出发深度遍历
	int flag = DepthFSearchPath(G, visited, v1, v2);
	free(visited);

	printf("%c 到 %c 是否存在路径：", G.Vertices.list[v1], G.Vertices.list[v2]);
	if (flag == 1)
		printf ("存在路径\n");
	else
		printf("不存在路径\n");
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
图的深度优先搜索算法使用堆栈以非递归的形式实现：
⑴ 首先将初始顶点v入栈；
⑵ 当堆栈不为空时，重复以下处理
栈顶元素出栈，
若未访问，则访问之并设置访问标志，将其未曾访问的邻接点入栈；
⑶ 如果图中还有未曾访问的邻接点，选择一个重复以上过程。
*/

void DFS(AdjMGraph G, int v, int visited[], void Visit(int item))
{	int i, j;
    SeqStack s;
    StackInitiate(&s);
    StackPush(&s, v);
    while (StackNotEmpty(s))
	{
       StackPop(&s, &i);
       if (!visited[i])
	   {
		   Visit(G.Vertices.list[v]);
		   visited[i] = 1;
		   for(j = G.Vertices.size-1; j >= 0; j--)
			   if(G.edge[i][j] > 0 && G.edge[i][j] < MaxWeight && !visited[j])
				   StackPush(&s, j);
       }
    }
}

void DFSearch(AdjMGraph G, void Visit(int item))
{
    int i;
    int *visited = (int *)malloc(sizeof(int)*G.Vertices.size);

    for(i = 0; i < G.Vertices.size; i++)
        visited[i] = 0;

    for(i = 0; i < G.Vertices.size; i++)
        if(! visited[i]) 
			DFS(G, i, visited, Visit);

    free(visited);
}

