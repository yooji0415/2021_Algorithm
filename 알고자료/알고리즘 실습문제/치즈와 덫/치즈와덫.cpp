#include<iostream>
#include<string>
using namespace std;
int N, M;
void input(int **map, int **cheeze) { 
	int i, j;
	int input;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			cin >> input;
			map[i][j] = input;
			cheeze[i][j] = 0;
		}
	}
}
void cheezenum(int **map, int **cheeze) {
	int i, j;
	for (i = N - 2; i >= 0; i--) {
		if (map[i][0] == 1) {
			cheeze[i][0] = cheeze[i + 1][0] + 1;
		}
		else if (map[i][0] == 0) {
			cheeze[i][0] = cheeze[i + 1][0];
		}
		else if (map[i][0] == 2) {
			break;
		}
	}
	for (j = 1; j < M; j++) {
		if (map[N-1][j] == 1) {
			cheeze[N-1][j] = cheeze[N-1][j - 1] + 1;
		}
		else if (map[N-1][j] == 0) {
			cheeze[N-1][j] = cheeze[N-1][j - 1];
		}
		else if (map[N-1][j] == 2) {
			break;
		}
	}
	for (i = N - 2; i >= 0; i--) {
		for (j = 1; j < M; j++) {
			if (map[i][j] == 1) {
				if (cheeze[i + 1][j] >= cheeze[i][j - 1]) {
					cheeze[i][j] = cheeze[i + 1][j] + 1;
				}
				else {
					cheeze[i][j] = cheeze[i][j - 1] + 1;
				}
			}
			else if (map[i][j] == 0) {
				if (cheeze[i + 1][j] >= cheeze[i][j - 1]) {
					cheeze[i][j] = cheeze[i + 1][j];
				}
				else {
					cheeze[i][j] = cheeze[i][j - 1];
				}
			}
			else if (map[i][j] == 2) {
				cheeze[i][j] = -1;
			}
		}
	}
}
int main() {
	int i, j;
	cin >> N >> M;
	int **map = new int*[N];
	for (i = 0; i < M; i++) {
		map[i] = new int[M];
	}
	int **cheeze = new int*[N];
	for (i = 0; i < N; i++) {
		cheeze[i] = new int[M];
	}
	input(map, cheeze);
	cheezenum(map, cheeze);
	cout << cheeze[0][M - 1];
}

//cheese (i,j) = if(map==1){max { cheese(i+1,j) , cheese(i,j-1)}+1 } else if(map==0){max{ cheese(i+1,j) , cheese(i,j-1)}} else if(map==2){ cheese(i,j)=-1}