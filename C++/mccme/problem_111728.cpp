#include <iostream>
#include <vector>
using namespace std;

template <class T>
int left_find(T& c, vector<T>& arr)
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

    if (arr[m] == c)
        return m+1;

    return -1;
}

template <class T>
int right_find(T& c, vector<T>& arr)
{

    int l = 0;
    int r = arr.size() -1;
    int m = (l+r+1)/2;

    while (l < r)
    {
        if (arr[m] > c)
            r = m-1;
        else
            l = m;

        m = (l+r+1)/2;
    }

    if (arr[m] == c)
        return m+1;

    return -1;
}

int main()
{
    int N;
    int K;
    int c;
    int input;
    cin >> N >> K;

    vector<int> arr;

    for(int i = 0; i < N; ++i)
    {
        cin >> input;
        arr.push_back(input);
    }

int temp;
    for(int i = 0; i < K; ++i)
    {
        cin >> input;

        temp = left_find(input, arr);

        if (temp == -1)
            cout << 0 << endl;

        else
        {
            cout << temp << ' ' << right_find(input, arr) << endl;
        }

    }
}
