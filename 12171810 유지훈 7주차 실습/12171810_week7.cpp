#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int* initNext(int p[], int m){ // initNext 함수로 패턴과 길이를 받아온다
    int i, j;
    int * next = new int[m]; // 넘겨줄 next 어레이를 동적으로 할당해준다
    for(i = 0, j = -1; i < m; i++, j++){
        if(p[i] == p[j]) next[i] = next[j];
        else next[i] = j;
        while((j>=0) && (p[i] != p[j])){
            j = next[j];
        }
    }
    return next;
}

int main(){
    int * temp; // initNext 함수에서 전달해준 포인터 값을 받기 위한 변수
    int testArr1[5] = {1,1,0,1,1}; // 테스트 해볼 어레이들
    int testArr2[7] = {1,0,1,1,0,1,0};
    int testArr3[8] = {1,2,1,2,1,2,1,3};
    temp = initNext(testArr1, 5); // 테스트 1번을 진행하고 결과를 본다
    cout<<"[A,A,B,A,A]의 next[] 결과 : ";
    for(int i = 0; i<5; i++){
        cout<<temp[i]<<"  ";
    }
    cout<<endl;

    temp = initNext(testArr2, 7); // 테스트 2번을 진행하고 결과를 본다
    cout<<"[A,B,A,A,B,A,B]의 next[] 결과 : ";
    for(int i = 0; i<7; i++){
        cout<<temp[i]<<"  ";
    }
    cout<<endl;

    temp = initNext(testArr3, 8); // 테스트 3번을 진행하고 결과를 본다
    cout<<"[A,B,A,B,A,B,A,C]의 next[] 결과 : ";
    for(int i = 0; i<8; i++){
        cout<<temp[i]<<" ";
    }
    cout<<endl;
    cout<<"12171810 정보통신공학과 유지훈"<<endl;
    return 0;
}