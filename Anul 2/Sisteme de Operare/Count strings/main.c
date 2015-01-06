#include <stdio.h>
#include <stdlib.h>

void sort(char *string, char *message)
{
    int counter = 0;
    int i = 0;
    for(i = 0; i < strlen(message) - strlen(string) + 1; i++)
    {
        int j = 0;
        int ok = 1;
        for(j = 0; j < strlen(string); j++)
        {
            if(message[i+j] != string[j])
            {
                ok = 0;
                break;
            }
        }
        if(ok)
        {
            counter++;
        }
    }
    return counter;
}

void read_ints(char *file_name)
{
    FILE *myFile;
    myFile = fopen(file_name, "r");

    //read file into array
    int numberArray[16];
    int i;

    for (i = 0; i < 16; i++)
    {
        fscanf(myFile, "%d", &numberArray[i]);
    }

    for (i = 0; i < 16; i++)
    {
        printf("Number is: %d\n\n", numberArray[i]);
    }
}

int count_strings(char *string, char *message)
{
    int counter = 0;
    int i = 0;
    for(i = 0; i < strlen(message) - strlen(string) + 1; i++)
    {
        int j = 0;
        int ok = 1;
        for(j = 0; j < strlen(string); j++)
        {
            if(message[i+j] != string[j])
            {
                ok = 0;
                break;
            }
        }
        if(ok)
        {
            counter++;
        }
    }
    return counter;
}

int mains()
{
    printf("Hello world!\n");
    char *string = "abc";
    char *message = "abc abc bac abc sss abc";
    printf("%d", count_strings(string, message));
    return 0;
}
