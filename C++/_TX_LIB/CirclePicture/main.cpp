#include "TXLib.h"
void Gr (double* y);
int main()
    {
    double y1 = 0, y2 = 293;
    txCreateWindow (800, 600);
    HDC picture1  = txLoadImage ("1.bmp");
    HDC picture2 = txLoadImage ("2.bmp");
    HDC picture3 = txLoadImage ("3.bmp");
    HDC picture4 = txLoadImage ("4.bmp");
    HDC picture5 = txLoadImage ("5.bmp");
    HDC picture6 = txLoadImage ("6.bmp");
    HDC picture7 = txLoadImage ("7.bmp");
    HDC picture8 = txLoadImage ("8.bmp");
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture1, 0, 0);
    txBitBlt (txDC(), 0, y2, 384, y2 +288, picture2, 0, 0);
    Gr (&y1);
    Gr (&y2);
    ////////
    y1 = 0;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture3, 0, 0);
    Gr (&y1);
    ///////
    y2 = 293;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture4, 0, 0);
    Gr (&y2);
    //////
    y1 = 0;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture5, 0, 0);
    Gr (&y1);
    ///////
    y2 = 293;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture6, 0, 0);
    Gr (&y2);
    //////
        y1 = 0;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture7, 0, 0);
    Gr (&y1);
    ///////
    y2 = 293;
    txBitBlt (txDC(), 0, y1, 384, y1 + 288, picture8, 0, 0);
    Gr (&y2);
    //////
    txDeleteDC (picture1);
    txDeleteDC (picture2);
    txDeleteDC (picture3);
    txDeleteDC (picture4);
    txDeleteDC (picture5);
    txDeleteDC (picture6);
    txDeleteDC (picture7);
    txDeleteDC (picture8);
    }

void Gr (double* y)
    {
    double a = 0, x = 0, yD = 0, yold = *y + 288;
    while (*y <= yold && !GetAsyncKeyState (VK_RETURN))
        {
        while (x<=384)
            {
            double r = sqrt (x*x + *y**y);
            //txSetPixel (x*cos (alpha) + 500, y*sin (alpha) + 500, txGetPixel (x, y));
            txSetPixel (yD/2*cos (a/(384/2/3.1415926)) + 590, yD/2*sin (a/(384/2/3.1415926))  + 150 + yold -288, txGetPixel (x, *y));
            a +=0.1;
            x+=0.1;//(a/(1280/20/3.14159269))
            }
        yD+=1;
        (*y)++;
        a = 0;
        x = 0;
        }
    }



