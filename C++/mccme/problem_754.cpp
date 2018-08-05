#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

template <class T>
class Myheap
{
private:
    size_t heapSize;
    vector<T> heap;

public:
    Myheap(vector<T> t_heap): heap(t_heap), heapSize(t_heap.size()){}
    void build();
    void heapify(size_t ind);
    void sort();
    void print() {for (auto i: heap) cout << i << ' ';}
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

int main()
{
    int N;
    cin >> N;

    int in;
    vector<int> v;
    while(cin >> in)
        v.push_back(in);


    Myheap<int> h(v);
    h.sort();
    h.print();

}
