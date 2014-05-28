#include "AFN.h"
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stdlib.h>


template <class T>
std::string ToString(const T &value_to_convert)
{
	std::ostringstream os;

	os << value_to_convert;

	return std::string(os.str());
}

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

int exista = 0;
int AFNN::verifica(int stare_curenta, int indice, std::string cuvant, int nr_litere)
{
    if (indice < nr_litere)
    {
        for (int i=0; i<nrstari; i++)
            if (tranzitie[stare_curenta][cuvant[indice]][i] == 1)
                verifica(i,indice + 1, cuvant, nr_litere);
    }
    else
        if (finala[stare_curenta] == 1)
        exista = 1;
    return exista;


}


int AFNN::recunoaste(std::string cuvant, int indice, int stare)
{
    for(int j = 0; j < 256; j++)
    {
        if(tranzitie[stare][cuvant[indice]][j] != -1)
        {
            recunoaste(cuvant, indice + 1, j);
        }
    }
	if(estefinala(stare))
    {
        a = 1;
    }
    return a;
}

int cmp(int a, int b)
{
    if(a < b)
    {
        return 1;
    }
    return 0;
}

int compare_2_vectori(std::vector<int> a, std::vector<int> b)
{
    if(a.size() != b.size())
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < a.size(); i++)
        {
            if(a[i] != b[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

int char_to_int(char c)
{
    if(c == '0')
    {
        return 0;
    }
    else
    if(c == '1')
    {
        return 1;
    }
    else
    if(c == '2')
    {
        return 2;
    }
    else
    if(c == '3')
    {
        return 3;
    }
    else
    if(c == '4')
    {
        return 4;
    }
    else
    if(c == '5')
    {
        return 5;
    }
    else
    if(c == '6')
    {
        return 6;
    }
    else
    if(c == '7')
    {
        return 7;
    }
    else
    if(c == '8')
    {
        return 8;
    }
    else
    if(c == '9')
    {
        return 9;
    }
}

struct stare
{
    std::string nume_stare = "";
    std::string litere_prin_care_ajunge = "";
};

std::unordered_map<std::string, bool> vizitari;

//void reuniune(std::vector<)

int AFNN::afn_to_afd(std::string stare_curenta)///, std::string litere)
{
//    std::cout<<stare_curenta<<' '<<vizitari[stare_curenta]<<":"<<'\n';
    if(!vizitari[stare_curenta])
    {
        std::vector<std::string> toate_starile;
        std::unordered_map<std::string, std::vector<stare*> > starile_mele;

        std::vector<int> litere[257];
        vizitari[stare_curenta] = true;

        ///retin toate starile posibile gen: {1}, {1,2,3}, {2,3}
        toate_starile.push_back(stare_curenta);
//        std::cout<<stare_curenta_int<<' '<<stare_curenta<<": ";

        for(int i = 0; i < stare_curenta.size(); i++)///parcurg elementele din starea mea. Ex: pentru starea {1,2,3} trec prin 1, 2 si 3
        {
//            std::cout<<"s "<<stare_curenta[i]<<'\n';
            for(int j = 0; j < alfabet.size(); j++)///trec prin tot alfabetul
            {
//                std::cout<<"alfabet: "<<alfabet[j]<<":\n";
                for(int k = 0; k < 256; k++)///trec prin toate starile din AFN-ul meu
                {
                    if(tranzitie[char_to_int(stare_curenta[i])] [alfabet[j]] [k] != -1)///daca am o tranzitie
                    {
//                        std::cout<<char_to_int(stare_curenta[i])<<' '<<k<<'\n';
                        ///Exemplu: pentru litere['a']:{1,2,3}, inseamna ca din starea curenta ajung prin 'a' in: 1, 2 si 3
                        litere[alfabet[j]].push_back(k);
                    }
                }
//                std::cout<<'\n';
            }
        }

        ///le sortez pentru ca de exemplu, prin 'a' ajung in 2, 3, si prin 'b' ajung in 3, 2, ceea ce inseamna ca prin 'a' si 'b' ajung in 2 si 3
        for(int i = 0; i < alfabet.size(); i++)
        {
            std::sort(litere[alfabet[i]].begin(), litere[alfabet[i]].end(), cmp);
        }

        std::vector<std::string> starile_nou_create;

        ///vad care sunt starile noi create (le compar intre ele)
        for(int i = 0; i < alfabet.size(); i++)
        {
//            std::cout<<alfabet[i]<<": "<<litere[alfabet[i]].size()<<'\n';;
            if(litere[alfabet[i]].size())
            {
                ///creez din vector un string
                std::string starea_mea = "";
                for(int j = 0; j < litere[alfabet[i]].size(); j++)
                {
                    starea_mea += ToString(litere[alfabet[i]][j]);
                }
                starile_nou_create.push_back(starea_mea);

                stare *s = new stare;
                s->nume_stare = starea_mea;
                s->litere_prin_care_ajunge = alfabet[i];


                for(int j = i + 1; j < alfabet.size(); j++)
                {
                    if(compare_2_vectori(litere[alfabet[i]], litere[alfabet[j]]))
                    {
//                        starile_mele[starea_mea].push_back(alfabet[j]);
                        s->litere_prin_care_ajunge += alfabet[j];
                        litere[alfabet[j]].clear();
                    }
                }
                starile_mele[stare_curenta].push_back(s);
                for(int w = 0; w < stare_curenta.size(); w++)
                {
                    std::cout<<stare_curenta[w]<<", ";
                }
                std::cout<<s->litere_prin_care_ajunge<<' ';///<<s->nume_stare<<' '<<'\n';
                for(int w = 0; w < s->nume_stare.size(); w++)
                {
                    std::cout<<s->nume_stare[w]<<", ";
                }
                std::cout<<'\n';
                afn_to_afd(s->nume_stare);
            }
            litere[alfabet[i]].clear();
        }
    }
}
