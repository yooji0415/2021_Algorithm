#include<iostream>

using namespace std;


void max_heapify(int* arr,int n,int heap_size){
	int left=2*n; // index start 1, left childnode 2,4,6,8.... 2*n
	int right=2*n+1; // also, right childnode 3,5,7,9.... 2*n+1;
	int largest;    // need swap childnode, parentnode

	if((left<=heap_size) && (arr[left]>arr[n])) // left<= heap_size and left childnode > parentnode
		largest = left; // then largest is left
	else
		largest = n;  // it's not largest is parent node

	if((right<=heap_size)&&(arr[right]>arr[largest])) // also compare rightchilde
		largest = right;

	if(largest != n){                          // largest is not n
		int temp = arr[n];                     // then, swap child and parent node
		arr[n] = arr[largest];
		arr[largest] = temp;
		max_heapify(arr,largest,heap_size);   // replay heapify because parent node compare up parentnode
	}
}

void build_max_heap(int* arr,int heap_size){    // max_heap build
	for(int i=heap_size/2; i>=1; i--){         
		max_heapify(arr,i,heap_size);            //use max_heapify
	}
}
void heap_sort(int *arr,int heap_size){ 
	build_max_heap(arr,heap_size);    //
	for(int i=heap_size;i>=2;i--){ 
		int temp=arr[1];             // swap arr[1] temp
		arr[1]=arr[i];               
		arr[i]=temp;
		heap_size--;                // node out, then heap_size -1

		max_heapify(arr,1,heap_size); //replay max_heapify
	} 

	
}
int main(){
	int size,a; // size is array size, a is input in array
	cin>>size; // array of size input
	int heap_size = size; //heap_size same size
	int* arr= new int[size+1]; // //dynamic allocation size +1 because index start 1.

	for(int i=1;i<=size;i++){ //input array
		cin>> a;
		arr[i]=a;
	}
	heap_sort(arr,heap_size); // start heap sort

	for(int i=1;i<=size;i++)
		cout<<arr[i]<<endl; // output array

	delete []arr; //delete dynamic allocation
	return 0;
}