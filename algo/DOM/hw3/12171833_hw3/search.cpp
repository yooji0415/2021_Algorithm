#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int main(int argc, char const *argv[])
{
    int M, N;       //Node개수, Line 개수
    cin>>M>>N;
    vector<int> *lines = new vector<int>[M];
    int **graph = new int*[M];
    for(int i=0; i<M; i++) graph[i] = new int[M];    
    for(int i=0; i<M; i++) 
        for(int j=0; j<M; j++)
            graph[i][j] = 0;
    for(int i=0; i<N; i++) {
        int s, e;
        cin>>s>>e;
        lines[s].push_back(e);
        lines[e].push_back(s);
        graph[s][e] = 1;
        graph[e][s] = 1;
    }
    int s;
    // cout<<"Start node : ";
    cin>>s;
    
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            cout<<graph[i][j]<<" ";
        }
        cout<<"\n";
    }

    cout<<"========BFS Test========\n";
    //12171833 이정우
    int *visit = new int[M];
    int *visited = new int[M];
    for(int i=0; i<M; i++) visit[i] = 0;
    for(int i=0; i<M; i++) visited[i] = -1;
    queue<int> order;
    order.push(s);
    visit[s] = 1;
    visited[s] = -1;
    while(!order.empty()){
        int curr = order.front();
        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        order.pop();
        for(int i=0; i<lines[curr].size(); i++){
            if(visit[lines[curr].at(i)]==0){
                order.push(lines[curr].at(i));
                visit[lines[curr].at(i)] = 1;
                visited[lines[curr].at(i)] = curr;
            }
        }
    }

    cout<<"========DFS Test========\n";
    //12171833 이정우
    for(int i=0; i<M; i++) visit[i] = 0;
    for(int i=0; i<M; i++) visited[i] = -1;
    stack<int> dfs_order;
    dfs_order.push(s);
    visit[s] = 1;
    visited[s] = -1;
    while(!dfs_order.empty()){
        int curr = dfs_order.top();
        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        dfs_order.pop();
        for(int i=0; i<lines[curr].size(); i++){
            if(visit[lines[curr].at(i)]==0){
                dfs_order.push(lines[curr].at(i));
                visit[lines[curr].at(i)] = 1;
                visited[lines[curr].at(i)] = curr;
            }
        }
    }
    cout<<"\n";

    return 0;
}
