#include <map>
using namespace std;

template<class TVertex, class TEdgeProperty>
class TGraph {
    typedef std::map<TVertex, TEdgeProperty> TAdjacencyList;   /// зачем мап в мапе (при том ключ
                                                            ///вложенного есть TVertex)
                                                            ///typename в typedef'ах
    typedef std::map<TVertex, TAdjacencyList> TAdjacencyData;
    TAdjacencyData Adjacencies;

public:

    TGraph () {}

    class iteratorV {               /*итератор по вершинам (внешний мап)*/
        typename TAdjacencyData::iterator it;
    public:
        iteratorV (typename TAdjacencyData::iterator A) : it (A) {}
        iteratorV (const iteratorV& A) : it (A.it) {}
        iteratorV& operator++ () {++it; return *this;}
        const TVertex& operator* () {return (it -> first);}
        bool operator!= (iteratorV A) {return it != A.it;}
        bool operator== (iteratorV& A) {return it == A;}
    };

    iteratorV begin () {
                    iteratorV x (Adjacencies.begin ());
                    return x;}
    iteratorV end () {iteratorV x (Adjacencies.end ());
                    return x;}

    class iteratorAdj {              /*итератор по по мапу смежности (внутренний мап)*/
        typename TAdjacencyList::iterator it;
public:
        iteratorAdj (TAdjacencyList& A): it (A.begin ()) {}
        iteratorAdj (typename TAdjacencyList::iterator A): it (A) {}
        iteratorAdj (const iteratorAdj& B): it (B.it) {}
        iteratorAdj& operator++ () {++it; return *this;}
        const TVertex& operator* () {return it -> first;}
        bool operator!= (iteratorAdj A) {return it != A.it;}
        bool operator== (iteratorAdj A) {return it == A.it;}
    };

    iteratorAdj begin (const TVertex& A) {iteratorAdj x (Adjacencies[A].begin ()); return x;}
    iteratorAdj end (const TVertex& A) {iteratorAdj x (Adjacencies[A].end ()); return x;}



    bool HasVertex(const TVertex& v) {
        return Adjacencies.count(v);
    }

    void AddEdge(const TVertex& a, const TVertex& b, const TEdgeProperty& props = TEdgeProperty()) {
        AddVertex(a);
        AddVertex(b);
        Adjacencies[a][b] = props;
    }

    void AddVertex(const TVertex& v) {
        if (!HasVertex(v))
            Adjacencies[v] = TAdjacencyList();
    }

};
