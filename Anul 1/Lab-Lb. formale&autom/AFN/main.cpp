//#include <iostream>
#include <fstream>
#include "AFN.h"

std::ifstream fin("tranzitii.txt");

AFNN bb;

int sf[10];

int main()
{
    int nr = 0;
    unsigned char c;
    int t, s;
    int nrSF;

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

    return 0;
}
