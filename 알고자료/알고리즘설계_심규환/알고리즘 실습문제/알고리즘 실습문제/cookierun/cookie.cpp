#include<iostream>
#include<vector>
int INF = 99999;
using namespace std;
int stage, line, finish;

void Bellman(int *dist,int **weight) {
	int i, j, k;
	dist[0] = 0;
	for (k = 2; k < stage - 1; k++) {
		for (i = 0; i < stage; i++) {
			for (j = 0; j < stage; j++) {
				if (i != j && weight[i][j] != INF) {
					if (dist[j] > dist[i] + weight[i][j]) {
						dist[j] = dist[i] + weight[i][j];
					}
				}
			}
		}
	}
	for (i = 0; i < stage; i++) {
		if (dist[i] <= finish) {
			cout << i << " ";
		}
	}
}

int main() {
	int i,j,v1,v2,w;
	cin >> stage >> line;
	int *dist = new int[stage];
	int **weight = new int *[stage];
	for (i = 0; i < stage; i++) {
		weight[i] = new int[stage];
	}
	for (i = 0; i < stage; i++) {
		for (j = 0; j < stage; j++) {
			weight[i][j] = INF;
			dist[i] = INF;
		}
	}
	for (i = 0; i < line; i++) {
		cin >> v1 >> v2 >> w;
		weight[v1][v2] = w;
	}
	cin >> finish;
	Bellman(dist, weight);
}