#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long n;
    long o;
    long p;
    int c;
    int q;
    int r;
    int s;
    int t;
    {
        n = get_long("Number: ");
        o = n;
        c = 0;
    }

    while (o > 10)
//calculate everyother digit x2 starting from 2nd to last
    {
        p = o % 10;
        o = (o - p)/10;
        p = o % 10;
        q = (p * 2);
        if (q > 9)
        {
            r = q % 10;
            s = (q - r)/10;
            c = c + r + s;
        }
        else
        {
            c = c + (p * 2);
        }
        p = o % 10;
        o = (o - p)/10;
        p = o % 10;
    }
    o = n;
    while (o > 1)
//calculate the sum of remaining digits
    {
        p = o % 10;
        c = c + p;
        o = (o - p)/10;
        p = o % 10;
        o = (o - p)/10;
    }
//check if ends in 0
    t = c % 10;
    if (t != 0)
    {
        printf("INVALID\n");
    }
    else
    {
// check for 13 digit VISA
        o = n % 1000000000000;
        p = (n - o)/1000000000000;
        if (p < 10){
            if (p == 4){
            printf("VISA\n");
            }
            else{
                printf("INVALID\n");
            }
        }
//check for 15 digit AMEX
        else if (p > 9 && p < 999){
            o = p % 10;
            p = (p - o) / 10;
            if (p == 34 || p == 37){
                printf("AMEX\n");
                }
            else{
                printf("INVALID\n");
            }
        }
 //check if 16 digit then check if Mastercard, Visa, or Invalid
            else if (p > 999){
                o = p % 100;
                p = (p - o) / 100;
                if (p == 51 || p == 52 || p == 53 || p == 54 || p == 55){
                    printf("MASTERCARD\n");
                }
                else if (p > 9){
                    o = p % 10;
                    p = (p - o) / 10;
                    if (p == 4){
                        printf("VISA\n");
                }
                    else{
                    printf("INVALID\n");
                }
                }

            }

            }

            }