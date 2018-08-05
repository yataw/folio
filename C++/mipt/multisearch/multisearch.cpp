#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <vector>
#include <set>
#define SIZE_ALPHABET 26
using namespace std;

struct vrtx {
    char next [SIZE_ALPHABET],
         go [SIZE_ALPHABET],
         symb;

    int  word_key,
         suff_link,
         p;              //parent
};


vrtx add_vrtx (int p, int c) {
    vrtx v;

    memset (v.next, 255, sizeof (v.next));
    memset (v.go, 255, sizeof (v.go));
    v.word_key = 0;
    v.suff_link = -1;
    v.p = p;
    v.symb = c;

return v;
}

void add_string_to_bohr (vector <vrtx>& bohr, const string& s, int key){
    int length = s.length (), num = 0;

    for (int i = 0; i < length; ++i)
        {
        if (bohr [num].next [s [i] - 'a'] == -1)
            {
            bohr.push_back (add_vrtx (num, s [i] - 'a'));
            bohr [num].next [s [i] - 'a'] = bohr.size () - 1;
            }

        num = bohr [num].next [s [i] - 'a'];
        }

    bohr [num].word_key = key;
}


int go (vector <vrtx>& bohr, int v, int c);

int get_link (vector <vrtx>& bohr, int v) {
	if (bohr[v].suff_link == -1)
		if (v == 0 || bohr[v].p == 0)
			bohr[v].suff_link = 0;
		else
			bohr[v].suff_link = go (bohr, get_link (bohr, bohr[v].p), bohr[v].symb);

return bohr[v].suff_link;
}

int go (vector <vrtx>& bohr, int v, int c) {
	if (bohr[v].go[c] == -1)
		if (bohr[v].next[c] != -1)
			bohr[v].go[c] = bohr[v].next[c];
		else
			bohr[v].go[c] = ((v == 0) ? 0 : go (bohr, get_link (bohr, v), c));

return bohr[v].go[c];
}

void seach (ifstream& fin, vector <vrtx>& bohr, map <int, string>& words, set <string>& res) {
    char c;
    int num = 0, temp_num = 0;
    while (!fin.eof ())
        {
        fin >> c;
        c -= 'a';
        if (c < 0 || c > 27) break;

        num = go (bohr, num, c);

        if (bohr [num].word_key)
            if (words.count (bohr [num].word_key) != 0)
                {
                res.insert (words [bohr [num].word_key]);
                words.erase (bohr [num].word_key);
                }

        temp_num = num;

        while (temp_num = get_link (bohr, temp_num))
            {
            if (bohr [temp_num].word_key)
                if (words.count (bohr [temp_num].word_key) != 0)
                    {
                    res.insert (words [bohr [temp_num].word_key]);
                    words.erase (bohr [temp_num].word_key);
                    }
            }
    }
}

int main () {
    ifstream fin ("input.txt");
    ofstream fout ("output.txt");

    map <int, string> words;
    set <string> res;
    int N;
    string str;
    vector <vrtx> bohr;
    bohr.push_back (add_vrtx (0, 0));

    fin >> N;

    for (int i = 1; i <= N; ++i)
        {
        fin >> str;
        words.insert (make_pair (i, str));
        add_string_to_bohr (bohr, str, i);
        }

    seach (fin, bohr, words, res);


for (auto i: res)
    if (i != *(--(res.end ()))) fout << i << endl;
    else fout << i;
}
