#include "txlib.h"
#define NUM_CH 30
int main ()

{
int x0 = 400, y0 = 300, x1 = 800, y1 = 400;
struct charge
{
int x, y, q;
} arr [NUM_CH];

struct str
{
int x, y, q;
} click [NUM_CH];

txCreateWindow (1366, 768);





for (int i = 0, color = 0; i < NUM_CH; i++)
{
while (!GetAsyncKeyState (VK_LBUTTON) & !GetAsyncKeyState (VK_RBUTTON));
if (GetAsyncKeyState (VK_RBUTTON)) click [i].q = 1;
else click [i]. q = -1;

click [i].x = txMouseX  ();
click [i].y = txMouseY  ();

if (click [i]. q == -1) color = RGB (0, 255, 0);
else color = RGB (0, 0, 255);

txSetFillColor (color);
txSetColor (color);

txCircle (click [i].x, click [i].y, 10);
while (GetAsyncKeyState (VK_LBUTTON) | GetAsyncKeyState (VK_RBUTTON));
}

cout << "WAIT PLS";

for (int i = 0; i < NUM_CH; i++)
    arr [i] = {click [i].x, click [i].y, click [i].q};


int x = 0;
long double max_tens = 0, tens_x = 0, tens_y = 0, total_tens = 0, r = 0;
for (int y = 0; y < 768; y++, x = 0)
    for (; x < 1366; x++)
        {
        for (int i = 0; i < NUM_CH; i++)
            {
            r = sqrt ((x - arr [i].x)*(x - arr [i].x) + (y - arr [i].y)*(y - arr [i].y));
            tens_x += abs (x - arr [i].x) / (r*r*r + 0.1) *arr [i].q;
            tens_y += abs (y - arr [i].y) / (r*r*r + 0.1) *arr [i].q;
            }
        total_tens = sqrt (tens_x * tens_x + tens_y * tens_y);
        if (max_tens < total_tens) max_tens = total_tens;
        tens_x = tens_y = total_tens = 0;
        }
long double** color = new long double* [1366];
for (int i = 0; i < 1366; i++) color [i] = new long double [768];

for (int y = 0; y < 768; y++, x = 0)
    for (; x < 1366; x++)
        {
        for (int i = 0; i < NUM_CH; i++)
            {
            r = sqrt ((x - arr [i].x)*(x - arr [i].x) + (y - arr [i].y)*(y - arr [i].y));
            tens_x += abs (x - arr [i].x) / (r*r*r + 0.1) *arr [i].q;
            tens_y += abs (y - arr [i].y) / (r*r*r + 0.1) *arr [i].q;
            }
        total_tens = sqrt (tens_x * tens_x + tens_y * tens_y);
        color [x] [y] = total_tens /max_tens;

        //cout << (total_tens /max_tens + 0.1) * 255 << std :: endl;
        tens_x = tens_y = total_tens = 0;
        }

/*
for (int i = 0; i < 10000; i++)
    for (int i = 0; i < 768*1366 - 1; i++)
        if (i %2) pt [i] = (pt [i + 1] + pt [i]) /2;
        else pt [1366*768 -1 - i] = (pt [1366*768 -1 - i] + pt [1366*768 -2 - i]) /2;
*/
int i = 0;
for (int j = 0; j < 768; j++, i = 0)
    for (; i < 1366; i++)
        txSetPixel (i, j, RGB (color [i] [j] *255 *1000 , color [i] [j] *255 *200, 0));


//for (int i = 0; i < NUM_CH; i++) txCircle (arr [i].x, arr [i].y, 10);
}

