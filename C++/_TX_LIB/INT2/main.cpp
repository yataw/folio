#include "TXLib.h"
void GrDraw ();

int main()
    {
    txBegin ();
    txCreateWindow (800, 600);
    GrDraw();
    txEnd ();
    }

void GrDraw()
    {
    double x = 0, y = 10, alpha = 0;
    int r = 0, g = 0, b = 0;
    while (y<=600)
        {
        while (x<=800)
            {
            //double alpha = y/ sqrt((x*x + y*y));
            double r = sqrt (x*x+y*y);
            //txSetColor (TX_WHITE);
            //txSetPixel ( r +300, alpha*10 +300, TX_WHITE);
            txLine (800, 600, r*cos(alpha),r*sin (alpha));
            alpha =x/y;
            x+=0.1;
            if (int(x)%10>5) txSetColor (RGB (rand (), rand (), rand ()));
            if (int(x)%100>70)
                {
                r++; g++; b+=0;
                txSetColor (RGB (r, g, b));
                }
            //if (int(x)%5 ==4)    txSleep (40);
            }
        x = 0;
        y+=0.1;
        }
    }
