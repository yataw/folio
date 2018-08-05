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

//v = current
int dfs(int v, int root, vector<vector<int>>& G, vector<int>& used)
{
    used[v] = 1;

    for(int i=0; i<G.size(); i++)
    {
        if(!G[v][i] || i == root) continue;

        if(used[i])
        {
            return 0;
        }
        else
            if(!dfs(i, v, G, used)) return 0;
    }


    return 1;
}

bool check(vector<int>& used)
{
    for(auto i: used)
    {
        if(!i)
            return 0;
    }

    return 1;
}

int main()
{
    int N, in;
    cin >> N;

    vector<vector<int>> G(N, vector<int>(N));
    vector<int> visited(N);

    //vector<vector<vector<int>>> G1(N*N*N, vector<vector<int>>(N*N, vector<int>(N)));

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
            cin >> G[i][j];
    }


    if(dfs(0, 0, G, visited) > 0 && check(visited))
        cout<<"YES";
    else
        cout<<"NO";

}
