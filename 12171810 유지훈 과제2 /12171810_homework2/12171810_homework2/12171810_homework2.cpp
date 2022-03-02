#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

#define ABS(X) ((X) < 0 ? -(X) : (X))
#define EPSILON 0.000001

using namespace std;

double insertCost = 1; // 동작별 코스트를 설정해준다.
double deleteCost = 1;
double changeCost = 1;

void Distance(char* source, int sourceLen, char* target, int targetLen);

int main() {
    char source1[5] = { 'G','U','M','B','O' };
    char target1[6] = { 'G','A','M','B','O','L' };
    Distance(source1, 5, target1, 6);
    insertCost = 0.7; // 각 동작별 코스트를 변경해준다.
    deleteCost = 0.5;
    changeCost = 0.3;
    Distance(source1, 5, target1, 6);
    char source2[11] = { 'L','e','v','e','n','s','h','t','e','i','n' };
    char target2[11] = { 'M','e','i','l','e','n','s','t','e','i','n' };
    Distance(source2, 11, target2, 11);
    char source3[5] = { 'T','A','C','T','G' };
    char target3[8] = { 'C','A','T','G','A','C','T','G' };
    Distance(source3, 5, target3, 8);
    char source4[6] = { '데','이','타','마','이','닝' };
    char target4[8] = { '데', '이', '터', '베', '이','스', '설', '계' };
    Distance(source4, 6, target4, 8);
    cout << "12171810 정보통신공학과 유지훈" << endl;
    return 0;
}

void Distance(char* source, int sourceLen, char* target, int targetLen) { // Levenshtein Distance 계산 함수
    double left, up, diagonal; // 어떠한 위치인지를 알 수 있게 도와주는 변수
    double min; // 각 위치에서 어떠한 값이 가장 작은지 파악하기 위한 함수
    double** arr = new double* [targetLen + 1]; // 값을 저장하기 위한 2차원 어레이 테이블 생성
    for (int j = 0; j < targetLen + 1; j++) {
        arr[j] = new double[sourceLen + 1];
    }
    arr[0][0] = 0;
    for (int i = 0; i < sourceLen + 1; i++) arr[0][i] = arr[0][0] + deleteCost * i; // 우선적으로 맨 위 행과 줄에 값을 넣어준다.
    for (int j = 0; j < targetLen + 1; j++) arr[j][0] = arr[0][0] + insertCost * j;
    for (int j = 1; j < targetLen + 1; j++) { // 이후 (1,1)의 위치에서부터 값을 계산해준다.
        for (int i = 1; i < sourceLen + 1; i++) {
            min = 100; // 우선적으로 최소값이 100을 넘을 일이 없으니 100으로 초기화를 매번 해준다.
            left = arr[j][i - 1] + deleteCost; // 해당 위치 기준으로 왼쪽, 위, 대각선의 경우에 값을 미리 계산해서 담는다,
            up = arr[j - 1][i] + insertCost;
            if (source[i - 1] == target[j - 1]) diagonal = arr[j - 1][i - 1]; // 대각선의 경우에는 내용이 같은 경우와
            else diagonal = arr[j - 1][i - 1] + changeCost; // 다른 경우를 따로 분리해서 값을 넣어준다.

            if (min > up) min = up; // if문을 3번 하면서 그중 가장 작은 수를 찾아준다.
            if (min > diagonal) min = diagonal;
            if (min > left) min = left;

            arr[j][i] = min; // 해당되는 값을 칸에 넣어준다.
        }
    }
    for (int j = 0; j < targetLen + 1; j++) { // 테이블이 맞게 만들어졌는지 확인하기 위해서 출력을 해본다.
        for (int i = 0; i < sourceLen + 1; i++) {
            cout << setw(5) << arr[j][i] << " ";
        }
        cout << endl;
    }
    cout << "Levenshtein Distance : " << arr[targetLen][sourceLen] << endl << endl; // 결과를 출력해준다.
    // 경로를 파악하는 알고리즘 
    int i = sourceLen; // while문을 돌기 전에 인덱스 i, j에 값을 넣어준다.
    int j = targetLen;
    int position = 0; // 어떠한 경로로 갔는지 해당 경로를 받는 변수
    int step[30] = { 0 }; // 맨 끝 결과에서 부터 시작 지점까지 역방향으로 경로를 저장하는 어레이
    int stepCount = 0; // 어레이의 몇 번째 칸까지 저장이 되어있는지 알려주는 인덱스
    while (i > 0 && j > 0) { // 둘 중 하나가 0라인에 도달하기 전끼자 반복한다.
        position = 0; // 경로 저장 변수를 0을 초기화 해준다.

        if (ABS(arr[j][i] - deleteCost - arr[j][i - 1])<EPSILON) position = 1; // 해당 지점에서 왼쪽 위쪽 대각선쪽의 값을 
        if (ABS(arr[j][i] - insertCost - arr[j - 1][i])<EPSILON) position = 2; // 각 코스트별 차이만큼 빼주고 비교를 해서 
        if (ABS(arr[j][i] - changeCost - arr[j - 1][i - 1])<EPSILON) position = 3; // 서로 일치하면 해당 위치를 나타내는 position 값을 넣는다.
        if (ABS(arr[j][i] - arr[j - 1][i - 1])<EPSILON) position = 4; // 경우의 수는 총 4가지를 정했다.
        // 1 : 왼쪽 / 2 : 위쪽 / 3 : 대각선(source와 target의 값이 다른경우) / 4 : 대각선(두 값이 같아서 값의 변동이 없는 경우)

        if (arr[j - 1][i] < arr[j - 1][i - 1]) { // if문의 순서 중 대각선이 가장 마지막에 있어서 대각선의 영향력이 커졌기 때문에 
                                         // 원하는 경로로 못 들어가는 경우가 있었다.
                                         // 따라서 왼쪽과 위쪽이 더 작을 경우 한번 더 기회를 주는 방식으로 설계를 했다.
            if (ABS(arr[j][i] - insertCost - arr[j - 1][i]) < EPSILON) position = 2;
        }
        if (arr[j][i - 1] < arr[j - 1][i - 1]) {
            if (ABS(arr[j][i] - deleteCost - arr[j][i - 1]) < EPSILON) position = 1;
        }

        // 위 작업을 통해 담아진 position 값에 따라서 step어레이에 값을 넣어주고 stepCount를 증가시켜준다.
        // 또한 해당 위치로 i, j 인덱스 위치를 바꾸어준다.
        if (position == 1) {
            step[stepCount] = 1;
            stepCount++;
            i--;
        }
        else if (position == 2) {
            step[stepCount] = 2;
            stepCount++;
            j--;
        }
        else if (position == 3) {
            step[stepCount] = 3;
            stepCount++;
            i--;
            j--;
        }
        else if (position == 4) {
            stepCount++;
            i--;
            j--;
        }

    }

    // 위 while문을 다 돌고 나왔으나 [0][0]위치에 안 와있을 경우에 대비해서 
    // 각 인덱스별 삽입, 삭제 처리를 만들어주었다. 0이 될 때 까지 for문을 통해서 
    // 삽입이나 삭제 연산의 값이 step어레이에 들어간다.
    if (j > 0) {
        for (int k = j; k > 0; k--) {
            step[stepCount] = 2;
            stepCount++;
        }
    }
    else if (i > 0) {
        for (int k = i; k > 0; k--) {
            step[stepCount] = 1;
            stepCount++;
        }
    }
    // 이제 step어레이에 값을 읽어오는 부분이다.
    // 역순의 경로를 담았기 때문에 출력을 역으로 처리해주면 정방향 경로가 나온다.
    // stepCount에서 부터 0 인덱스까지 for문을 돌게 하면서 입력되있는 값에 따라서 
    // 경로와 cost를 출력해준다. 
    for (int k = stepCount; k >= 0; k--) {
        if (step[k] == 1) cout << "삭제연산 실행 " << deleteCost << endl;
        else if (step[k] == 2) cout << "삽입연산 실행" << insertCost << endl;
        else if (step[k] == 3) cout << "교환연산 실행" << changeCost << endl;
    }
    cout << endl;
}