#include <iostream>
#include <fstream>
#include <algorithm>

std::ifstream fin("date.txt");

struct nod
{
    int grad, indice;
};

int nr_grade;
nod grade[100];
int matrice_adiacenta[100][100];

int cmp(nod a, nod b)
{
    if(a.grad > b.grad)
    {
        return 1;
    }
    return 0;
}

void citire()
{
    fin>>nr_grade;
    for(int i = 0; i < nr_grade; i++)
    {
        fin>>grade[i].grad;
        grade[i].indice = i;
    }
    std::sort(grade, grade + nr_grade, cmp);
}

void rezolvare()
{
    while(grade[0].grad != 0)
    {
        for(int j = 1; j <= grade[0].grad; j++)
        {
            matrice_adiacenta[grade[0].indice][grade[j].indice] = 1;
            grade[j].grad--;
        }
        grade[0].grad = 0;

        std::sort(grade, grade + nr_grade, cmp);
    }
}

void afisare()
{
    for(int i = 0; i < nr_grade; i++)
    {
        std::cout<<i + 1<<": ";
        for(int j = 0; j < nr_grade; j++)
        {
            if(matrice_adiacenta[i][j])
            {
                std::cout<<j + 1<<' ';
            }
        }
        std::cout<<'\n';
    }
}

int main()
{
    citire();
    rezolvare();
    afisare();
    return 0;
}
