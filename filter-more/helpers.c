#include "helpers.h"
#include "stdio.h"
#include "math.h"

int ecalc(int g_x, int g_y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //create buffer arrays to hold new averaged grey values
    uint8_t grey_red[height][width];
    uint8_t grey_green[height][width];
    uint8_t grey_blue[height][width];

    //calculate averages for rgb and populate to buffer array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((double)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            grey_red[i][j] = average;
            grey_green[i][j] = average;
            grey_blue[i][j] = average;
        }
    }

    //populate new grey values from buffer to image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = grey_red[i][j];
            image[i][j].rgbtGreen = grey_green[i][j];
            image[i][j].rgbtBlue = grey_blue[i][j];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create buffer arrays to hold new reflected values
    uint8_t red_buff[height][width];
    uint8_t green_buff[height][width];
    uint8_t blue_buff[height][width];

    //append new reflected values to buffer arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_buff[i][j] = image[i][(width - 1) - j].rgbtRed;
            green_buff[i][j] = image[i][(width - 1) - j].rgbtGreen;
            blue_buff[i][j] = image[i][(width - 1) - j].rgbtBlue;
        }
    }
    //move new values from buffer to image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = red_buff[i][j];
            image[i][j].rgbtGreen = green_buff[i][j];
            image[i][j].rgbtBlue = blue_buff[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //buffer for updated blur values
    uint8_t blur_red[height][width];
    uint8_t blur_green[height][width];
    uint8_t blur_blue[height][width];

    int8_t neighbor[] = {-1, 0, 1};

    int red_t, green_t, blue_t, div;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //reset number variables for new pixel
            red_t = green_t = blue_t = div = 0;

            //iter through neighboring pixels to calculate new averages
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    //if middle pixel
                    if (i != 0 && j != 0 && i != (height - 1) && j != (width - 1))
                    {
                        red_t = red_t + image[i + neighbor[x]][j + neighbor[y]].rgbtRed;
                        green_t = green_t + image[i + neighbor[x]][j + neighbor[y]].rgbtGreen;
                        blue_t = blue_t + image[i + neighbor[x]][j + neighbor[y]].rgbtBlue;
                        div = div + 1;
                    }
                    //if corner or edge
                    else
                    {
                        int i_check = i + neighbor[x];
                        int j_check = j + neighbor[y];
                        //only average valid pixels
                        if (i_check >= 0 && i_check < width && j_check >= 0 && j_check < height)
                        {
                            red_t = red_t + image[i + neighbor[x]][j + neighbor[y]].rgbtRed;
                            green_t = green_t + image[i + neighbor[x]][j + neighbor[y]].rgbtGreen;
                            blue_t = blue_t + image[i + neighbor[x]][j + neighbor[y]].rgbtBlue;
                            div = div + 1;
                        }
                    }
                }
            }
            //calculate new average for pixel[i][j], apend to buffer array
            blur_red[i][j] = round((double)red_t / div);
            blur_green[i][j] = round((double)green_t / div);
            blur_blue[i][j] = round((double)blue_t / div);

        }
    }


    //move new values from buffer to image[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_red[i][j];
            image[i][j].rgbtGreen = blur_green[i][j];
            image[i][j].rgbtBlue = blur_blue[i][j];
        }
    }


    return;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //buffer for updated edge values
    uint8_t e_red[height][width];
    uint8_t e_green[height][width];
    uint8_t e_blue[height][width];

    int8_t neighbor[] = {-1, 0, 1};
    int8_t gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int8_t gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int red_x, red_y, green_x, green_y, blue_x, blue_y;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //reset number variables for new pixel
            red_x = green_x = blue_x = red_y = green_y = blue_y = 0;

            //iter through neighboring pixels to calculate new averages
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    //if middle pixel
                    if (i != 0 && j != 0 && i != (height - 1) && j != (width - 1))
                    {
                        //calculate Gx
                        red_x = red_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtRed);
                        green_x = green_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtGreen);
                        blue_x = blue_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtBlue);

                        //calculate Gy
                        red_y = red_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtRed);
                        green_y = green_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtGreen);
                        blue_y = blue_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtBlue);

                    }

                    //if corner or edge
                    else
                    {
                        int i_check = i + neighbor[x];
                        int j_check = j + neighbor[y];
                        //only average valid pixels
                        if (i_check >= 0 && i_check < width && j_check >= 0 && j_check < height)
                        {
                            //calculate Gx
                            red_x = red_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtRed);
                            green_x = green_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtGreen);
                            blue_x = blue_x + (gx[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtBlue);

                            //calculate Gy
                            red_y = red_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtRed);
                            green_y = green_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtGreen);
                            blue_y = blue_y + (gy[x][y] * image[i + neighbor[x]][j + neighbor[y]].rgbtBlue);
                        }
                    }

                }
            }
            //calculate new value for pixel[i][j], apend to buffer array
            e_red[i][j] = ecalc(red_x, red_y);
            e_green[i][j] = ecalc(green_x, green_y);
            e_blue[i][j] = ecalc(blue_x, blue_y);

        }
    }


    //move new values from buffer to image[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = e_red[i][j];
            image[i][j].rgbtGreen = e_green[i][j];
            image[i][j].rgbtBlue = e_blue[i][j];
        }
    }



}

int ecalc(int g_x, int g_y)
{
    int total, rough, final;
    total = rough = final = 0;
    total = ((g_x * g_x) + (g_y * g_y));
    rough = round(sqrt((double)total));
    if (rough > 255)
    {
        final = 255;
    }
    else
    {
        final = rough;
    }

    return final;
}
