#include <iostream>
#include <fstream>

std::ifstream fin("date.txt");

struct nod
{
    int balance_factor = 0;
    int valoare = -1;
    nod *left, *right, *up;
};

nod *prim;
int nr_noduri;

void echilibreaza_avl(nod *nodul_curent)
{

}

void add_in_avl(nod *nodul_curent, const int &valoare, int &balance_factor)
{
    if(nodul_curent)
    {
        if(nodul_curent->valoare > valoare)
        {
            if(nodul_curent->left)
            {
                add_in_avl(nodul_curent->left, valoare);
            }
            else
            {
                nodul_curent->left = new nod;
                nodul_curent->left->valoare = valoare;
                nodul_curent->left->up = nodul_curent;
            }
        }
        else
            if(nodul_curent->valoare < valoare)
            {
                if(nodul_curent->right)
                {
                    add_in_avl(nodul_curent->right, valoare);
                }
                else
                {
                    nodul_curent->right = new nod;
                    nodul_curent->right->valoare = valoare;
                    nodul_curent->right->up = nodul_curent;
                }
            }
    }
    ///o sa intre pe else doar pentru varf
    else
    {
        nodul_curent = new nod;
        nodul_curent->valoare = valoare;
    }
}

void remove_from_avl(nod *nodul_curent, const int &valoare)
{
    if(nodul_curent)
    {
        if(nodul_curent->valoare > valoare)
        {
            remove_from_avl(nodul_curent->left, valoare);
        }
        else
            if(nodul_curent->valoare < valoare)
            {
                remove_from_avl(nodul_curent->right, valoare);
            }
            else
                if(nodul_curent->valoare == valoare)
                {
                    delete nodul_curent;
                }
    }
}

void citire()
{
    fin>>nr_noduri;
    int valoare_curena;
    char action;

    for(int i = 0; i < nr_noduri; i++)
    {
        fin>>action>>valoare_curena;
        if(action == 'a')
        {
            add_in_avl(prim, valoare_curena)
        }
        else
            if(action == 'r')
            {
                remove_from_avl(prim, valoare_curena);
            }
    }
}

void rezolvare()
{

}

int main()
{
    citire();
    rezolvare();
    return 0;
}
