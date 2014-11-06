#ifndef AFN_H_INCLUDED
#define AFN_H_INCLUDED

#include <iostream>

class AFNN
{
	int nrstari;
	std::string alfabet;
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

    void add_to_alfabet(std::string c)
    {
        alfabet = c;
    }

    int verifica(int stare_curenta, int indice, std::string cuvant, int nr_litere);
	int getnrstari()
	{
		return nrstari;
	}
    int afn_to_afd(std::string stare_curenta);///, std::string litere);

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
