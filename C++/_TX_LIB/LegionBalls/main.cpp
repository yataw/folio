#include "TXLib.h"
const int N_BALLS = 4000;
const int TOP_Y = 559;
const int TOP_X = 759;
const int SaveWindow_x1 = 0;
const int SaveWindow_x2 = 800;
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
void EngineAllBalls (Ball_t b[], int size);
void EngineBall (Ball_t* b);
void DrawAllBalls (Ball_t b[], int size);
void RandomBalls (Ball_t b[]);
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

     while (!GetAsyncKeyState (VK_RETURN))
        {
        DrawAllBalls (b, N_BALLS);
        EngineAllBalls (b, N_BALLS);
        txSetFillColor (TX_BLACK);
        txRectangle (800, 0, 1000, 600);
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
void EngineAllBalls (Ball_t b[], int size)
    {
    int i = 0;
    while (i < size)
        {
         EngineBall (&b[i]);
         i++;
        }
    }

void EngineBall (Ball_t* b)
    {
    int a = 1;

    b -> x += b -> vx;
    b -> y += (b -> vy)*((b -> r))/20;
    b -> vy += a;
//----------------------------------------------------------------------------------
    if (b -> x  <= (b -> r) + SaveWindow_x1)
        {
        b -> vx = - (b -> vx);
        b -> x = (b -> r) + SaveWindow_x1 + 1;
        }

    if (b -> x  >= SaveWindow_x2 - (b -> r))
        {
        b -> vx = - (b -> vx);
        b -> x = SaveWindow_x2 - (b -> r) - 1;
        }

    if (b -> y  <= SaveWindow_y1 + (b -> r))
        {
        b -> vy = - (b -> vy);
        b -> y = (b -> r) + SaveWindow_y1 + 1;
        }

    if (b -> y  >= SaveWindow_y2 - (b -> r))
        {
        b -> vy = (- (b -> vy))/2;
            if (abs (b -> vy) <= 1)
                {
                (b -> vy) = 0;
                (b -> vx) = 0;
                }
        b -> y = SaveWindow_y2 - (b -> r) - 1;
        }

//----------------------------------------------------------------------------------
    //if (GetAsyncKeyState (VK_SPACE) && (b -> vy) >= 0) (b -> vy) -= 10;
    }


void DrawAllBalls (Ball_t b[], int size)
    {
    for (int i = 0; i < size; i++)
        DrawBall (b[i]);
    }

void RandomBalls (Ball_t b[])
    {
    int i = 0; int a = 1;
    while (i < N_BALLS)
        {
        b[i].r = rand ()%14 + 7;
        b[i].x = rand ()%TOP_X + b[i].r + 1;
        b[i].y = rand ()%TOP_Y + b[i].r + 1;
        b[i].vx = rand ()%5 - rand ()%5;
            if (b[i].vx == 0) b[i].vx = rand ()%5 - rand ()%5;
            if (b[i].vx == 0) b[i].vx = rand ()%5 - rand ()%5;
            if (b[i].vx == 0) b[i].vx = 1;
        b[i].vy = rand ()%4 - rand ()%4;
            if (b[i].vy == 0) b[i].vy = rand ()%5 - rand ()%5;
            if (b[i].vy == 0) b[i].vy = rand ()%5 - rand ()%5;
            if (b[i].vy == 0) b[i].vy = 1;
        b[i].color = RGB (rand ()%256, rand ()%256, rand ()%256);

        i++;
        }
    }
