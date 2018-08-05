using std:: cout;
using std:: endl;
#define error 1

template <class T>
Matrix <T>::Matrix (size_t n, size_t m):
    N (n),M (m)
    {
    Arr = new T* [n];
    for (int i = 0; i < N; ++i)
        {
        Arr [i] = new T [M];

        for (int j = 0; j < M; ++j)
            Arr [i] [j] = 0;
        }
    }


template <class T>
Matrix <T>::Matrix (Matrix const& b)
    {
    M = b.GetM (), N = b.GetN ();

    Arr = new T* [N];
    for (int i = 0; i < N; ++i)
        {
        Arr [i] = new T [M];

        for (int j = 0; j < M; ++j)
            Arr [i] [j] = b.Get (i, j);
        }

    }

template <class T>
void Matrix <T>::Set (size_t n, size_t m, T val)
    {
    if (n < N && m < M)
            Arr [n] [m] = val;
    }

template <class T>
T Matrix <T>::Get (size_t n, size_t m) const
    {
    if (n < N && m < M)
        return Arr [n] [m];

    }

template <class T>
Matrix <T> Matrix<T>::operator+ (const Matrix <T> & b) const
    {
    if (N == b.GetN () && M == b.GetM ())
        {
        Matrix <T> C (N, M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                C.Set (i, j, Get (i, j) + b.Get (i, j));

        return C;
        }
    else throw error;
    }

template <class T>
Matrix <T> Matrix <T>::operator- (const Matrix <T> & b) const
    {
    if (N == b.GetN () && M == b.GetM ())
        {
        Matrix C (N, M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                C.Set (i, j, Get (i, j) - b.Get (i, j));

        return C;
        }
    else throw error;
    }

template <class T>
Matrix <T> Matrix <T>::operator* (const Matrix& B) const
    {
    if (M == B.N)
        {
        Matrix C (N, B.M);

        for (int i = 0; i < M; ++i)
            for (int j = 0, res = 0; j < B.N; ++j)
                {
                for (int k = 0; k < N; ++k)
                    res += Get (i, k)*B.Get (k, i);

                C.Set (i, j, res);
                }
        return C;
        }
    else throw error;
    }

template <class T>
Matrix <T>& Matrix <T>::operator= (const Matrix b)
    {
    T** copy;
    copy = new T* [b.GetN ()];
    for (int i = 0; i < b.GetN (); ++i)
        copy [i] = new T [b.GetM ()];
    //ELSE
    N = b.GetN ();
    M = b.GetM ();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            copy [i] [j] = b.Get (i, j);

    for (int i = 0; i < N; ++i)
        delete [] Arr [i];
    delete [] Arr;

    Arr = copy;


    return *this;
    }


/*
template <class T>
int Matrix <T>::Det ()
    {

    }*/

template <class T>
ostream& operator<< (ostream& out, const Matrix <T> & A)
    {
    for (int i = 0; i < A.N; ++i)
        {
        for (int j = 0; j < A.M; ++j)
             out << A.Arr [i] [j] << ' ';
        out << endl;
        }

    return out;
    }

template <class T>
void Matrix <T>:: Print ()
    {
    for (int i = 0; i < N; ++i)
            {
            for (int j = 0; j < M; ++j)
                cout << Arr [i] [j] << ' ';

            cout << endl;
            }
    }

template <class T>
Matrix <T>:: ~Matrix ()
    {
    for (int i = 0; i < N; ++i)
        delete [] Arr [i];
    delete [] Arr;
    }
//--

long long SqrMatrix::Trace () const
    {
    long long res = 0;
    int n = GetN ();
        for (int i = 0; i < n; ++i)
            res += Get (i, i);

    return res;
    }

long long SqrMatrix::Det () const
    {
    long long res = 1, res_del = 1;
    int *cur_line;
    cur_line = new int [N];
    SqrMatrix copyM (N);
    copyM = *this;
    int temp, j = 0;

    for (int i = 0; i < N; ++i, j = 0)
        {
        if (copyM.Get (i, i) == 0)
            {
            for (j = i + 1; j < N; ++j)
                if (copyM.Get (j, i) != 0)
                    {
                    for (int k = i; k < N; ++k)
                        {
                        temp = copyM.Get (i, k);
                        copyM.Set (i, k, copyM.Get (j, k));
                        copyM.Set (j, k, temp);
                        }
                    j = 0; break;
                    }

            if (j) return 0;
            res *= -1;
            }

        res *= copyM.Get (i, i);
        for (int j = i + 1; j < N; ++j)
            {
            if (copyM.Get (j, i))
                {
                for (int k = i; k < N; ++k) cur_line [k] = copyM.Get (i, k)*copyM.Get (j, i);
                for (int k = i; k < N; ++k) copyM.Set (j, k, copyM.Get (j, k)*copyM.Get (i, i));
                for (int k = i; k < N; ++k) copyM.Set (j, k, copyM.Get (j, k) - cur_line [k]);
                res_del *= copyM.Get (i, i);
                }
            }


        }

    //res *= copyM.Get (N - 1, N - 1) * copyM.Get (0, 0);
    return res / res_del;
    }
