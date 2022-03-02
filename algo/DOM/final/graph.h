#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
using std::cout;

#include "list.h"

struct line{
    int s;
    int e;
    int w;
};

void BFS(List<int> *lines, int N, int s){
    int *visit = new int[N];
    int *visited = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    for(int i=0; i<N; i++) visited[i] = -1;
    Queue<int> order;
    order.insert(s);
    visit[s] = 1;
    visited[s] = -1;
    while(!order.empty()){
        int curr = order.front();
        order.remove();

        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        for(int i=0; i<lines[curr].size(); i++){
            if(visit[lines[curr][i]]==0){
                order.insert(lines[curr][i]);
                visit[lines[curr][i]] = 1;
                visited[lines[curr][i]] = curr;
            }
        }
    }
}

void BFS(int **graph, int N, int s){
    int *visit = new int[N];
    int *visited = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    for(int i=0; i<N; i++) visited[i] = -1;
    Queue<int> order;
    order.insert(s);
    visit[s] = 1;
    visited[s] = -1;
    while(!order.empty()){
        int curr = order.front();
        order.remove();

        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        for(int i=0; i<N; i++){
            if(graph[curr][i]==1 && visit[i]==0){
                order.insert(i);
                visit[i] = 1;
                visited[i] = curr;
            }
        }
    }
}

void DFS(List<int> *lines, int N, int s){
    int *visit = new int[N];
    int *visited = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    for(int i=0; i<N; i++) visited[i] = -1;
    Stack<int> order;
    order.insert(s);
    visited[s] = -1;
    while(!order.empty()){
        int curr = order.top();
        order.remove();
        if(visit[curr]==1) continue;
        else visit[curr] = 1;
        
        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        for(int i=0; i<lines[curr].size(); i++){
            if(visit[lines[curr][i]]==0){
                order.insert(lines[curr][i]);
            }
        }
        visited[order.top()] = curr;
    }
}

void DFS(int **graph, int N, int s){
    int *visit = new int[N];
    int *visited = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    for(int i=0; i<N; i++) visited[i] = -1;
    Stack<int> order;
    order.insert(s);
    visited[s] = -1;
    while(!order.empty()){
        int curr = order.top();
        order.remove();
        if(visit[curr]==1) continue;
        else visit[curr] = 1;
        
        if(visited[curr]==-1) cout<<"Start Node : "<<curr<<"\n"; 
        else cout<<"line : "<<visited[curr]<<"-"<<curr<<"\n";
        for(int i=0; i<N; i++){
            if(graph[curr][i]==1 && visit[i]==0){
                order.insert(i);
            }
        }
        visited[order.top()] = curr;
    }
}

///////////////////////////////////////////////////////
template <class T>
void _swap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}   

void Kruskal(int **graph, int N){
    List<line> lines;
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(graph[i][j]!=0) lines.insert({i, j, graph[i][j]});
        }
    }

    //sorting by weight
    for(int i=0; i<lines.size()-1; i++){
        int min_idx=i;
        for(int j=i; j<lines.size(); j++){
            if(lines[j].w < lines[min_idx].w) min_idx=j;
        }
        if(min_idx != i) _swap(lines[i], lines[min_idx]);
    }

    //집합
    int *parent = new int[N];
    for(int i=0; i<N; i++) parent[i] = i;
    List<line> uni;
    for(int i=0; i<N; i++){
        line curr = lines[i];
        // parent가 동일 => cycle 생성
        if(parent[curr.s] != parent[curr.e]){
            parent[curr.s] = parent[curr.e];
            uni.insert(curr);
        }
    }
    for(int i=0; i<uni.size(); i++) cout<<"line : "<<uni[i].s<<"-"<<uni[i].e<<"/ weight : "<<uni[i].w<<"\n";
}

void Prim(int **graph, int N, int s){
    List<line> uni;
    
    int *visit = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    visit[s] = 1;

    while(uni.size() != N-1){
        int min_idx=-1;
        line min_line;
        for(int i=0; i<N; i++){
            if(visit[i] == 0) continue;
            for(int j=0; j<N; j++){
                if(graph[i][j] != 0 && visit[j] == 0){
                    if(min_idx==-1) {
                        min_line = {i, j, graph[i][j]};
                        min_idx=j;
                    } else {
                        if(graph[i][j] < min_line.w) {
                            min_line = {i, j, graph[i][j]};
                            min_idx=j;
                        }
                    }
                }
            }
        }
        visit[min_idx] = 1;
        uni.insert(min_line);
    }

    for(int i=0; i<uni.size(); i++) cout<<"line : "<<uni[i].s<<"-"<<uni[i].e<<"/ weight : "<<uni[i].w<<"\n";
}

///////////////////////////////////////////////////////
void Topological_sort(int **graph, int N){
    int *visit = new int[N];
    for(int i=0; i<N; i++) visit[i] = 0;
    List<int> order;
    while(order.size()!=N){
        for(int i=0; i<N; i++){
            if(visit[i]==1) continue;
            bool flag=false;
            for(int j=0; j<N; j++){
                if(graph[j][i]!=0){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                order.insert(i);
                visit[i]=1;
                for(int j=0; j<N; j++){
                    graph[i][j]=0;
                }
                break;
            }
        }
    }
    for(int i=0; i<order.size(); i++) cout<<order[i]<<" ";
    cout<<"\n";
}


#endif

    // int N, L;       //Node개수, Line 개수
    // cin>>N>>L;
    // List<int> *lines = new List<int>[N];
    // int **graph = new int*[N];
    // for(int i=0; i<N; i++) graph[i] = new int[N];    
    // for(int i=0; i<N; i++) 
    //     for(int j=0; j<N; j++)
    //         graph[i][j] = 0;
    // for(int i=0; i<L; i++) {
    //     int s, e;
    //     cin>>s>>e;
    //     lines[s].insert(e);
    //     lines[e].insert(s);
    //     graph[s][e] = 1;
    //     graph[e][s] = 1;
    // }
    // int s;
    // cin>>s;

    // BFS(lines, N, s);
    // BFS(graph, N, s);
    // DFS(lines, N, s);
    // DFS(graph, N, s);

///////////////////////////////////////////////////////////////
    // int N, L;       //Node개수, Line 개수
    // cin>>N>>L;
    // int **graph = new int*[N];
    // for(int i=0; i<N; i++) graph[i] = new int[N];    
    // for(int i=0; i<N; i++) 
    //     for(int j=0; j<N; j++)
    //         graph[i][j] = 0;
    // for(int i=0; i<L; i++) {
    //     int s, e, w;
    //     cin>>s>>e>>w;
    //     graph[s][e] = w;
    //     graph[e][s] = w;
    // }

    // Kruskal(graph, N);
    // Prim(graph, N, 1);
    
///////////////////////////////////////////////////////////////////
    // int N, L;       //Node개수, Line 개수
    // cin>>N>>L;
    // List<int> *lines = new List<int>[N];
    // int **graph = new int*[N];
    // for(int i=0; i<N; i++) graph[i] = new int[N];    
    // for(int i=0; i<N; i++) 
    //     for(int j=0; j<N; j++)
    //         graph[i][j] = 0;
    // for(int i=0; i<L; i++) {
    //     int s, e;
    //     cin>>s>>e;
    //     lines[s].insert(e);
    //     graph[s][e] = 1;
    // }

    // Topological_sort(graph, N);