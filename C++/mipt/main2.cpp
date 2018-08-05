#include "mygraph.h"
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
using namespace std;

enum COLOR {w, g, b}; //white gray black;
typedef TGraph <int, int> Graph;
typedef map <int, int> Timeout;

struct Make_comp{
    map <int, int>& sequence;
    vector <vector <int> >& comp;
};


inline void DFS_extra (Graph& G, int& time, const int& i, stack <int>& S, Timeout* result,
                       map <int, COLOR>& color, vector <int>* comp = 0);


Timeout* DFS (Graph& G, Make_comp* make_comp = 0)
{
stack <int> S;
map <int, COLOR> color;
Timeout* result = new Timeout;

for (typename Graph::iteratorV i (G.begin ()); i != G.end (); ++i)
    color.insert (make_pair (*i, w));

int time = 0;
if (make_comp == 0)
    for (typename Graph::iteratorV i (G.begin ()); i != G.end (); ++i)
        DFS_extra (G, time, *i, S, result, color);
else
    for (map <int, int>::reverse_iterator i (make_comp -> sequence.rbegin ());
                                                      i != make_comp -> sequence.rend (); ++i)
        {
        make_comp -> comp.resize (make_comp -> comp.size () + 1);
        DFS_extra
            (G, time, i -> second, S, result, color, &make_comp -> comp [make_comp -> comp.size() - 1]);
        }

return result;
}


inline void DFS_extra (Graph& G, int& time, const int& i, stack <int>& S, Timeout* result,
                       map <int, COLOR>& color, vector <int>* comp)
{
int V;
if (color [i] == w)
    {
    S.push (i);
    color [i] = g; ++time;

    while (!S.empty ())
        {
        V = S.top ();

        typename Graph::iteratorAdj it (G.begin (V));

        for (; it != G.end (V); ++it)
            if (color [*it] == w)
                {
                color [*it] = g; ++time;
                S.push (*it);
                break;
                }

        if (it == G.end (V))
            {
            color [V] = b; ++time;
            S.pop ();
            if (comp) {comp -> push_back (V);}

            result -> insert (make_pair (time, V));
            }
        }
    }
}


Graph* rollgraph (Graph& G) {
    Graph* res = new Graph;

    for (typename Graph::iteratorV i (G.begin ()); i != G.end (); ++i)
        for (typename Graph::iteratorAdj i2 (G.begin (*i)); i2 != G.end (*i); ++i2)
            res -> AddEdge(*i2, *i);

    return res;
    }


Timeout TOPOLOG;

vector <vector <int>>* SCC (Graph& G) {
    shared_ptr <Timeout> pre_result (DFS (G));
    vector <vector <int>>* res = new vector <vector <int>>;
    Make_comp M {*pre_result, *res};
    TOPOLOG = *pre_result;
    shared_ptr <Graph> RG (rollgraph (G));

    shared_ptr <Timeout> pre_result2 (DFS (*RG, &M));

    return res;
}


bool comp_check (int x, vector <vector <int>>* sccres) {
bool flag1, flag2;
    for (vector <vector <int>>::iterator it = sccres -> begin (); it != sccres -> end (); ++it) {
        flag1 = 0, flag2 = 0;
        for (vector <int>::iterator itt = it -> begin (); itt != it -> end (); ++itt) {
            if (*itt == x) flag1 = true;
            if (*itt == -x) flag2 = true;
        }

    if (flag1 && flag2) return true;
    }

return false;
}


int main () {
Graph G;

int numV, numEdges, p1, p2;
ifstream fin ("input.txt");
ofstream fout ("output.txt");
fin >> numV >> numEdges;

for (int i = 0; i < numEdges; ++i) {
    fin >> p1 >> p2;
    G.AddEdge (-p1, p2);
    G.AddEdge (-p2, p1);
    }

Timeout Topolog2;

shared_ptr <vector <vector <int>>> sccres (SCC (G));
vector <bool> res (numV, 0);

for (auto i: TOPOLOG)
    Topolog2.insert (make_pair (i.second, i.first));

for (Graph::iteratorV it = G.begin (); it != G.end (); ++it)
    {
    if (*it < 0) continue;
    if (comp_check (*it, sccres.get ())) //n^2
        {
        fout << "NO";
        return 0;
        }

    if (Topolog2 [*it] < Topolog2 [- *it]) res [*it - 1] = true;
    }

fout << "YES\n";
for (vector <bool>::iterator it = res.begin (); it != res.end (); ++it)
    fout << *it << ' ';
}

