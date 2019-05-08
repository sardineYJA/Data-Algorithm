//
////////////////////////// ��ͨͼ�Ĺ�����ȱ���
//
//void BroadFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
//{
//	int u, w;
//	SeqCQueue queue;
//	Visit(G.Vertices.list[v]);      // ���ʶ��� v 
//	visited[v] = 1;                 // ���ѷ���
//	
//	QueueInitiate(&queue);          // ���г�ʼ��
//	QueueAppend(&queue, v);         // ���� v �����
//	while (QueueNotEmpty(queue))    // ���зǿ�ʱ
// 	{
//		QueueDelete(&queue, &u);    // ������
//		w = GetFirstVex(G, u);      // ȡ���� u �ĵ�һ���ڽӶ��� w
//		while (w != -1)
//		{
//			if (!visited[w])
//			{
//				Visit(G.Vertices.list[w]);  // ���ʶ��� w
//				visited[w] = 1;
//				QueueAppend(&queue, w);     // ���� w �����
//			}
//			w = GetNextVex(G, u, w);        
//		}
//	}
//}
//
//
//////////// ����ͨͼ�Ĺ�����ȱ���
//void BroadFirstSearch(AdjMGraph G, void Visit(int item))
//{
//	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);
//	for (int i = 0; i < G.Vertices.size; i++)
//		visited[i] = 0;            // ���ʱ�ǳ�ʼ��Ϊ 0
//	
//	for (int i = 0; i < G.Vertices.size; i++)
//		if (!visited[i])
//			BroadFSearch(G, i, visited, Visit);  // ��ÿ������Ϊ��ʼ������е���
//	free(visited);
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//// ���ù�����ȱ���������û��Ȩֵ���ҵ�ÿ����ĳ���
//// ÿ���ʵ�һ�����㣬����������ڽӶ���
//
//// ��ȱ������ҵ�ÿ����������
//// ÿ����һ�����㣬������ȫ���ڽӵ��inDegree[]++
//
//// u v w ȫ���±�
//void BroadFSearchDegree(AdjMGraph G, int v, int visited[], int outDegree[], int inDegree[])
//{
//	int u, w;
//	SeqCQueue queue;
//	visited[v] = 1;                 // ���ѷ���
//	
//	QueueInitiate(&queue);          // ���г�ʼ��
//	QueueAppend(&queue, v);         // ���� v �����
//	while (QueueNotEmpty(queue))    // ���зǿ�ʱ
// 	{
//		QueueDelete(&queue, &u);    // ������
//		w = GetFirstVex(G, u);      // ȡ���� u �ĵ�һ���ڽӶ��� w
//		while (w != -1)
//		{
//			// ���� u ���ȼ�1
//			outDegree[u]++;
//
//			// u ���ڽӵ����ȼ�1
//			inDegree[w]++;
//
//			if (!visited[w])
//			{
//				visited[w] = 1;
//				QueueAppend(&queue, w);     // ���� w �����
//			}
//			w = GetNextVex(G, u, w);        
//		}
//	}
//}
//void BroadFirstSearchDegree(AdjMGraph G)
//{
//	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);        // �Ƿ񱻷��ʹ�
//	int *outDegree = (int *)malloc(sizeof(int) * G.Vertices.size);      // ÿ������ĳ���
//	int *inDegree = (int *)malloc(sizeof(int) * G.Vertices.size);       // ÿ����������
//	
//	// ��ʼ��
//	for (int i = 0; i < G.Vertices.size; i++)
//	{
//		visited[i] = 0;            // ���ʱ�ǳ�ʼ��Ϊ 0
//		outDegree[i] = 0;          // �������ʼ����Ϊ 0
//		inDegree[i] = 0;           // �������ʼ���Ϊ 0
//	}
//		
//	for (int i = 0; i < G.Vertices.size; i++)
//		if (!visited[i])
//			BroadFSearchDegree(G, i, visited, outDegree, inDegree);  // ��ÿ������Ϊ��ʼ������е���
//
//	// ���������������������ĳ���
//	for (int i = 0; i < G.Vertices.size; i++)
//	{
//		printf("%c �ĳ��� = %d����� = %d\n", G.Vertices.list[i], outDegree[i], inDegree[i]);
//	}
//	free(outDegree);
//	free(inDegree);
//	free(visited);
//}
//
