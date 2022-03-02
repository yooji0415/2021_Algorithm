#include<iostream>
#include<queue>
using namespace std;
int map[101][101][101];
bool visited[101][101][101];
int num = 0;
int r, n;
void BFS(int i, int j, int k) {
	queue<int> q;
	q.push(i);
	q.push(j);
	q.push(k);
	int x, y, z;
	int dx, dy, dz;
	while (!q.empty()) {
		x = q.front();
		q.pop();
		y = q.front();
		q.pop();
		z = q.front();
		q.pop();
		x - r < 0 ? dx = 0 : dx = x - r;
		y - r < 0 ? dy = 0 : dy = y - r;
		z - r < 0 ? dz = 0 : dz = z - r;

		for (int a = dx; a < n && a <= x + r; a++) {
			for (int b = dy; b < n && b <= y + r; b++) {
				for (int c = dz; c < n && c <= z + r; c++) {
					if (map[a][b][c] == 1 && visited[a][b][c] == false) {
						visited[a][b][c] = true;
						q.push(a);
						q.push(b);
						q.push(c);
						
					}
				}
			}
		}
	}
	num++;
}

int main() {
	int i, j, k;
	int star;
	cin >> r >> n;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				cin >> star;
				map[i][j][k] = star;
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				visited[i][j][k] = false;
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				if (map[i][j][k] == 1 && visited[i][j][k] == false)BFS(i, j, k);
			}
		}
	}
	cout << num;
	return 0;
}