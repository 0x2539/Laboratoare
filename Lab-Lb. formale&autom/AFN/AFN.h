#ifndef AFN_H_INCLUDED
#define AFN_H_INCLUDED

#include <iostream>

class AFNN
{
	int nrstari;
	//starile vor fi 0, 1,..., nrstari-1
	//starea initiala este 0
	int finala[256];//vectorul caracteristic al starilor finale
	//(finala[0..nrstari-1])
	int tranzitie[256][256][256];//functia de tranzitie
	//tranzitie[s][c][t]=1 daca t apartine la d(s,c), altfel =0, unde
	//s si t sunt stari, iar c este un caracter
	//alfabetul automatului este intreg setul de caractere ASCII
public:

    int a = 0;

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

	int gettranzitie(int s, unsigned char c, int t)
	{
		return tranzitie[s][c][t];
	}

	void settranzitie(int s, unsigned char c, int t)
	{
		tranzitie[s][c][t] = 1;
	}

	int exectranzitie(int s, unsigned char c, int t[256]);

    int recunoaste(std::string cuvant, int indice, int stare);
};

#endif // AFN_H_INCLUDED
