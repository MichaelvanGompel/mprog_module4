/*********************************************************************************************
 * helpers.c
 *
 * Michael van Gompel - mprog1
 *
 * contains 3 functions for filtering images
 * - grayscale() converts a coloured image to black and white
 * - sepia(), brownish tone with an old feel
 * - reflect(), reflects the image horizontally
 *
**********************************************************************************************/
#include <math.h>
#include "helpers.h"

#define NUMCOL 3
#define MAX_SAT 255
// constants for converting to sepia red, green and blue
// red
#define RREDC .393
#define RGREENC .769
#define RBLUEC .189
// green
#define GREDC .349
#define GGREENC .686
#define GBLUEC .168
// blue
#define BREDC .272
#define BGREENC .534
#define BBLUEC .131

// functions
int avg_pix(int a, int b, int c);
int sepia_red(int og_red, int og_green, int og_blue);
int sepia_green(int og_red, int og_green, int og_blue);
int sepia_blue(int og_red, int og_green, int og_blue);

/* grayscale()
 * Convert image to grayscale by taking the average of the colours and applying this to all three
*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iteration over the rows of the bitmap image
    for (int i = 0; i < height; i++)
    {
        // iteration over the columns
        for (int j = 0; j < width; j++)
        {
            // generate average of colours in pixel[i][j]
            int avg = avg_pix(image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
            // transfer average out the colours
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

/* sepia()
* giving the image a brownish tone
* colour filtering values from https://prog1.mprog.nl/problems/cs50/filter/small
*/
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // iteration over the rows of the bitmap image
    for (int i = 0; i < height; i++)
    {
        // iteration over the columns
        for (int j = 0; j < width; j++)
        {
            // saving red, green and blue in temporary storage
            temp.rgbtRed = image[i][j].rgbtRed;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            // calculating sepia values
            image[i][j].rgbtRed = sepia_red(temp.rgbtRed, temp.rgbtGreen, temp.rgbtBlue);
            image[i][j].rgbtGreen = sepia_green(temp.rgbtRed, temp.rgbtGreen, temp.rgbtBlue);
            image[i][j].rgbtBlue = sepia_blue(temp.rgbtRed, temp.rgbtGreen, temp.rgbtBlue);
        }
    }
    return;
}

/* reflect()
 * Reflects image horizontally
*/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create RGBTRIPLE variable to facilitate swap
    RGBTRIPLE temp;
    // iteration only has to go over half the pixels in a row
    int halfwidth = width / 2;
    // iteration for the rows
    for (int i = 0; i < height; i++)
    {
        // iteration for the columns
        for (int j = 0; j < halfwidth; j++)
        {
            // swapping pixels
            temp = image[i][j];
            image[i][j] = image[i][width - 1  - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}


/* avg_pix()
 * Takes the average of the saturation values of three colours
*/
int avg_pix(int a, int b, int c)
{
    int temp_avg = round((a + b + c) / (float) NUMCOL);
    return temp_avg;
}

/* sepia_red()
 * calculates the value for sepia red
*/
int sepia_red(int og_red, int og_green, int og_blue)
{
    int sred = round(RREDC * og_red + RGREENC  * og_green + RBLUEC * og_blue);
    if (sred > MAX_SAT)
    {
        return 0xff;
    }
    return sred;
}

/* sepia_green()
 * calculates the value for sepia green
*/
int sepia_green(int og_red, int og_green, int og_blue)
{
    int sgreen = round(GREDC * og_red + GGREENC * og_green + GBLUEC * og_blue);
    if (sgreen > MAX_SAT)
    {
        return 0xff;
    }

    return sgreen;
}

/* sepia_blue()
 * calculates the value for sepia blue
*/
int sepia_blue(int og_red, int og_green, int og_blue)
{
    int sblue = round(BREDC * og_red + BGREENC * og_green + BBLUEC * og_blue);
    if (sblue > MAX_SAT)
    {
        return 0xff;
    }
    return sblue;
}
