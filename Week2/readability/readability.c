#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int no_of_letters(string text);
int no_of_words(string text);
int no_of_sentences(string text);

int main(void)
{
    string textin = get_string("Text : ");

    //get number of letters
    int letters = no_of_letters(textin);

    //get number of words
    int words = no_of_words(textin);

    //get number of sentences
    int sentences = no_of_sentences(textin);

    //calculate index
    int index = 0.0588 * (((double)letters / words) * 100) - 0.296 * (((double)sentences / words) * 100) - 15.8 + 0.5 ;

    int first = (double)1.2;
    printf("1.2 -> %i ", first);

    int second = (double)1.999;
    printf("1.9 -> %i ", second);

    if (index >= 17)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }


}

//function that takes string and returns number of letters in it
int no_of_letters(string text)
{
    int number = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90)
        {
            number++;
        }
    }

    return number;
}

//function that takes string and returns number of words in it
int no_of_words(string text)
{
    int number = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            number++;
        }
    }

    return number;
}

//function that takes string and returns number of sentences in it
int no_of_sentences(string text)
{
    int number = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            number++;
        }
    }

    return number;
}