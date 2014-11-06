#include <iostream>

using namespace std;

class Punct
{
   public:
    float x,y,z;
};

Punct a, b, c;

float raport(int x, int y)
{
    return (float)(x / y);
}

Punct egalitate(Punct punct1, Punct punct2, float alpha, float beta)
{
    Punct punct3;
    punct3.x = (float)(punct1.x * alpha);
    punct3.y = (float)(punct1.y * alpha);
    punct3.z = (float)(punct1.z * alpha);

    punct3.x += (float)(punct2.x * beta);
    punct3.y += (float)(punct2.y * beta);
    punct3.z += (float)(punct2.z * beta);
    return punct3;

    //cout<<"---"<<punct3.x<<' '<<punct3.y<<' '<<punct3.z<<'\n';
}

bool egalitate(Punct punct1, Punct punct2)
{
    //cout<<"   | "<< punct1.x<<' '<<punct2.x<<", "<<punct1.y<<' '<<punct2.y<<", "<<punct1.z<<' '<<punct2.z<<'\n';
    if((int)punct1.x == (int)punct2.x && (int)punct1.y == (int)punct2.y && (int)punct1.z == (int)punct2.z)
    {
        return true;
    }
    return false;
}

void checkVector(int &poz, int i,
                 bool &ok, float rapoarte[], int &n, int punct1, int punct2, int punct3)
{
    if((punct3 - punct2 == 0 && punct2 - punct1 != 0))// || (punct3 - punct2 != 0 && punct2 - punct1 == 0))
    {
        ok = false;
    }
    else
    {
        if(punct3 - punct2 != 0)
        {
            poz = i;
            rapoarte[n] = raport(punct2 - punct1, punct3 - punct2);
        n++;
        }
        else
        if(punct2 - punct1 != 0)
        {
            poz = i;
            rapoarte[n] = raport(punct3 - punct2, punct2 - punct1);
        n++;
        }
    }
}

void init()
{
    cout<<"coordonatele lui a: \n";
    cin>>a.x>>a.y>>a.z;
    cout<<"coordonatele lui b: \n";
    cin>>b.x>>b.y>>b.z;
    cout<<"coordonatele lui c: \n";
    cin>>c.x>>c.y>>c.z;
    float rapoarte[3];
    int n = 0;
    int poz = 0;
    bool ok = true;

//    if(egalitate(a, b) || egalitate(b, c) || egalitate(a, c))
//    {
//        cout<<"Coliniaritate: 1"<<'\n';
//        cout<<"r = 0"<<'\n';
//        cout<<"A2 = ...\n";
//    }
//else
{
    checkVector(poz, 1, ok, rapoarte, n, a.x, b.x, c.x);
    checkVector(poz, 2, ok, rapoarte, n, a.y, b.y, c.y);
    checkVector(poz, 3, ok, rapoarte, n, a.z, b.z, c.z);

    /*if(c.x - b.x == 0)
    {
        if(b.x - a.x != 0)
        {
            ok = false;
        }
    }
    else
    {
        rapoarte[n] = raport(b.x - a.x, c.x - b.x);
        n++;
    }*/

    for(int i = 1; i < n; i++)
    {
        if(rapoarte[i] != rapoarte[i-1])
        {
            ok = false;
        }
    }

    cout<<"Coliniaritatea punctelor: "<<ok<<'\n';;

    if(ok)
    {
        float alpha = (float)(1/(rapoarte[0]+1));
        float beta = (float)(rapoarte[0]/(rapoarte[0]+1));
        cout<<"raport: "<<poz<<" | "<<rapoarte[0]<<'\n';
        cout<<"Alpha: "<<alpha<<'\n';
        cout<<"Beta: "<<beta<<'\n';

        if(egalitate(a, egalitate(b, c, alpha, beta)))
        {
            cout<<"A1 = ...\n";
        }
        else
        if(egalitate(b, egalitate(a, c, alpha, beta)))
        {
            cout<<"A2 = ...\n";
        }
        else
        if(egalitate(c, egalitate(a, b, alpha, beta)))
        {
            cout<<"A3 = ...\n";
        }
    }
}
}

int main()
{
    init();
    return 0;
}
