#include<iostream>
using namespace std;
#define NMAX 500
#define PI 3.1416
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double a[NMAX][NMAX];
double b[NMAX], x[NMAX][NMAX], y[NMAX][NMAX];
vector<double> v;

void computeMatrix(int m) {
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = 0.0;
	for(int i = 1; i <= m; ++i)  {
		a[i][i] = 2.0 + 1.0 / m / m;
		b[i] = 1.0 / m / m;
	}
	for(int i = 1; i < m; ++i) {
		a[i + 1][i] = -1.0;
		a[i][i + 1] = -1.0;
	}
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= m; ++j)
			x[i][j] = a[i][j];

}

void solve(int m, double eps) 
{
	double modul = 0;
	computeMatrix(m);
	int nr = 0;
	int num = 100000;
	do {
		++nr;
		int p, q;
		double maxim = -1.0;
		for(int i = 1; i <= m; ++i)
			for(int j = i + 1; j <= m; ++j) 
			{
				if(abs(x[i][j]) > maxim) 
				{
					maxim = abs(x[i][j]);
					p = i;
					q = j;
				}
			}
			double fi;
			if(x[p][p] == x[q][q])
				fi = PI / 4;
			else
				fi = 1.0 / 2 * atan(2.0 * x[p][q] / (x[p][p] - x[q][q])) ;
			double c = cos(fi );
			double s = sin(fi );

			for(int i = 1; i <= m; ++i)
				for(int j = 1; j <= m; ++j) 
				{
					if (i != p && j != p && i != q && j != q)
						y[i][j] = x[i][j];
				}

				for(int j = 1; j <= m; ++j) 
				{
					if(j != p && j != q)
					{
						y[p][j] = y[j][p] = c * x[p][j] + s * x[q][j];
						y[q][j] = y[j][q] = -s * x[p][j] + c * x[q][j];
					}
				}
				y[p][q] = y[q][p] = 0.0;
				y[p][p] = c * c * x[p][p] + 2.0 * c * s * x[p][q] + s * s * x[q][q];
				y[q][q] = s * s * x[p][p] - 2.0 * c * s * x[p][q] + c * c * x[q][q];

				double sum = 0.0;
				for(int i = 1; i <= m; ++i)
					for(int j = 1; j <= m; ++j) 
					{
						if(i != j)
							sum += (y[i][j] * y[i][j]);
					}

					modul = sqrt(sum);
					for(int i = 1; i <= m; ++i)
						for(int j = 1; j <= m; ++j) 
						{
							x[i][j] = y[i][j];
						}
	}while(modul > eps);
	for(int i = 1; i <= m; ++i) 
	{
		v.push_back(x[i][i]);
	}
	sort(v.begin(), v.end());
	for(int i = 0; i < m; ++i)
		cout << v[i] << " ";
}

int main()
{
	int m;
	cin >> m;
	solve(m, 0.0000000001);
	return 0;
}
