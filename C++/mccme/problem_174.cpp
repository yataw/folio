#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
            buff[i++] = arr[l++];
            continue;
        }

        if (arr[r] <= arr[l])
        {
            buff[i++] = arr[r++];
            continue;
        }

    }

    if(l<=m)
        copy(&arr[l], &arr[m+1], &buff[i]);
    else
        copy(&arr[r], &arr[right+1], &buff[i]);

    copy(buff.begin(), buff.end(), &arr[left]);

}

int main()
{
    int N, in, res = 0;
    cin >> N;

    for(int i = 0; i<N; i++)
    {

        for(int j = N-i; j<N; j++)
                cin>>in;

        for(int j = i; j<N; j++)
        {
            cin>>in;
            if(in) res++;
        }

    }

    cout << res;

}
