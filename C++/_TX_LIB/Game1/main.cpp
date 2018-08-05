#include "TXLib.h"

void Drawball (int x, int y, int r, COLORREF color);
void FisicsBall (int* x, int* y, int* vx, int* vy, int* r, int* color);
void MoveBallandLine ();
void CommandsBall (int* vx, int* vy);
void DrawPicture ();


int main()
    {
    txBegin ();
    txCreateWindow (800, 600);

    txSetFillColor (TX_WHITE);
    txClear ();
    MoveBallandLine ();
    txEnd ();


    return 0;
    }

void Drawball (int x, int y, int r, COLORREF color)
    {
    txSetFillColor (color);
    txSetColor (TX_BLACK, 1);
    txCircle (x, y, r);
    }

void FisicsBall (int* x, int* y, int* vx, int* vy, int* r, int* color)
    {
    *x += *vx;
    *y += *vy;

    if (*x >= 800 - *r)
        {
        *x = 800 - 1 - *r, *vx = -*vx, *color = RGB (rand(), rand(), rand());
        }

    if (*x <= 0 + *r)
        {
        *x = 0 + 1 + *r, *vx = -*vx, *color = RGB (rand(), rand(), rand());
        }

    if (*y >= 600 - *r)
        {
        *y = 600 - 1 - *r, *vy = -*vy, *color = RGB (rand(), rand(), rand());
        }

    if (*y <= 0 + *r)
        {
        *y = 0 + 1 + *r, *vy = -*vy, *color = RGB (rand(), rand(), rand());
        }

    if (*x >= 403 + *r)
        {
        *color = RGB (rand (), rand (), rand ());
        }

    }

void MoveBallandLine ()
    {
    int x = 30, y = 30, vx = 0, vy = 0, r = 15, color = TX_BLACK;
    //HDC portal2  = txLoadImage ("portal2.bmp");

    while (!GetAsyncKeyState (VK_RETURN))
        {
        //txBitBlt (txDC(), 650, 516, 800, 600, portal2, 0, 0);

        txSetColor (TX_PINK, 6);
        txLine (400, 0, 400, 600);

        DrawPicture ();

        Drawball (x, y, r, color);
        FisicsBall (&x, &y, &vx, &vy, &r, &color);
        CommandsBall (&vx, &vy);

        txSleep (20);



        if (x <= 400 + r)
            {
            txSetFillColor (TX_WHITE);
            txClear ();
            DrawPicture ();
            }
        }
    //txDeleteDC (portal2);
    }

void CommandsBall (int* vx, int* vy)
    {
    if (GetAsyncKeyState (VK_RIGHT))
        {
        *vx = 7;
        }

    if (GetAsyncKeyState (VK_LEFT))
        {
        *vx = -7;
        }

    if (!GetAsyncKeyState (VK_RIGHT) && !GetAsyncKeyState (VK_LEFT))
        {
        *vx = 0;
        }

    if (GetAsyncKeyState (VK_UP))
        {
        *vy = -7;
        }

    if (GetAsyncKeyState (VK_DOWN))
        {
        *vy = 7;
        }

    if (!GetAsyncKeyState (VK_UP) && !GetAsyncKeyState (VK_DOWN))
        {
        *vy = 0;
        }

    }

void DrawPicture ()
    {

    }
