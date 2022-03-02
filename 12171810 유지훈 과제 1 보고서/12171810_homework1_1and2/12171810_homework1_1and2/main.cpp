#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <Windows.h> 
using namespace std;

LARGE_INTEGER freq, start, stop;
const int TESTNUM = 16777216;

void swap(int* arr, int a, int b) { // 입력위치의 값을 바꿔주는 swap 함수
    int temp = 0;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void QuickSort(int arr[], int l, int r) { //QuickSort 함수
    int m, v, i, j; // 필요한 변수 선언
    if (r - l > 1) { // 쪼개진 크기가 1칸~2칸일 경우를 체크
        m = (l + r) / 2;
        if (arr[l] > arr[m]) swap(arr, l, m); // 앞과 중간의 크기비교
        if (arr[l] > arr[r]) swap(arr, l, r); // 앞과 끝의 크기비교
        if (arr[m] > arr[r]) swap(arr, m, r); // 중간과 끝의 크기비교
        swap(arr, m, r - 1); // 중간값을 옮겨준다
        v = arr[r - 1]; // 피봇의 크기를 알려준다
        i = l; // 앞부터 시작되는 포인트
        j = r - 1; // 뒤부터 시작되는 포인트
        for (;;) {
            while (arr[++i] < v); // 피봇보다 큰 경우 스탑
            while (arr[--j] > v); // 피봇보다 작은 경우 스탑
            if (i >= j) break; // 두개가 같은 위치를 가리키면 브레이크
            swap(arr, i, j); // 두 위치의 값을 바꿔준다
        }
        swap(arr, i, r - 1); // 피봇의 위치와 멈춘 위치를 바꾸어준다
        QuickSort(arr, l, i - 1); // 피봇기준 앞 뒤를 나누어 반복한다
        QuickSort(arr, i + 1, r);
    }
    else if (arr[l] > arr[r]) swap(arr, l, r); // 2칸일 경우 앞뒤를 비교하고 바꾼다
}

void ShellSort(int arr[], int n) { //ShellSort 함수
    int h, i, j, v; // 필요한 변수 선언
    for (h = 1; h < n; h = 3 * h + 1) {}; // 우선 Concrete gap을 가장 뒤로 미룬다
    // 여기서 사용한 방법은 Knuth의 알고리즘으로 1,4,13 .. 3배 + 1 알고리즘 이다
    for (; h > 0; h /= 3) { // 한번 반복될 때 마다 gap을 줄여준다
        for (i = h + 1; i <= n; i++) { // h 간격을 가진 두 수를 순서대로 찾는다
            v = arr[i]; // 우선 현 위치의 값을 담아두고
            j = i; // 현 인덱스 또한 변수에 담아둔다
            while (j > h && arr[j - h] > v) { // 움직여주는 j 위치값이 간격보다 크고
            // 그 값이 미리 저장한 값보다 클때 계속 앞칸으로 옮겨준다.
                arr[j] = arr[j - h]; // 이 코드가 실행된다는 것은
                // 앞 수보다 작다는 의미니 위치를 바꾸어준다
                j = j - h; // j 위치를 앞으로 옮겨준다
            }
            arr[j] = v; // 본인보다 작은 수가 앞에 존재하는 것이므로 현 위치에 
            // 수를 넣어준다
        }
    }
}

int main() {
    int* arr = new int[TESTNUM]; // 동일한 어레이를 정렬하기 위해 
    int* copy1 = new int[TESTNUM]; // 복사를 위한 어레이를 설정한다
    int* copy2 = new int[TESTNUM];
    QueryPerformanceFrequency(&freq);
    srand(2001); // 난수생성을 위한 srand 설정을 해준다. 이 부분은 3번 쿠다 프로그램과 동일하게 시드부여를 했다
    for (int n = 1024; n <= TESTNUM; n *= 2) { // 개수를 1024개부터 TESTNUM까지 두 배씩 증가시켜줍니다.
        for (int i = 0; i < n; i++) { // 개수에 맞는 랜덤 인풋을 만든다.
            arr[i] = rand() % TESTNUM;
        }
        for (int i = 0; i < n; i++) { 
            copy1[i] = arr[i];
            copy2[i] = arr[i];
        }
        cout << n << "개의 입력에 대한 소요시간" << endl;
        QueryPerformanceCounter(&start);
        QuickSort(copy1, 0, n - 1); // 시간을 측정해본다
        QueryPerformanceCounter(&stop);
        cout << "QuickSort 소요시간 : " << double(stop.QuadPart - start.QuadPart) * 1000 / freq.QuadPart << "ms" << endl; // 소요시간을 출력해준다.
        QueryPerformanceCounter(&start);
        ShellSort(copy2, n); // 시간을 측정해본다
        QueryPerformanceCounter(&stop);
        cout << "ShellSort 소요시간 : " << double(stop.QuadPart - start.QuadPart) * 1000 / freq.QuadPart << "ms" << endl; // 소요시간을 출력해준다.
        cout << endl;
    }
    //delete[] arr;
    //delete[] copy1;
    //delete[] copy2;
    cout << "12171810 정보통신공학과 유지훈" << endl;
    return 0;
}