#include <iostream>
using namespace std;

#define TRUE 1;
#define FALSE 0;
void swap(int a[],int i,int j){
	int t=a[i];a[i]=a[j];a[j]=t;
}
//void selectionsort(int a[],int n){
//	int i,j,min;
//	for(i=0;i<n;i++){
//		min=i;
//		for(j=i+1;j<n; j++)
//			if(a[j]<a[min])min=j;
//		swap(a,min,i);
//	}
//}
//void insertionsort(int a[],int n){
//	int i,j,v;
//	for(i=2;i<n;i++){
//		v=a[i];j=i;
//		while(a[j-1]>v){
//			a[j]=a[j-1];j--;
//		}
//		a[j]=v;
//	}
//}
//void quicksort(int a[], int l, int r){
//	int i,j,v;
//	if(r>1){
//		v=a[r];i=l-1;j=r;
//	for(;;){
//		if(a[i]<v && i<j)i++;
//		if(a[j]>v && i<j)j--;
//		if(i>=j)break;
//		swap(a,i,j);
//	}
//	swap(a,i,r);
//	quicksort(a,l,i-1);
//	quicksort(a,i+1,r);
//	}
//}
void mergesort(int a[],int i,int r){
	int i,j,k,m;
	if(r>1){
		m=(r+1)/2;
		mergesort(a,l,m);
		mergesort(a,m+1,r);
		for(i=m+1;i>l;i--)b[i-1]=a[i-1];
		for(j=m;j<r;j++)b[r+m-j]=a[j+1];
		for(k=1;k<=r;k++)
			a[k]=(b[i]<b[j])?b[++]:b[j--];
	}
}
void checksort(int a[],int n){
	int i,sorted;
	sorted = TRUE;
	for(i=1;i<n;i++){
		if(a[i]>a[i+1])sorted = FALSE;
		if(!sorted)break;
	}
	if(sorted)printf("정렬완료\n");
	else printf("정렬 오류 발생\n");
}
int main(){
	int b[11];
	int i;
	int a[11]={-1,-5,4,2,1,9,0,3,6,8,7};
	/*selectionsort(a,10);*/
	/*insertionsort(a,10);*/
	mergesort(a,1,10)
	checksort(a,10);
	for(i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
}
