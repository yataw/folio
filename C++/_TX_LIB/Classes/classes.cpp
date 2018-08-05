#include <stdio.h>
#include <TXlib.h>

struct Color_t
{
int r, g, b;
};

struct ball_t
{
double x, y, vx, vy, r;
struct {int r, g, b;} color;
};

const int N_BALLS = 50;

Color_t  ARR_COLORS [] = { {255, 0, 0}, {0, 255, 0}, {88, 231, 18}, {18, 231, 203}, {17, 108, 232},
        {238, 29, 240}, {133, 127, 127}, {255, 255, 1}};

void start_param_all     (ball_t* arr, int color);
void start_param         (ball_t* arr, int color);
void engine_all          (ball_t* arr);
void engine              (ball_t* arr);
void draw_all            (ball_t* arr);
void draw                (ball_t* arr);
void play                (void* arr);

int main ()
{
txBegin ();
txCreateWindow (1366, 768);

ball_t arr1 [N_BALLS];
ball_t arr2 [N_BALLS];
//_beginthread
start_param_all (arr1, 0);
start_param_all (arr2, 1);

//_beginthread (play, 0, (void*) arr1);
//_beginthread (play, 0, (void*) arr2);

play (arr1);

getch ();

txEnd ();

return 0;
}

void start_param_all (ball_t* arr, int color)
{
for (int i = 0; i < N_BALLS; i++)
    start_param (arr + i, color);
}

void start_param (ball_t* arr, int color)
{
//int temp = rand () % 8;

arr -> x = rand ()%1300 + 30;
arr -> y = rand ()%700 + 30;
arr -> color.r = ARR_COLORS [color].r;
arr -> color.g = ARR_COLORS [color].g;
arr -> color.b = ARR_COLORS [color].b;
arr -> vx = rand ()%5 + 1;
arr -> vy = rand ()%5 + 1;
arr -> r = 6;

}

void engine_all (ball_t* arr)
{
int temp;

for (int i = 0; i < N_BALLS; i++)
    engine (arr + i);

if (!(rand () % 200))
    {
    temp = rand () % 8;
    arr [N_BALLS - 1].color.r = ARR_COLORS [temp].r;
    arr [N_BALLS - 1].color.g = ARR_COLORS [temp].g;
    arr [N_BALLS - 1].color.b = ARR_COLORS [temp].b;
    }
}

void engine (ball_t* arr)
{
    (arr -> x > arr -> r + abs (arr -> vx)) && (arr -> x < 1366 - arr ->  r - abs (arr -> vx)) ?
        arr -> x += arr -> vx: (arr -> vx *= -1, arr -> x += arr -> vx);


    (arr -> y > arr -> r + abs (arr -> vy)) && (arr -> y < 766 - arr ->  r - abs (arr -> vy)) ?
        arr -> y += arr -> vy: (arr -> vy *= -1, arr -> y += arr -> vy);

}

void draw_all (ball_t* arr)
{
for (int i = 0; i < N_BALLS; i++)
    draw (arr + i);
}

void draw (ball_t* arr)
{
double temp_inc = 2.0, temp_dinc = 5;
int i = 0, temp1, temp2, temp3;

temp1 = arr -> color.r;
temp2 = arr -> color.g;
temp3 = arr -> color.b;

for (; i < 5; i++, temp_inc += 1.0, temp_dinc -= 1.0)
    {
    txSetColor (RGB (temp1 + (255 - temp1) /temp_inc,
                          temp2 + (255 - temp2) /temp_inc, temp3 + (255 - temp3) /temp_inc));

    if (i > 1) txSetColor (RGB (255 /temp_inc *3, 255 /temp_inc *3, 255 /temp_inc *3));

     txSetFillColor (RGB (temp1 + (255 - temp1) /temp_inc,
                          temp2 + (255 - temp2) /temp_inc, temp3 + (255 - temp3) /temp_inc));

    txCircle (arr -> x - temp_dinc* arr -> vx , arr -> y - temp_dinc* arr -> vy , arr -> r);
    }


txSetColor (0);
txSetFillColor (RGB (temp1, temp2, temp3));
txCircle (arr -> x, arr -> y, arr -> r);
}

void play (void* arr)
{

while (!GetAsyncKeyState (VK_RETURN))
    {
    txSetFillColor (0xffffff);
    if (!GetAsyncKeyState (VK_CONTROL)) txClear ();

    //txCircle (100,

    engine_all ((ball_t*) arr);
    draw_all ((ball_t*) arr);
    GetAsyncKeyState (VK_SHIFT) ? Sleep (40): Sleep (21);
    }
}
