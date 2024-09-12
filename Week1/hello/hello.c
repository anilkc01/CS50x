#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //take Name input from user
    string name = get_string("What is you name? ");

    //print Name along with Hello World
    printf("Hello World %s\n", name);
}