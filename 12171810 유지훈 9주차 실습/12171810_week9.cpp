#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string.h>
using namespace std;

const int NUM = 5; // 패턴 길이를 지정함
int skip[NUM+1] ={}; // skip 어레이를 전역으로 설정해줌

int FindIndex(const char *arr, char num){ // 인덱스의 위치를 찾는 함수
    int i = 0;
    for(i=0; i<strlen(arr); i++){ // 단순하게 앞에서부터 맞는 위치를 찾는다
        if(arr[i] == num) break;
    }
    return i;
}

void InitSkip(const char *p){ // skip 어레이에 값을 부여하는 함수
    int i;
    int M = strlen(p);
    for(i=0;i<=NUM;i++) skip[i] = M; // 처음에는 모든 칸에 길이인 M값을 넣고
    for(i=0;i<M;i++) skip[FindIndex(p,p[i])] = M-i-1; // 이후에 각 칸에 맞는 수를 넣어줌
                                                      // 이때 맨 마지막 칸은 M값이 그대로 들어가 있다.
}

void MisChar(const char *p, const char *t){ // 맞는 패턴위치를 알려주는 함수
    int i,j,k;
    int M = strlen(p);
    int N = strlen(t);
    for(i = M-1, j=M-1; j>=0 && i<N; i--, j--){ // 알고리즘과 약간 다르게 i<N 조건을 부여함
                                                // 이는 실습 결과 예시에서 맞는 결과를 모두 도출하기 때문에 동일하게 구현하려면 
                                                // 기존의 맞는 위치를 발견하면 끝나는 것이 아닌 계속 해주어야 하기 때문이다.
        while(t[i] != p[j]){ // 불일치 할 경우 skip 어레이에 해당하는 값을 가져오고
                             // 그 값을 M-j 값과 비교해 상황에 맞게 j 값을 옮겨준다.
                             // 이는 비교 어레이가 오히려 이미 했던 앞부분으로 이동할 수 있기 때문이다.
            k = skip[FindIndex(p,t[i])];
            if((M-j)>k) i = i + M - j;
            else i += k;
            j = M - 1;
            //cout<<"불일치 : k="<<k<<" M-j="<<M-j<<" i ="<<i<<" j="<<j<<endl;
            // 맞게 구현이 된건지 확인을 하기 위한 cout
        }
        //cout<<"일치 : i="<<i<<" j="<<j<<endl; 
        // 맞게 구현이 된건지 확인을 하기 위한 cout
        if(j==0){ // 여기도 조건을 하나 넣어줬는데 만약 j가 0 값이라는 건
                  // 패턴이 일치했다는 것이니 위치를 출력해주고 다시 j를 5로
                  // i 값은 비교했던 위치들보다 한칸 뒤로 이동시켜준다.
            cout<<"패턴이 발생한 위치 : "<< i <<endl;
            j = 5;
            i = i + M + 1;
        } 
    }
}

int main(){ // 문장과 패턴의 정보를 알려주고 이를 이용해 함수를 실행시킨다.
    string text = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
    string pattern = "ATION";
    const char *t = text.c_str();
    const char *p = pattern.c_str();
    InitSkip(p);
    /*for(int i=0; i<=NUM; i++){ // skip 어레이 값이 정확하게 들어갔는지 확인하기 위한 for문
        cout<<"skip["<<i<<"] = "<<skip[i]<<endl;
    }*/
    MisChar(p, t);
    cout<<"12171810 정보통신공학과 유지훈"<<endl;
    return 0;
}