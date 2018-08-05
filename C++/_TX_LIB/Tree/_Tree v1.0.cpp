#include <stdio.h>
#include "txlib.h"

int SPEED = 5, SWITCH = 0;

void draw (double x, double y, double l, double alpha)
{
if (l < 3) return ;
if (GetAsyncKeyState (VK_RETURN)) exit (0);

while (GetAsyncKeyState (VK_UP) && SPEED < 11) SWITCH = 1;
while (GetAsyncKeyState (VK_DOWN) && SPEED > 5) SWITCH = -1;

switch (SWITCH)
{
case -1: SPEED -= 1; break;
case 1: SPEED += 1; break;
}

SWITCH = 0;

double x1 = x + l*cos (alpha), y1 = y - l*sin (alpha);

txSetColor (RGB (108, 53, 0), l/12);

if (l < 12)
    {
    if (!(rand ()%30)) {txSetColor (255, 2); txSetFillColor (255); txCircle (x1, y1, 5);}
    txSetColor (RGB (0, 255, 0), l/12);
    }

if (!(rand ()%SPEED)) txSleep (0);
txLine (x, y, x1, y1);


draw (x1, y1, l - rand ()%20, alpha - (rand ()%100)/1.6e2);
draw (x1, y1, l - rand ()%20, alpha + (rand ()%100)/1.6e2);
}


main ()
{
int len1;
txCreateWindow (1024, 766);
txSetColor (RGB (108, 53, 0), 2);
txSetConsoleAttr (0x02);

for (int i = 0; true; i++)
    {
    txSetFillColor (TX_WHITE);
    txClear ();
    len1 = printf ("number [%d] :: SPEED = %d :: Press RETURN to exit :: waiting time = ", i + 1, SPEED);

    draw (500, 766, 80, 3.1415926 / 2);

    for (int count = 90 / SPEED; count; count--)
        {
        for (int count2 = printf ("%d", count); count2; count2--)
            {
            txSleep (100);
            printf ("\b \b");
            }
        if (GetAsyncKeyState (VK_RETURN)) exit (0);
        }

    while (len1--) printf ("\b \b");
    }
}
