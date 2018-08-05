#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct S
{
    S(int &t_id, int& t_score): id(t_id), score(t_score) {}
    int score, id;

};


int main()
{
    int N;
    cin >> N;

    vector<S> vec;
    int in1, in2;

    while(cin >> in1 >> in2)
        vec.push_back(S(in1, in2));

    sort(vec.begin(), vec.end(), [] (const S& S1, const S& S2)
        {return S1.score > S2.score || (S1.score == S2.score && S1.id < S2.id);});

    for(auto i: vec)
        cout << i.id << ' ' << i.score << endl;
}
