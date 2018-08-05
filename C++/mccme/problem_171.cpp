#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<list>
#include<stack>
#include<queue>
#include<cstdlib>
using namespace std;

typedef vector<vector<int>> Graph;

void Floyid(Graph& G, Graph& d)
{
    int N = G.size();

    for(int k=0; k<N; ++k)
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                if(d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];
}

int main()
{
    int N;
    cin >> N;


    Graph G(N, vector<int>(N)); //first - vertex_to, second - probability
    Graph d(N, vector<int>(N));

    for(auto& i: G)
        for(auto& j: i)
            cin >> j;


    //for(int i=0; i<N; ++i)
        //for(int j=0; j<N; ++j)
            //d[i][j] = G[i][j];
    //copy(d, G.begin(), G.end());
    d = G;
    Floyid(G, d);

    for(auto& i: d)
    {
        for(auto& j: i)
            cout << j << ' ';
    cout << endl;
    }


}
