#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

double fibo(int n){ // 피보나치 수열을 위한 함수를 생성
    // 0 혹은 1인 경우를 제외하고는 다시 제귀로 이전 두 개의 수로 함수를 호출
    if(n==0) return 0;
    if(n==1) return 1;
    return (fibo(n-1) + fibo(n-2));
}

int main() {
    clock_t start, end; // 시간측정을 위한 변수 생성
    int num; // 원하는 숫자를 입력
    cin>>num;
    int** arr1 = new int*[num]; // 동적할당으로 2차원 배열 3개를 생성
    int** arr2 = new int*[num];
    int** arr3 = new int*[num];
    int* arr4 = new int[num]; // 결과를 받기위한 임시 통 구현
    for(int m=0; m<num; m++){
        arr1[m] = new int[num];
        arr2[m] = new int[num];
        arr3[m] = new int[num];
    }
    srand(time(NULL)); // 임의의 100 미만의 숫자를 각 행렬에 저장
    for(int n=0; n<num; n++){
        for(int l=0; l<num; l++){
            arr1[n][l] = rand() % 100;
            arr2[n][l] = rand() % 100;
            arr3[n][l] = rand() % 100;
        }
    }
    double result; // 수열의 결과값을 리턴받기 위한 변수 생성

    //Cubic complexity
    start = clock();
    for(int i=0; i<num; i++){ // 어떠한 결과값을 보고싶은 것이 아니기 때문에
    // 단순히 계산을 하고 arr4의 값을 바꿔주는 것으로 코드 생성
        for(int j=0; j<num; j++){
            for(int k=0; k<num; k++){
                arr4[k] = arr1[i][j] * arr2[i][j] * arr3[i][j];
            }
        }
    }
    end = clock();
    for(int a=0; a<num; a++){ // 실행이 끝나고 할당을 해재
        delete[] arr1[a];
        delete[] arr2[a];
        delete[] arr3[a];
    }
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<"n^3(Cubic complexity) 소요시간 = "<<double(end-start)<<"ns"<<endl; // 걸린시간 출력

    //Exponential complextiy
    start = clock();
    result = fibo(num); // 시간을 맞춰주고 피보나치 수열 실행
    end = clock();
    cout<<"2^n(Exponential complexity) 소요시간 = "<<double((end-start)/1000)<<"ms"<<endl; // 걸린시간 출력

    cout<<"12171810 정보통신공학과 유지훈 2주차 과제"<<endl;
}