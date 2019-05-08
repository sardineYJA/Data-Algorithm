#include <list>
#include <stack>
#include <queue>
#include <iostream>
using namespace std ;

/**********    ͼ�������������� **********/

class Graphic 
{
private :
	int vertexNum;          // ������
	list <int> * adjacents; // �ڽӱ�洢�߹�ϵ
public :
	Graphic (int vertex) 
	{
		this->vertexNum = vertex;
		adjacents = new list <int>[this->vertexNum];
	}

	int getVertexNum() 
	{
		return this->vertexNum;// ��ȡ������
	}

	void setVertexNum(int number) 
	{
		this->vertexNum = number;// �޸Ķ�����
	}

	void addEdge(int start, int end)
	{
		this->adjacents[start].push_back(end);// ��ӱ�
	}

	void countOutdegree(int * outdegree);     // �������ж���ĳ���
	bool isDAG();                             // �ж��Ƿ�Ϊ�����޻�ͼ
	void deleteVertex(int v);                 // ɾ��ָ���Ķ����Լ�����ȱ�
	void topologySort();                      // ��������
};


/********************** �ж��Ƿ�Ϊ�����޻�ͼ ***************/
/*
1.�����޻�ͼһ������һ����������Ϊ 0 �Ķ��㣬���û�������Ķ��㣬
  ��һ�����л�ͼ
2.���ͼ�о��г���Ϊ 0 �Ķ��㣬��ɾ���ö��㼰�����б�
3.�ж�ʣ�µ���ͼ�Ƿ���г���Ϊ 0 �ĵ㣬�������ɾ����
  ��������е㱻ɾ�����������޻�ͼ��������
*/


// ����ÿ������ĳ��ȣ������ж��Ƿ�Ϊ�����޻�ͼ
void Graphic::countOutdegree(int * outdegree) 
{
	int vertexes = this->getVertexNum();
	list<int>::iterator iters;

	for (int v = 0; v < vertexes; v++)
	{
		int number = 0;
		for (iters = adjacents[v].begin(); iters != adjacents[v].end();
			iters++) 
		{
			number++;   // ͳ��ÿ������ĳ���
		}
		outdegree[v] = number;
	}
}
// ɾ��ɾ���������ȱߣ������ж��Ƿ�Ϊ�����޻�ͼ
void Graphic::deleteVertex(int v)
{
	///////////////////////////// ����
	int vertexes = this->getVertexNum();
	cout << "��������" << vertexes << endl;
	cout << "ȥ���㣺" << v << endl;

	list<int>::iterator iters;
	for (int i = 0; i < vertexes; i++)
		{
			for (iters = this->adjacents[i].begin(); iters != this->adjacents[i].end();) 
			{
				if (*iters == v)
				{
					iters = adjacents[i].erase(iters);
				}
				else
					++iters;
			}

			cout << "��� i " << i << endl;
		}


	int *outdegree = new int[vertexes];   // �洢ÿ������ĳ���
	
	for (int i = 0; i < vertexes; i++)
		outdegree[i] = 0;

	Graphic::countOutdegree(outdegree);   // ����ÿ������ĳ���


	for (int i = 0; i < vertexes; i++)
		cout << outdegree[i] << "  ";
	cout << endl;
	///////////////////////////// ����




	list <int> * p = &adjacents[v];  // ��ȡָ����ĳ���
	//p->clear();
	//delete p;  // ɾ��ָ��������г��� ?????????????????

	// �޸�ͼ�ṹ
	for (int i = v; i < vertexNum-1; i++)
		adjacents[v] = adjacents[v+1];   // ǰ��һ��
	this->vertexNum--;

	list<int> * newAdjacents = new list<int>[this->vertexNum];
	for (int j = 0; j < this->vertexNum; j++)
		newAdjacents[j] = adjacents[j];

	list<int> * q = adjacents;
	this->adjacents = newAdjacents;
	//delete p;/////////////////////////// ???????????
}

bool Graphic::isDAG()
{
	int vertexes = this->getVertexNum();  // ͼ�Ķ�����
	int *outdegree = new int[vertexes];   // �洢ÿ������ĳ���
	
	for (int i = 0; i < vertexes; i++)
		outdegree[i] = 0;

	Graphic::countOutdegree(outdegree);   // ����ÿ������ĳ���


	////////////////////////////////////////////
	cout << "isDAG������";
	for (int i = 0; i < vertexes; i++)
		cout << outdegree[i] << "  ";
	cout << endl;
	///////////////////////////// ����




	int flag = 0;         // �ж��Ƿ����޳��ȵĶ��㣬0Ϊû�У�1Ϊ��
	list <int> zeroOutDegree;
	for (int j = 0; j < vertexes; j++)
		if (outdegree[j] == 0)
			zeroOutDegree.push_back(j);

	if (zeroOutDegree.size() != 0)
		flag = 1;         // �ж��Ƿ���ڳ���Ϊ0�ĵ�

	if (flag)      
	{
		// ����г���Ϊ0 �ĵ㣬��ɾ���õ������ȱ�
		this->deleteVertex(zeroOutDegree.front()); 
		cout << this->getVertexNum() << endl;
		// �ݹ��жϸ�ͼ
		if (this->getVertexNum() > 0)
			this->isDAG();
		else
			return true;    // ���������е㱻ɾ������Ϊ�����޻�ͼ
	}
	else
		return false;       // ��������ڳ���Ϊ 0 �ĵ㣬���л�
}



/****************** �ڽ�����ṹ���������� ********************/
/*
�ҵ����һ���㣬�����洢��һ��ջ�У�ջ�Ĵ�СΪͼ�Ķ�����
�ҵ����һ����֮�󣬽���ɾ�����ظ���ͼû�ж���
��ջ�еĵ����γ�ջ�������������
adjacents[i]���ϴ洢�˵�i�������ıߣ������ȵ��ĸ��㣩
*/
void Graphic::topologySort()
{
	int flag = 1;        // ͼ���޻��ı�־
	stack<int> s;        // ���ô洢������������ջ
	queue<int> q;        // �洢����Ϊ0 �Ķ���Ķ���

	int vertexes = this->getVertexNum();  // ������
	int * outDegree = new int[vertexes];  // ������ĳ���

	for (int i = 0; i < vertexes; i++)
		outDegree[i] = 0;

	list<int>::iterator iters;
	for (int j = 0; j < vertexes; j++)
	{
		int outEdgeNumber = 0;
		for (iters = this->adjacents[j].begin(); iters != this->adjacents[j].end();
			iters++) 
		{
			outEdgeNumber++;   // ͳ��ÿ������ĳ���
		}
		outDegree[j] = outEdgeNumber;
	}

	for (int i = 0; i < vertexes; i++)
		if (outDegree[i] == 0)
			q.push(i);     // ������Ϊ 0 �Ķ������

	for (int v = 0; v < vertexes; v++)
	{
		if (q.empty())  // ����Ϊ�գ�ͼ���л�
		{
			flag = 0; 
			break;
		}
		int vertex = q.front();  // ������Ԫ�س���
		s.push(vertex);          // �����Ԫ����ջ
		q.pop();
		outDegree[vertex] = -1;  // ��Ǹö����ѷ��ʹ�

		for (int i = 0; i < vertexes; i++)
		{
			for (iters = this->adjacents[i].begin(); iters != this->adjacents[i].end();
			iters++) 
			{
				if (*iters == vertex)
				{
					outDegree[i]--; // �������б�ָ��ý��Ķ���ĳ��ȼ�һ
				
					if (outDegree[i] == 0)
						q.push(i);  // ������µĳ���Ϊ0�ĵ㣬��õ����
				}
			}
		}
	}

	if (flag)
		while (!s.empty())
		{
			cout << s.top() << "  "; // ���ջԪ�أ��õ���������
			s.pop();
		}
	else
		cout << "��ͼ�л����ܽ�����������" << endl;
}



void mainasfc()
{
	Graphic * g = new Graphic(6);
	g->addEdge(0,1);
	g->addEdge(0,2);
	g->addEdge(2,3);
	g->addEdge(2,4);
	g->addEdge(1,5);
	g->addEdge(3,5);
	g->addEdge(4,5);
	//g->addEdge(5,2);    // ɾ������

	//g->topologySort();

	if ( g->isDAG() == true )
		cout << "true" << endl;
	if ( g->isDAG() == false )
		cout << "false" << endl;

	//g->topologySort();

	/*
	�ж��Ƿ��������޻�ͼ��ɾ���㼰��ߵĺ����д�����
	������ҵķ���ɾ���ߣ�������0 ��1�� 2�� 3�� 4 
	���ɾ��1�������1 ���ĵ�߼�һ������Ḳ�ǣ���0,2,3,4���0,1,2,3��
	������û�취�жϴ�ʱ1������ԭ���ļ��㡣
	*/

}


