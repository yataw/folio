#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;
int N;
const unsigned long long END_STATUS = 0xfedcba987654321;

class Tstat {
public:
    unsigned long long game_stat;
    unsigned long long parent;
    unsigned deep;
    Tstat (unsigned long long a, unsigned long long b, unsigned c):
        game_stat (a), parent (b), deep (c) {}
    Tstat () {}
    void operator= (Tstat& B) {game_stat = B.game_stat, parent = B.parent, deep = B.deep;}
};

class Tclose_stat {
public:
    unsigned long long parent;
    unsigned deep;
    Tclose_stat (unsigned long long a, unsigned c):
        parent (a), deep (c) {}
    Tclose_stat () {}
    void operator= (Tclose_stat& B) {parent = B.parent, deep = B.deep;}
};

int inline what_number (unsigned long long, int);
int inline where_null (unsigned long long);
int inline evrka (Tstat a);
int inline manhattan (unsigned long long);
unsigned long long inline mypow (int);
bool solvabiliti (unsigned long long _stat);

void inline child_problem (multimap <unsigned, Tstat>&, unordered_map <unsigned long long,
                multimap <unsigned, Tstat>::iterator>&, unordered_map <unsigned long long, Tclose_stat>&,
                Tstat&, Tstat&, unsigned&, unsigned&);

int main () {
ifstream fin ("input.txt");
ofstream fout ("output.txt");

fin >> N;

multimap <unsigned, Tstat> open_stat; //list of free (open) statuses
unordered_map <unsigned long long,
                    multimap <unsigned, Tstat>::iterator> ref_open_stat; //for fast search in open_stat

unordered_map <unsigned long long, Tclose_stat> close_stat; //list of locked statuses. stat-{parent, deep}


unsigned long long _stat (0), k = 1;
int temp = 0;
for (int i = 0; i < N*N; ++i, k*= 16) {
    fin >> temp;
    _stat += temp*k;
    }

Tstat stat (_stat, _stat, 0), child_stat;

if (!solvabiliti (_stat)) //Does bb-game have a solution?
    {
    fout << -1;
    return 0;
    }

open_stat.insert (make_pair (evrka (stat), stat)); /*!evrka includes deep*/
ref_open_stat.insert (make_pair (stat.game_stat, open_stat.begin ()));

unsigned null_pos, number;
multimap <unsigned, Tstat>::iterator save_begin_it;
//!!!!!!!!!!!!
//int i = 0;
//!!!!!!!!!!!!
while (1) {
    if (open_stat.begin () -> second.game_stat == END_STATUS) break; //bb-find_path completed
//cout << open_stat.begin () -> first << endl;
//for (int i  = 0; i < 9e7; ++i);
    save_begin_it = open_stat.begin ();
    stat = open_stat.begin () -> second;
    null_pos = where_null (stat.game_stat);
    //cout << null_pos << endl;
/*
    for (; ;) if (i < 4) {
        ++i;
        cout << endl << dec << open_stat.begin () -> first << ' ' << hex << stat.game_stat << endl;
        break;
        }
*/
    /*right_move (NULL left_move)*/
    if (null_pos %N != 0)
        {   //!!!!!!
        number = what_number (stat.game_stat, null_pos - 1);
        child_stat.game_stat = stat.game_stat + number*mypow (null_pos) - number*mypow (null_pos - 1);
//cout << 'R' << child_stat.game_stat << endl;
        child_problem (open_stat, ref_open_stat, close_stat, stat, child_stat, null_pos, number);
        }

    /*left_move*/
    if (null_pos %N != N - 1)
        {
        number = what_number (stat.game_stat, null_pos + 1);
        child_stat.game_stat = stat.game_stat + number*mypow (null_pos) - number*mypow (null_pos + 1);
//cout << 'L' << child_stat.game_stat << endl;
        child_problem (open_stat, ref_open_stat, close_stat, stat, child_stat, null_pos, number);
        }

    /*down_move*/
    if (null_pos >= N)
        {
        number = what_number (stat.game_stat, null_pos - N);
        child_stat.game_stat = stat.game_stat + number*mypow (null_pos) - number*mypow (null_pos - N);
//cout << 'D'  << child_stat.game_stat << endl;
        child_problem (open_stat, ref_open_stat, close_stat, stat, child_stat, null_pos, number);
        }

    /*up_move*/
    if (null_pos < N*(N-1))
        {
        number = what_number (stat.game_stat, null_pos + N);
        child_stat.game_stat = stat.game_stat + number*mypow (null_pos) - number*mypow (null_pos +N);
//cout << 'U' << child_stat.game_stat << endl;
        child_problem (open_stat, ref_open_stat, close_stat, stat, child_stat, null_pos, number);
        }

    ref_open_stat.erase (stat.game_stat);
    close_stat.insert (make_pair(stat.game_stat, Tclose_stat (stat.parent, stat.deep)));
    open_stat.erase (save_begin_it);
}

/*print the path*/
int final_deep = open_stat.begin () -> second.deep;
fout << final_deep << endl;
vector <int> res;
unsigned long long shift;

stat = open_stat.begin () -> second;

for (int i = 0; i < final_deep; ++i)
    {
    shift = what_number (stat.game_stat, where_null (stat.parent));

    res.push_back (shift);

    if (ref_open_stat.count(stat.parent)) stat = ref_open_stat [stat.parent] -> second;
    else {
        stat.game_stat = stat.parent;
        stat.parent = close_stat [stat.parent].parent;
        }
    }

for (vector<int>::reverse_iterator rit = res.rbegin (); rit != res.rend (); ++rit)
    fout << *rit << ' ';
}


void inline child_problem (multimap <unsigned, Tstat>& open_stat, unordered_map <unsigned long long,
            multimap <unsigned, Tstat>::iterator>& ref_open_stat,
            unordered_map <unsigned long long, Tclose_stat>& close_stat, Tstat& stat, Tstat& child_stat,
            unsigned& null_pos, unsigned& number)
{
multimap <unsigned, Tstat>::iterator it;
unsigned sewd; //sewd == save evrka without deep

child_stat.deep = stat.deep + 1;
child_stat.parent = stat.game_stat;

if (close_stat.count (child_stat.game_stat))
    {
    if (child_stat.deep < close_stat [child_stat.game_stat].deep)
        {
        close_stat [child_stat.game_stat].deep = child_stat.deep;
        close_stat [child_stat.game_stat].parent = child_stat.parent;
        }
    }
else if (!ref_open_stat.count (child_stat.game_stat))
    {//cout << endl << "INSERT" << hex << child_stat.game_stat<< endl;
    it = open_stat.insert (make_pair (evrka (child_stat), child_stat));
    ref_open_stat.insert (make_pair (child_stat.game_stat, it));
    }
else { //update
    it = ref_open_stat [child_stat.game_stat];
    if (it -> second.deep > child_stat.deep)
        {//cout << endl << "INSERT" << hex << child_stat.game_stat<< endl;
        sewd = it -> first - it -> second.deep;
        open_stat.erase (it);
        it = open_stat.insert (make_pair (sewd + child_stat.deep, child_stat));
        ref_open_stat [child_stat.game_stat] = it;
        }
    }
}

int inline what_number (unsigned long long ll, int x)
{
for (int i = 0; i < x; ++i)
    ll /= 16;

return ll %16;
}

int inline where_null (unsigned long long ll)
{
int i = 0;
for (;;++i) {
    if (ll /16*16 == ll) break;
    ll /= 16;
    }

return i;
}

int inline evrka (Tstat a) {
return a.deep + manhattan (a.game_stat);
}

int inline manhattan (unsigned long long ll) {
int number = 0, res = 0;

for (int i = 1; i <= 15; ++i) {
    number = what_number (ll, i - 1);
    if (!number) continue;

    if (i%N) res += abs (number %N - i%N);
    else if (number %N) res += (N - number %N);
    res += abs (number /N - i/N);
}

return res;
}


unsigned long long inline mypow (int x)
{
unsigned long long ll = 1;
for (int i = 0; i < x; ++i)
    ll *= 16;

return ll;
}

bool solvabiliti (unsigned long long _stat)
{
unsigned inversions = 0, count = 0;
unsigned long long _stat2 = 0;

for (int i = 0; i < 16; ++i, _stat /= 16)
    if (_stat - _stat /16*16 == 0) {inversions += i%N + 1;}
    else {
        _stat2 = _stat;
        count = _stat - _stat /16*16;

        for (int j = i + 1; j < 16; ++j, _stat2 /= 16)
            if (_stat2 - _stat2/16*16 == 0) continue;
            else if (count > _stat2 - _stat2 /16*16) ++inversions;
        }

return !(inversions %2);
}
