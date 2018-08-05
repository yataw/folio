#include "TXLib.h"
const int N_BALLS = 1000;
const int TOP_Y = 600;
const int TOP_X = 775;//with rectangles
const int SaveWindow_x1 = 0 + 25;
const int SaveWindow_x2 = 800 - 25;
const int SaveWindow_y1 = 0;
const int SaveWindow_y2 = 600;
//----------------------------------------STRUCTURES-------------------------------------------------
struct Ball_t
    {
    double x, y, r, vx, vy;
    COLORREF color;
    };
//----------------------------------------VOIDS------------------------------------------------------
void DrawBall (Ball_t b);
void MoveBall ();
void EngineAllBallsAndTemperatureOfWalls (Ball_t b[], int size, double* Ql, double* Qr);
void EngineBall (Ball_t* b, double* Ql, double* Qr);
void DrawAllBalls (Ball_t b[], int size);
void RandomBalls (Ball_t b[]);
//void WriteTermoFisics ();
void TermoWalls (int Tleft, int Tright);
/*void ReflectionBalls (int xA, int yA, int* vxA, int* vyA, int rA,
                      int xB, int yB, int* vxB, int* vyB, int rB);*/

///-------------------------------------------------------------------------------------------
int main()
    {
    txCreateWindow (1000, 600);
    txBegin ();
    txSetFillColor (TX_WHITE);
    txClear ();
    MoveBall ();
    txEnd ();

    return 0;
    }
//---------------------------------------------------------------------------------------------------

void DrawBall (Ball_t b)
    {
        txSetFillColor (b.color);
        txCircle (b.x, b.y, b.r);
    }

void MoveBall ()
    {
    Ball_t b[N_BALLS] = {};
    RandomBalls (b);
    int Tleft = RGB (0, 0, 0), Tright = RGB (0, 0, 0);
    double Ql = 1000, Qr = 1000;

     while (!GetAsyncKeyState (VK_RETURN))
        {
        txSetColor (TX_BLACK);
        DrawAllBalls (b, N_BALLS);
        EngineAllBallsAndTemperatureOfWalls (b, N_BALLS, &Ql, &Qr);
        //WriteTermoFisics ();
        TermoWalls (Tleft, Tright);



        txSleep (40);
        txSetFillColor (TX_WHITE);
        txClear ();
        }
    }




/*void EngineBall (Ball_t b[])
    {
    int i = 0;
        while (!GetAsyncKeyState (VK_RETURN))
            {
            b[i] -> x += b[i] -> vx;
            b[i] -> y += b[i] -> vy;
            }

    }*/
void EngineAllBallsAndTemperatureOfWalls (Ball_t b[], int size, double* Ql, double* Qr)
    {
    double Qlnew = 0, Qrnew = 0;
    int i = 0, Tl = 0, Tr = 0;
    int goodTl = 0, goodTr = 0;
    Qlnew  = *Ql; Qrnew  = *Qr;
    while (i < size)
        {
         EngineBall (&b[i], &Qlnew, &Qrnew);
         goodTl += Tl;
         goodTr += Tr;
         i++;
        }
    }

void EngineBall (Ball_t* b, double* Ql, double* Qr)
    {
    b -> x += b -> vx;
    b -> y += b -> vy;


//----------------------------------------------------------------------------------
    if (b -> x  <= (b -> r) + SaveWindow_x1)
        {
        b -> vx = - (b -> vx);

        if (*Ql > (b -> vx)*100)
            {
            double oldQ = *Ql;
            *Ql-= b -> vx;
            b -> vx += oldQ/50;
            }
        b -> x = (b -> r) + SaveWindow_x1 + 1;

        if (*Ql < (b -> vx)*100)
            {
            double oldQ = *Ql;
            *Ql+= b -> vx;
            b -> vx -= oldQ/50;
            }
        }

    if (b -> x  >= SaveWindow_x2 - (b -> r))
        {
        b -> vx = - (b -> vx);


        if (*Qr > (b -> vx)*100)
            {
            double oldQ = *Qr;
            *Qr-= b -> vx;
            b -> vx += oldQ/50;
            }
        b -> x = SaveWindow_x2 - (b -> r) - 1;

        if (*Qr < (b -> vx)*100)
            {
            double oldQ = *Qr;
            *Qr+= b -> vx;
            b -> vx -= oldQ/50;
            }
        }

    if (b -> y  <= SaveWindow_y1 + (b -> r))
        {
        b -> vy = - (b -> vy);
        b -> y = (b -> r) + SaveWindow_y1 + 1;
        }

    if (b -> y  >= SaveWindow_y2 - (b -> r))
        {
        b -> vy = (- (b -> vy));
        b -> y = SaveWindow_y2 - (b -> r) - 1;
        }


    }


void DrawAllBalls (Ball_t b[], int size)
    {
    for (int i = 0; i < size; i++)
        DrawBall (b[i]);
    }

void RandomBalls (Ball_t b[])
    {
    int i = 0; int a = 1; int colorR = 0;
    while (i < N_BALLS)
        {
        b[i].r = 7;
        b[i].x = rand ()%TOP_X + b[i].r + 1 + 25;
        b[i].y = rand ()%TOP_Y - b[i].r - 1;
        b[i].vx = rand ()%7 - rand ()%7;
            if (b[i].vx == 0) b[i].vx = rand ()%7 - rand ()%7;
            if (b[i].vx == 0) b[i].vx = rand ()%7 - rand ()%7;
            if (b[i].vx == 0) b[i].vx = 5;
        b[i].vy = rand ()%4 - rand ()%4;
            if (b[i].vy == 0) b[i].vy = rand ()%7 - rand ()%7;
            if (b[i].vy == 0) b[i].vy = rand ()%7 - rand ()%7;
            if (b[i].vy == 0) b[i].vy = 5;
        if (colorR%3 == 0) b[i].color = (RGB (6, 221, 208));
        if (colorR%3 == 1) b[i].color = (RGB (6, 221, 47));
        if (colorR%3 == 2) b[i].color = (RGB (252, 155, 40));
        colorR ++;
        i++;
        }
    }


/*void WriteTermoFisics (int Tleft, int Tright)
    {
    txSetFillColor (TX_BLACK);
    txRectangle (800, 0, 1000, 600);
    txSetColor (TX_WHITE);
    txSelectFont ("Times New Roman", 30);
    txTextOut (850, 30, "Расчеты");
    }*/

void TermoWalls(int Tleft, int Tright)
    {
    txSetFillColor (TX_PINK);
    txRectangle (0, 0, 25, 600);
    txRectangle (775, 0, 800, 600);
    }


