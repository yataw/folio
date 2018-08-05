#include <stdio.h>
#include "TXlib.h"

main ()
{
#define sizesq 20
int sizeX = 600, sizeY = 600, neigh = 0;
int x = 1 - sizesq*10, y = 1 - sizesq*10;
int outcolor = TX_WHITE; int colorSQ = TX_RED;
txCreateWindow (sizeX, sizeY);
txSetFillColor (outcolor);
txRectangle (-250, -250, sizeX + 250, sizeY + 250);

txSetColor (TX_GREEN);
txSetFillColor (outcolor);

while ((y+=sizesq) <= sizeY)
{
while ((x+=sizesq) <= sizeX) txRectangle (x - 1, y - 1, x + 19, y + 19);
x = 1 - sizesq*10;
}
//---------------------------------------------------------
txSetFillColor (colorSQ);
txRectangle (sizesq*13,sizesq*13, sizesq*14, 16*sizesq);
txRectangle (sizesq*13,sizesq*13, sizesq*15, 14*sizesq);
txRectangle (sizesq*12,sizesq*14, sizesq*13, 15*sizesq);
//txRectangle (sizesq*5,sizesq*5, sizesq*8, 6*sizesq);
//---------------------------------------------------------

x = 1 - sizesq*10; y = 1 - sizesq*10;

while (!GetAsyncKeyState (VK_RETURN))
    {
    //while (!GetAsyncKeyState (VK_SPACE));
    //while (GetAsyncKeyState (VK_SPACE));
    txSleep (40);
    while (y <= sizeY)//Здесь ставим метки
        {
            while (x <= sizeX)
                {
                if (txGetPixel  (x+sizesq, y) == colorSQ) neigh++;
                if (txGetPixel  (x-sizesq, y) == colorSQ) neigh++;
                if (txGetPixel  (x, y+sizesq) == colorSQ) neigh++;
                if (txGetPixel  (x, y-sizesq) == colorSQ) neigh++;
                if (txGetPixel  (x+sizesq, y+sizesq) == colorSQ) neigh++;
                if (txGetPixel  (x+sizesq, y-sizesq) == colorSQ) neigh++;
                if (txGetPixel  (x-sizesq, y+sizesq) == colorSQ) neigh++;
                if (txGetPixel  (x-sizesq, y-sizesq) == colorSQ) neigh++;

                if (neigh <2 || neigh > 3) txSetPixel (x+5, y, TX_PINK);

                if (neigh == 3) txSetPixel (x+10,y, colorSQ);

                neigh = 0;
                x+=sizesq;
                }
            x = 1 - sizesq*10;
            y+= sizesq;
        }

    x = 11 - sizesq*10; y = 1 - sizesq*10;
     while (y<= sizeY)
        {
        while (x<= sizeX)
            {
            if (txGetPixel  (x, y) == colorSQ && txGetPixel  (x-5, y) != TX_PINK)
                {
                txSetFillColor (colorSQ);
                txRectangle (x - 11, y - 1, x + sizesq - 11, y + sizesq - 1);
                }
            x+=sizesq;
            }
        x = 11 - sizesq*10;
        y+=sizesq;
        }



        x = 6 - sizesq*10; y = 1 - sizesq*10;
    while (y<= sizeY)
        {
        while (x<= sizeX)
            {
            if (txGetPixel  (x, y) == TX_PINK)
                {
                txSetFillColor (outcolor);
                txRectangle (x - 6, y - 1, x + sizesq - 6, y + sizesq - 1);
                }
            x+=sizesq;
            }
        x = 6 - sizesq*10;
        y+=sizesq;
        }
         x = 1 - sizesq*10; y = 1 - sizesq*10;

    }
    }
