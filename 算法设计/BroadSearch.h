//
////////////////////////// 连通图的广度优先遍历
//
//void BroadFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
//{
//	int u, w;
//	SeqCQueue queue;
//	Visit(G.Vertices.list[v]);      // 访问顶点 v 
//	visited[v] = 1;                 // 置已访问
//	
//	QueueInitiate(&queue);          // 队列初始化
//	QueueAppend(&queue, v);         // 顶点 v 入队列
//	while (QueueNotEmpty(queue))    // 队列非空时
// 	{
//		QueueDelete(&queue, &u);    // 出队列
//		w = GetFirstVex(G, u);      // 取顶点 u 的第一个邻接顶点 w
//		while (w != -1)
//		{
//			if (!visited[w])
//			{
//				Visit(G.Vertices.list[w]);  // 访问顶点 w
//				visited[w] = 1;
//				QueueAppend(&queue, w);     // 顶点 w 入队列
//			}
//			w = GetNextVex(G, u, w);        
//		}
//	}
//}
//
//
//////////// 非连通图的广度优先遍历
//void BroadFirstSearch(AdjMGraph G, void Visit(int item))
//{
//	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);
//	for (int i = 0; i < G.Vertices.size; i++)
//		visited[i] = 0;            // 访问标记初始均为 0
//	
//	for (int i = 0; i < G.Vertices.size; i++)
//		if (!visited[i])
//			BroadFSearch(G, i, visited, Visit);  // 以每个顶点为初始顶点进行调用
//	free(visited);
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//// 利用广度优先遍历，可以没有权值的找到每个点的出度
//// 每访问到一个顶点，则计算它的邻接顶点
//
//// 广度遍历，找到每个顶点的入度
//// 每访问一个顶点，则它的全部邻接点的inDegree[]++
//
//// u v w 全是下标
//void BroadFSearchDegree(AdjMGraph G, int v, int visited[], int outDegree[], int inDegree[])
//{
//	int u, w;
//	SeqCQueue queue;
//	visited[v] = 1;                 // 置已访问
//	
//	QueueInitiate(&queue);          // 队列初始化
//	QueueAppend(&queue, v);         // 顶点 v 入队列
//	while (QueueNotEmpty(queue))    // 队列非空时
// 	{
//		QueueDelete(&queue, &u);    // 出队列
//		w = GetFirstVex(G, u);      // 取顶点 u 的第一个邻接顶点 w
//		while (w != -1)
//		{
//			// 顶点 u 出度加1
//			outDegree[u]++;
//
//			// u 的邻接点的入度加1
//			inDegree[w]++;
//
//			if (!visited[w])
//			{
//				visited[w] = 1;
//				QueueAppend(&queue, w);     // 顶点 w 入队列
//			}
//			w = GetNextVex(G, u, w);        
//		}
//	}
//}
//void BroadFirstSearchDegree(AdjMGraph G)
//{
//	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);        // 是否被访问过
//	int *outDegree = (int *)malloc(sizeof(int) * G.Vertices.size);      // 每个顶点的出度
//	int *inDegree = (int *)malloc(sizeof(int) * G.Vertices.size);       // 每个顶点的入度
//	
//	// 初始化
//	for (int i = 0; i < G.Vertices.size; i++)
//	{
//		visited[i] = 0;            // 访问标记初始均为 0
//		outDegree[i] = 0;          // 各顶点初始出度为 0
//		inDegree[i] = 0;           // 各顶点初始入度为 0
//	}
//		
//	for (int i = 0; i < G.Vertices.size; i++)
//		if (!visited[i])
//			BroadFSearchDegree(G, i, visited, outDegree, inDegree);  // 以每个顶点为初始顶点进行调用
//
//	// 结束遍历后，输出各个顶点的出度
//	for (int i = 0; i < G.Vertices.size; i++)
//	{
//		printf("%c 的出度 = %d，入度 = %d\n", G.Vertices.list[i], outDegree[i], inDegree[i]);
//	}
//	free(outDegree);
//	free(inDegree);
//	free(visited);
//}
//
