#include <txlib.h>

char arr [] = {'?', '!', '"', '(', ')', '/', '\\', '.', ',', ':', ';', '-', 184};
int s_arr = sizeof (arr);

int symb ()
{
switch (rand () %10)
    {
    case 0: return ' ';
    case 1:
    case 2:
    case 3: return arr [rand () %s_arr];
    default: return 224 + rand () %32;
    }
}

int main ()
{
char text [] = {"stamina_text .txt"};

for (int i = 0; i < 10; i++)
    {
    text [sizeof (text) - 1 - 5] = i + '0';

    FILE* f = fopen (text ,"w");
    for (int i = 0, temp; i < 1e3; i++)
        fprintf (f, "%c", temp = symb (), temp);

    fclose (f);
    }
}
