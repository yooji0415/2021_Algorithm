#include <iostream>
#include <vector>
using namespace std;

bool check_cycle(int **weight, int M, int s, int n){
    for(int i=0; i<M; i++){
        if(weight[n][i]!=0 && weight[n][i]!=999999999){
            if(s==i) return true;
            cout<<s<<" "<<n<<" "<<i<<"\n";
            if(check_cycle(weight, M, i, i)) return true;
            if(check_cycle(weight, M, s, i)) return true;
        }
    }
    cout<<n<<"f"<<"\n";
    return false;
}

int main(int argc, char const *argv[])
{
    int M, N;       //Node개수, Line 개수
    cin>>M>>N;
    int **weight = new int*[M];
    for(int i=0; i<M; i++) weight[i] = new int[M];
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            if(i==j) weight[i][j] = 0;
            else weight[i][j] = 999999999;
        }
    }
    for(int i=0; i<N; i++) {
        int s, e, w;
        cin>>s>>e>>w;
        weight[s][e] = w;
        // lines[s].push_back(e);
    }
    int s;
    cin>>s;

    // int **copy = new int*[M];
    // for(int i=0; i<M; i++) copy[i] = new int[M];
    // for(int i=0; i<M; i++) 
    //     for(int j=0; j<M; j++) 
    //         copy[i][j] = weight[i][j];
    // cout<<check_cycle(weight, M, 0, 0)<<"\n";

    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            if(weight[i][j]==999999999) cout<<"  ∞ ";
            else printf("%3d ", weight[i][j]);
        }
        cout<<"\n";
    }

    int *Dist = new int[M];
    for(int i=0; i<M; i++) Dist[i] = weight[s][i];
    //12171833 이정우
    for(int k=1; k<M-1; k++) {
        for(int u=0; u<M; u++){
            if(u!=s){
                for(int i=0; i<M; i++) {
                    if(Dist[i]==999999999 || weight[i][u]==999999999) continue;
                    if (Dist[u] > Dist[i]+weight[i][u])
                        Dist[u] = Dist[i]+weight[i][u];
                }
            }
        }
    }
    
    bool check_cycle = false;
    for(int u=0; u<M; u++){
        if(u!=s){
            for(int i=0; i<M; i++) {
                if(Dist[i]==999999999 || weight[i][u]==999999999) continue;
                if (Dist[u] > Dist[i]+weight[i][u]){
                    check_cycle = true;
                    break;
                }
            }
            if(check_cycle) break;
        }
    }
    
    cout<<"Start Node : "<<s<<"\n"; 
    cout<<"Distance : ";
    if(check_cycle) cout<<"It has negative cycle";
    else {
        for(int i=0; i<M; i++) {
            if(Dist[i]==999999999) cout<<"∞ ";
            else cout<<Dist[i]<<" ";
        }
    }
    cout<<"\n";

    return 0;
}
