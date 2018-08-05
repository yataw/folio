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

bool flag = 0;

void dfs(int v, vector<vector<int>>& G, vector<int>& used)
{
    used[v] = 1;

    for(int i=0; i<G.size(); ++i)
    {
        if(G[v][i])
            if(used[i] == 1)
                {
                flag = 1;
                }
            else if(used[i] == -1)
                    dfs(i, G, used);
    }

    used[v] = 0;
}


int main()
{
    int N;
    cin >> N;

    vector<vector<int>> G(N, vector<int>(N));

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            cin >> G[i][j];
        }

    vector<int> used(N, -1);

    for(int i=0; i<N; ++i)
    {
        if(used[i] == -1)
            dfs(i, G, used);

    }

    cout << flag;

}
