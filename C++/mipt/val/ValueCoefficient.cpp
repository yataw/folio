#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define INF 1e10

struct Edge
{
	size_t from;
	size_t to;
	double cost;

	Edge() {}
	Edge(size_t _from, size_t _to, double _cost) : from(_from), to(_to), cost(_cost) {}
	~Edge() {}
};

void Initialization(std::vector<Edge>& G, std::vector<int>& parent, std::vector<double>& dist)
{
	std::ifstream fin;
	fin.open("input.txt");

	size_t n;
	fin >> n;
	parent.resize(n);
	dist.resize(n);

	for(size_t i = 0; i < n; ++i)
	{
		parent[i] = -1;
		for(size_t j = 0; j < n; ++j)
		{
			double t;
			fin >> t;
			G.push_back(Edge(i,j,log(t))); // храним в виде логарифмов, чтобы складывать как расстояния
		}
	}
	fin.close();
}
void Show(std::vector<Edge>& G)
{
	for(size_t i = 0; i < G.size(); ++i)
		std::cout << G[i].from << ' ' << G[i].to << ' ' << G[i].cost << '\n';
}
void Relax(std::vector<Edge>& G, std::vector<int>& parent, std::vector<double>& dist, size_t j, int& flag)
{
	if (dist[G[j].to] > dist[G[j].from] + G[j].cost)
	{
		dist[G[j].to] = std::max(-INF, dist[G[j].from] + G[j].cost);
		parent[G[j].to] = G[j].from;
		flag = G[j].to;
	}
}
void ShowSolution(std::vector <size_t>& solution)
{double res = 0;
	std::ofstream fout;
	fout.open("output.txt");
	if( solution.size() > 1)
		for(auto it = solution.rbegin(); it != solution.rend(); ++it)
			fout << *it+1 << ' ';
	else
		fout << '0';

	fout.close();
}


void BellmanFord()
{
	std::vector <Edge> G;
	std::vector <int> parent;
	std::vector <double> dist;
	std::vector <size_t> solution;


	Initialization(G, parent, dist);
//	Show(G);

	int flag(-1); // проверка на то, что произошла реласкация
	for(size_t i = 0; i < parent.size(); ++i)
	{
		flag = -1;
		for(size_t j = 0; j < G.size(); ++j)
			Relax(G,parent,dist,j,flag);
	}


	if( flag == -1 ) //	если в последний раз, релаксации не произошло, то в графе нет циклов отрицательного веса
		solution.push_back(0);
	else // иначе, ищем цикл отрицательного веса
	{
		int temp = flag;
		for(size_t i = 0; i < parent.size(); ++i)
			temp = parent[temp];

		int current = temp;
		while(true)
		{
			solution.push_back(current);
			if(( current == temp )&&( solution.size() > 1 ))
				break;
			current = parent[current];
		}
	}

	ShowSolution(solution);
}


int main()
{
	BellmanFord();
//	std::cout << '\n';
//	system("pause");
	return 0;
}
