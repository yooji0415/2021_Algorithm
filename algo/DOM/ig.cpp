#include <iostream>
#include <queue>
using namespace std;

int board[100][100][100] = { 0, };
int visit[100][100][100] = { 0, };
int R, N;

struct point {
   int x;
   int y;
   int z;
};
queue<point> q;

void BFS() {
   point j;
   while (!q.empty()) {
      j = q.front();
      q.pop();

      visit[j.z][j.y][j.x] = 1;

      int s_x_b = j.x - R;
      int s_y_b = j.y - R;
      int s_z_b = j.z - R;

      if (s_x_b < 0) s_x_b = 0;
      if (s_y_b < 0) s_y_b = 0;
      if (s_z_b < 0) s_z_b = 0;


      int x_b = j.x + R + 1;
      int y_b = j.y + R + 1;
      int z_b = j.z + R + 1;
      if (x_b > N) x_b = N;
      if (y_b > N) y_b = N;
      if (z_b > N) z_b = N;

      for (int h = s_z_b; h < z_b; h++) {
         for (int i = s_y_b; i < y_b; i++) {
            for (int k = s_x_b; k < x_b; k++) {
               if (visit[h][i][k] == 0 && board[h][i][k] == 1) {
                  visit[h][i][k] = 1;
                  point p = { k,i,h };
                  q.push(p);
               }
            }
         }
      }
      /*for (int i = 0; i < 6; i++) {
      if (_y >= 0 && _y < N &&_x >= 0 && _x < N && _z >= 0 && _z < N) {
      if (visit[_z][_y][_x] == 0 && board[_x][_y][_z] == 1) {
      visit[_z][_y][_x] = 1;
      point p = { _x, _y, _z };
      q.push(p);
      }
      }
      }
      }*/
   }
}

void print() {
   for (int h = 0; h < N; h++) {
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            cout << visit[h][i][j] << " ";
         }
         cout << endl;
      }
      cout << endl;
   }
}

int main() {
   cin.tie(NULL);
   ios_base::sync_with_stdio(false);
   cin >> R >> N;
   bool flag = true;
   point p;
   for (int h = 0; h < N; h++) {
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            cin >> board[h][i][j];
         }
      }
   }

   int cnt = 0;
   for (int h = 0; h < N; h++) {
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            if (board[h][i][j] == 1 && visit[h][i][j] == 0) {
               p = { j, i,h };
               //cout << "i, j, h" << i << " " << j << " " << h << endl;
               q.push(p);
               visit[h][i][j] = 1;
               BFS();
               //print();
               cnt++;
            }
         }
      }
   }
   cout << cnt << endl;
}