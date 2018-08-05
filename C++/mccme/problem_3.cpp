#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

template <class T>
int bin_find(T& c, vector<T>& arr)
{

    int l = 0;
    int r = arr.size() -1;
    int m = (l+r)/2;

    while (l < r)
    {
        if (arr[m] < c)
            l = m+1;
        else
            r = m;

        m = (l+r)/2;
    }

    int smallest = m > 0?(m-1):m;
    if (smallest + 1 >= arr.size())
        return arr[smallest];


    for (int i = smallest + 1; i < ((m+1) < arr.size()?(m+1):m); ++i)
    {
        if (abs((long long)(arr[i]) - (long long)(c)) <
            abs((long long)(arr[smallest]) - (long long)(c)) ||
            (abs((long long)(arr[i]) - (long long)(c)) ==
            abs((long long)(arr[smallest]) - (long long)(c)) &&
            arr[i] < arr[smallest]))
                smallest = i;
    }

    return arr[smallest];
}

int main()
{
    int N;
    cin >> N;
    cout << ceil(log2(N));
}
