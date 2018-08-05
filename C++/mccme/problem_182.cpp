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

list<pair<int, int>> res;
void dfs(int V, int parent, vector<list<int>>& G, vector<int>& used, vector<int>& p)
{

    for(auto& i: G[V])
    {
        if(used[i] || i == parent || p[i] != -1) continue;

        p[i] = V;
        res.push_back({V, i});
        dfs(i, V, G, used, p);

    }
    used[V] = 1;

}


int main()
{
    int N, M, in1, in2;
    cin >> N >> M;

    vector<list<int>> G(N);
    vector<int> p(N, -1);
    vector<int> used(N);

    for(int i=0; i<M; ++i)
    {
        cin >> in1 >> in2;
        in1--; in2--;
        G[in1].push_back(in2);
        G[in2].push_back(in1);
    }

    p[0] = 0;
    dfs(0, 0, G, used, p);

    for(auto& i: res)
    {
        cout << i.first+1 << ' ' << i.second+1 << endl;
    }

}
