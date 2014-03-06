#include "AFN.h"


void AFNN::setnrstari(int ns)
{
//similar functiei corespunzatoare de la programul pentru AFD
	nrstari = ns;

	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			for(int k = 0; k < 256; k++)
			{
				tranzitie[i][j][k] = -1;
			}
		}
	}

	for(int i = 0; i < 256; i++)
	{
		finala[i] = 0;
	}
}

int AFNN::exectranzitie(int s, unsigned char c, int t[256])
{
//functie ajutatoare pentru scrierea functiei de recunoastere

//pune in t vectorul caracteristic al starilor destinatie in care
//ajunge automatul pornind din starea s, prin citirea caracterului c
//dintr-un cuvant
    bool done = false;
    for(int i = 0; i < 256; i++)
    {
        t[i] = tranzitie[s][c][i];
        if(tranzitie[s][c][i] != -1)
        {
            done = true;
//            return tranzitie[s][c];
        }
    }
    if(!done)
    {
        return -1;
    }
    return 1;
}
int AFNN::recunoaste(std::string cuvant, int indice, int stare)
{
    /// (Q, Sigma, delta, q0, F)
    /// delta : Q x V -> Q
    /// delta' : Q x V* -> Q

//	std::cout<<indice<<' '<<stare<<'\n';
//    bool done = false;
//	for(int i = indice; i < cuvant.size(); i++)
	{
	    for(int j = 0; j < 256; j++)
        {
            if(tranzitie[stare][cuvant[indice]][j] != -1)
            {
//                std::cout<<stare<<' '<<j<<' '<<cuvant[indice]<<'\n';
//                done = true;
                recunoaste(cuvant, indice + 1, j);
            }
        }
//        if(!done)
//        {
//            return 0;
//        }
	}
	if(estefinala(stare))
    {
        a = 1;
        return 1;
    }
    return 0;
//functia de recunoastere a cuvintelor
}
