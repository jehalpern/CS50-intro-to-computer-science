#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int hex_size = sizeof(uint8_t);
char filename[9];
uint8_t buffer;
bool file[100];



int main(int argc, char *argv[])
{
    //check for number of command line arguments
    if (argc != 2)
    {
        printf("Please enter 1 argument\n");
        return 1;
    }
    //check that the file isn't empty
    FILE *data = fopen(argv[1], "r");
    if (data == NULL)
    {
        printf("Sorry could not open file\n");
        return 1;
    }

    FILE *img;
    int n = - 1;
    uint8_t* ptr = (uint8_t*) malloc(512 * sizeof(hex_size));

    //loop through file
    while(fread(ptr, 1, 512, data) == 512)
    {
        if (ptr[0] == 0xff && ptr[1] == 0xd8 && ptr[2] == 0xff && (ptr[3] & 0xf0) == 0xe0)
        {
            n = n + 1;
        }
    }
    printf("%i\n", n);
    free(ptr);
}









