#include <iostream>
#include <vector>
using namespace std;

void floyd(int n, int **W, int **D, int **P){
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            P[i][j] = 0;

    for(int i=0; i<=n; i++)
        for(int j=0; j<=n; j++)
            D[i][j] = W[i][j];

    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(i==j) continue;
                if(D[i][k] + D[k][j] < D[i][j]){
                    P[i][j]=k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
    
}

void path(int **P, int q, int r){
    if(P[q][r] != 0){
        path(P, q, P[q][r]);
        cout<<P[q][r]<<" ";
        path(P, P[q][r], r);
    }
}

int main(int argc, char **argv){
    int n, m;
    cin>>n>>m;
    int **W = new int*[n+1];
    for(int i=0; i<=n; i++) W[i] = new int[n+1];
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            if(i==j) {
                W[i][j]=0;
                continue;
            }
            W[i][j] = 1000000000;
        }
    }

    for(int i=0; i<m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        W[a][b] = w;
    }
    int **D = new int*[n+1];
    int **P = new int*[n+1];
    for(int i=0; i<=n; i++) {
        D[i] = new int[n+1];
        P[i] = new int[n+1];
    }
    floyd(n, W, D, P);

    // for(int i=0; i<=n; i++){
    //     for(int j=0; j<=n; j++){
    //         cout<<W[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=0; i<=n; i++){
    //     for(int j=0; j<=n; j++){
    //         cout<<D[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=0; i<=n; i++){
    //     for(int j=0; j<=n; j++){
    //         cout<<P[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    while(true){
        int s, e;
        cin>>s;
        if(s==0) break;
        cin>>e;
        if(D[s][e]==1000000000) {
            cout<<"0"<<endl;
            continue;
        }
        cout<<D[s][e]<<" ";
        cout<<s<<" ";
        path(P, s, e);
        cout<<e<<" ";
        cout<<endl;
    }
    
    return 0;
}