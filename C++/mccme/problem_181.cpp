#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<list>
#include<stack>
#include<queue>
#include<cstdlib>
#include<set>
#include<map>
#include<unordered_map>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
typedef vector<vector<int>> Graph; // �� list

bool flag = 0;
void dfs(int V, int parent, Graph& G, vector<int>& used, vector<int>& p)
{
    int N = G.size();

    for(int i=0; i<N; ++i)
    {
        if(!G[V][i] || used[i] || i == parent) continue;

        if(p[i] != -1)
        {
            flag = 1;
            return;
        }

        p[i] = V;
        dfs(i, V, G, used, p);

    }
    used[V] = 1;

}


int main()
{
    int N, inp;
    cin >> N;

    Graph G(N, vector<int>(N));
    vector<int> p(N, -1);
    vector<int> used(N);

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            cin >> inp;
            G[i][j] = G[j][i] = inp;
        }


    dfs(0, 0, G, used, p);

    if(flag || count(p.begin(), p.end(), -1)>1) cout << "NO";
    else cout << "YES";

}
