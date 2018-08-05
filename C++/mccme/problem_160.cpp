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

//v - vertex, G - graph, p - parent
void bfs(int start, int end, vector<vector<int>>& G, vector<int>& used, vector<int>& p)
{
    int N = G.size();
    queue<int> q;

    int v;
    q.push(start);
    used[start] = 1;

    while(!q.empty())
    {
        v = q.front();
        q.pop();

        for(int i=0; i<N; ++i)
        {
            if(G[v][i] && !used[i])
            {
                q.push(i);
                p[i] = v;
                used[i] = true;
                if(i == end) return;
            }

        }
    }
}


int main()
{   int N;
    cin >> N;

    vector<vector<int>> G(N, vector<int>(N));
    vector<int> used(N);
    vector<int> p(N, -1);

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            cin >> G[i][j];

    int start, end;

    cin >> start >> end;
    start--; end--;

    if(start == end)
    {
        cout << 0;
        return 0;
    }

    bfs(start, end, G, used, p);

    if(p[end] == -1)
    {
        cout << -1;
        return 0;
    }


    vector<int> path;
    for(int i = end; i != -1; i = p[i])
    {
        path.push_back(i);
    }

    reverse(path.begin(), path.end());

    cout << path.size()-1 << endl;

    if(path.size()-1 != 0)
        for(auto& i: path)
            cout << i+1 << ' ';

}
