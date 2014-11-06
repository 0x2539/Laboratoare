#include <iostream>
#include <fstream>

std::ifstream fin("date.txt");

struct nod
{
    int value = 0;
    nod *left, *right;
};

nod *prim;
int minimul_meu = 1000000, maximul_meu = -1000000;


template <class T>
T maximF(T a, T b)
{
    if(a < b)
    {
        return b;
    }
    return a;
}
template <class T>
T minimF(T a, T b)
{
    if(a > b)
    {
        return b;
    }
    return a;
}

bool check(nod *nodul_meu, int minim, int maxim)
{
    if(nodul_meu)
    {
        std::cout<<nodul_meu->value<<' '<<minim<<' '<<maxim<<'\n';

        if(nodul_meu->value > minim && nodul_meu->value < maxim)
        {
            return check(nodul_meu->left, minim, nodul_meu->value - 1) && check(nodul_meu->right, nodul_meu->value + 1, maxim);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

nod* creeare()
{
    int a = 0;
    nod *p;
    fin>>a;
    if(a)
    {
        minimul_meu = minimF(a, minimul_meu);
        maximul_meu = maximF(a, maximul_meu);

        p = new nod;

        p->value = a;
        p->left = creeare();
        p->right = creeare();
    }
    else
    {
        p = NULL;
    }
    return p;
}

int main()
{
    prim = creeare();
    minimul_meu--;
    maximul_meu++;
    std::cout<<'\n';
    std::cout<<check(prim, minimul_meu, maximul_meu)<<'\n';
    return 0;
}
