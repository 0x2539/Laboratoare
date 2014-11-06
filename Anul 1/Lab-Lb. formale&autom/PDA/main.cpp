#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AFD
{
	int nrstari, f[100], tos;
	string s;
	struct tranz
	{
		int q;
		string sir;
	} m[100][256][256];
public:
	int get_nrstari()
	{
		return nrstari;
	}
	void set_nrstari(int n)
	{
		nrstari = n;
	}
	int get_finala(int n)
	{
		return f[n];
	}
	void set_finala(int n)
	{
		f[n] = 1;
	}
	int get_tranzitie1(int n, unsigned char c1, unsigned char c2)
	{
		return m[n][c1][c2].q;
	}
	string get_tranzitie2(int n, unsigned char c1, unsigned char c2)
	{
		return m[n][c1][c2].sir;
	}
	void set_tranzitie(int n, unsigned char c1, unsigned char c2, int x, string c)
	{
		m[n][c1][c2].q = x;
		m[n][c1][c2].sir = c;
	}
	void set_tranzitie(int n, unsigned char c1, unsigned char c2)
	{
		m[n][c1][c2].q = -1;
		m[n][c1][c2].sir = "";
	}
	void init()
	{
		tos = 1;
		s[tos] = '~';
	}
	int get_tos()
	{
		return tos;
	}
	char show()
	{
		return s[tos];
	}
	void push(string c)
	{
		if (c == "lambda")
			tos--;
		else
		{
			for (int i = 0; i <= c.size() - 1; i++)
				s[tos + i] = c[i];
			tos = tos + c.size() - 1;
		}
	}
} a;

int n, x, nr;
char c1, c2;
string s;

int main()
{
    ifstream fin("tranz.txt");
	//cout << "Nr. stari: ";
	fin >> n;
	a.set_nrstari(n);
	//cout << "Nr. stari finale: ";
	fin >> n;
	if (n > 0)
	{
		//cout << "Starile finale: ";
		for (int i = 1; i <= n; i++)
		{
			fin >> x;
			a.set_finala(x);
		}
	}
	for (int i = 0; i <= a.get_nrstari() - 1; i++)
		for (int j = 0; j <= 256; j++)
			for (int k = 0; k <= 256; k++)
				a.set_tranzitie(i, j, k);
	//cout << "Nr. tranzitii: ";
	fin >> n;
	//cout << "Tranzitii: " << '\n';
	for (int i = 1; i <= n; i++)
	{
		fin >> nr >> c1 >> c2 >> x >> s;
		a.set_tranzitie(nr, c1, c2, x, s);
	}
	cout << "Cuvinte de verificat:" << '\n';
	cin >> s;
	while (s != "stop")
	{
		int ok = 1, q = 0;
		a.init();
		for (int i = 0; i <= s.size() - 1 && ok == 1; i++)
		{
			if (a.get_tos() == 0)
				ok = 0;
			else
				if (a.get_tranzitie1(q, s[i], a.show()) == -1)
					ok = 0;
				else
				{
				    int q2 = q;
					q = a.get_tranzitie1(q, s[i], a.show());
					a.push(a.get_tranzitie2(q2, s[i], a.show()));
				}
		}
		if (ok == 0)
			cout << "Incorect!" << '\n';
		else
			if (a.get_tos() == 0)
				cout << "Corect!" << '\n';
			else
				if (a.get_finala(q) == 0)
					cout << "Incorect!" << '\n';
				else
					cout << "Corect!" << '\n';
		cin >> s;
	}
	return 0;
}
