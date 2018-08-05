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

//!p - parent, d - distance, v - vertex
void dxtra(int S, int F, vector<vector<int>>& G, vector<int>& p, vector<int>& d)
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
        for(int to=0; to<N; ++to)
        {

            if(G[min][to]>-1 && !used[to])
            {
                if(d[min]+G[min][to] < d[to])
                {
                    d[to] = d[min]+G[min][to];
                    p[to] = min;
                }
            }
        }

        used[min] = 1;
    }
}

int main()
{
    int N, S, F;
    cin >> N >> S >> F;
    S--; F--;

    vector<vector<int>> G(N, vector<int>(N));

    for(int i = 0; i<N; ++i)
        for(int j = 0; j<N; ++j)
            cin >> G[i][j];

    vector<int> p(N, -1);
    vector<int> d(N, INF);


    dxtra(S, F, G, p, d);

    if(d[F] == INF)
    {
        cout << -1;
        return 0;
    }

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

}
