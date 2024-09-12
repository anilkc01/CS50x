#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //check if all 3 values of pixe are 3
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                image[i][j].rgbtBlue = 0x00;  //change blue value to zer0
                image[i][j].rgbtGreen = 0x00;  // change green value to complete zer0
                image[i][j].rgbtRed = 0xFF;    // change red value to maximum (i.e FF in Hexadecimal)
            }
        }
    }
}
