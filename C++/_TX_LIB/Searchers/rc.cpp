#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT "A whaler is a specialized ship, designed for whaling, the catching and/or processing of whales \
he former included the whale catcher, a steam or diesel-driven vessel with a harpoon gun mounted at its bows. \
The latter included such vessels as the sail or steam-driven whaleship of the 16th to early 20th century and the \
floating factory or factory ship of the modern era. There were also vessels that combined the two, such as Bottlenose \
whalers of the late 19th and early 20th century and catcher/factory ships of the modern era."

int hash (char* text, int lenf);
char* search (char* text, char* phrase);

int main ()
{
char* phrase = "f the modern", *text = TEXT;

char* status = search (text, phrase);

if (!status) printf ("ERROR :: NOT FIND");
else for (int i = 0, lenf = strlen (phrase); i < lenf; i++) printf ("%c", status [i]);
}

int hash_ (char* text, int lenf)
{
int hash = 0;
for (int i = 0; i < lenf; i++) hash += text [i];
return hash;
}

char* search (char* text, char* phrase)
{
int lent = strlen (text), lenf = strlen (phrase);

if (lent < lenf) return NULL;

for (int i = 0, hash = 0; i < lent; i++, hash = 0)
    {
    for (int count = 0; count < lenf; count++)
        hash += phrase [count];

    if (hash != hash_ (text + i, lenf)) continue;

    for (int count = 0; count < lenf; count++)
        {
        if (phrase [count] != text [i +  count]) break;
        if (count == lenf - 1) return text + i;
        }
    }

return NULL;
}
