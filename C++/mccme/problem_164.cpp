#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


void dfs(const int& v, const vector<vector<int>>& G, vector<int>& visited)
{
    static int cc_num = 1;

    visited[v] = cc_num;

    for(int i=0; i<G.size();i++)
    {
        if(G[v][i] !=0 && !visited[i])
            dfs(i, G, visited);
    }
}

int main()
{
    int N, in, v;
    cin >> N >> v;
    v--;//!!!

    vector<vector<int>> G(N*N, vector<int>(N));
    vector<int> visited(N);
    //vector<vector<vector<int>>> G1(N*N*N, vector<vector<int>>(N*N, vector<int>(N)));

    for(int i=0; i<N; i++)
    {

        for(int j=0; j<N; j++)
            cin >> G[i][j];

    }

    dfs(v, G, visited);

    cout << count(visited.begin(), visited.end(), 1);
}
