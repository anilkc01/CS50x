#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Please provide one argument with image name\n");
        return 1;
    }


    FILE *in = fopen(argv[1], "r");
    FILE *out = NULL;

    BYTE buff[512];
    int counter = 0;
    char fname[12];

    if (NULL == in)
    {
        printf("This File could not be opened\n");
        return 1;
    }

    while (fread(&buff, 512, 1, in) == 1)
    {

        if ((buff[0] == 0xff) && (buff[1] == 0xd8) && (buff[2] == 0xff) && (buff[3] >= 0xe0) && (buff[3] <= 0xef))
        {

            // Close the previous file if it's open
            if (out != NULL)
            {
                fclose(out);
            }

            sprintf(fname, "%03i.jpg", counter);
            out = fopen(fname, "w");
            counter++;

            fwrite(buff, 512, 1, out);
        }
        else if (out != NULL)
        {
            fwrite(buff, 512, 1, out);
        }

    }
    if (out != NULL)
    {
        fclose(out);
    }

    fclose(in);
}
