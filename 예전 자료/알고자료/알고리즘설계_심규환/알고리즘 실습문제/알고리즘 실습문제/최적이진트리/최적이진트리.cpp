#include<iostream>
using namespace std;
struct number {
	int key;
	float numb;
};

float sum(float **map, int start, int end) {
	int i;
	float sumf = 0;
	for (i = start; i <= end; i++) {
		sumf = sumf + map[i][i];
	}
	return sumf;
}

void optimalBST(float **map, int **mapidx, int num, number *m) {
	int i, j, k, x;
	int minidx;
	float min, temp;
	for (x = 1; x < num; x++) {
		for (i = 1; i <= num - x; i++) {
			j = i + x;
			min = 99999999.9;
			for (k = i; k <= j; k++) {
				temp = map[i][k - 1] + map[k + 1][j] + sum(map, i, j);
				if (temp < min) {
					min = temp;
					minidx = k;
				}
			}
			map[i][j] = min;
			mapidx[i][j] = m[minidx].key;
		}
	}
}

int main() {
	int num, i, j;
	cin >> num;
	number *m = new number[num + 1];
	int *key = new int[num + 1];
	float **map = new float*[num + 2];
	for (i = 0; i <= num + 1; i++) {
		map[i] = new float[num + 2];
	}
	int **mapidx = new int*[num + 2];
	for (i = 0; i <= num + 1; i++) {
		mapidx[i] = new int[num + 2];
	}
	for (int i = 0; i <= num + 1; i++) {
		for (int j = 0; j <= num + 1; j++) {
			map[i][j] = 0;
			mapidx[i][j] = 0;
		}
	}
	for (i = 1; i <= num; i++) {
		cin >> m[i].key >> m[i].numb;
	}
	for (i = 1; i <= num; i++) {
		for (j = 1; j < num; j++) {
			if (m[j].key > m[j + 1].key) {
				number a = m[j + 1];
				m[j + 1] = m[j];
				m[j] = a;
			}
		}
	}
	for (i = 1; i <= num; i++) {
		map[i][i] = m[i].numb;
	}
	optimalBST(map, mapidx, num, m);
	
	cout << map[1][num] << " " << mapidx[1][num];

}