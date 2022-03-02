#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b){
    int t=a;
    a=b;
    b=t;
}

void min_heapify(vector<int> &arr, int location){
    int p=location;
    while(true){
        if(p==1) break;
        if(arr[p] > arr[p/2]) break;
        swap(arr[p], arr[p/2]);
        p/=2;
    }
}

int min_pop(vector<int> &arr){
    int result = arr[1];

    int n = arr.size()-1;
	swap(arr[1], arr[n]);
	arr.pop_back();

	for(int i=1; i<n; i++) min_heapify(arr, i);

    return result;
}

int main(int argc, char const *argv[])
{
    vector<int> tunas;
    tunas.push_back(-1);
    while(true){
        int n;
        cin>>n;
        if(n==0) break;
        if(0<n && n<=20){
            for(int i=0; i<n; i++) cout<<min_pop(tunas)<<endl;
            continue;
        }
        if(n<20200101 || tunas.size()>100) continue;
        tunas.push_back(n);
        min_heapify(tunas, tunas.size()-1);
    }
   
    return 0;
}
