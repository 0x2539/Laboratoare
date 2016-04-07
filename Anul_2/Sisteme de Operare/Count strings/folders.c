#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>

int counter = 0;
char *name_of_file = "fisier.txt";

int listdir(const char *nf)
{
    DIR *pd;
    struct dirent *pde;
    char cale[256], specificator[256];
    if((pd=opendir(nf))==NULL)return -1;
    strcpy(cale, nf);
    strcat(cale,"/");
    while((pde=readdir(pd))!=NULL)
    {
        strcpy(specificator, cale);
        strcat(specificator, pde->d_name);
        if(strcmp("..", pde->d_name) != 0 && strcmp(".", pde->d_name) != 0)
        {
            if(fileinfo(specificator)==-1)perror(specificator);
        }
    }
    closedir(pd);
    return 0;
}

int check_name(char *file)
{
    if(strlen(file) < strlen(name_of_file))
    {
        return 0;
    }
    if(file[strlen(file) - strlen(name_of_file) - 1] == '/')
    {
        int i;
        int k = 0;
        for(i = strlen(file) - strlen(name_of_file); i < strlen(file); i++)
        {
            if(file[i] != name_of_file[k])
            {
                return 0;
            }
            k++;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

int fileinfo(const char *nf)
{
    struct stat s;
    struct dirent *entry;
    if(stat(nf,&s)==-1)return -1;

    if((s.st_mode & S_IFMT) == S_IFREG)
    {
        //printf("<FILE>");
        if(check_name(nf) != 0)
        {
            counter++;
        }
    }
    else if((s.st_mode & S_IFMT) == S_IFDIR)
    {
            listdir(nf);
    }
    //printf("%s\n",nf);
    return 0;
}

int mainss()
{
    listdir("G:\\Folder");
    printf("%d", counter);
}
