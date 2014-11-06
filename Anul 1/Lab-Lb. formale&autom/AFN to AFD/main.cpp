#include <iostream>
#include <fstream>
#include "AFN.h"

std::ifstream fin("tranzitii.txt");

AFNN bb;

int sf[10];

int main()
{
//    int mare;
//    mare = 0;//mare
//    int mm;
//    mm = 1;
//    if(mm == 1)
//    {
//        mare = 2;
//    }

    int nr = 0;
    unsigned char c;
    int t, s;
    int nrSF;

    std::string alfabet;
        fin>>alfabet;
        bb.add_to_alfabet(alfabet);

    fin>>nr;
    bb.setnrstari(nr);

    fin>>nrSF;
    for(int i = 0; i < nrSF; i++)
    {
        fin>>sf[i];
        bb.setfinala(sf[i]);
    }

    fin>>nr;

    for(int i = 0; i < nr; i++)
    {
        fin>>s>>c>>t;
        bb.settranzitie(s, c, t);
    }

    fin>>nr;
    std::string citit = "";
    for(int i = 0; i < nr; i++)
    {
        fin>>c;
        citit += c;
    }
    if(citit != "")
    {
        int sff = bb.recunoaste(citit, 0, 0);

        if(bb.a)
        {
            std::cout<<1<<'\n';
        }
        else
        {
            std::cout<<-1<<'\n';
        }
//        for(int i = 0; i < nrSF; i++)
//        {
//            if(sff == sf[i])
//        }
    }
    else
    {
        std::cout<<-1<<'\n';
    }

    bb.afn_to_afd("0");

    return 0;
}
