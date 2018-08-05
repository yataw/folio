#include <stdio.h>
#include "txlib.h"
#define phrase "Hello, this is an universal determinant a symbol in ASCII"
#define i "  "/*indentation*/
main ()
{
char symb;
printf ("%s%s\n%sEnter a symbol\n", i, phrase, i);
for (;!GetAsyncKeyState (VK_ESCAPE);)
{
if ((symb = getchar ()) != '\n')

//while (GetAsyncKeyState (VK_RETURN)); // Здесь не обязательно. Почему? (в exe обязат)
printf ("%sname \"%c\", 8-numer = %o, 10-numer = %d, occupies memory = %d;\n",
         i, symb, symb, symb, sizeof symb);
}
}
