#include <iostream>
using namespace std;

int main() {
    int arr[10]={0}; //입력된 값을 받기위한 어레이 생성
    int max = 0; // 초기 최대 최소값을 생성한다
    int min = 100000;
    int temp = 0; //정렬에 쓰일 temp를 만든다
    
    for(int i=0; i<10; i++){ //10개의 입력을 받는다.
        cin>>arr[i];
        if(arr[i]>max) max = arr[i]; //최대 최소값 받을때마다 바꿔준다
        if(arr[i]<min) min = arr[i];
    }
    cout<<"최소값, 최대값 : "<<min<<","<<max<<endl;

    //선택정렬을 이용한 역순정렬을 이용하기로 생각을 함
    int max_num = 0; //선택정렬을 위한 맥스 인덱스를 만든다
    for(int j=0; j<10; j++){
        max_num=j; //현 위치를 맥스 인덱스로 우선 초기화
        for(int k=j+1; k<10; k++){
            if(arr[max_num]<arr[k]) max_num = k; //가장 큰수의 인덱스를 저장
        }
        temp = arr[j]; //temp를 활용한 위치 바꾸기
        arr[j] = arr[max_num];
        arr[max_num] = temp;
    }
    cout << "역순정렬 : "; //역순정렬 출력부분
    for(int l=0; l<10; l++){
        cout<<arr[l]<<" ";
    }
    cout<<endl;

    //삽입정렬을 이용한 정순정렬을 이용하기로 생각을 함
    int key = 0; //삽입정렬을 위한 민 인덱스를 만든다
    int m,n; //for문에 사용될 변수를 선언한다 
    //따로 만든 이유는 인덱스 위치를 따로 저장하지 않기 위해서이다
    for(m=1; m<10; m++){
        key = arr[m]; //1번 인덱스부터 끝까지 움직인다
        for(n=m-1; n>=0; n--){ //들고있는 키의 왼쪽부터 움직인다
            if(arr[n] < key) break; //만일 키보다 작은(정렬된) 수를 만나면 멈춘다
            arr[n+1] = arr[n]; //아닌경우 한칸씩 민다
        }
        arr[n+1] = key; //정렬할 위치에 값을 넣어준다
    }
    cout << "정순정렬 : "; //역순정렬 출력부분
    for(int l=0; l<10; l++){
        cout<<arr[l]<<" ";
    }
    cout<<endl;

    cout<<"정보통신공학과 12171810 유지훈"<<endl;
    return 0;
}