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

typedef pair<int, int> ints;

void push_neibhs(ints el, int& N, int& M, vector<ints>& neibhs)
{
    if(el.first>0) neibhs.push_back({el.first-1, el.second});
    if(el.first<N-1) neibhs.push_back({el.first+1, el.second});
    if(el.second>0) neibhs.push_back({el.first, el.second-1});
    if(el.second<M-1) neibhs.push_back({el.first, el.second+1});
}

void bfs(vector<vector<int>>& G,  vector<vector<int>>& used, vector<vector<int>>& d,
        vector<vector<ints>>& p, ints star)
{
    int N(G.size()), M(G[0].size());
    ints el; //element
    vector<ints> neibhs(4);
    queue<ints> q;
    q.push(star);

    while(!q.empty())
    {
        el = q.front();
        q.pop();


        neibhs.clear();
        push_neibhs(el, N, M, neibhs);

        for(auto& i: neibhs)
        {
            if(!used[i.first][i.second] && !G[i.first][i.second])
            {
                q.push(i);
                d[i.first][i.second] =
                    (d[el.first][el.second]==-1?0:d[el.first][el.second]) + 1;
                //used[i.first][i.second] = 1;
                p[i.first][i.second] = {el.first, el.second};
            }
        }

        used[el.first][el.second] = 1;
    }

}

int main()
{
    int N, M;

    //cin >> N >> M;
    scanf("%i %i\n", &N, &M);
    ints star;

    vector<vector<int>> G(N, vector<int>(M)); //labirint
    vector<vector<int>> d(N, vector<int>(M, -1)); //distance;
    vector<vector<int>> used(N, vector<int>(M));
    vector<vector<ints>> p(N, vector<ints>(M, {-1, -1}));

    string inp_str; //input
    char inp_char;


    for(int i=0; i<N; ++i)
    {
        //in = getchar();
        getline(cin, inp_str);

        for(int j=0; j<M; ++j)
        {
            inp_char = inp_str[j];

            if(inp_char == '*')
            {
                star.first = i;
                star.second = j;
            }

            G[i][j] = (inp_char == '1')? 1:0;
        }
    }


    bfs(G, used, d, p, star);


    int K;
    cin >> K;

    ints min_pos = {-1, -1};
    int min_dist = -1, a, b;

    for(int i=1; i<=K; ++i)
    {
        cin >> a >> b;


        a--; b--;

        if(d[a][b] == -1) continue;

        if(min_dist == -1 || min_dist > d[a][b])
        {
            min_pos = make_pair(a, b);
            min_dist = d[a][b];
        }

    }

    cout << min_dist << endl;





    if(min_pos != make_pair(-1, -1))
    {
        queue<ints> q;

        while(min_pos != make_pair(-1, -1))
        {
            q.push(min_pos);
            min_pos = make_pair(p[min_pos.first][min_pos.second].first,
                        p[min_pos.first][min_pos.second].second);

        }

        while(!q.empty())
        {
            cout << q.front().first+1 << ' ' << q.front().second+1 << endl;

            q.pop();
        }
    }

    system("pause");
}
