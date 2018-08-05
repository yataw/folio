#include "TXLib.h"
const int N_BUMS = 3333;
//int N_BUMS;


struct Bum
    {
    int a, b, color, r;
    };

void RandomBums (Bum b[]);
void DrawBum (Bum b);
void AllBumsDraw (Bum b[]);

int main()
    {
        //std::cin >> N_BUMS;
    int i = 0;
    txBegin ();
    txCreateWindow (1300, 700);
    Bum b[N_BUMS] = {};

    RandomBums (b);
    AllBumsDraw (b);

    txEnd ();
    }

void AllBumsDraw (Bum b[])
    {
    int i = 0;
    while (i< N_BUMS && !GetAsyncKeyState (VK_RETURN))
        {
        if (GetAsyncKeyState (VK_LBUTTON)) {DrawBum (b[i]); i++;}
        }
    }

void RandomBums (Bum b[])
    {
    int i = 0; int a = 1; int k = 2;
    while (i < N_BUMS)
        {
        b[i].a = rand ()%1000 + 150;
        b[i].b = rand ()%500 + 150;
        b[i].color = RGB (rand (), rand (), rand ());
        b[i].r = rand ()%k + 1;
        if (rand ()%7 == 6) b[i].r = 3;
        k = 2;
        i++;
        }
    }

void DrawBum (Bum b)
    {
    double x = 0, y = 10, alpha = 0;
    int x0 = txMouseX(), y0 = txMouseY();
    int sound = 0;
        while (x <= 4000)
            {
            double r = sqrt (x*x+y*y);
            txSetPixel ( r*cos(alpha) +x0, r*sin(alpha) + y0, b.color);
            alpha += 0.01;
            x+=0.1*(b.r)/alpha;
            if (alpha >= 1000) break;
            if (x>=0 && sound<2) sound++;
            if (sound==1) txPlaySound ("salut.wav");
            }
    }
