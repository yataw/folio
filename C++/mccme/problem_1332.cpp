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


void Floid_Warsell(vector<vector<int>>& d)
{
    int N(d.size());

    for(int k=0; k<N; ++k)
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
            {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
}

int main()
{
    int N, in;
    cin >> N;

    vector<vector<int>> d(N, vector<int>(N));

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            cin >> in;

            d[i][j] = in? 1:INF;
        }

    Floid_Warsell(d);

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout << (d[i][j] == INF? 0:1) << ' ';
        }

        cout << endl;
    }

}
