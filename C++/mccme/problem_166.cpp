#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <list>
#include <limits.h>
#include <cmath>
#include <climits>
using namespace std;

static int t(1);

int dfs(int v, vector<list<int>>& G, vector<int>& used, vector<int>& out)
{
    //in[v] = t++;
    used[v] = 1;

    for(auto i: G[v])
    {
        if(out[i] != 0) continue;

        if(used[i])
            return 1;

        if(dfs(i, G, used, out))
            return 1;
    }

    out[v] = t++;

return 0;
}


int main()
{
    int N, M, in1, in2;

    cin >> N >> M;

    vector<list<int>> G(N);
    vector<int> used(N);
    vector<int> out(N);

    for(int i=0; i<M; ++i)
    {
        cin >> in1 >> in2;

        G[in2-1].push_back(in1-1);
    }

    for(int i=0; i<N; ++i)
        if(!out[i])
            {
            if(dfs(i, G, used, out))
                {
                cout << "No";
                return 0;
                }
            }


    vector<int> out_copy(out);

    sort(out_copy.begin(), out_copy.end());

    cout << "Yes" << endl;
    for(auto i: out_copy)
    {
        cout << find(out.begin(), out.end(), i) - out.begin() + 1 << ' ';
    }

}
