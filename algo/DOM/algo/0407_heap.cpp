#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b){
    int t=a;
    a=b;
    b=t;
}

void max_heapify(vector<int> &arr, int location){
    int p=location;
    while(true){
        if(p==1) break;
        if(arr[p] < arr[p/2]) break;
        swap(arr[p], arr[p/2]);
        p/=2;
    }
}

int max_pop(vector<int> &arr, int location){
    int result = arr[1];

	swap(arr[1], arr[location]);
	arr.pop_back();

	for(int i=2; i<location; i++) max_heapify(arr, i);

    return result;
}


int main(int argc, char const *argv[])
{
    int N;
    cin>>N;
    vector<int> alpha;    //max heap
    alpha.push_back(-1);
    for(int i=1; i<=N; i++) {
        int a;
        cin>>a;
        alpha.push_back(a);
        max_heapify(alpha, i);
    }
    for(int i=1; i<=N; i++) 
        cout<<alpha[i]<<" ";
    cout<<endl;
   
    return 0;
}
