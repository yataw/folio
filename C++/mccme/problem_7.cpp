#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <list>
#include <limits.h>
#include <cmath>
#include <climits>
using namespace std;
const int INF = 1000000000;

//! G - Graph, p - parent, d - distance, v - vertex
void dxtra(int S, int F, vector<list<int>>& G, vector<int>& prices, vector<int>& p,
             vector<int>& d)
{
    int N = G.size();
    vector<int> used(N);

    int min = S;
    d[S] = 0;


    for(int i=0; i<N; ++i)
    {
        //find_min block
        min = -1;
        for(int j = 0; j<N; ++j)
        {
            if(!used[j] && (min == -1 || d[min] > d[j]))
                min = j;
        }

        if(d[min] == INF)
            return;

        //relaxation block
        for(auto& to: G[min])
        {

            if(!used[to])
            {
                if(d[min]+prices[min] < d[to])
                {
                    d[to] = d[min]+prices[min];
                    p[to] = min;
                }
            }
        }

        used[min] = 1;
    }
}

int main()
{
    int N;
    cin >> N;

    vector<int> prices(N);
    for(int i=0; i<N; ++i)
        cin >> prices[i];

    int M, in1, in2;
    cin >> M;

    vector<list<int>> G(N);
    for(int i=0; i<M; ++i)
    {
        cin >> in1 >> in2;

        G[in1-1].push_back(in2-1);
        G[in2-1].push_back(in1-1);
    }

    int S = 0, F = N-1; //Start, Final


    vector<int> p(N, -1);
    vector<int> d(N, INF);


    dxtra(S, F, G, prices, p, d);

    if(d[F] == INF)
    {
        cout << -1;
        return 0;
    }

    cout << d[F];

/*
    stack<int> s;

    for(int i=F; i != -1; i=p[i])
    {
        s.push(i);

    }

    while(!s.empty())
    {
        cout << s.top()+1 << ' ';
        s.pop();
    }
*/
}
