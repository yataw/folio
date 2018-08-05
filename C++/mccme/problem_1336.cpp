#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<list>
#include<stack>
#include<queue>
#include<cstdlib>
using namespace std;

typedef vector<list<pair<int, double>>> Graph;

void dxtra(int S, int E, Graph& G, vector<double>& price)
{
    int N = G.size();
    vector<int> used(N);

    int max = S;
    price[S] = 1;

    for(int i=0; i<N; ++i)
    {
        max = -1;

        for(int j=0; j<N; ++j)
        {
            if(!used[j] && (max == -1 || price[j]>price[max]))
                max = j;
        }

    if(max == -1) return;

    for(auto& to: G[max])
    {
        if(!used[to.first] && price[to.first] < price[max]*to.second)
        {
            price[to.first] = price[max]*to.second;
        }
    }
    used[max] = 1;

    }
}

int main()
{
    int N, M, v1, v2, prob;
    cin >> N >> M;

    int S, E;
    cin >> S >> E;
    S--; E--;

    Graph G(N); //first - vertex_to, second - probability
    vector<double> price(N, 0.);

    for(int i=0; i<M; ++i)
    {
        cin >> v1 >> v2 >> prob;


        G[v1-1].push_back(make_pair(v2-1, 1.-prob/100.));
        G[v2-1].push_back(make_pair(v1-1, 1.-prob/100.));
    }

    dxtra(S, E, G, price);

    cout  << 1-price[E];

}
