#include <stdio.h>
#include "txlib.h"

#define MAXSIZE 1000
#define NUMSORTS 8

enum consts {xwin = 1366, ywin = 768, x_bckg_gr = 600, y_bckg_gr = 480, bckg_up = 10,
    bckg_lr = 5, box_y = 40, box_x1 = x_bckg_gr + bckg_lr + 5, box_x2 = xwin - x_bckg_gr - bckg_lr - 5,
    color_box = RGB (148, 154, 151), minibox_x = 30, minibox_y = 20};

int _comp = 0, _numassig = 0, n = 1;

struct sort
{
char* _name;
int _numswaps, _numassig;
struct {int r, g, b;} color;
};

void puts_start_parameters ();
void draw ();
void control_panel ();
void GRdraw ();
void sort_boxes ();

void myswap                        (int*, int*);
int shift                          (int*, int, int);
void compare                       (int* ,int, int);
void extra_quick_sort_recursiv     (int* , int*, int*);

void _0_quick_sort_recursiv        (int*);
void _1_buble_simple               (int*);
void _2_select_2x                   (int*);
void _3_shaker                     (int*);
void _4_insert_simple              (int*);
void _5_insert_binary_search       (int*);
void _6_selection                  (int*);

void (*arr_sorts [NUMSORTS]) (int*) = {_0_quick_sort_recursiv, _1_buble_simple, _2_select_2x, _3_shaker,
    _4_insert_simple, _5_insert_binary_search, _6_selection};// в перебирающем цикле конст

char* sorts_names [] =
    {"quickSR", "buble_s", "select_2x", "shaker", "insert_s", "insert_bs",
    "select", "uni_find"};

int sorts_colors [] [3] = { {246, 12, 12}, {252, 202, 48}, {88, 231, 18}, {18, 231, 203}, {17, 108, 232},
    {238, 29, 240}, {133, 127, 127}, {255, 255, 0}};

sort sorts_arr [NUMSORTS];

int main (int argc, char** argv)
{
txCreateWindow (xwin, ywin);

puts_start_parameters ();

draw ();
}

void puts_start_parameters ()
{
for (int i = 0; i < NUMSORTS; i++)
    {
    sorts_arr [i]._name = sorts_names [i];
    sorts_arr [i].color.r = sorts_colors [i] [0];
    sorts_arr [i].color.g = sorts_colors [i] [1];
    sorts_arr [i].color.b = sorts_colors [i] [2];
    }
}

void draw ()
{
control_panel ();
GRdraw ();
}

void control_panel ()
{
txSetColor (0, 2);
txSetFillColor (0xFFFFFF);
txRectangle (bckg_lr, bckg_up, x_bckg_gr + bckg_lr, y_bckg_gr + bckg_up);
txRectangle (xwin - bckg_lr, bckg_up, xwin - x_bckg_gr - bckg_lr, y_bckg_gr + bckg_up);
sort_boxes ();
}

void sort_boxes ()
{
int temp = 80;

txSetColor (color_box);
txSetFillColor (color_box);

for (int i = 0, count = 0; count < NUMSORTS; i += box_y + 5, count++)
    {
    txSetColor (color_box);
    txSetFillColor (color_box);
    txRectangle (box_x1, 0 + i + temp, box_x2, box_y + i + temp);

    txSetColor (RGB (sorts_colors [count] [0], sorts_colors [count] [1], sorts_colors [count] [2]));
    txSetFillColor (RGB (sorts_colors [count] [0], sorts_colors [count] [1], sorts_colors [count] [2]));
    txRectangle (box_x1 + 10, i + temp + 10, box_x1 + 10 + minibox_x, i + temp + 10 + minibox_y);

    txSetColor (0);
    txTextOut (box_x1 + 10 + minibox_x + 1, i + temp + 10 + 1, sorts_names [count]);
    }
}

void GRdraw ()
{
int testing_arr [MAXSIZE] = {}, xold = 0, yold = 0, flag = 0;

for (int i = 0; i < 7; i++) // !NUMSORTS
    {
    txSetColor (RGB (sorts_colors [i] [0], sorts_colors [i] [1], sorts_colors [i] [2]));
    txSetFillColor (RGB (sorts_colors [i] [0], sorts_colors [i] [1], sorts_colors [i] [2]));

    xold = yold = 0;

    for (n = 1; n <= MAXSIZE; n++)
        {
        _comp = _numassig = 0;

        for (int i = 0; i < n; i++) testing_arr [i] = rand () % 2500;
        (*arr_sorts [i]) (testing_arr);


        txLine ((double) (x_bckg_gr - 5)*n /MAXSIZE + 5,
                y_bckg_gr - xold/n > bckg_up ? y_bckg_gr - xold/n : bckg_up,
                (double) (x_bckg_gr - 5)*n /MAXSIZE + 5,
                y_bckg_gr - _comp /n > bckg_up ? y_bckg_gr - _comp/n : bckg_up);

        txLine ((double) (x_bckg_gr - 5)*n /MAXSIZE + 5 + xwin - x_bckg_gr - bckg_lr,
                y_bckg_gr - yold/n > bckg_up ? y_bckg_gr - yold/n : bckg_up,
                (double) (x_bckg_gr - 5)*n /MAXSIZE + 5 + xwin - x_bckg_gr - bckg_lr,
                y_bckg_gr - _numassig /n > bckg_up ? y_bckg_gr - _numassig/n : bckg_up);

        xold = _comp;
        yold = _numassig;
        }
    }
}












void myswap (int* x, int* y)
{
int z = *x;
*x = *y;
*y = z;
_numassig++;
}

int shift (int* arr, int i, int count)
{
int save = arr [i];

for (; i > count; i--)
    {arr [i] = arr [i - 1]; _numassig++;}
return save;
}

void compare (int* arr ,int max, int min)
{
int newmax = max, newmin = min, count = min - max;
for (int i = 1; i < count; i++)
    {
    if (arr [newmin] < arr [min - i]) newmin = min - i;
    else if (arr [newmax] > arr [min - i]) {newmax = min - i; _comp++;}
    _comp += 2;
    }
myswap (arr + newmin, arr + min);
myswap (&arr [newmax], &arr [max]);
}

void extra_quick_sort_recursiv (int* arr, int* start, int* end)
{
if (end < start) {_comp++; return;}
if (end - start == 1) if (*end < *start) {myswap (end, start); _comp += 2;} else {_comp += 2; return;}
if (end - start == 2)
    {
    for (int i = 0; i < 2; i++)
        {
        for (int count = i + 1; count < 3; count++)
            if (start [i] > start [count]) {myswap (start + i, start + count);}
        _comp += 2;
        }
    }

int key = start - arr + rand () % (end - start + 1);
int i = start - arr, j = end - arr;

while (i <= j)
{
while (arr [i] <= arr [key] && i < end - arr) {i++; _comp ++;}
while (arr [j] >= arr [key] && j > start - arr) {j--; _comp++;}
if (i > j) break;
myswap (arr + i, arr + j);
i++; j--;
}

if (i > key)
    {
    myswap (arr + i - 1, arr + key);
    extra_quick_sort_recursiv (arr, start, arr + i - 2);
    extra_quick_sort_recursiv (arr, arr + i, end);
    }
else if (j < key)
    {
    myswap (arr + j + 1, arr + key);
    extra_quick_sort_recursiv (arr, start, arr + j);
    extra_quick_sort_recursiv (arr, arr + j + 2, end);
    }
}

//-----------------------------------------------------------------------------------------------------------//
///                                         _SORTS_
//-----------------------------------------------------------------------------------------------------------//

void _0_quick_sort_recursiv (int* arr)
{
extra_quick_sort_recursiv (arr, arr, arr + n - 1);
}

void _1_buble_simple (int* arr)
{
for (int i = 0, swaps = 1; i < n - 1 && swaps; i++)
    for (int count = 0, swaps = 0; count < n - i - 1; count++)
        if (arr [count] > arr [count + 1]) {myswap (arr + count, arr + count + 1); swaps = 1;}
}

void _2_select_2x (int* arr)
{
int x, y, temp;
bool end = true;

for (int count1 = 0; count1 < n /2 && end; count1++)
    {
    x = count1;
    y = n - count1 - 1;

    if (x >= y) {end = false; break;}

    if (arr [x] < arr [y]) {compare (arr, x, y); _comp++; continue;}
        else if (arr [x] > arr [y]) {myswap (arr + x, arr + y); compare (arr, x, y); _comp++; continue;}
            else
                {
                for (temp = y; arr [x] == arr [temp]; )
                    {temp--; _comp++; if (x >= temp) {end = false; break;}}
                if (arr [x] > arr [temp]) {myswap (arr + temp, arr + x); compare (arr, x, y); _comp++; continue;}
                    else {myswap (&arr [y], &arr [temp]); compare (arr, x, y);}
                 _comp++;
                }
    }
}

void _3_shaker (int* arr)
{
}

void _4_insert_simple (int* arr)
{
for (int i = 1; i < n; i++)
    for (int count = 0; count < i; count++)
        if (arr [i] < arr [count]) {_comp++; arr [count] = shift (arr, i, count); break;}
}

void _5_insert_binary_search (int* arr)
{
int r, l;

for (int i = 1; i < n; i++)
    {
    for (r = i - 1, l = 0; r > l; )
        {
        _comp++;                         //down
        if (arr [i] < arr [(r - l) / 2 + l])
            {if ((r - l) == 1) {r = l; break;} r = (r - l) /2 - 1 + l;}
        else {l = (r - l) /2 + 1 + l;}
        }

    if (arr [i] < arr [r]) {arr [r] = shift (arr, i, r); _numassig++;  _comp++;}
    else {arr [r + 1] = shift (arr, i, r + 1); _numassig++;}
    }
}

void _6_selection (int* arr)
{
for (int i = 0; i < n - 1; i++)
    for (int count = n - 1 - i, max = count; count > 0; count--)
        arr [max] < arr [count - 1] ? myswap (arr + max, arr + count - 1), _comp++ : 0;
}
