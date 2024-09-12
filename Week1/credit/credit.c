#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool validate(long cardNumber);

int main(void)
{

    long num;

    //get card number
    do
    {
        num = get_long("enter number : ");
    }
    while (num < 0);

    //get the length of card number
    int length = (int) log10(num) + 1;



    // check and act if it validates sucessfully
    if (validate(num))
    {


        //if length is 13 and first digit is 4 then it is visa
        if (length == 13 && num / (long) pow(10, 12) == 4)
        {
            printf("VISA");
        }
        // if length is 15 and first two digits are 34 or 37, it is american express
        else if (length == 15)
        {
            int firstTwoDigit = num / (long) pow(10, 13);
            if (firstTwoDigit == 34 || firstTwoDigit == 37)
            {
                printf("AMEX");
            }
            // it length is 15 and first two digits are neither 34 nor 37, it it invalid
            else
            {
                printf("INVALID");
            }

        }
        // if length is 16 it may be visa or american express
        else if (length == 16)
        {
            int firstTwoDigit = num / (long) pow(10, 14);
            // if starts with 4 then it is visa
            if (num / (long) pow(10, 15) == 4)
            {
                printf("VISA");
            }
            // if starts with 51, 52,53, 54 or 55, it is American express
            else if (firstTwoDigit >= 51 && firstTwoDigit <= 55)
            {
                printf("MASTERCARD");
            }
            else
            {
                printf("INVALID");
            }

        }

        // if length doesnot match to any
        else
        {
            printf("INVALID");
        }
    }

    //if doesnot valid print INVALID
    else
    {
        printf("INVALID");
    }

    printf("\n");


}









bool validate(long cardNumber)
{
    int length = (int) log10(cardNumber) + 1;
    int sum = 0;

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    for (int i = length - 2; i >= 0; i = i - 2)
    {
        //every other digit by 2, starting with the number’s second-to-last digit
        int digit = (cardNumber / (long) pow(10, length - i - 1)) % 10;

        //add those products’ digits together.
        sum = sum + (digit * 2) % 10 + (digit * 2) / 10;
    }

    //Add the sum to the sum of the digits that weren’t multiplied by 2.
    for (int j = length - 1; j >= 0; j = j - 2)
    {
        // get the digits that weren't multiplied by 2.
        int digitS = (cardNumber / (long) pow(10, length - j - 1)) % 10;
        sum = sum + digitS;
    }

    //check if the last digit of sum in zero
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}