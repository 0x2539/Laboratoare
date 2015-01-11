#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void read_file()
{
     int d1,d2,d3;
     char buf[10];

     d1=open("f1.txt",O_RDONLY);
     d2=open("f1.txt",O_RDWR);
     d3=dup(d2);

     read(d2,buf, 2); buf[3]='\0'; printf("%s\n",buf);
     char *haa = '\0';
     write(d2, ' ', 2);
     read(d1,buf, 4); buf[4]='\0'; printf("%s\n",buf);
     read(d3,buf, 2); buf[3]='\0'; printf("%s\n",buf);
}

int main()
{
    read_file();
    return 0;
}
