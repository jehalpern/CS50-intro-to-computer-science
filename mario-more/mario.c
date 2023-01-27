#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (1 > n || n > 8) ;
    for (int i = n; i > 0; i--)
    {
        for (int j = i - 2; j >=0; j--)
        {
            printf(" ");
        }
        for (int k = i - 1; k < n; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = i -1; l < n; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}