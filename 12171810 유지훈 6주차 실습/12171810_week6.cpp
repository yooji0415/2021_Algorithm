#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

void rxSort(int *data, int size, int p, int k){
	int *counts;
	int *temp;
	int index, pval, i, j, n;
	if((counts = (int*) malloc(k * sizeof(int))) == NULL) return;
	if((temp = (int*) malloc(size * sizeof(int))) == NULL) return;
	for(n=0; n<p;n++){
		for(i=0;i<k;i++){
			counts[i] = 0;
		}
		pval = (int)pow((double)k, (double)n);
		for(j=0;j<size;j++){
			index = (int)(data[j]/pval)%k;
			counts[index] = counts[index] + 1;
		}
		for(i=1;i<k;i++){
			counts[i] = counts[i] + counts[i-1];
		}
		for(j=size-1;j>=0;j--){
			index = (int)(data[j]/pval) % k;
			temp[counts[index]-1] = data[j];
			counts[index] = counts[index] -1;
		}
		memcpy(data, temp, size * sizeof(int));
	}
}

int main(){
	int arr[8] = {170, 45, 75, 90, 2, 24, 802, 66};
	cout<<"정렬 전 어레이 : ";
	for(int i = 0; i<8; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	rxSort(arr, 8, 3, 10);
	cout<<"정렬 후 어레이 : ";
	for(int i = 0; i<8; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl<<"12171810 정보통신공학과 유지훈"<<endl;
	return 0;
}