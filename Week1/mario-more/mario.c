#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //get height from user
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height >= 9);


    //loop that runs for height
    for (int i = 0; i < height; i++)
    {
        //nested loop to print # in LHS where needed
        for (int j = height; j > 0; j--)
        {
            if (j <= i + 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        //provide double space in between two sides
        printf("  ");

        //nested loop to print # in RHS where needed
        for (int k = 0; k < height; k++)
        {
            if (k <= i)
            {
                printf("#");
            }
            else
            {
                //break loop to reduce space at the end of pyramid
                break;
            }

        }

        //create newline
        printf("\n");


    }

}