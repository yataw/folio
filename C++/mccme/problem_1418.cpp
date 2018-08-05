#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

template <class T>
void my_qsort(int left, int right, vector<T>& arr)
{
    int l = left, r = right, mid = arr[(left+right)/2];

    while(l<=r)
    {
        while(arr[l]<mid) l++;
        while(arr[r]>mid) r--;

        if(l<=r)
            swap(arr[l++], arr[r--]);
    }

    if(l < right) my_qsort(l, right, arr);
    if(r > left) my_qsort(left, r, arr);

}

int main()
{
    int N;
    cin >> N;

    vector<int> vec;
    int in;

    while(cin >> in)
        vec.push_back(in);

    my_qsort(0, vec.size()-1, vec);

    int counter = 1;
    int x = vec[0];
    for(auto i: vec)
        if(x != i)
        {
            x = i;
            counter++;
        }

    cout << counter;
}
