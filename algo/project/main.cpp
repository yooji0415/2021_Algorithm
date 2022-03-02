#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
using std::cout;
using std::cin;
using std::vector;
using std::stack;

struct pair{
    int level;
    int p;
};

// int cnt=0;
// void visit(int *visited, int n, int level) {
//     if(level==n) {
// 		cnt++;
// 		return;
// 	}
//     for(int i=0; i<n; i++) {
// 		bool flag=true;
// 		for(int j=0; j<level; j++) {
// 			if(visited[j]==i || level-j==abs(i-visited[j]) ) {
// 				flag=false;
// 				break;
// 			}
// 		}
// 		if(flag) {
// 			visited[level] = i;
// 			visit(visited, n, level+1);
// 		}
// 	}
// }

// int cnt=0;
// void visit(int n) {
//     int *visited = new int[n];
//     stack<pair> order;
//     for(int i=0; i<n; i++) order.push({0, i});

//     while(!order.empty()){
//         pair curr = order.top();
//         order.pop();
//         visited[curr.level] = curr.p;
//         int level = curr.level+1;
//         if(level==n){
//             cnt++;
//             continue;
//         }
//         for(int i=0; i<n; i++) {
//             bool flag=true;
//             for(int j=0; j<level; j++) {
//                 if(visited[j]==i || level-j==abs(i-visited[j]) ) {
//                     flag=false;
//                     break;
//                 }
//             }
//             if(flag) {
//                 order.push({level, i});
//             }
//         }
//     }
// }

int* visit(int n) {
    int *visited = new int[n];          // 체스판에서 i행, visited[i]열에 퀸을 놓는 다는 것을 의미
    stack<pair> order;    
    // 맨 윗 줄을 order에 넣어준다.
    for(int i=0; i<n; i++) order.push({0, i});

    while(!order.empty()){
        pair curr = order.top();            // 현재 방문 위치
        order.pop();
        visited[curr.level] = curr.p;       // 방문 한 위치 저장
        int level = curr.level+1;
        if(level==n){                       // 체스판의 모든 행을 방문했음을 의미
            return visited;                 // 퀸의 위치를 return
        }
        for(int i=0; i<n; i++) {            // level행의 모든 열 방문
            bool flag=true;                 // 위치 방문 가능 여부
            // level위쪽의 행에 놓여있는 퀸의 위치에 영향을 받음
            for(int j=0; j<level; j++) { 
                // 세로방향 체크 || 대각선방향 체크
                if(visited[j]==i || level-j==abs(i-visited[j]) ) {
                    flag=false;
                    break;
                }
            }
            if(flag) {
                order.push({level, i});
            }
        }
    }
}

int main(int argc, char **argv){
    int n;
    cin>>n;

    int *visited = new int[n];
    visited = visit(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(j==visited[i]) cout<<"■ ";
            else cout<<"□ ";
        }
        cout<<"\n";
    }


    // visit(n);
    // int *visited = new int[n];
    // visit(visited, n, 0);
    // cout<<cnt<<"\n";

    return 0;
}
