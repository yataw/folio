#include "TXLib.h"
void GrDraw ();
int Formula (double x0, double y0);

int main()
    {
    txCreateWindow (800, 600);
    GrDraw ();
    }

void GrDraw ()
    {
    double x = 0, y = 0;
    while (y<=600)
        {
        while (x<=800)
            {
            txSetPixel (x, y, TX_GRAY);
            txSetPixel (x, y, Formula (x, y));
            x++;
            }
        x = 0;
        y++;
        }
    }

int Formula (double x0, double y0)
    {
    int schetckick = 0;
    double x = x0;
    double y = y0;
    while (3>2)
        {
        double xn = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xn;
        schetckick++;
        if (schetckick == 1)
            {
            return (sqrt (x*x + y*y)*1000);

            //*color = 10000;

            }
        //if (9 >= x*x + y*y

        }
    }

