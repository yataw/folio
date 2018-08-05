#include "TXLib.h"
#include "MATH.h"

void OperationGr (double x = -400, double y = -100);
void DrawGr (double x, double y);

int main()
    {
    txCreateWindow (800, 600);
    OperationGr ();
    }

void DrawGr (double x, double y)
    {

        while (x<= 800)
            {
            y = x*x/100 + 15*sin (0.1*x);
            txSetFillColor (TX_RED);
            txSetColor (TX_RED);
            txCircle (x+400, -y + 500, 3);
            x+=0.1;
            if (x>=800) break;
            }
    }

void OperationGr (double x, double y)
    {
    ;
    while (5>3)
        {
        while (x<=800)
            {
            if (y <= x*x/100 + 15*sin (0.1*x))
                     txSetPixel (x+400, -y + 500, TX_GREEN);

            x+=5;
            }
        y++;
        x = -400;
        if (-y + 500<0)
            {
            DrawGr (-400, 0);
            break;
            }
        }
    }




