//{===========================================================================
//           Библиотека DirectTX - Demo/Smooth.cpp
//           Copyright (C) Nikita Uvarov, 7 класс
//}===========================================================================

/**\file     Demo/Smooth.cpp
 *
 * \brief    Пример для DirectTX - Smoothing Demo
 *
 * \version  [v 0.2]
 *
 * \author   Copyright (C) Nikita Uvarov, 7 класс
 * \date     2009
 */

#include "..\DirectTX.cpp"

const int SizeX = 1000,
          SizeY = 768;

unsigned char Screen [SizeX] [SizeY] [3] = {};
unsigned char Buffer [SizeX] [SizeY] [3] = {};

void Smooth()
    {
    for (int y = 1; y < SizeY; y++)
    for (int x = 1; x < SizeX; x++)
        Buffer [x] [y] [1] = (Screen [x-1] [y  ] [1] +
                              Screen [x+1] [y  ] [1] +
                              Screen [x  ] [y-1] [1] +
                              Screen [x  ] [y+1] [1] +
                              Screen [x-1] [y-1] [1] +
                              Screen [x+1] [y-1] [1] +
                              Screen [x-1] [y+1] [1] +
                              Screen [x+1] [y+1] [1]) / 8;

    for (int y = 1; y < SizeY; y++)
    for (int x = 1; x < SizeX; x++)
        Screen [x] [y] [1] = Buffer [x] [y] [1];
    }

int main()
    {
    srand (time (0));

    DirectTXCreateWindow (SizeX, SizeY, "*PIMKIN & KORNEY are COPY-PASTERS!*  [Esc] to exit");

    for (int y = 1; y < SizeY; y++)
    for (int x = 1; x < SizeX; x++)
        Screen [x] [y] [1] = rand() % 255;

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        for (int y = 1; y < SizeY; y++)
        for (int x = 1; x < SizeX; x++)
            Screen [x] [y] [1] = rand() % 255;

        DirectTXBegin();
        Smooth();

        for (int y = 1, temp = rand (); y < SizeY; y++)
        for (int x = 1; x < SizeX; x++)
            DirectTXPutPixel (x, y, temp, temp, temp);

        DirectTXFlush();
        DirectTXEnd();
        }
    }
