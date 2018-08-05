#include "TXLib.h"
void DrawBall (int x, int y, int r, COLORREF color);
void MoveBall ();
void EngineBall (int* x, int* y, int r, int* vx, int* vy);
void ReflectionBalls (int xA, int yA, int* vxA, int* vyA, int rA,
                      int xB, int yB, int* vxB, int* vyB, int rB);

int main()
    {
    txCreateWindow (800, 600);
    txBegin ();
    txSetFillColor (TX_WHITE);
    MoveBall ();
    txEnd ();


    return 0;
    }

void DrawBall  (int x, int y, int r, COLORREF color)
    {
    txSetFillColor (color);
    txCircle (x, y, r);
    }

void MoveBall ()
    {
    int x1 = 50, y1 = 50, x2 = 750, y2 = 50, x3 = 350, y3 = 50;
    int vx1 = 5, vy1 = 3, vx2 = 3, vy2 = 7, vx3 = 9, vy3 = 5;
    int r1 = 15, r2 = 15, r3 = 15;
    COLORREF color1 = TX_RED, color2 = TX_BLUE, color3 = TX_BLACK;

    while (!GetAsyncKeyState (VK_RETURN))
        {
        txSetFillColor (TX_WHITE);

        txClear ();

        DrawBall (x1, y1, r1, color1);
        DrawBall (x2, y2, r2, color2);
        DrawBall (x3, y3, r3, color3);

        EngineBall (&x1, &y1, r1, &vx1, &vy1);
        EngineBall (&x2, &y2, r2, &vx2, &vy2);
        EngineBall (&x3, &y3, r3, &vx3, &vy3);

        ReflectionBalls (x1, y1, &vx1, &vy1, r1, x2, y2, &vx2, &vy2, r2);
        ReflectionBalls (x1, y1, &vx1, &vy1, r1, x3, y3, &vx3, &vy3, r3);
        ReflectionBalls (x2, y2, &vx2, &vy2, r2, x3, y3, &vx3, &vy3, r3);


        txSleep (20);


        }
    }

void EngineBall (int* x, int* y, int r, int* vx, int* vy)
    {

    *x += *vx;
    *y += *vy;

    if (*x <= r)
        {
        *vx = - *vx, *x = 1 + r;
        }

    if (*x >= 800 - r)
        {
        *vx = - *vx, *x = 800 - 1 - r;
        }

    if (*y <= r)
        {
        *vy = - *vy, *y = 1 + r;
        }

    if (*y >= 600 -1 - r)
        {
        *vy = - *vy, *y = 600 - 1 - r;
        }
    }

void ReflectionBalls (int xA, int yA, int* vxA, int* vyA, int rA,
                      int xB, int yB, int* vxB, int* vyB, int rB)
     {
     if ((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB) <= (rA + rB) * (rA + rB))
        {
        int saveSpeedX = *vxA; *vxA = *vxB; *vxB = saveSpeedX;
        int saveSpeedY = *vyA; *vyA = *vyB; *vyB = saveSpeedY;
        }
     }
