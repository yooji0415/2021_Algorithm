#include<iostream>
using namespace std;

void floyd2(int n, int **w, int **d, int **p) {
	int i, j, k;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			p[i][j] = 0;
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			d[i][j] = w[i][j];
		}
	}
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (d[i][k] + d[k][j] < d[i][j]) {
					p[i][j] = k;
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
}
void path(int **p, int q, int r) {
	if (p[q][r] != 0) {
		path(p, q, p[q][r]);
		cout <<" "<< p[q][r];
		path(p, p[q][r], r);
	}
}

int main() {
	int num,i,j,a,b,c,m;
	cin >> num >> m;
	int **w = new int*[num + 1];
	for (i = 0; i < num + 1; i++) {
		w[i] = new int[num + 1];
	}
	int **d = new int*[num + 1];
	for (i = 0; i < num + 1; i++) {
		d[i] = new int[num + 1];
	}
	int **p = new int*[num + 1];
	for (i = 0; i < num + 1; i++) {
		p[i] = new int[num + 1];
	}
	for (i = 0; i < num + 1; i++) {
		for (j = 0; j < num + 1; j++) {
			w[i][j] = 999999999;
			w[i][i] = 0;
		}
	}
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		w[a][b] = c;
	}
	
	floyd2(num, w, d, p);
	/*cout << "w" << endl;
	for (i = 1; i <= num; i++) {
		for (j = 1; j <= num; j++) {
			cout << w[i][j] << " ";
		}
		cout << endl;
	}
	cout << "d" << endl;
	for (i = 1; i <= num; i++) {
		for (j = 1; j <= num; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
	cout << "p" << endl;
	for (i = 1; i <= num; i++) {
		for (j = 1; j <= num; j++) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}*/
	int count = 0;
	int zzz[2][100];
	for (;;) {
		cin >> i;
		if (i == 0)break;
		cin >> j;
		zzz[0][count] = i;
		zzz[1][count] = j;
		count++;
	}
	for (i = 0; i < count; i++) {
		a = zzz[0][i];
		b = zzz[1][i];
		if (d[a][b] == 999999999) {
			cout << "0" << endl;
		}
		else {
			cout << d[a][b] << " ";
			cout << a;
			path(p, a, b);
			cout << " " << b << endl;
		}
	}
}