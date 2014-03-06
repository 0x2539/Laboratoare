#include "AFD.h"

void AFD::setnrstari(int ns)
{
    nrstari = ns;
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            tranzitie[i][j] = -1;
        }
    }

    for(int i = 0; i < 256; i++)
    {
        finala[i] = 0;
    }
//face alocare de memorie si initializare pentru nrstari (cu ns),
//finala (cu o peste tot), tranzitie (cu -1 peste tot)

}
int AFD::recunoaste(std::string cuvant, int f[])
{
    for(int i = 0; i < cuvant.size(); i++)
    {
        f[i+1] = gettranzitie(f[i], cuvant[i]);
        if(f[i+1] == -1)
        {
            return -1;
        }
    }
    return 1;
//functia de recunoastere a cuvintelor
//*f va fi starea in care a ajuns automatul, indiferent daca accepta
//cuvantul sau nu

}
