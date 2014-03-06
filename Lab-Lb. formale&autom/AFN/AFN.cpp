#include "AFN.h"


void AFN::setnrstari(int ns)
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

int AFN::exectranzitie(int s, unsigned char c, int t[256])
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
int a = 0;
int AFN::recunoaste(std::string cuvant, int indice, int stare)
{
    bool done = false;
	for(int i = indice; i < cuvant.size(); i++)
	{
	    for(int j = 0; j < 256; j++)
        {
            if(tranzitie[stare][cuvant[i]][j] != -1)
            {
                done = true;
                return recunoaste(cuvant, i + 1, j) || a;
            }
        }
        if(!done)
        {
            return 0;
        }
	}
	a = 1;
	return 1;
//functia de recunoastere a cuvintelor
}
