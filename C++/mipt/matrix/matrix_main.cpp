#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "matrix.h"
#include "matrix.cpp"

int main (int argc, char* argv [])
    {
    //ostream a;
    #define X 3
    #define Y X
/*Matrix A (X, Y), B (X, Y), C (X, Y);

    for (int i = 0; i < X; ++i)
        for ( int j = 0; j < Y; ++j)
            A.Set (i, j, 1), B.Set (i, j, 1);

    //cout << (A + B).Get (0, 0) << endl;
    C = A*B;
    C.Print ();
*/
    srand (time (0));
    SqrMatrix D (X);

    for (int i = 0; i < X; ++i)
        for ( int j = 0; j < Y; ++j)
            D.Set (i, j, rand ()%100);

//D.Set (0, 0, 2);
//D.Set (0, 1, 2);
//D.Set (1, 0, 1);
//D.Set (1, 1, 2);
    D.Print ();
    cout << D.Det ();
    }
