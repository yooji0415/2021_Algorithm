#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

using namespace std;

void path(int index[6][6], int q, int r){
    if(index[q][r] != 0){
        path(index, q, index[q][r]);
        cout<<"v"<<index[q][r]<<" -> ";
        path(index, index[q][r], r);
    }
}

void floyd(int n, int arr[6][6], int index[6][6]){
    int i, j, k;
    int minNum = 0;
    for(k=1; k<=n; k++){
        for(i=1; i<=n; i++){
            for(j=1; j<=n; j++){
                if(arr[i][j] > arr[i][k] + arr[k][j]){
                    minNum = arr[i][k] + arr[k][j];
                    index[i][j] = k;
                } 
                else minNum = arr[i][j];
                arr[i][j] = minNum;
            }
        }
    }
    cout<<"각 정점들 사이의 최단거리"<<endl;
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++){
            cout<<setw(5)<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"최단경로"<<endl;
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++){
            cout<<setw(5)<<index[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<" shortest path(2, 5) is v2 ->";
    path(index, 2, 5);
    cout<<"v5"<<endl;
    cout<<" shortest path(5, 3) is v5 ->";
    path(index, 5, 3);
    cout<<"v3"<<endl;
    cout<<" shortest path(1, 3) is v1 ->";
    path(index, 1, 3);
    cout<<"v3"<<endl;
}

int main(){
    int w[6][6] = {{0,1,2,3,4,5},{1,0,1,100,1,5},{2,9,0,3,2,100},
                    {3,100,100,0,4,100},{4,100,100,2,0,3},{5,3,100,100,100,0}};
    int index[6][6] = {0};
    cout<<"w array"<<endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout<<setw(5)<<w[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    floyd(5,w,index);
    cout<<"12171810 정보통신공학과 유지훈"<<endl;
    return 0;
}