#include <iostream>
#include <cmath>
using namespace std;


int main()
{
    long long x, y;
    cin >> x;

    long long l = 1, r = pow(x, 2.), m = 0; /*binary search*/

    while(1)
    {
        m = (l+r)/2;
        y = floor(pow(m, 1./2)) + floor(pow(m, 1./3)) - floor(pow(m, 1./6));

        if(y == x)
            break;

        if (y < x)
            l=m+1;
        else
            r=m-1;
    }

    m = max(pow(floor(pow(m, 1./2)), 2), pow(floor(pow(m, 1./3)), 3));
    cout << m;
}
