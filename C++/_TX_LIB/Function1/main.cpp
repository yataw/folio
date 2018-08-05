#include "TXLib.h"
#include "math.h"
struct Balls_t
    {
    double x, y, r, vx, vy;
    COLORREF color;
    };
void DrawFunction ()
    {
    double x = 0, v = 0, oldX = 0;
    double sin_a = 0, cos_a = 1, p1 = 1;
    double alpha = 0;
    double dobX = 220;
    int color = RGB (0, 200, 0), k = -1;
    //for (double x =  1; x >= -1; x -= 0.01) txCircle (x*50 + 200,  sqrt (1 - x*x) *50 + 200, 3);
    //for (double x = -1; x <=  1; x += 0.01) txCircle (x*50 + 200, -sqrt (1 - x*x) *50 + 200, 3);


    while (!GetAsyncKeyState (VK_RETURN))
        {
        //if (cos_a < -1) break;

        sin_a = p1 *sqrt (1 - cos_a*cos_a);
  //      if (cos_a >= 1) p1 = -p1;
  //      if (cos_a <= -1) p1 = -p1;
  //      if (cos_a >= -1 && cos_a <= 1) cos_a += p1*0.01;
        //txCircle (cos_a*50 + 200,  sin_a*50 + 200, 3);
        //txCircle (cos_a*50 + 200, -sin_a*50 + 200, 3);
        cos_a -= 0.01;

//----------------------------------------------------------1
        /*double y = sin (alpha);
        double x = cos (alpha);


        Sleep (100);
        alpha +=0.1;
        txCircle (x*50 + 400, -y*50 + 200, 3);*/
//-----------------------------------------------------------
        double sinA = sin (alpha);
        double cosA = cos (alpha);

        double y = x*x;
        if (x >= 21.5) break;
        txSetFillColor (TX_WHITE);
        txSetColor (TX_WHITE, 1);
        if (x >=0 && x <= 20) txCircle (x*10 + cosA*10 + 400, -y - sinA*10 + 600 - 4, 5);
        if (x >=0 && x <= 20) txCircle (-x*10 - cosA*10 + 400, -y - sinA*10 + 600 - 4, 5);

        if (x >= 13) txCircle (cosA*40 + 330, -sinA*40 + 320, 3);
        if (x >= 15 && x<= 20) txCircle (cosA*40 + 330, -sinA*20 + 320, 3);
        txSetFillColor (color);
        txSetColor (color);
        if (x >= 17) txCircle (cosA*20 + 330, sinA*20 + 320, 3);

        txSetFillColor (TX_WHITE);
        txSetColor (TX_WHITE);
        if (x >= 13) txCircle (-cosA*40 + 480, -sinA*40 + 320, 3);
        if (x >= 15 && x<= 20) txCircle (-cosA*40 + 480, -sinA*20 + 320, 3);
        txSetFillColor (color);
        txSetColor (color);
        if (x >= 17) txCircle (-cosA*20 + 480, sinA*20 + 320, 3);
        oldX = x + 6;
        v = (oldX*oldX) - (x*x)/(oldX - x);

        alpha +=0.1;
        x +=  40/v;
        printf("%f\nx= ", x);
        txSetColor (RGB(0, 200, 0));
        txSelectFont ("Lucida Console", 30);
        txTextOut (220, 100, "The face of");
        txSetColor (RGB (210, 0, 0));
        txSelectFont ("Lucida Console", 40);
        if (dobX >= 450) txTextOut (450, 90, "ALGEBRA!");
        txSetFillColor (TX_BLACK);
        txSetColor (TX_BLACK);
        txRectangle (dobX, 80, dobX + 420, 150);
        if (dobX <= 365) dobX+=1.5;
            else dobX+=4.8;
        if (alpha >= 11.8 && alpha<11.9) k =0;


       while (k>=0 && k<= 26)
           {
           if (k == 0) alpha = 9.2;
           sinA = sin (alpha);
           cosA = cos (alpha);
           color = RGB (210, 0, 0);

           txSetFillColor (color);
           txSetColor (color);
           txCircle (cosA*20 + 330, sinA*20 + 320, 3);
           txCircle (-cosA*20 + 480, sinA*20 + 320, 3);
           alpha += 0.1;
           k ++;
           }

        txSleep (40);

        }
    }

int main()
    {
    txCreateWindow (800, 600);
    txSetConsoleAttr (0x02);

    txBegin ();
    DrawFunction ();
    txEnd ();
    }

