#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void find_divs(int nr)
{
    int i;
    for(i = 2; nr != 1; i++)
    {
        int nrOfDivs = 0;
        while(nr % i == 0)
        {
            nr/=i;
            nrOfDivs++;
        }
        if(nrOfDivs)
        {
            printf("%d ^ %d\n", i, nrOfDivs);
        }
    }
}

int main()//int argc, char *argv[])
{
    find_divs(12);
    //count_strings(string, "file.txt");
    return 0;
}
