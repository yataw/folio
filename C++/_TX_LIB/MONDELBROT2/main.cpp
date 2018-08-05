#include "TXLib.h"
void GrDraw (int* scale);
int Gr (double x, double y);

int main()
    {
    txCreateWindow (1000, 768);
    txSelectFont ("Times New Roman", 22);


    int color = 1, r = 0, g = 255, b = 0, numerator = 0, kcolor = 1;
    double x = 0;
    double y = 0;
    int alpha = 0, k = 0, i =0, scale = 300;
    while (i>=0 && !GetAsyncKeyState (VK_RETURN))
        {
        if (i<1)
            { txTextOut (380, 384, "Нажмите SPAСE для запуска");
            txTextOut (1130-366, 730, "Нажмите ENTER для выхода");
            numerator++;
            if (numerator%90 == 89)
                {
                txSetColor (RGB (r, g, b));
                r+=1*kcolor;
                g+=-1*kcolor;
                if (r>=255 || r<=0) kcolor =-kcolor;
                }
            }

        if (i>=1)
            {
            if (i==1)
                {
                txSetFillColor (TX_BLACK);
                txClear ();
                }
            //txSetColor (TX_WHITE);
            txSetColor (TX_WHITE);
            GrDraw (&scale);
            i++;
            //if (GetAsyncKeyState (VK_UP)) scale +=100;
            }
        if (GetAsyncKeyState (VK_SPACE))
            {
             i++;
             txSetColor (TX_WHITE);
            }
        }


    }

void GrDraw (int* scale)
    {
    double x = -2.7, y = -1.2, r = 0, g = 0, b = 0;
    int StopScale = 0, StopLRUP = 0, leftright = 1100-366, updown = 400;
    while (y<=1.3 && !GetAsyncKeyState (VK_RETURN))
        {
        while (x<1)
            {
            r = Gr (x, y);
            g = 0;
            b = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('Q') && StopScale == 0)
                {
                *scale +=50;

                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                StopScale ++;
                }
////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('E') && StopScale == 0)
                {
                *scale -=50;

                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                StopScale ++;
                }
            if (!GetAsyncKeyState ('Q') && !GetAsyncKeyState ('E')) StopScale = 0;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('A') && StopLRUP == 0)
                {
                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                leftright +=10;
                StopLRUP ++;
                }
////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('D') && StopLRUP == 0)
                {
                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                leftright -=10;
                StopLRUP ++;
                }
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('W') && StopLRUP == 0)
                {
                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                updown -=10;
                StopLRUP ++;
                }
////////////////////////////////////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState ('S') && StopLRUP == 0)
                {

                txSetFillColor (TX_BLACK);
                txClear ();
                x = -3.7*300/(*scale);
                y = -1.3*300/(*scale);
                updown +=10;
                StopLRUP ++;
                }
            if (!GetAsyncKeyState ('S') && !GetAsyncKeyState ('W') &&
                !GetAsyncKeyState ('A') && !GetAsyncKeyState ('D')) StopLRUP = 0;

            txSetPixel (x**scale+leftright, -y**scale+updown, RGB (r, g, b));/////////////

            x+=0.003*300/(*scale);
            }
        x=-2.7*300/(*scale);
        y+=0.003*300/(*scale);
        if (y<=50) txTextOut (5, 10, "Нажмите ENTER для выхода");
        }
    }

int Gr (double x0, double y0)
    {
    double color = 0, i = 0;
    double x = x0, y = y0;
    while (i<=70)
        {
        double xn = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xn;

        i++;
        color = i*1000;
        if (3<= sqrt (x*x + y*y)) return color;

        //printf ("%f\n",sqrt (x*x + y*y));
        //if (sqrt (x*x + y*y)>=1000) txSleep (300);
        }
    return 0;
    }



