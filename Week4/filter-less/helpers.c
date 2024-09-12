#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgVal = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            int newVal = round(avgVal);
            image[i][j].rgbtBlue = newVal;
            image[i][j].rgbtGreen = newVal;
            image[i][j].rgbtRed = newVal;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            double sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            double sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            image[i][j].rgbtRed = round(sepiaRed) > 255 ? 255 : round(sepiaRed);
            image[i][j].rgbtBlue = round(sepiaBlue) > 255 ? 255 : round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen) > 255 ? 255 : round(sepiaGreen);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tRed, tGreen, tBlue;

            tRed = image[i][j].rgbtRed;
            tGreen = image[i][j].rgbtGreen;
            tBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tRed;
            image[i][width - j - 1].rgbtGreen = tGreen;
            image[i][width - j - 1].rgbtBlue = tBlue;


        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE cImage[height][width])
{

    RGBTRIPLE image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = cImage[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double avgRed, avgGreen, avgBlue;
            if (i == 0)
            {
                if (j == 0) //top left corner
                {
                    avgRed = (double)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                      image[i + 1][j + 1].rgbtRed) / 4;
                    avgGreen = (double)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                        image[i + 1][j + 1].rgbtGreen) / 4;
                    avgBlue = (double)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j + 1].rgbtBlue) / 4;
                }
                else if (j == width - 1) // top right corner
                {
                    avgRed = (double)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                      image[i + 1][j - 1].rgbtRed) / 4;
                    avgGreen = (double)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                        image[i + 1][j - 1].rgbtGreen) / 4;
                    avgBlue = (double)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j - 1].rgbtBlue) / 4;
                }
                else //top edge
                {
                    avgRed = (double)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                      image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                    avgGreen = (double)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                        image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                    avgBlue = (double)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
                }
            }
            else if (i == height - 1)
            {
                if (j == 0) //button left corner
                {
                    avgRed = (double)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                      image[i - 1][j + 1].rgbtRed) / 4;
                    avgGreen = (double)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                        image[i - 1][j + 1].rgbtGreen) / 4;
                    avgBlue = (double)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue) / 4;
                }
                else if (j == width - 1) //buttom right corner
                {
                    avgRed = (double)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                      image[i - 1][j - 1].rgbtRed) / 4;
                    avgGreen = (double)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                        image[i - 1][j - 1].rgbtGreen) / 4;
                    avgBlue = (double)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue) / 4;
                }
                else // buttom edge
                {
                    avgRed = (double)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                      image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6;
                    avgGreen = (double)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                        image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6;
                    avgBlue = (double)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6;
                }
            }
            else if (j == 0) //left edge
            {
                avgRed = (double)(image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                  image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                avgGreen = (double)(image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                    image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                avgBlue = (double)(image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                   image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
            }
            else if (j == width - 1) //right edge
            {
                avgRed = (double)(image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed +
                                  image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;
                avgGreen = (double)(image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                    image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;
                avgBlue = (double)(image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                   image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;
            }
            else //middle pixels
            {
                avgRed = (double)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                  image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                  image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9;

                avgGreen = (double)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                    image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9;

                avgBlue = (double)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                   image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                   image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9;
            }

            cImage[i][j].rgbtRed = round(avgRed);
            cImage[i][j].rgbtGreen = round(avgGreen);
            cImage[i][j].rgbtBlue = round(avgBlue);

        }
    }
    return;
}
