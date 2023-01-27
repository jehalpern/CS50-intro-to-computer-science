#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int hex_size = sizeof(uint8_t);
char filename[10];
uint8_t buffer;
bool file[51];



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
    uint8_t *ptr = (uint8_t *) malloc(512 * sizeof(hex_size));

    //read 512 bytes to ptr at a time until end of file
    while (fread(ptr, 1, 512, data) == 512)
    {
        //if the 512 byte block starts with a jpg header
        if (ptr[0] == 0xff && ptr[1] == 0xd8 && ptr[2] == 0xff && (ptr[3] & 0xf0) == 0xe0)
        {
            //if first jpg in file -> write the 512 bytes to new file called 000.jpg
            if (file[0] == 0)
            {
                n = n + 1;
                sprintf(filename, "%03i.jpg", n);
                img = fopen(filename, "a");
                file[0] = 1;
                fwrite(ptr, 1, 512, img);
            }
            //if new jpg -> write 512 bytes to new file
            else
            {
                fclose(img);
                n = n + 1;
                sprintf(filename, "%03i.jpg", n);
                img = fopen(filename, "a");
                fwrite(ptr, 1, 512, img);
            }
        }
        //continue writing the next 512 bytes of the jpg
        else
        {
            if (file[0] == 1)
            {
                fwrite(ptr, 1, 512, img);
            }

        }
    }
    free(ptr);
    fclose(data);
    fclose(img);
}









