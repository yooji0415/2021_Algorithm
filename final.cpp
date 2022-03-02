#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct point{
    int x;
    int y;
    int z;
};

int cnt = 0;

int R, N;
queue<point> order;
int visit[100][100][100] = {0, };
int map[100][100][100] = {0, };

void bfs(){
    while (!order.empty()) {
        point p = order.front();
        order.pop();

        visit[p.z][p.y][p.x] = 1;

        int sz=(p.z<R)?0:p.z-R;
        int ez=(p.z+R+1>N)?N:p.z+R+1;
        int sy=(p.y<R)?0:p.y-R;
        int ey=(p.y+R+1>N)?N:p.y+R+1;
        int sx=(p.x<R)?0:p.x-R;
        int ex=(p.x+R+1>N)?N:p.x+R+1;
        for (int i=sz; i<ez; i++) {
            for (int j=sy; j<ey; j++) {
                for (int k=sx; k<ex; k++) {
                    if (visit[i][j][k] == 0 && map[i][j][k] == 1) {
                        visit[i][j][k] = 1;
                        point temp = {k,j,i};
                        order.push(temp);
                        cnt++;
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    cin>>R>>N;
    
    int *tk = new int [N*N*N]; // 그룹을 저장하는 어레이

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                cin>>map[i][j][k];
            }
        }
    }


    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                if (map[i][j][k] == 1 && visit[i][j][k] == 0) {
                    cnt = 0;
                    visit[i][j][k] = 1;
                    point temp = {k,j,i};
                    order.push(temp);
                    bfs();
                    tk[cnt]++;
                }
            }
        }
    }
    cout<<tk[0]<<endl<<endl;

    /*for (int i = 0; i < 10; i++)
    {
        cout<<"tk["<<i<<"] : "<<tk[i]<<" ";
    }*/
    return 0;
}
