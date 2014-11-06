#include <iostream>
#include <fstream>

struct nod
{
    int value;
    bool esteSetat = false;
    nod *stanga = NULL, *dreapta = NULL;
};

nod *varf;

void adauga(nod *current, int value)
{
    if(current != NULL)
    {
        if(current->esteSetat == true)
        {
            if(current->value < value)
            {
                if(current->dreapta == NULL)
                {
                    current->dreapta = new nod;
                }
                adauga(current->dreapta, value);
            }
            else
                if(current->value > value)
                {
                    if(current->stanga == NULL)
                    {
                        current->stanga = new nod;
                    }
                    adauga(current->stanga, value);
                }
        }
        else
        {
            current->value = value;
            current->esteSetat = true;
        }
    }
}

void sterge(int value)
{
    nod *current = varf;
    bool amSters = false;

    while(current && current->esteSetat == true && amSters == false)
    {
        if(current->value > value)
        {
            current = current->stanga;
        }
        else
            if(current->value < value)
            {
                current = current->dreapta;
            }
            else
                if(current->value == value)
                {
                    amSters = true;
                    int valueToReplace = 0;
                    bool found = false;

                    nod *replaceable = current;

                    //ma duc in stanga daca exista
                    if(replaceable->stanga && replaceable->stanga->esteSetat == true)
                    {
                        //ma duc in stanga
                        replaceable = replaceable->stanga;
                        found = true;

//                        delete replaceable;
//                        replaceable = NULL;
                    }
//                    else
//                        //ma duc in dreapta daca pot
//                        if(replaceable->dreapta && replaceable->dreapta->esteSetat == true)
//                        {
//                            //ma duc in dreapta
//                            replaceable = replaceable->dreapta;
//                            found = true;
//
//                            while(replaceable->dreapta && replaceable->dreapta->esteSetat == true)
//                            {
//                                //valueToReplace = replaceable->value;
//                                replaceable = replaceable->dreapta;
//                            }
//                            valueToReplace = replaceable->value;
//                            replaceable->esteSetat = false;
////                            delete replaceable;
////                            replaceable = NULL;
//                        }

                    while(replaceable->dreapta && replaceable->dreapta->esteSetat == true)
                    {
                        found = true;
                        //valueToReplace = replaceable->value;
                        replaceable = replaceable->dreapta;
                    }
                    valueToReplace = replaceable->value;
                    replaceable->esteSetat = false;

                    if(found)
                    {
                        current->value = valueToReplace;
                    }
                    else
                    {
                        current->esteSetat = false;
                        //delete current;
                        //current = NULL;
                    }
                }
    }
}

void cauta(nod *current, int value)
{
    if(current != NULL && current->esteSetat == true)
    {
        if(current->value > value)
        {
            cauta(current->stanga, value);
        }
        else
            if(current->value < value)
            {
                cauta(current->dreapta, value);
            }
            else
            {
                std::cout<<"am gasit valoarea: "<<value<<'\n';
            }
    }
    else
    {
        std::cout<<"NU am gasit valoarea: "<<value<<'\n';
    }
}

void citire()
{
    int nrActions;

    std::ifstream fin("date.txt");

    fin>>nrActions;

    for(int w = 0; w < nrActions; w++)
    {
        char action;
        int value;

        fin>>action>>value;
        //std::cout<<action<<'\n';

        if(action == 'a')
        {
            if(varf == NULL)
            {
                varf = new nod;
            }
            adauga(varf, value);
        }
        else
            if(action == 's')
            {
                sterge(value);
            }
            else
                if(action == 'c')
                {
                    cauta(varf, value);
                }
    }
}

int main()
{
    citire();
    return 0;
}
