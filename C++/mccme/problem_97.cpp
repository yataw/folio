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
const int INF = 1000000000;
//G - Graph, d - distance, p - parent

void Floyd_Warsell(vector<vector<int>>& d, vector<vector<int>>& p)
{
    int N = d.size();

    for(int k=0; k<N; ++k)
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
            {
                p[i][j] = d[i][j] > d[i][k]+d[k][j]? k:p[i][j];
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
}

int main()
{
    int N, S, F;
    cin >> N;
    S--; F--;

    vector<vector<int>> G(N, vector<int>(N)),
                          d(N, vector<int>(N)),
                          p(N, vector<int>(N));

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cin >> G[i][j];
            d[i][j] = G[i][j];
        }
    }

    Floyd_Warsell(d, p);

/*
    cout << endl;

    for(auto& i: d)
    {
        cout << endl;

        for(auto j:i)
            cout << j << ' ';
    }
*/

    for(int i=0; i<N; ++i)
    {
        if(d[i][i]<0)
        {
            cout << -1;
            return 0;
        }
    }

    int min_ = INF;
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            if(i==j) continue;
            min_ = min(min_, d[i][j]);
        }

    cout << (min_ == INF? -1: min_);

}
