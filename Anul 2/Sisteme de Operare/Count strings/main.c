#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int check_strings(char *string, char *message)
{
//    printf("%s %s\n", string, message);
    int i;
    //for(i = strlen(message) - 1; i >= strlen(message) - strlen(string); i--)
    for(i = 0; i < strlen(string); i++)
    {
        if(string[i] != message[i])
        {
            return 0;
        }
    }
    return 1;
}

int count_strings(char *string, char *file)
{
    int counter = 0;
    int i = 0;

    char buf[strlen(string) + 1];
    char secondBuf[1];
    for(i = 0; i < strlen(string) + 1; i++)
    {
        buf[i] = '\0';
    }
    secondBuf[0] = '\0';

    int d=open(file,O_RDONLY);
    int reading = read(d,buf, strlen(string));

    while(reading > 0)
    {
        counter += check_strings(string, buf);
        reading = read(d, secondBuf, 1);

        if(reading > 0)
        {
            for(i = 0; i < strlen(string) - 1; i++)
            {
                buf[i] = buf[i+1];
            }
            buf[strlen(string) - 1] = secondBuf[0];
        }
    }

    close(d);

    return counter;
}

int mains()
{
    char *string = "lin";
    char *message = "f1.txt";
    printf("%d", count_strings(string, message));
    //count_strings(string, "file.txt");
    return 0;
}
