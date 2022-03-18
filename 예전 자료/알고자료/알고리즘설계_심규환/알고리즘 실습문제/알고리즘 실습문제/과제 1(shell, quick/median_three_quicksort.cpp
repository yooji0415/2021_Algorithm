#include<iostream>
using namespace std;
void swap(int a[],int l,int r){
	int term=a[l];
	a[l]=a[r];
	a[r]=term;
}

int median_three(int a[],int left,int right){ // find mid
	int mid=(left+right)/2;

	if(a[left]>a[mid])
		swap(a,left,mid);
	if(a[left]>a[right])
		swap(a,left,right);
	if(a[mid]>a[right])
		swap(a,mid,right);
	return mid;
}
void median_three_quicksort(int a[],int left, int right){
	int i,j,pivot,mid;
	
	if(right-left>1){
		mid=median_three(a,left,right); // find mid
		swap(a,mid,right-1);   // swap right-1, mid
		pivot=a[right-1];i=left;j=right-1; //pivot is mid
		for(;;){
			while(a[++i]<pivot);  //a[i]>pivot stop
			while(a[--j]>pivot);  //a[j]<pivot stop
			if(i>=j)break;          
				swap(a,i,j);
		}
		swap(a,i,right-1);      
		median_three_quicksort(a,left,i-1);
		median_three_quicksort(a,i+1,right);
	}
	else if(a[left]>a[right])swap(a,left,right);
}

int main(){
	int a[7]={5,3,4,6,1,2,7};
	median_three_quicksort(a,0,6);
	for(int i=0;i<7;i++){
		cout<<a[i]<<" ";
	}
}

		