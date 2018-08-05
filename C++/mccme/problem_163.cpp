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

void push_neighs(pair<cell, cell> v, vector<pair<cell, cell>>& neighs, int N)
{
    pair<cell, cell> new_v;


    for(auto& i: pos)
    {
        if(v.first.x+i.x >= 0 && v.first.x + i.x < N)
            if(v.first.y+i.y >= 0 && v.first.y + i.y < N)
                for(auto& j: pos)
                {
                    if(v.second.x+j.x >= 0 && v.second.x + j.x < N)
                        if(v.second.y+j.y >= 0 && v.second.y + j.y < N)
                            {
                                new_v.first.x = v.first.x+i.x;
                                new_v.first.y = v.first.y+i.y;
                                new_v.second.x = v.second.x+j.x;
                                new_v.second.y = v.second.y+j.y;

                                neighs.push_back(new_v);
                            }
                }
    }
//MISTAKE!!!!!!!!
    //for(auto i: neighs)
    //{
    //  cout << i.first.x << ' ' << i.first.y << endl;
    //  cout << i.second.x << ' ' << i.second.y << endl << endl;
    //}

    //exit(0);
}

//v - vertex, G - graph, p - parent
int bfs(cell first, cell second)
{
    if(first == second) return 0;


    int N = 8;

    vector<vector<vector<vector<int>>>>
     used(N, vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(N))));

    vector<vector<vector<vector<int>>>>
     dist(N, vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(N, -1))));

    typedef pair<cell, cell> cells;

    queue<cells> q;

    cells v;
    v.first = first;
    v.second = second;

    q.push(v);
    used[v.first.x][v.first.y][v.second.x][v.second.y] = 1;
    dist[v.first.x][v.first.y][v.second.x][v.second.y] = 0;
    vector<cells> neighs(8*8);

    while(!q.empty())
    {

        v = q.front();
        q.pop();

        neighs.clear();
        push_neighs(v, neighs, N);

        for(auto i: neighs)
        {
            if(!used[i.first.x][i.first.y][i.second.x][i.second.y])
            {
                q.push(i);
                //p[i.x][i.y] = v;
                used[i.first.x][i.first.y][i.second.x][i.second.y] = true;
                dist[i.first.x][i.first.y][i.second.x][i.second.y] =
                        dist[v.first.x][v.first.y][v.second.x][v.second.y] + 1;
                if(i.first == i.second)
                    return  dist[i.first.x][i.first.y][i.second.x][i.second.y];
            }

        }
    }

return -1;
}


int main()
{
    int N = 8;
    string in;

    cell first, second;

    cin >> in;
    first.x = in[0] - 'a';
    first.y = in[1] - '1';

    cin >> in;
    second.x = in[0] - 'a';
    second.y = in[1] - '1';

    cout << bfs(first, second);
}
