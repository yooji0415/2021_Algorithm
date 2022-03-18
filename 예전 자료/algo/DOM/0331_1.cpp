#include <iostream>
#include <string>
using namespace std;

// void swap(int &a, int &b){
//     int t=a;
//     a=b;
//     b=t;
// }
// void swap2(string &a, string &b){
//     string t=a;
//     a=b;
//     b=t;
// }

// void sort(int *arr, string *arr2, int n){
//     for(int i=0; i<n-1; i++){
//         int si=i;
//         for(int j=i+1; j<n; j++){
//             if(arr[j] < arr[si])
//                 si=j;
//         }
//         swap(arr[i], arr[si]);
//         swap2(arr2[i], arr2[si]);
//     }
// }

void sort(int *arr, string *arr2, int n){
    for(int i=1; i<n; i++){
        int x = arr[i];
        string sx = arr2[i];
        int j=i-1;
        while(j > -1 && arr[j] > x){
            arr[j+1] = arr[j];
            arr2[j+1] = arr2[j];
            j--;
        }
        arr[j+1] = x;
        arr2[j+1] = sx;
    }
}

int main()
{
    int N;
    cin>>N;
    int *heights = new int[N];
    string *names = new string[N];
    for(int i=0; i<N; i++){
        cin>>heights[i]>>names[i];
    }
    sort(heights, names, N);
    for(int i=0; i<N; i++){
        cout<<heights[i]<<" "<<names[i]<<endl;
    }
    return 0;
}