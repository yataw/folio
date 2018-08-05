#include <iostream>
#include <cstdlib>
#define POINTER_ERROR 1
using namespace std;

template <class T>
class Vector {
        T* Data;
        size_t Size, Capacity, Min_els;

        public:

        Vector (size_t n, T val = T ());
        void push_back (T val);
        T get (size_t x);
        T& operator [] (size_t x);/*без проверки*/
        void pop_back ();
        void reserv (size_t n);

        class iterator{
            private:
            T* pt;

            public:
            iterator (T* ppt)
                {
                pt = ppt;
                }
            iterator& operator++ ()
                {++pt; return *this;}
            iterator& operator-- ()
                {--pt; return *this;}
            iterator operator- (int x)
                {return iterator (Data - x);}
            iterator operator+ (int x)
                {return (Data + x);}
            iterator& operator= (iterator& x)
                {pt = &*x; return *this;}
            T& operator* ()
                {
                return *pt;
                }
            bool operator!= (iterator b)
                {
                return pt != &(*b);
                }
            };

        iterator begin ()
            {
            return iterator (Data);
            }
        iterator end ()
            {
            return iterator (Data + Size);
            }

};

template <class T>
T& Vector <T> :: operator[] (size_t x)
    {
    return *(T)(Data + sizeof (T)*x);
    }

template <class T>
Vector <T> ::Vector (size_t n, T val)
    {
    int size = 1;
    Min_els = 0;
    for (; size <= n; size*= 2);

    Data = (T*) malloc (size*sizeof (T));
    for (int i = 0; i < n; ++i)
        Data [i] = val;

    Size = n;
    Capacity = size;
    }

template <class T>
T Vector <T>:: get (size_t x)
    {
    try {if (x < Size || x < 0) throw POINTER_ERROR;}
    catch (int) {cout << "POINTER_ERROR"; T rub; return rub;}

    return Data [x];
    }

template <class T>
void Vector <T>::push_back (T x)
    {
    if (Capacity < Size)
        {
        void* ptr =  realloc ((void*)Data, Capacity*2);
        if (!ptr) exit (1);
        Data = (T*) ptr;
        Capacity *= 2;
        }

    Data [Size++] = x;
    }

template <class T>
void Vector <T>::pop_back ()
    {
    if (!Size) return 0;
    --Size;

    if (Size > 0 && Size*4 <= Capacity && Size*4 <= Min_els)
        realloc ((void*)Data, Capacity /= 2);
    }

template <class T>
void Vector <T>::reserv (size_t n)
    {
    Min_els = n;
    if (Capacity < n)
        {
        void* pt = realloc ((void*)Data, n);
        if (!ptr) exit (1);
        Data = (T*) ptr;
        Capacity = n;
        }
    }

int main ()
{
Vector <int> x (5, 5);

for (Vector <int>::iterator it = x.begin(); it != x.end (); ++it)
    cout << *it << endl;

}
