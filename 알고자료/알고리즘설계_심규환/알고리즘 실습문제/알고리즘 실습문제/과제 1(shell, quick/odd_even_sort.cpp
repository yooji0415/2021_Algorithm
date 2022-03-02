#include<iostream>
using namespace std;
void swap(int a[],int i,int j){
	int term=a[i];
	a[i]=a[j];
	a[j]=term;
}

void odd_even(int a[],int size){
	int i,j;
	for(i=0;i<size/2;i++){
		for(j=0;j<size/2;j++){
			if(a[2*j]>a[2*j+1]){
				swap(a,2*j,2*j+1);
			}
		}
		for(j=1;j<size/2;j++){
			if(a[2*j-1]>a[2*j]){
				swap(a,2*j-1,2*j);
			}
		}
	}
}

int main(){
	int a[10]={5,6,4,8,7,1,2,9,0,10};
	odd_even(a,10);
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}