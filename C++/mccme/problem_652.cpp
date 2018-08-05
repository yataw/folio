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


void dfs(pair<int, int> v, pair<int, int> parent, vector<vector<int>>& G, vector<vector<int>>& used)
{
    int M = G.size(), N = G[0].size();
    used[v.first][v.second] = 1;


    if(v.first>0 && G[v.first-1][v.second] && used[v.first-1][v.second] != 1)
        dfs(make_pair(v.first-1, v.second), v, G, used);

    if(v.first<M-1 && used[v.first+1][v.second] != 1 && G[v.first+1][v.second])
        dfs(make_pair(v.first+1, v.second), v, G, used);

    if(v.second>0 && used[v.first][v.second-1] != 1 && G[v.first][v.second-1])
        dfs(make_pair(v.first, v.second-1), v, G, used);

    if(v.second<N-1 && used[v.first][v.second+1] != 1 && G[v.first][v.second+1])
        dfs(make_pair(v.first, v.second+1), v, G, used);
}

int num_cc(vector<vector<int>>& G)
{
    int res=0, M = G.size(), N = G[0].size();

    vector<vector<int>> used(M, vector<int>(N));


    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            if(!used[i][j] && G[i][j] != 0)
            {
                dfs(make_pair(i, j), make_pair(i, j), G, used);
                ++res;
            }

    return res;
}



int main()
{
    int M, N;
    char in;
    cin >> M >> N;

    vector<vector<int>> G(M, vector<int>(N));

    for(auto& i: G)
        for(auto& j: i)
        {
            cin >> in;

            if(in == '#')
                j = 1;
        }

    cout << num_cc(G);
}
