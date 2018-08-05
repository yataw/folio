#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
using namespace std;



void dfs(int v, vector<int>& comp, vector<list<int>>& G, vector<int>& visited);
//!connectivity components
void cc_num(vector<list<int>>& G)
{
    vector<int> visited(G.size());
    vector<vector<int>> comp(G.size());

    int cc_number=0;

    for(int i=0; i<visited.size(); i++)
    {
        if(!visited[i])
        {
        dfs(i, comp[cc_number++], G, visited);
        }
    }


    cout << cc_number << endl;

    for (int i=1; i<=cc_number;i++)
    {
        cout << comp[i-1].size() << endl;
        for(auto& j:comp[i-1])
            cout << j+1 << ' ';
        cout << endl;
    }


}

void dfs(int v, vector<int>& comp, vector<list<int>>& G, vector<int>& visited)
{
    visited[v] = 1;
    comp.push_back(v);

    for(list<int>::iterator it = G[v].begin(); it != G[v].end(); it++)
    {
        if(!visited[*it])
            dfs(*it, comp, G, visited);
    }
}

int main()
{
    int N, M, in1, in2;
    cin >> N >> M;
    //!v--;

    vector<list<int>> G(N);

    //vector<vector<vector<int>>> G1(N*N*N, vector<vector<int>>(N*N, vector<int>(N)));

    for(int i=0; i<M; i++)
    {
        cin >> in1 >> in2;
        G[in1-1].push_back(in2-1);
        G[in2-1].push_back(in1-1);

    }

    cc_num(G);
}
