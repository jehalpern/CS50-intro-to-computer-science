#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letters(string t);
int words(string t);
int sentences(string t);
float l, w, s, a_l, a_s, index;
int a;

int main(void)
{
    //get text from user
    string t = get_string("Text: ");

    //calculate number of letters
    l = letters(t);

    //calculate number of words
    w = words(t);

    //calculate number of sentences
    s = sentences(t);

    //calculate average letters per 100 words
    a_l = (l / w) * 100;

    //calculate average sentences per 100 words
    a_s = 100 / (w / s);

    //plug averages into formula
    index = .0588 * a_l - .296 * a_s - 15.8;
    a = round(index);
    if (a >= 1 && a <= 16)
    {
        printf("Grade %i\n", a);
    }
    else if (a < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}


int letters(string t)
{
    int n = strlen(t);
    for (int i = 0; i < n; i++)
    {
        if ((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z'))
        {
            l = l + 1;
        }
    }
    return l;
}

int words(string t)
{
    int n = strlen(t);
    for (int i = 0; i < n; i++)
    {
        if (t[i] == 32)
        {
            w = w + 1;
        }
    }
    return w + 1;
}

int sentences(string t)
{
    int n = strlen(t);
    for (int i = 0; i < n; i++)
    {
        if (t[i] == 33 || t[i] == 46 || t[i] == 63)
        {
            s = s + 1;
        }
    }
    return s;
}