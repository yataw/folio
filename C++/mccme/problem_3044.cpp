#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

template <class T>
class Myheap
{
private:
    size_t heapSize;
    vector<T> heap;

public:
    Myheap(vector<T> t_heap): heap(t_heap), heapSize(t_heap.size()){}
    Myheap(): heapSize(0){}
    void build();
    void heapify(size_t ind);
    void sort();
    void print() {for (auto i: heap) cout << i << ' ';}
    void insert(T el);
    T extract();
};

template <class T>
void Myheap<T>::heapify(size_t ind)
{
    size_t leftChild;
    size_t rightChild;
    size_t maxChild;

    while(1)
    {
        leftChild = 2*ind+1;
        rightChild = 2*ind+2;
        maxChild = ind;


        if(rightChild<heapSize && heap[maxChild] < heap[rightChild])
            maxChild = rightChild;

        if(leftChild<heapSize && heap[maxChild] < heap[leftChild])
            maxChild = leftChild;

        if(maxChild == ind)
            break;

        swap(heap[ind], heap[maxChild]);
        ind = maxChild;
    }
}

template <class T>
void Myheap<T>::build()
{
    for(int i = heapSize/2; i>=0; i--)
        heapify(i);
}

template <class T>
void Myheap<T>::sort()
{
    build();

    while(heapSize>1)
    {
        swap(heap[0], heap[heapSize-1]);
        heapSize--;
        heapify(0);
    }

}

template<class T>
void Myheap<T>::insert(T el)
{
    heap.push_back(el);

    int child = heapSize;
    int parent = (child-1)/2;
    heapSize++;

    while(parent != child)
    {
        if(heap[parent] < heap[child])
        {
            swap(heap[parent], heap[child]);
            child = parent;

        }
        else break;

        parent = (child-1)/2;
    }
}

template<class T>
T Myheap<T>::extract()
{
    if(heapSize < 1)
    {
        cout << "extract error";
        throw 1;
    }

    swap(heap[0], heap[heapSize - 1]);
    heapSize--;
    heapify(0);

    T last = heap.back();
    heap.pop_back();
    return last;
}

class int_mod{
public:
    int x;
    bool operator<(const int_mod& other)
    {
        return this->x < other.x;
    }
};
