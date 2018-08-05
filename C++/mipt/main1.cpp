#include "mygraph.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

enum COLOR {w, g, b}; //white gray black;
typedef TGraph <class TVertex, class TEdgeProperty> Graph;



template <class TVertex>
class DFS_ret {
public:
    map <int, TVertex> starttime;
    map <int, TVertex> endtime;
    map <TVertex, TVertex> p; //predecessor
};


template <class TVertex, class TEdgeProperty>
inline void DFS_extra (TGraph <TVertex, TEdgeProperty>& G, int& time, const TVertex& i, stack <TVertex>& S, DFS_ret<TVertex>* result,
                       map <TVertex, COLOR>& color, bool throw_flag);


template <class TVertex,  class TEdgeProperty>
DFS_ret<TVertex>* DFS (TGraph <TVertex, TEdgeProperty>& G, map <int, TVertex>* sequence = 0) {
    stack <TVertex> S;
    map <TVertex, COLOR> color;
    DFS_ret<TVertex>* result = new DFS_ret<TVertex>;
    //TVertex V;
    //sequence == DEFAULT_SEQ<TVertex>.data? S.push (*(G.begin ())): S.push (sequence.rbegin () -> second);

    for (typename TGraph <TVertex, TEdgeProperty>::iteratorV i (G.begin ()); i != G.end (); ++i)
        {
        color.insert (make_pair (*i, w));
        (*result).p.insert (make_pair (*i, TVertex ()));
        //result -> starttime.insert (*i, _int ());
        //result -> endtime.insert (*i, _int ());
        }

    int time = 0;
    if (sequence == 0)
        for (typename TGraph <TVertex, TEdgeProperty>::iteratorV i (G.begin ()); i != G.end (); ++i)
            DFS_extra <TVertex, TEdgeProperty> (G, time, *i, S, result, color, 0);
    else
        for (typename map <int, TVertex>::reverse_iterator i (sequence -> rbegin ()); i != sequence -> rend (); ++i)
            DFS_extra <TVertex, TEdgeProperty> (G, time, i -> second, S, result, color, 1);


return result;
}


template <class TVertex, class TEdgeProperty>
inline void DFS_extra (TGraph <TVertex, TEdgeProperty>& G, int& time, const TVertex& i, stack <TVertex>& S, DFS_ret<TVertex>* result,
                       map <TVertex, COLOR>& color, bool throw_flag) {
    TVertex V;
    if (color [i] == w)
                    {
                    S.push (i);
                    set <TVertex> comp;
                    if (throw_flag) comp.insert (i);

                    while (!S.empty ())
                        {
                        V = S.top ();
                        S.pop ();

                        typename TGraph <TVertex, TEdgeProperty>::iteratorAdj it (G.begin (V));

                        for (; it != G.end (V); ++it)
                            if (color [*it] == w)
                                {
                                S.push (*it);
                                (result -> starttime).insert (make_pair (++time, *it));
                                result -> p[*it] = V;

                                if (throw_flag)
                                    {
                                    if (comp.count (-*it)) throw 1;
                                    comp.insert (*it);
                                    }
                                color [*it] = g;
                                break;
                                }

                        if (it == G.end (V))
                            {
                            (result -> endtime).insert (make_pair (++time, *it));
                            color [V] = b;
                            }
                        }
                    }
    }

template <class TVertex, class TEdgeProperty>
TGraph <TVertex, TEdgeProperty>* rollgraph (TGraph <TVertex, TEdgeProperty>& G) {
    TGraph <TVertex, TEdgeProperty>* res = new TGraph <TVertex, TEdgeProperty>;

    for (typename TGraph <TVertex, TEdgeProperty>::iteratorV i (G.begin ()); i != G.end (); ++i)
        for (typename TGraph <TVertex, TEdgeProperty>::iteratorAdj i2 (G.begin (*i)); i2 != G.end (*i); ++i2)
            res -> AddEdge(*i2, *i);

    return res;
    }


template <class TVertex, class TEdgeProperty>
map <TVertex, TVertex>* SCC (TGraph <TVertex, TEdgeProperty>& G) {
    DFS_ret<TVertex>* pre_result = DFS<TVertex> (G);
    map <int, TVertex>* seq = &(pre_result -> endtime);

    //delete pre_result;
    TGraph <TVertex, TEdgeProperty>* RG = rollgraph<TVertex> (G);
    DFS_ret<TVertex>* pre_result2 = DFS<TVertex> (*RG, seq);

    map <TVertex, TVertex>* res = &(pre_result2 -> p);
    delete pre_result;
    delete pre_result2;
    delete RG;

    return res;
    }





int main () {
TGraph <int, int> G;

ifstream fin ("t.txt");

int num, p1, p2;

fin >> num >> num;

for (int i = 0; i < num; ++i) {
    fin >> p1 >> p2;
    G.AddEdge (-p1, p2);
    G.AddEdge (-p2, p1);
    }



try {SCC (G);}
catch (int x) {if (x) cout << "NO"; return 0;}
cout << "YES";
}
