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
    int N, inp;
    cin >> N;

    vector<int> v;

    for(int i=0; i<N; ++i)
    {
        cin >> inp;
        v.push_back(inp);
    }

    int q, w;
    cin >> q >> w;
    q = v[q-1];
    w = v[w-1];

    for(auto& i: v)
        if(i == q) i = w;

    for(auto& i: v)
        cout << i << ' ';


}
