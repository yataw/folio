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

struct cell
{
    int x, y;

    bool operator==(cell other)
    {
        if(x == other.x && y == other.y)
            return true;

        return false;
    }

    bool operator!=(cell other)
    {
        if(x == other.x && y == other.y)
            return false;

        return true;
    }
};


static vector<cell> pos = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void push_neighs(cell v, vector<cell>& neighs, int N, int M)
{
    for(auto& i: pos)
    {
        if(v.x+i.x >= 0 && v.x + i.x < N)
            if(v.y+i.y >= 0 && v.y + i.y < M)
                neighs.push_back({v.x+i.x, v.y+i.y});
    }
}


//v - vertex, G - graph, p - parent
void bfs(vector<vector<int>>& G)
{
    int N = G.size(), M = G[0].size();

    vector<vector<int>> used(N, vector<int>(M));

    queue<cell> q;

    for(int i=0; i<N; ++i)
        for(int j=0; j<M; ++j)
        {
            if(G[i][j] == 0)
            {
                q.push(cell({i, j}));
                used[i][j] = 1;
            }

        }


    cell v;
    vector<cell> neighs(4);
    while(!q.empty())
    {
        v = q.front();
        q.pop();

        neighs.clear();
        push_neighs(v, neighs, N, M);

        for(auto& i: neighs)
        {
            if(!used[i.x][i.y])
            {
                used[i.x][i.y] = 1;
                G[i.x][i.y] = G[v.x][v.y] + 1;
                q.push(i);
            }
        }
    }

}


int main()
{   int N, M, in;
    cin >> N >> M;

    vector<vector<int>> G(N, vector<int>(M));

    for(int i=0; i<N; ++i)
        for(int j=0; j<M; ++j)
        {
            cin >> in;
            if(in) G[i][j] = !in;
            else G[i][j] = -1;
        }

    bfs(G);

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<M; ++j)
        {
            cout << G[i][j] << ' ';
        }

        cout << endl;
    }

}
