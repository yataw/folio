#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<list>
#include<stack>
#include<queue>
#include<cstdlib>
using namespace std;

const int INF = 1000000000;
typedef vector<vector<int>> Graph; // �� list
struct Edge{
    int a, b, price;
};


void Ford(int v, Graph& G, vector<int>& d, vector<int>& p)
{
    int N = d.size();
    d[v] = 0;



    for(int t=0; t<N; ++t)
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j) //!��� �������� �� INF
            {
                if(d[j] > d[i]+G[i][j])
                {
                    d[j] = d[i]+G[i][j];
                    p[j] = i;
                }
            }

    int x = -1;

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j) //!��� �������� �� INF
        {
            if(d[j] > d[i]+G[i][j])
            {
                d[j] = d[i]+G[i][j];
                p[j] = i;
                x = j;
            }
        }


    if(x == -1)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    for(int i=0; i<N; ++i)
        x=p[x];

    stack<int> s;
    int y=x;

    s.push(y);
    y=p[y];


    while(y!=x)
    {
        s.push(y);
        y=p[y];
    }
    s.push(y);


    cout << s.size() << endl;
    while(!s.empty())
    {
        cout << s.top()+1 << ' ';
        s.pop();
    }

}

int main()
{
    int N, inp;
    cin >> N;

    Graph G(N, vector<int>(N));
    vector<int> d(N, INF);
    vector<int> p(N, -1);


    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            cin >> inp;
            G[i][j] = (inp==100000?INF:inp);
        }

    Ford(0, G,  d, p);
}
