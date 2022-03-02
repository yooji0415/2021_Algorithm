#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int sorted[100000]; // 합병정렬을 위한 정렬된 수를 저장하는 어레이를 생성한다.

void merge(int *arr, int start, int mid, int end){ // 합병하는 함수
    int i = start; // 시작점, 중간점, 끝점을 생성한다.
    int j = mid+1;
    int k = start;
    while(i <= mid && j <= end) { // 하나는 시작점, 하나는 중간점부터 시작해서
        // 두 조각 중 각 정렬 부분의 끝까지 진행이 되었다면 반복문을 종료한다.
        if(arr[i] <= arr[j]){ // 각각의 조각의 앞부분을 비교해 더 작은 것을 
        // 정렬된 어레이에 값을 넣어주고 위치를 한칸씩 앞당겨 준다.
            sorted[k] = arr[i]; i++;
        }else{
            sorted[k] = arr[j]; j++; 
        } k++;
    } 
    // 여기로 왔다는 것은 두 조각 중 하나가 정렬어레이에 삽입이 다 완료된 상태이다.
    // 따라서 남은 한 조각에 남은 숫자들을 순서대로 정렬어레이에 넣어준다.
    if(i > mid){
        for(int t = j; t<=end; t++){
            sorted[k] = arr[t]; k++;
        }   
    }else{
        for(int t = i; t<=mid; t++){
            sorted[k] = arr[t]; k++;
        }
    }
    for(int t=start; t<=end; t++){ // 정렬된 어레이의 값을 원래 어레이 값에 넣어준다. 
        arr[t] = sorted[t];
    }
}

void mergeSort(int *arr, int start, int end){ // 합병정렬 알고리즘
    if(start < end){ // 시작점과 끝점이 같아지는 순간을 제외하고는 아래의 활동을 진행한다.
        int mid = (start+end)/2; // 중간지점의 값을 저장하는 변수를 만들어준다.
        mergeSort(arr, start, mid); // 시작지점부터 중간까지, 즉 현 어레이의 좌측을 정렬한다.
        mergeSort(arr, mid+1, end); // 중간지점부터 끝지점 까지, 즉 현 어레이의 우측을 정렬한다.
        merge(arr, start, mid, end); // 정렬된 좌측 우측을 연결해준다.
    }
}

void selectionSort(int *arr, int size){ // 선택정렬 알고리즘
    int temp = 0; // 위치변경을 위한 변수를 생성한다.
    int min_num = 0; //선택정렬을 위한 맥스 인덱스를 만든다.
    for(int j=0; j<size; j++){
        min_num=j; //현 위치를 맥스 인덱스로 우선 초기화
        for(int k=j+1; k<size; k++){
            if(arr[min_num]>arr[k]) min_num = k; //가장 큰수의 인덱스를 저장한다.
        }
        temp = arr[j]; //temp를 활용한 위치를 바꾸어준다.
        arr[j] = arr[min_num];
        arr[min_num] = temp;
    }
}

void checkSort(int a[], int n){ // 주어진 정렬확인 함수를 적어주었다. 
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
    int arr1[10] = {6, 2, 8, 1, 3, 9, 4, 5, 10}; // 테스트를 위한 두개의 어레이를 만든다.
    int arr2[10] = {6, 2, 8, 1, 3, 9, 4, 5, 10};
    int test[100000] = {0}; // 10만개를 돌릴 경우 필요한 어레이를 만들어준다.
    selectionSort(arr1, 10); // 선택정렬 10개 테스트
    cout << "선택정렬 결과 : "; // 결과를 출력해준다.
    for(int l=0; l<10; l++){
        cout<<arr1[l]<<" ";
    }
    cout<<endl;
    mergeSort(arr2,0,9); // 합병정렬 10개 테스트
    cout << "합병정렬 결과 : "; // 결과를 출력해준다.
    for(int m=0; m<10; m++){
        cout<<arr2[m]<<" ";
    }
    cout<<endl;

    // 10만개 이상으로 본격적인 실행
    srand(time(NULL)); // 난수생성을 위한 srand 설정을 해준다.
    for(int i=0; i<100000; i++){ // 어레이에 난수를 넣어준다.
        test[i] = rand()%100000;
    }
    clock_t start, end; // 시간측정을 위한 변수 생성한다.
    start = clock();
    selectionSort(test, 100000); // 선택정렬의 시간 측정
    end = clock();
    checkSort(test, 100000); // 정렬이 완료되었는지를 테스트 해본다.
    cout<<"선택정렬 소요시간 : "<<double((end-start)/1000)<<"ms"<<endl; // 소요시간을 출력해준다.
    // 선택정렬의 경우 숫자가 너무 커진 관계로 ms 단위로 바꿔주었다. (맥 기본 설정이 ns 단위)

    srand(time(NULL));
    for(int i=0; i<100000; i++){ // 이미 정렬된 어레이를 넣을 수 없기에 다시 난수를 넣어준다.
        test[i] = rand()%100000;
    }
    start = clock();
    mergeSort(test, 0, 99999); // 합병정렬의 시간 측정
    end = clock();
    checkSort(test, 100000); // 정렬이 완료되었는지를 테스트 해본다.
    cout<<"합병정렬 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.
    cout<<"12171810 정보통신공학과 유지훈"<<endl;

    return 0;
}