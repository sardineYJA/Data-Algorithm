#include <list>
#include <stack>
#include <queue>
#include <iostream>
using namespace std ;

/**********    图的拓扑排序例子 **********/

class Graphic 
{
private :
	int vertexNum;          // 顶点数
	list <int> * adjacents; // 邻接表存储边关系
public :
	Graphic (int vertex) 
	{
		this->vertexNum = vertex;
		adjacents = new list <int>[this->vertexNum];
	}

	int getVertexNum() 
	{
		return this->vertexNum;// 获取顶点数
	}

	void setVertexNum(int number) 
	{
		this->vertexNum = number;// 修改顶点数
	}

	void addEdge(int start, int end)
	{
		this->adjacents[start].push_back(end);// 添加边
	}

	void countOutdegree(int * outdegree);     // 计算所有顶点的出度
	bool isDAG();                             // 判断是否为有向无环图
	void deleteVertex(int v);                 // 删除指定的顶点以及其出度边
	void topologySort();                      // 拓扑排序
};


/********************** 判断是否为有向无环图 ***************/
/*
1.有向无环图一定存在一个或多个出度为 0 的顶点，如果没有这样的顶点，
  则一定是有环图
2.如果图中具有出度为 0 的顶点，则删除该顶点及其所有边
3.判定剩下的字图是否具有出度为 0 的点，有则继续删除，
  到最后所有点被删除则是有向无环图，否则不是
*/


// 计算每个顶点的出度，用于判断是否为有向无环图
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
			number++;   // 统计每个顶点的出度
		}
		outdegree[v] = number;
	}
}
// 删除删除点和其出度边，用于判断是否为有向无环图
void Graphic::deleteVertex(int v)
{
	///////////////////////////// 测试
	int vertexes = this->getVertexNum();
	cout << "顶点数：" << vertexes << endl;
	cout << "去掉点：" << v << endl;

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

			cout << "输出 i " << i << endl;
		}


	int *outdegree = new int[vertexes];   // 存储每个顶点的出度
	
	for (int i = 0; i < vertexes; i++)
		outdegree[i] = 0;

	Graphic::countOutdegree(outdegree);   // 计算每个顶点的出度


	for (int i = 0; i < vertexes; i++)
		cout << outdegree[i] << "  ";
	cout << endl;
	///////////////////////////// 测试




	list <int> * p = &adjacents[v];  // 获取指定点的出表
	//p->clear();
	//delete p;  // 删除指定点的所有出度 ?????????????????

	// 修改图结构
	for (int i = v; i < vertexNum-1; i++)
		adjacents[v] = adjacents[v+1];   // 前移一格
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
	int vertexes = this->getVertexNum();  // 图的顶点数
	int *outdegree = new int[vertexes];   // 存储每个顶点的出度
	
	for (int i = 0; i < vertexes; i++)
		outdegree[i] = 0;

	Graphic::countOutdegree(outdegree);   // 计算每个顶点的出度


	////////////////////////////////////////////
	cout << "isDAG函数：";
	for (int i = 0; i < vertexes; i++)
		cout << outdegree[i] << "  ";
	cout << endl;
	///////////////////////////// 测试




	int flag = 0;         // 判断是否有无出度的顶点，0为没有，1为有
	list <int> zeroOutDegree;
	for (int j = 0; j < vertexes; j++)
		if (outdegree[j] == 0)
			zeroOutDegree.push_back(j);

	if (zeroOutDegree.size() != 0)
		flag = 1;         // 判断是否存在出度为0的点

	if (flag)      
	{
		// 如果有出度为0 的点，则删除该点和其出度边
		this->deleteVertex(zeroOutDegree.front()); 
		cout << this->getVertexNum() << endl;
		// 递归判断该图
		if (this->getVertexNum() > 0)
			this->isDAG();
		else
			return true;    // 如果最后所有点被删除，则为有向无环图
	}
	else
		return false;       // 如果不存在出度为 0 的点，则有环
}



/****************** 邻接链表结构的拓扑排序 ********************/
/*
找到最后一个点，将它存储在一个栈中，栈的大小为图的顶点数
找到最后一个点之后，将其删除，重复至图没有顶点
将栈中的点依次出栈，完成拓扑排序
adjacents[i]集合存储了点i到其他的边（即出度到哪个点）
*/
void Graphic::topologySort()
{
	int flag = 1;        // 图中无环的标志
	stack<int> s;        // 设置存储拓扑排序结果的栈
	queue<int> q;        // 存储出度为0 的顶点的队列

	int vertexes = this->getVertexNum();  // 顶点数
	int * outDegree = new int[vertexes];  // 各顶点的出度

	for (int i = 0; i < vertexes; i++)
		outDegree[i] = 0;

	list<int>::iterator iters;
	for (int j = 0; j < vertexes; j++)
	{
		int outEdgeNumber = 0;
		for (iters = this->adjacents[j].begin(); iters != this->adjacents[j].end();
			iters++) 
		{
			outEdgeNumber++;   // 统计每个顶点的出度
		}
		outDegree[j] = outEdgeNumber;
	}

	for (int i = 0; i < vertexes; i++)
		if (outDegree[i] == 0)
			q.push(i);     // 将出度为 0 的顶点入队

	for (int v = 0; v < vertexes; v++)
	{
		if (q.empty())  // 队列为空，图中有环
		{
			flag = 0; 
			break;
		}
		int vertex = q.front();  // 队列首元素出队
		s.push(vertex);          // 将最后元素入栈
		q.pop();
		outDegree[vertex] = -1;  // 标记该顶点已访问过

		for (int i = 0; i < vertexes; i++)
		{
			for (iters = this->adjacents[i].begin(); iters != this->adjacents[i].end();
			iters++) 
			{
				if (*iters == vertex)
				{
					outDegree[i]--; // 将所有有边指向该结点的顶点的出度减一
				
					if (outDegree[i] == 0)
						q.push(i);  // 如果有新的出度为0的点，则该点入队
				}
			}
		}
	}

	if (flag)
		while (!s.empty())
		{
			cout << s.top() << "  "; // 输出栈元素，得到拓扑排序
			s.pop();
		}
	else
		cout << "该图有环不能进行拓扑排序" << endl;
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
	//g->addEdge(5,2);    // 删除这条

	//g->topologySort();

	if ( g->isDAG() == true )
		cout << "true" << endl;
	if ( g->isDAG() == false )
		cout << "false" << endl;

	//g->topologySort();

	/*
	判断是否是有向无环图：删除点及其边的函数有错？？？
	如果用我的方法删除边，本来点0 ，1， 2， 3， 4 
	如果删点1，则则根1 连的点边减一；后面会覆盖（即0,2,3,4变成0,1,2,3）
	这样就没办法判断此时1到底是原来的几点。
	*/

}


