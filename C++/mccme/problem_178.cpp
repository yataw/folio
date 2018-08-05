#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<list>
#include<stack>
#include<queue>
#include<cstdlib>
using namespace std;

const int INF = 1000000000;
typedef vector<vector<int>> Graph;
struct Edge{
    int a, b, price;
};


void Ford(int v, vector<Edge>& edges, vector<int>& d)
{
    int N = d.size();
    int M = edges.size();
    d[v] = 0;

    for(int i=0; i<N; ++i)
        for(int j=0; j<M; ++j)
            if(d[edges[j].a] != INF)
                d[edges[j].b] = min(d[edges[j].b], d[edges[j].a] + edges[j].price);
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;
    vector<int> d(N, INF);

        int _a, _b, _price;
    for(int i=0; i<M; ++i)
    {
        cin >> _a >> _b >> _price;
        _a--; _b--;
        edges.push_back({_a, _b, _price});
    }

    Ford(0, edges, d);

    for(auto& i: d)
        cout << (i==INF?30000:i) << ' ';
}
