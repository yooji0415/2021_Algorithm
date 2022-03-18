#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct point{
    int x;
    int y;
    int z;
};

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
                        order.push({k, j, i});
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    cin>>R>>N;
    // int ***map = new int**[N];
    // for(int i=0; i<N; i++) map[i] = new int*[N];
    // for(int i=0; i<N; i++)
    //     for(int j=0; j<N; j++) 
    //         map[i][j] = new int[N];

    // int ***visit = new int**[N];
    // for(int i=0; i<N; i++) visit[i] = new int*[N];
    // for(int i=0; i<N; i++)
    //     for(int j=0; j<N; j++) 
    //         visit[i][j] = new int[N];
    // for(int i=0; i<N; i++)
    //     for(int j=0; j<N; j++)
    //         for(int k=0; k<N; k++)
    //             visit[i][j][k] = 0;
    // vector<point> points;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                cin>>map[i][j][k];
                // if(map[i][j][k]==1) {
                //     points.push_back({k, j, i});
                // }
            }
        }
    }

    int cnt = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                if (map[i][j][k] == 1 && visit[i][j][k] == 0) {
                    order.push({k, j, i});
                    visit[i][j][k] = 1;
                    bfs();
                    cnt++;
                }
            }
        }
    }
    // int cnt=0;
    // queue<point> order;
    // while(!points.empty()){
    //     order.push(points.front());
    //     points.erase(points.begin());
    //     while(!order.empty()){
    //         point p = order.front();
    //         order.pop();
    //         int i=0;
    //         while(true){
    //             if(i==points.size()) break;
    //             point tp = points[i];
    //             int dx=(p.x-tp.x>=0)?p.x-tp.x:tp.x-p.x;
    //             int dy=(p.y-tp.y>=0)?p.y-tp.y:tp.y-p.y;
    //             int dz=(p.z-tp.z>=0)?p.z-tp.z:tp.z-p.z;
    //             if(dx<=R && dy<=R && dz<=R){
    //                 order.push(tp);
    //                 points.erase(points.begin()+i);
    //                 i--;
    //             }
    //             i++;
    //         }
    //     }
    //     cnt++;
    // }
    cout<<cnt<<endl;

    return 0;
}
