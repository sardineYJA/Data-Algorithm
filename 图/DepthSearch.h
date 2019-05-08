


////////////////// ��ͨͼ��������ȱ���

// ��ͨͼ G �� v Ϊ��ʼ����ģ����ʲ���ΪVisit()
// ����visited �����Ӧ�����Ƿ��ѷ��ʹ���0��ʾδ���ʣ�1��ʾ�ѷ��ʣ�
void DepthFSearch(AdjMGraph G, int v, int visited[], void Visit(int item))
{
	int w;
	Visit(G.Vertices.list[v]);   // ���ʶ��� v
	visited[v] = 1;              // ���ѷ��ʱ��
	
	/*
	for (w = 0; w < G.Vertices.size; w++)
		if (G.edge[v][w] > 0 && G.edge[v][w] < MaxWeight && !visited[w])
			DepthFSearch(G, w, visited, Visit);
	*/

	w = GetFirstVex(G, v);       // ȡ��һ���ڽӶ���
	while (w != -1)
	{
		if (!visited[w])
			DepthFSearch(G, w, visited, Visit);  // �ݹ�
		w = GetNextVex(G, v, w);                 // ȡ��һ���ڽӶ���
	}
}



////////////// ����ͨͼ ��������ȱ���
void DepthFirstSearch(AdjMGraph G, void Visit(int item))
{
	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);
	for (int i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;                       // ���ʱ༭��ʼ��Ϊ0

	for (int i = 0; i < G.Vertices.size; i++)
		if (!visited[i])
			DepthFSearch(G, i, visited, Visit); // ��ÿ������Ϊ��ʼ������е���
	free(visited);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

// ������ȱ������ҵ���������֮���·���������Ƕ���

int DepthFSearchPath(AdjMGraph G, int visited[], int v1, int v2)
{
	int w;
	int flag = 0;
	visited[v1] = 1;         // ���ѷ��ʱ��
	w = GetFirstVex(G, v1);  // ȡ��һ���ڽӶ���

	while (w != -1)          // ��·�ߴ����￪ʼֱ��β��
	{
		if (w == v2)         // ����ҵ�·��
		{
			flag = 1;
			break;
		}

		if (!visited[w])
			if ((flag = DepthFSearchPath(G, visited, w, v2)) == 1)
				break;
		w = GetNextVex(G, v1, w);   // ȡ��һ���ڽӶ���
	}
	return flag;
}



/////////  �ж��Ƿ�����±�Ϊ v1 �Ķ��㵽�±�Ϊ v2 �Ķ����·��
void DepthFirstSearchPath(AdjMGraph G, int v1, int v2)
{
	int *visited = (int *)malloc(sizeof(int) * G.Vertices.size);

	for (int i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;         // ���ʱ༭��ʼ��Ϊ0		

	// ֻ��Ҫ��v1 ������ȱ���
	int flag = DepthFSearchPath(G, visited, v1, v2);
	free(visited);

	printf("%c �� %c �Ƿ����·����", G.Vertices.list[v1], G.Vertices.list[v2]);
	if (flag == 1)
		printf ("����·��\n");
	else
		printf("������·��\n");
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
ͼ��������������㷨ʹ�ö�ջ�Էǵݹ����ʽʵ�֣�
�� ���Ƚ���ʼ����v��ջ��
�� ����ջ��Ϊ��ʱ���ظ����´���
ջ��Ԫ�س�ջ��
��δ���ʣ������֮�����÷��ʱ�־������δ�����ʵ��ڽӵ���ջ��
�� ���ͼ�л���δ�����ʵ��ڽӵ㣬ѡ��һ���ظ����Ϲ��̡�
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

