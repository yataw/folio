#include <iostream>
#include <vector>
using namespace std;

template <class T>
string bin_find(T& c, vector<T>& arr)
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
        return "YES";

    return "NO";

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


    for(int i = 0; i < K; ++i)
    {
        cin >> input;
        cout << bin_find(input, arr) << endl;

    }
}
