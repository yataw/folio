#include "TXLib.h"
void Grdraw ()
    {
    double x = 0, y = 0, alpha = 500;
    while (!GetAsyncKeyState (VK_RETURN))
        {
        while (x<=800)
            {
            if (y>= 10*cos (0.1*x) + alpha && y<= 800) txSetPixel (x , y, TX_WHITE);
            if (y>=400 && y<= 10*cos (0.1*x) + alpha && x<=700 && x>= 450 && y <= x-20)
             txSetPixel (x , y, TX_BLUE);
            if (y>=300 && y<= 400 && x <= 685 && x>= 655) txSetPixel (x , y, TX_BLUE);

            if (y >= -(2*x - 1350)  && y<= 400 && y >= 2*x - 650) txSetPixel (x , y, TX_WHITE);
            if (y >= -(2*x - 1475)  && y<= 400 && y >= 2*x - 775) txSetPixel (x , y, TX_WHITE);
            if (170 >= (x-500)*(x-500) +(y-350)*(y-350)) txSetPixel (x , y, TX_WHITE);
            if (170 >= (x-562)*(x-562) +(y-350)*(y-350)) txSetPixel (x , y, TX_WHITE);
            if (300 >= (x-700)*(x-700) +(y-280)*(y-280)) txSetPixel (x , y, TX_WHITE);
            if (400 >= (x-750)*(x-750) +(y-250)*(y-250)) txSetPixel (x , y, TX_WHITE);
            //if (y>=
            //if (y>= x*x + y*y - 5)
            //else txSetPixel (x, y, TX_GREEN);
            x+=1;
            if (GetAsyncKeyState (VK_UP)) alpha=10;
//y +650>= 2*x
            }
        y+=1;
        x = 0;
        //if (y>=51) txSleep (100);
        }
    }
void Grdraw2 ()
    {
    double x = 0, y = 0;
    txSetColor (TX_BLUE);
    txSetFillColor (TX_BLUE);
    while (x<=800)
        {
        //y = 20*cos (0.1*x);
        //y= cos (x) + sin (x);
        txCircle (50*cos (x) + 300, 50*sin (x)+ 300, 3);
        x+=0.01;
        }
    }
int main()
    {
    txCreateWindow (800, 600);
    //Grdraw2 ();
    Grdraw ();

    }

