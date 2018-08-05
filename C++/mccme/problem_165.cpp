#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <list>
#include <limits.h>
#include <cmath>
#include <climits>
using namespace std;


//!connectivity components

int dfs(int v, int root, vector<list<int>>& G, vector<int>& used, vector<int>& comp)
{
    used[v] = 1;
    comp[v] = !comp[root];

    for(list<int>::iterator it = G[v].begin(); it != G[v].end(); it++)
    {
        if(*it == root) continue;

        if(!used[*it])
        {
            if(dfs(*it, v, G, used, comp))
                return 1;
        }
        else
            if(comp[*it] == comp[v])
                return 1;
    }

return 0;
}

int main()
{
    int N, M, in1, in2;
    cin >> N >> M;
    //!v--;

    vector<list<int>> G(N);
    vector<int> used(N);
    vector<int> comp(N);

    //vector<vector<vector<int>>> G1(N*N*N, vector<vector<int>>(N*N, vector<int>(N)));

    for(int i=0; i<M; i++)
    {
        cin >> in1 >> in2;
        G[in1-1].push_back(in2-1);
        G[in2-1].push_back(in1-1);

    }

    for(int i=0; i<N; ++i)
        if(!used[i])
            if(dfs(i, i, G, used, comp))
            {
                cout << "NO";
                return 0;
            }


    cout << "YES\n";

    for(int i=0; i<N; ++i)
        if(comp[i])
            cout << i+1 << ' ';
}
