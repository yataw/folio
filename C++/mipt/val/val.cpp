#include <cmath>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

const double INF = std::numeric_limits<double>::infinity();

struct Edge {
    int a, b;
    double cost;
    Edge (int _a, int _b, double _cost): a (_a), b (_b), cost (_cost) {}
};

void fb (vector <Edge>& E, vector <int>& p, vector <double>& d, bool& flag, int* cycle_start = 0);
void print_res (vector <int>& p, ofstream& fout, int cycle, int save);

int main () {
int N;
ifstream fin ("input.txt");
ofstream fout ("output.txt");

fin >> N;
vector <Edge> E;
double _cost;

for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        {
        fin >> _cost;
        E.push_back (Edge(i, j, log (_cost)));
        }

vector <int> p (N, -1); //parents
vector <double> d (N, INF);//distance
d [0] = 0;

int cycle_start = -1;
bool flag = 0;

for (int i = 0; i < N - 1; ++i)
    {
    flag = 0;
    fb (E, p, d, flag);

    if (!flag) break;
    }

if (flag) fb (E, p, d, flag, &cycle_start);

if (cycle_start == -1)
    {
    fout << 0;
    return 0;
    }

else
    {
    for (int i = 0; i < N; ++i)
        cycle_start = p [cycle_start];

    int save = cycle_start;

    print_res (p, fout, p [cycle_start], save);
    fout << save + 1;
    }

}


void fb (vector <Edge>& E, vector <int>& p, vector <double>& d, bool& flag, int* cycle_start) {
for (auto i: E)
    {
    if (d [i.b] > d [i.a] + i.cost)
        {
        d [i.b] = d [i.a] + i.cost;
        p [i.b] = i.a;
        flag = true;
        if (cycle_start)
            *cycle_start = i.b;
        }
    }
}

void print_res (vector <int>& p, ofstream& fout, int cycle, int save)
{
if (cycle != save) print_res (p, fout, p [cycle], save);

fout << cycle + 1 << ' ';
return;
}
