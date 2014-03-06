#ifndef AFD_H
#define AFD_H

#include <iostream>
#include <string.h>
#include <stdlib.h>

class AFD
{
public:

	int nrstari;
	//starile vor fi 0, 1,..., nrstari-1
	//starea initiala este 0
	//-1 va semnifica stare nedefinita
	int finala[256];//vectorul caracteristic al starilor finale
	//(finala[0..nrstari-1])
	int tranzitie[256][256];//matricea care defineste functia de tranzitie
	//alfabetul automatului este intreg setul de caractere ASCII

	int getnrstari()
	{
		return nrstari;
	}

	void setnrstari(int);

	int estefinala(int s)
	{
		return finala[s];
	}

	void setfinala(int s)
	{
		finala[s] = 1;
	}

	int gettranzitie(int s, unsigned char c)
	{
		return tranzitie[s][c];
	}

	void settranzitie(int s, unsigned char c, int t)
	{
		tranzitie[s][c] = t;
	}

	int recunoaste(std::string, int[]);
};



#endif // AFD_H
