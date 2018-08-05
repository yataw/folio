//1)Ќе учтена ф-и€ плавного торможени€ (из-за if !getasync... && ....v=0)
#include "TXLib.h"

enum {HERO_U = 0, HERO_UR = 1, HERO_R = 2, HERO_DR = 3, HERO_D = 4,
      HERO_DL = 5, HERO_L = 6, HERO_UL = 7}

enum {BckGPicture = 0}

//--------------------------------STRUCTURES----------------------------------------
struct Hero
    {
    int x, y, vx, vy;
    HDC hero[8];
    };

struct Background
    {
    HDC BckGPicture;
    };
//---------------------------------VOIDS--------------------------------------------
void DrawHeroAndBackGround ();
void EngineHero (Hero* MainHero, Background* BckG);
//----------------------------------------------------------------------------------


//---------------------------------MAIN---------------------------------------------
int main()
    {
    txBegin ();
    txCreateWindow (1280, 719);
    DrawHeroAndBackGround ();
    txEnd ();

    return 0;
    }
//----------------------------------------------------------------------------------


void DrawHeroAndBackGround ()
    {

    Hero H =  {0, 0, 0, 0, { txLoadImage ("HeroU.bmp"),
                             txLoadImage ("HeroUR.bmp"),
                             txLoadImage ("HeroR.bmp"),
                             txLoadImage ("HeroDR.bmp"),
                             txLoadImage ("HeroD.bmp"),
                             txLoadImage ("HeroDL.bmp"),
                             txLoadImage ("HeroL.bmp"),
                             txLoadImage ("HeroUL.bmp") }};

    Background BckG = {txLoadImage ("Background.bmp")};
/*
    x = 25;

    mov x, 25

    B8F9AE19
    --\__/
        x

int x;
x = 25;

x
&x

mov bx, offset x
mov ax, [bx]
mov y, ax

x dw 0


    10111000 11111001 10101110 00011001 */
    while (!GetAsyncKeyState (VK_RETURN))
        {
        EngineHero (&H, &BckG);

        txSetFillColor (TX_BLACK);
        txCircle (640, 360, 55);
        txSetFillColor (TX_WHITE);

        txSleep (20);

        }

//-------------------------------------------HDC_Delete----------------------------------------------
    int n = 0;
    while (n < 8)
        {
        txDeleteDC (H.hero[n]);
        n++;
        }


    txDeleteDC (BckG.BckGPicture);
//---------------------------------------------------------------------------------------------------
    }

void EngineHero (Hero* H, Background* BckG)
    {
    int vx1 = 6, vy1 = 6;
    int StopSimpleAction = 1;



    (*H).x += (*H).vx;
    H -> y += H -> vy;


    if (GetAsyncKeyState (VK_UP) && GetAsyncKeyState (VK_RIGHT))
        {
        StopSimpleAction = -1;
        H -> vx = vx1;
        H -> vy = -vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 71, 71, H -> hero[HERO_UR], 0, 0);
        }

    if (GetAsyncKeyState (VK_DOWN) && GetAsyncKeyState (VK_RIGHT))
        {
        StopSimpleAction = -1;
        H -> vx = vx1;
        H -> vy = vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 71, 71, H -> hero[HeroDR], 0, 0);
        }

    if (GetAsyncKeyState (VK_DOWN) && GetAsyncKeyState (VK_LEFT))
        {
        StopSimpleAction = -1;
        H -> vx = -vx1;
        H -> vy = vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 71, 71, H -> hero[HeroDL], 0, 0);
        }

    if (GetAsyncKeyState (VK_UP) && GetAsyncKeyState (VK_LEFT))
        {
        StopSimpleAction = -1;
        H -> vx = -vx1;
        H -> vy = -vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 71, 71, H -> hero[HeroU], 0, 0);
        }
//--------------------------------------------------------------------------------------------------

    if (GetAsyncKeyState (VK_UP) && StopSimpleAction == 1)
        {
        H -> vy = -vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 50, 50, H -> hero[HeroU], 0, 0);
        }

    if (GetAsyncKeyState (VK_DOWN) && StopSimpleAction == 1)
        {
        H -> vy = vy1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 50, 50, H -> hero[HeroD], 0, 0);
        }

    if (!GetAsyncKeyState (VK_UP) && !GetAsyncKeyState (VK_DOWN))
        {
        H -> vy = 0;
        }

    if (GetAsyncKeyState (VK_RIGHT) && StopSimpleAction == 1)
        {
        H -> vx = vx1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 50, 50, H -> hero[HeroR], 0, 0);
        }

    if (GetAsyncKeyState (VK_LEFT) && StopSimpleAction == 1)
        {
        H -> vx = -vx1;
        txBitBlt (txDC (), 0, 0, 1280, 719, BckG -> BckGPicture, 0, 0);
        txAlphaBlend (txDC(), H -> x, H -> y, 50, 50, H -> hero[HeroL], 0, 0);
        }

    if (!GetAsyncKeyState (VK_RIGHT) && !GetAsyncKeyState (VK_LEFT))
        {
        H -> vx = 0;
        }

    StopSimpleAction = 1;
    }

