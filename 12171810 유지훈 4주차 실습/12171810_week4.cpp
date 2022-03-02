#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void swap(int *arr, int a, int b){ // 입력위치의 값을 바꿔주는 swap 함수
    int temp = 0;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void QuickSort(int arr[], int l, int r){ //QuickSort 함수
    int m, v, i, j; // 필요한 변수 선언
    if(r - l > 1){ // 쪼개진 크기가 1칸~2칸일 경우를 체크
        m = (l+r)/2;
        if(arr[l]>arr[m]) swap(arr,l,m); // 앞과 중간의 크기비교
        if(arr[l]>arr[r]) swap(arr,l,r); // 앞과 끝의 크기비교
        if(arr[m]>arr[r]) swap(arr,m,r); // 중간과 끝의 크기비교
        swap(arr,m,r-1); // 중간값을 옮겨준다
        v = arr[r-1]; // 피봇의 크기를 알려준다
        i = l; // 앞부터 시작되는 포인트
        j = r-1; // 뒤부터 시작되는 포인트
        for(;;){
            while(arr[++i]<v); // 피봇보다 큰 경우 스탑
            while(arr[--j]>v); // 피봇보다 작은 경우 스탑
            if(i>=j) break; // 두개가 같은 위치를 가리키면 브레이크
            swap(arr,i,j); // 두 위치의 값을 바꿔준다
        }
        swap(arr,i,r-1); // 피봇의 위치와 멈춘 위치를 바꾸어준다
        QuickSort(arr,l,i-1); // 피봇기준 앞 뒤를 나누어 반복한다
        QuickSort(arr,i+1,r);
    }
    else if(arr[l]>arr[r]) swap(arr,l,r); // 2칸일 경우 앞뒤를 비교하고 바꾼다
}

void checkSort(int a[], int n){ // 주어진 정렬확인 함수를 적어주었다
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

int main(){
    int arr[10] = {6,2,8,1,3,9,4,5,10,7};
    int test[100000] = {};
    clock_t start, end; // 시간측정을 위한 변수 생성한다
    srand(time(NULL)); // 난수생성을 위한 srand 설정을 해준다

    QuickSort(arr,0,9); // 잘 돌아가는지 10개로 테스트
    for(int i=0; i<10; i++){ // 출력해본다
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<100000; i++){ // 10만개의 입력 난수 생성
        test[i] = rand()%100000;
    }
    start = clock();
    QuickSort(test,0,99999); // 시간을 측정해본다
    end = clock();
    checkSort(test,100000); // 정렬이 잘 되었는지 체크해본다
    cout<<"퀵정렬 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.
    cout<<"12171810 정보통신공학과 유지훈"<<endl;
}