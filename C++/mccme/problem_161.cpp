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


static vector<cell> pos = {{1, 2}, {1, -2}, {-1, 2}, {-1,-2}, {2,1}, {2,-1}, {-2,1}, {-2,-1}};

void push_neighs(cell v, vector<cell>& neighs, int N)
{
    for(auto& i: pos)
    {
        if(v.x+i.x >= 0 && v.x + i.x < N)
            if(v.y+i.y >= 0 && v.y + i.y < N)
                neighs.push_back({v.x+i.x, v.y+i.y});
    }
}

//v - vertex, G - graph, p - parent
void bfs(cell start, cell end, vector<vector<int>>& used, vector<vector<cell>>& p)
{

    queue<cell> q;

    cell v;
    q.push(start);
    used[start.x][start.y] = 1;
    vector<cell> neighs(8); //������

    while(!q.empty())
    {
        v = q.front();
        q.pop();

        neighs.clear();
        push_neighs(v, neighs, used.size());

        for(auto i: neighs)
        {
            if(!used[i.x][i.y])
            {
                q.push(i);
                p[i.x][i.y] = v;
                used[i.x][i.y] = true;
                if(i == end) return;
            }

        }
    }
}


int main()
{   int N;
    cin >> N;

    cell start, end;
    cin >> start.x >> start.y >> end.x >> end.y;

    start.x--;
    start.y--;
    end.x--;
    end.y--;

    vector<vector<int>> used(N, vector<int>(N));
    vector<vector<cell>> p(N, vector<cell>(N, {-1, -1}));



    bfs(start, end, used, p);

/*
    if(p[end] == -1)
    {
        cout << -1;
        return 0;
    }
*/

    vector<cell> path;
    for(cell i = end; i != cell({-1, -1}); i = p[i.x][i.y])
    {
        path.push_back(i);
    }

    reverse(path.begin(), path.end());

    cout << path.size()-1 << endl;

    if(path.size()-1 != 0)
        for(auto& i: path)
            cout << i.x+1 << ' ' << i.y+1 << endl;

}
