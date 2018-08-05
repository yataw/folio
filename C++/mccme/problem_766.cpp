#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <list>
#include <limits.h>
#include <cmath>
#include <climits>
using namespace std;


template <class T>
void my_msort(int left, int right, vector<T>& arr)
{
    if (right-left<1) return;
    if(right-left==1)
    {
        if(arr[left] > arr[right])
            swap(arr[left], arr[right]);
        return;
    }

    int m = (left+right)/2;

    my_msort(left, m, arr);
    my_msort(m+1, right, arr);

    int size = right-left+1;
    int l = left, r = m+1, i = 0;
    vector<T> buff(size);

    while(l<=m && r<=right)
    {
        if (arr[l] <= arr[r])
        {
            buff[i++] = move(arr[l++]);
            continue;
        }

        if (arr[r] <= arr[l])
        {
            buff[i++] = move(arr[r++]);
            continue;
        }

    }

    if(l<=m)
        copy(make_move_iterator(&arr[l]), make_move_iterator(&arr[m+1]), &buff[i]);
    else
        copy(make_move_iterator(&arr[r]), make_move_iterator(&arr[right+1]), &buff[i]);

    copy(make_move_iterator(buff.begin()), make_move_iterator(buff.end()), &arr[left]);

}

int main()
{
    int N;
    cin >> N;

    vector<int> vec;
    int in;

    while(cin >> in)
        vec.push_back(in);

    my_msort(0, vec.size()-1, vec);

    for(auto i: vec)
        cout << i << ' ';

    cout << endl;
}
