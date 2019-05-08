//
//
//void DepthFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
//{
//	int w;
//	Visit(v);                    // 访问顶点 v
//	visited[v] = 1;              // 置已访问标记
//	
//	w = GetFirstVex(G, v);       // 取第一个邻接顶点
//	while (w != -1)
//	{
//		if (!visited[w])
//			DepthFSearch(G, w, visited, Visit);  // 递归
//		w = GetNextVex(G, v, w);                 // 取下一个邻接顶点
//	}
//}
//
//////////////// 非连通图 的深度优先遍历
//void DepthFirstSearch(AdjMGraph G, void Visit(int item))
//{
//	int *visited = (int *)malloc(sizeof(int) * 90);
//	for (int i = 0; i < 90; i++)
//		visited[i] = 0;                       // 访问编辑初始均为0
//
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <= 8; j++)
//		{
//			if (!visited[i+j])
//			DepthFSearch(G, i+j, visited, Visit); // 以每个顶点为初始顶点进行调用
//		}
//	}
//	free(visited);
//}