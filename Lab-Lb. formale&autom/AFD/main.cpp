#include <iostream>
#include <fstream>
#include <AFD.h>

std::ifstream fin("tranzitii.txt");

AFD a;
int sf[10];

int main()
{
    int nr = 0;
    unsigned char c;
    int t, fr;

    int nrSF;

    fin>>nr;
    a.setnrstari(nr);

    fin>>nrSF;
    for(int i = 0; i < nrSF; i++)
    {
        fin>>sf[i];
    }

    fin>>nr;

    for(int i = 0; i < nr; i++)
    {
//        for(int j = 0; j < nr; j++)
        {
            fin>>fr>>c>>t;
            a.settranzitie(fr, c, t);
        }
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
        int sff = a.recunoaste(citit, a.finala);
        bool done = false;
        for(int i = 0; i < nrSF; i++)
        {
            if(a.estefinala(sff) == sf[i])
            {
                done = true;
                std::cout<<1<<'\n';
                break;
            }
        }
        if(!done)
        {
            std::cout<<-1<<'\n';
        }
    }
    else
    {
        std::cout<<-1<<'\n';
    }

    return 0;
}
