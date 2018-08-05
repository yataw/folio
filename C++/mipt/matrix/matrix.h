#ifndef MATRIX



#define MATRIX
#include <iostream>
using namespace std;
template <class T = int>
class Matrix {
    private:
        T** Arr;
    protected:
        size_t N;
        size_t M;
    public:
        Matrix <T> (size_t n, size_t m);
        void Set (size_t n, size_t m, T v);
        T Get (size_t n, size_t m) const;
        Matrix <T> operator+ (const Matrix <T>& b) const;
        Matrix <T> operator- (const Matrix <T>& b) const;
        Matrix <T> operator* (const Matrix <T>& B) const;
        Matrix <T>& operator= (const Matrix <T> b);
        Matrix <T> (Matrix <T> const& copy);              /*copyconstructor*/
        size_t GetM () const {return M;}
        size_t GetN () const {return N;}
        void Print ();
        ~Matrix <T> ();
        friend ostream& operator<< (ostream& out, const Matrix <T>& A);
};

class SqrMatrix: public Matrix <int> {
    public:
    SqrMatrix (size_t n):
        Matrix <int> (n, n)
    {}

    long long Det () const;
    long long Trace () const;
};
#endif
