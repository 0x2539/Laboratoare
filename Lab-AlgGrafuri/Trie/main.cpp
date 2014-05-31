#include <iostream>
#include <fstream>
#include <unordered_map>

struct nod
{
    int nrCuvintePrinCaracterulCurent = 0;
    bool esteCuvant = false;
    std::unordered_map<char, nod*> alfabet;
};

nod *varf = new nod;

void adauga(std::string cuvant)
{
    nod *current = varf;
    for(int i = 0 ; i < cuvant.size(); i++)
    {
        if(current->alfabet[cuvant[i]] == NULL)
        {
            current->alfabet[cuvant[i]] = new nod;
        }
        current = current->alfabet[cuvant[i]];
        current->nrCuvintePrinCaracterulCurent++;
    }
    current->esteCuvant = true;
    std::cout<<"am adaugat cuvantul '"<<cuvant<<"' in dictionar"<<'\n';
}

void sterge(std::string cuvant)
{
    bool existaCuvant = true;
    nod *current = varf;
    for(int i = 0 ; i < cuvant.size(); i++)
    {
        if(current->alfabet[cuvant[i]] == NULL)
        {
            existaCuvant = false;
            break;
        }
        current->nrCuvintePrinCaracterulCurent--;
        current = current->alfabet[cuvant[i]];
    }
    std::cout<<"am sters cuvantul '"<<cuvant<<"' din dictionar"<<'\n';
}

void cauta(std::string cuvant)
{
    bool existaCuvantul = true;
    nod *current = varf;
    for(int i = 0; i < cuvant.size(); i++)
    {
        ///dac nu am creat un nod nou, sau daca am sters din nodul vechi caracterul
        if(current->alfabet[cuvant[i]] == NULL || current->alfabet[cuvant[i]]->nrCuvintePrinCaracterulCurent == 0)
        {
            existaCuvantul = false;
            break;
        }
        current = current->alfabet[cuvant[i]];
    }
    if(existaCuvantul == true)
    {
        if(current->esteCuvant == true)
        {
            std::cout<<"cuvantul: '"<<cuvant<<"' exista in dictionar"<<'\n';
        }
        else
        {
            std::cout<<"cuvantul: '"<<cuvant<<"' NU exista in dictionar"<<'\n';
        }
    }
    else
    {
        std::cout<<"cuvantul: '"<<cuvant<<"' NU exista in dictionar"<<'\n';
    }
}

void citire()
{
    std::ifstream fin("date.txt");

    int nrActions = 0;
    fin>>nrActions;

    for(int w = 0; w < nrActions; w++)
    {
        char action;
        std::string cuvant;
        fin>>action>>cuvant;

        if(action == 'a')
        {
            adauga(cuvant);
        }
        else
            if(action == 's')
            {
                sterge(cuvant);
            }
            else
                if(action == 'c')
                {
                    cauta(cuvant);
                }
    }
}

int main()
{
    citire();
    return 0;
}
