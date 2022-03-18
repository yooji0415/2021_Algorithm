#include<iostream>
using namespace std;
int heap_size=0;
void min_heapify(int* arr,int n){   //min_heapify
	int left=2*n; 
	int right=2*n+1; 
	int min;    

	if((left<=heap_size) && (arr[left]<arr[n])) 
		min = left; 
	else
		min = n; 

	if((right<=heap_size)&&(arr[right]<arr[min])) 
		min = right;

	if(min != n){                       
		int temp = arr[n];                   
		arr[n] = arr[min];
		arr[min] = temp;
		min_heapify(arr,min);  
	}
}
void build_min_heap(int* arr){    //build_min_heap
	for(int i=heap_size/2; i>=1; i--){         
		min_heapify(arr,i);            
	}
}
int popMin(int* arr) { //output arr[1]
      int v=arr[1];
      arr[1]=arr[heap_size];
      heap_size--;
      build_min_heap(arr); 
      return v;
}
void push(int *arr,int num){//input arr[1]
	heap_size++;
	arr[heap_size]=num;
}
int main(){
	int fish[101];//make fish array[101]
	int num;
	for(;;){
		cin>>num;
		if(num==0){  // 0 is stop
			return 0; //end main
		}else if(num>=1 && num<=20){  //1~20 pop fish
			for(int i=1;i<=num;i++){
				cout<<popMin(fish)<<endl; // print pop
			}
		}else if(num>=20200101){  // input year
			push(fish,num);   //push year
			build_min_heap(fish); //restart min_heap
		}
	}

}
