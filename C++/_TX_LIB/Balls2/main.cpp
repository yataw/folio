#include "TXLib.h"
void DrawBall ();
void MoveBall (double* x, double* y, double r, double* vx, double* vy);



int main()
    {
    txCreateWindow (800, 600);
    txBegin ();
    txSetFillColor (TX_BLACK);
    DrawBall ();
    txEnd ();


    return 0;
    }
void DrawBall ()
    {
    double x = 25, y = 25, vx = 7, vy = 8, r = 55;
    double xm = 0, ym = 0;
    while (!GetAsyncKeyState (VK_RETURN))
            {
            ym = 0;
            txClear ();
            MoveBall (&x, &y, r, &vx, &vy);
            while (ym<=600)
                {
                while (xm<=800)
                    {
                    if (r*r>=(xm-x)*(xm-x) + (ym-y)*(ym-y)) txSetPixel (xm, ym, cos(xm/10)*sin(ym/10)*100000000);

                    xm++;
                    }
                xm=0;
                ym++;
                }
            txSleep (40);
            txSetFillColor (TX_BLACK);

            }
    }

void MoveBall (double* x, double* y, double r, double *vx, double *vy)
    {
    *x+=*vx;
    *y+=*vy;





    if (*x>=800 - r)
        {
        *x = 800 - 1 - r;
        *vx = -*vx;
        }
    if (*x<=0 + r)
        {
        *x = 1 +r;
        *vx=-*vx;
        }
    if (*y>=600 - r)
        {
        *y = 600-1 - r;
        *vy = -*vy;
        }
    if (*y<=0 +r)
        {
        *y = 1 +r;
        *vy = -*vy;
        }
    }




