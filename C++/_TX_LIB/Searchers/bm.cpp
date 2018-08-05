//! With Russian language

#include <stdio.h>
#include <windows.h>

#define TEXT_ "A whaler is a specialized ship, designed for whaling, the catching and/or processing of whales. The former \
included the whale catcher, a steam or diesel-driven vessel with a harpoon gun mounted at its bows. The latter included \
such vessels as the sail or steam-driven whaleship of the 16th to ÿçü early 20th century and the floating factory or factory"

char* bm (int l1, char* text, char* phr);

int main ()
{
SetConsoleOutputCP (1251);

char *phr = "o ÿçü early 20t", *text = TEXT_;
int l1 = strlen (text);

char* status = bm (l1, text, phr);

if (status) for (int i = 0; phr [i]; i++) printf ("%c",  phr [i]);
else printf ("\n ***ERROR :: NOT FIND");
}

char* bm (int l1, char* text, char* phr)
{
int TABL_ARR [256] = {};
int l2 = 0;

for (int i = 0; phr [i]; i++)
    {
    l2++;
    TABL_ARR [ (unsigned char) phr [i]] =  i;
    }

if (l1 < l2) return NULL;

for (int i = l2; i <= l1; )
        for (int count = l2 - 1; count >= 0; count--)
            {
            if (text [i -l2 + count] != phr [count])
                {
                i += l2 - TABL_ARR [ (unsigned char) phr [count]];
                //printf ("%d", l2 - TABL_ARR [ (unsigned char) phr [count]]);
                break;
                }
            if (!count) return text + i - l2;
            }

return NULL;
}

