#include <iostream>
#include <stdio.h>
#include <ctime>
using namespace std;

void maxHeapify(int arr[], int h, int m){ //가장 큰수를 위로 올리는 함수
    int v = arr[h]; // 루트의 값을 받아온다
    int j = 0; // 비교를 위한 변수 생성
    for(j=2*h; j<=m; j=j*2){ // 루트로 부터 m의 위치까지 자식들을 확인해준다
        if(j<m && arr[j]<arr[j+1]) j++; // 왼쪽 자식과 오른쪽 자식을 비교한다
        if(v>=arr[j]) break; // 만일 루트가 해당 자식보다 크면 중복을 멈춘다
        else arr[j/2] = arr[j]; // 아닐경우 부모와 값을 바꿔준다
    }
    arr[j/2] = v; // 찾아낸 위치에 기존 루트값을 넣어준다
}

void minHeapSort(int arr[], int n){
    int temp; // 스왑을 위한 변수 생성
    for(int i = n/2; i>=1; i--){ // sort전 heapify로 정리를 한번 해준다
        maxHeapify(arr,i,n);
    }
    for(int i = n-1; i>=1; i--){ // 가장 큰수를 뒤로 이동시키고
        // 해당 칸을 제외시키고 다시 가장 큰수를 위로 올린다
        // 이렇게 하면 맨 뒷 칸에서 부터 가장 큰수부터 차례대로 정렬이 된다
        temp = arr[1];
        arr[1] = arr[i+1];
        arr[i+1] = temp;
        maxHeapify(arr,1,i);
    }
}

void minHeapify(int arr[], int h, int m){ // maxHeapify의 반대로 
    // 가장 작은 수를 위로 올려준다 
    int v = arr[h];
    int j = 0;
    for(j=2*h; j<=m; j=j*2){
        if(j<m && arr[j]>arr[j+1]) j++; // 여기 부분에서 
        // 왼쪽 자식과 오른쪽 자식중 더 작은 위치를 선정하도록 만들어주었다
        if(v<=arr[j]) break; // 여기 또한 루트가 더 작을 때 멈추도록 설정해 주었다
        else arr[j/2] = arr[j];
    }
    arr[j/2] = v;
}

void maxHeapSort(int arr[], int n){ // 여기부분은 위의 minHeapSort와 동일한 코드이다
    int temp;
    for(int i = n/2; i>=1; i--){
        minHeapify(arr,i,n);
    }
    for(int i = n-1; i>=1; i--){
        temp = arr[1];
        arr[1] = arr[i+1];
        arr[i+1] = temp;
        minHeapify(arr,1,i);
    }
}

void checkSort1(int a[], int n){ // minheap 확인용
    int i, result;
    result = 1;

    for(i=0; i<n-1; i++){
        if(a[i]>a[i+1]){
            result = 0;
        }
        if(!result) {
            break;
        }
    }
    if(result==1){
        cout<<"Sorting complete!"<<endl;
    } else {
        cout<<"Error during sorting..."<<endl;
    }

}

void checkSort2(int a[], int n){ // maxheap 확인용
    int i, result;
    result = 1;

    for(i=1; i<n-1; i++){
        if(a[i]<a[i+1]){
            result = 0;
        }
        if(!result) {
            break;
        }
    }
    if(result==1){
        cout<<"Sorting complete!"<<endl;
    } else {
        cout<<"Error during sorting..."<<endl;
    }

}

int main(){
    int test1[11] = {0,6,2,8,1,3,9,4,5,10,7}; // 정렬 확인을 위한 어레이
    int test2[11] = {0,6,2,8,1,3,9,4,5,10,7};
    int arr[1000001] = {};
    clock_t start, end; // 시간측정을 위한 변수 생성한다
    srand(time(NULL)); // 난수생성을 위한 srand 설정을 해준다

    minHeapSort(test1,10); // 각 정렬의 결과를 확인한다.
    cout<<"MinHeap 정렬 결과 : "; 
    for(int i=0; i<11; i++){
        cout<<test1[i]<<" ";
    }
    cout<<endl;

    maxHeapSort(test2,10);
    cout<<"MaxHeap 정렬 결과 : ";
    for(int i=0; i<11; i++){
        cout<<test2[i]<<" ";
    }
    cout<<endl; 

    for(int i=0; i<100001; i++){ // 10만개의 입력 난수 생성
        if(i==0) arr[i]=0;
        else arr[i] = rand()%100000;
    }
    start = clock();
    minHeapSort(arr,100000); // 시간을 측정해본다
    end = clock();
    cout<<"minHeap정렬 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.
    checkSort1(arr, 100001);
    
    for(int i=0; i<100001; i++){ // 10만개의 입력 난수 재생성
        if(i==0) arr[i]=0;
        else arr[i] = rand()%100000;
    }
    start = clock();
    maxHeapSort(arr,100000); // 시간을 측정해본다
    end = clock();
    cout<<"maxHeap정렬 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.
    checkSort2(arr, 100001);

    cout<<"12171810 정보통신공학과 유지훈"<<endl;

    return 0;
}