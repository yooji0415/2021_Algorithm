#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "list.h"

void mot_quick_process(int *arr, int s, int e){
    int bs=s, be=e;
    int m = (s+e)/2;
    if(arr[s]>arr[m]) swap(arr[s], arr[m]);
    if(arr[m]>arr[e]) swap(arr[m], arr[e]);
    if(arr[s]>arr[m]) swap(arr[s], arr[m]);
    if(e-s<3) return ;

    int pivot = arr[m];
    swap(arr[bs+1], arr[m]);
    s++; e--;
    //12171833 이정우
    while(s<e){
        while(pivot<=arr[e] && s<e) e--;
        if(s>e) break;
        while(pivot>=arr[s] && s<e) s++;	
        if(s>e) break;
        swap(arr[s], arr[e]);
    }
    swap(arr[bs+1], arr[s]);
    if(bs<s) mot_quick_process(arr, bs, s-1);
    if(be>e) mot_quick_process(arr, s+1, be);
}

void mot_quick_sort(int *arr, int length){
    mot_quick_process(arr, 0, length-1);
}

int min(int a, int b) 
{ 
    return (a < b) ? a : b; 
} 

List<List<int>> idx;
int get_sum(int *diff, List<int>count, int i, int n, int cap, int w){
    if(cap==0) {
        if(w==0){
            idx.insert(count);
        }
        return 0;
    }
    else {
        for(int i=0; i<cap; i++){
            count.insert(i);
            get_sum(diff, count, i+1, n, cap-i, w + i*diff[i]);
        }
    }
}

List<List<int>> get_count(int *diff, int n, int capacity) { 
    List<List<int>> ret;
    for(int i=0; i<ret.size(); i++) {
        for(int j=0; j<ret[0].size(); j++) {
            cout<<ret[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(int argc, char const *argv[]){
    // int N;
    // cin>>N;
    // int *use_a = new int[N];
    // int *use_b = new int[N];
    // int *use_diff = new int[N];
    // int *weight = new int[N];
    // for(int i=0; i<N; i++) weight[i] = 0;
    // for(int i=0; i<N; i++){
    //     int a, b;
    //     cin>>a>>b;
    //     use_a[i] = a;
    //     use_b[i] = b;
    //     use_diff[i] = a-b;
    // }
    // bool enable_flag=true;
    // int mi=-1;
    // for(int i=0; i<N; i++){
    //     if(use_diff[0]<0) {
    //         if(mi==-1) mi=0;
    //         if(mi==1){
    //             enable_flag = false;
    //             break;
    //         }
    //     } else if(use_diff[0]<0) {
    //         if(mi==-1) mi=1;
    //         if(mi==0){
    //             enable_flag = false;
    //             break;
    //         }
    //     }
    // }
    // if(!enable_flag) cout<<"-1\n";


    // get_count(use_diff, N, 3);


    return 0;
}