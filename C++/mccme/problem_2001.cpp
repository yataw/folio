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


void push_neighs(int v, vector<int>& neibhs)
{
    if(v/1000 != 9)
        neibhs.push_back(v + 1000);
    if(v%10 != 1)
        neibhs.push_back(v - 1);

    neibhs.push_back( (v%1000)*10 + v/1000);
    neibhs.push_back( (v%10)*1000 + v/10);
}

//p - parent, v - vertex
void bfs(int start, int end, vector<int>& used, vector<int>& p)
{
    queue<int> q;

    int v = start;
    vector<int> neibhs;
    q.push(v);
    used[v] = 1;

    while(!q.empty())
    {
        v = q.front();
        q.pop();

        neibhs.clear();
        push_neighs(v, neibhs);

        for(auto i: neibhs)
        {
            if(!used[i])
            {
                q.push(i);
                used[i] = 1;
                p[i] = v;

                if(i == end) return;
            }
        }
    }

}

int main()
{
    int start, end;
    cin >> start >> end;

    vector<int> used(10000);
    vector<int> p(10000, -1);

    bfs(start, end, used, p);

    stack<int> output;
    for(int i = end; i != -1; i = p[i])
        output.push(i);

    while(!output.empty())
    {
        cout << output.top() << endl;
        output.pop();
    }

}
