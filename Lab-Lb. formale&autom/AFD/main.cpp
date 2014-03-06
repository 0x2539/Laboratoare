#include <iostream>
#include <fstream>
#include <AFD.h>

std::ifstream fin("tranzitii.txt");

AFD a;

int main()
{
    int nr = 0;
    unsigned char c;
    int t, fr;

    fin>>nr;
    a.setnrstari(nr);

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
    std::cout<<a.recunoaste(citit, a.finala)<<'\n';

    return 0;
}
