#include "..\DirectTX.cpp"

int main()
 {
 DirectTXCreateWindow (1366, 768);

 while (true)
     {
     DirectTXBegin();

     DirectTXSetFillColor (rand ());

     DirectTXDrawRectangle (0, 0, 1366, 768);



     DirectTXFlush();

     DirectTXEnd();
     }
 }
