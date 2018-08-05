#include <iostream>
#include <map>
#include <vector>
#include "mygraph.h"
#include <queue>
#include <stack>

enum COLOR {w, g, b}; //white gray black;

class _int { //with inf
    int x;
    bool inf;
public:
    _int (): inf (1), x () {}
    _int operator= (_int y) {x = y.x, inf = y.inf; return *this;}
    _int operator= (int y) {x = y; if (inf) inf = 0; return *this;}
    operator int () {return x;}
    bool operator< (_int y) {if (inf) return 0;
                              else if (y.inf || x < y.x) return 1;}
};


    typedef TGraph <class TVertex, class TEdgeProperty> Graph;

    template <class TVertex>
    class BFS_ret {
    public:
        map <TVertex, _int> d; //distance
        map <TVertex, TVertex> p; //predecessor
    };

    template <class TVertex>
    class DFS_ret {
    public:
        map <int, TVertex> starttime;
        map <int, TVertex> endtime;
        map <TVertex, TVertex> p; //predecessor
    };


template <class TVertex, class TEdgeProperty>
inline void DFS_extra (TGraph <TVertex, TEdgeProperty>& G, int& time, const TVertex& i, stack <TVertex>& S, DFS_ret<TVertex>* result,
                       map <TVertex, COLOR>& color);



  template <class TVertex, class TEdgeProperty>
    BFS_ret<TVertex>* BFS (TGraph <TVertex, TEdgeProperty>&  G, TVertex& A) {
        queue <TVertex> Q;
        map <TVertex, COLOR> color;
        BFS_ret<TVertex>* result = new BFS_ret<TVertex>;
        TVertex V;
        Q.push (A);
        for (typename TGraph <TVertex, TEdgeProperty>::iteratorV i (G.begin ()); i != G.end (); ++i)
            {
            color.insert (make_pair (*i, w));
            (*result).d.insert (make_pair (*i, _int ()));
            (*result).p.insert (make_pair (*i, TVertex ()));
            }


        color[A] = g;
        result -> d[A] = 0;

        for (int deep = 1; !Q.empty (); ++deep)
            {
            V = Q.pop ();

            for (typename TGraph <TVertex, TEdgeProperty>::iteratorAdj it (V); it != G.end (V); ++it)
                if (color [*it] == w)
                    {
                    Q.push (*it);
                    result -> d[*it] = deep;
                    result -> p[*it] = V;
                    color [*it] = g;
                    }

            color [V] = b;
            }

    return result;
    }


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
                DFS_extra <TVertex, TEdgeProperty> (G, time, *i, S, result, color);
        else
            for (typename map <int, TVertex>::reverse_iterator i (sequence -> rbegin ()); i != sequence -> rend (); ++i)
                DFS_extra <TVertex, TEdgeProperty> (G, time, i -> second, S, result, color);

    return result;
    }


template <class TVertex, class TEdgeProperty>
inline void DFS_extra (TGraph <TVertex, TEdgeProperty>& G, int& time, const TVertex& i, stack <TVertex>& S, DFS_ret<TVertex>* result,
                       map <TVertex, COLOR>& color) {
    TVertex V;
    if (color [i] == w)
                    {
                    S.push (i);

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

        delete pre_result;
        TGraph <TVertex, TEdgeProperty>* RG = rollgraph<TVertex> (G);
        pre_result = DFS<TVertex> (*RG, seq);
        delete RG;

        map <TVertex, TVertex>* res = &(pre_result -> p);
        delete pre_result;

        return res;
        }


