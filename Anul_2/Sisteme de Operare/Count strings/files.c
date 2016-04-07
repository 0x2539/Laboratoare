#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void solve(int nrOfFiles, char *files[])
{
    int f = creat(files[nrOfFiles - 1], S_IWRITE);
    char buffer[1024];
    int i;
    close(f);

    f = open(files[nrOfFiles - 1], O_RDWR);

    for(i = 1; i < nrOfFiles - 1; i++)
    {
        if(files[i] != '+')
        {
            int auxF=open(files[i],O_RDONLY);

            int j;
            for(j = 0; j < 1024; j++)
            {
                buffer[j] = '\0';
            }

            while(read(auxF, buffer, 1024) > 0)
            {
                printf("%s %d %s\n", buffer, i, files[i]);
                write(f, buffer, strlen(buffer));
            }

            close(auxF);
        }
    }
    //write(f, "yellow", 1024);
    close(f);
}

int mainssss()
{
    char *files[] = {"nume", "f1.txt", '+', "f2.txt", "f3.txt"};
    solve(5, files);
    return 0;
}
