#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>

std::vector<int> matrice[1000];
std::ifstream fin("date.txt");

int nodPornire, n, m;

void citire()
{
    fin>>n>>m>>nodPornire;
    int x, y;
    for(int j = 0; j < m; j++)
    {
        fin>>x>>y;
        matrice[x].push_back(y);
        matrice[y].push_back(x);
    }
}

void bfs(int nod)
{
    std::queue<int> coada_smechera;
    std::bitset<100000> retinere_smechera;

    coada_smechera.push(nod);

    while(coada_smechera.size())
    {
        int p = coada_smechera.front();

        retinere_smechera[p] = true;

        std::cout<<p<<' ';

        for(int i = 0; i < matrice[p].size(); i++)
        {
            if(retinere_smechera[matrice[p][i]] == false)
            {
                coada_smechera.push(matrice[p][i]);
            }
        }
        coada_smechera.pop();
    }
}

int main()
{
    citire();
    bfs(nodPornire);
    return 0;
}
