//
//
//void DepthFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
//{
//	int w;
//	Visit(v);                    // ���ʶ��� v
//	visited[v] = 1;              // ���ѷ��ʱ��
//	
//	w = GetFirstVex(G, v);       // ȡ��һ���ڽӶ���
//	while (w != -1)
//	{
//		if (!visited[w])
//			DepthFSearch(G, w, visited, Visit);  // �ݹ�
//		w = GetNextVex(G, v, w);                 // ȡ��һ���ڽӶ���
//	}
//}
//
//////////////// ����ͨͼ ��������ȱ���
//void DepthFirstSearch(AdjMGraph G, void Visit(int item))
//{
//	int *visited = (int *)malloc(sizeof(int) * 90);
//	for (int i = 0; i < 90; i++)
//		visited[i] = 0;                       // ���ʱ༭��ʼ��Ϊ0
//
//	for (int i = 80; i >= 10; i=i-10)
//	{
//		for (int j = 1; j <= 8; j++)
//		{
//			if (!visited[i+j])
//			DepthFSearch(G, i+j, visited, Visit); // ��ÿ������Ϊ��ʼ������е���
//		}
//	}
//	free(visited);
//}