#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool valid_trianlge(int a, int b, int c);



int valid_triangle(int a, int b, int c)
{
    int result;
    if (a + b > c)
    {
        if (b + c > a)
        {
            if (a + c > b)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

int main(void)
{
    int d = get_int("Length of side a: ");
    int e = get_int("Length of side b: ");
    int f = get_int("Lenth of side c: ");
    int result = valid_triangle(d, e, f);
    printf("%i\n", result );

}