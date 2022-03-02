#include<iostream>
using namespace std;

void shellsort(int a[],int n){
	int v,h,i,j;
	for(h=1;h<n;h=3*h+1){};
	for(;h>0;h=h/3){
		for(i=h+1;i<=n;i++){
			v=a[i];
			j=i;
			while(j>h && a[j-h]>v){
				a[j]=a[j-h];
				j=j-h;
			}
			a[j]=v;
		}
	}
}

int main(){
	int a[10]={0,6,1,7,4,8,2,9,10,11};
	shellsort(a,9);
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
}