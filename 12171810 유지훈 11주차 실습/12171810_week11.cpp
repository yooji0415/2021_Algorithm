#include<iostream>
#include<string>
using namespace std;

#define N 9
#define M 9

int cheesenum(int cheese[9][9], int countcheese[9][9]) { // 최대 먹을 수 있는 치즈를 새는 함수
                                                         // 비교해줘야 하는 위치가 보통 아래칸과 왼쪽칸이나
                                                         // 가장 왼쪽줄과 가장 아래줄은 한가지 경우만 보면 된다.
                                                         // 그렇기 때문에 두 줄의 경우에는 따로 처리를 하였다.
	int i, j;
	for (i = N - 2; i >= 0; i--) { // 가장 왼쪽줄을 우선적으로 카운트를 새준다.
                                   // 이전 데이터를 불러올 곳이 아래 밖에 없으니 따로 비교를 하지는 않는다.
                                   // 쥐덫 위치일 경우에는 -10으로 값 변경을 해주었다. 
		if (cheese[i][0] == 1) countcheese[i][0] = countcheese[i + 1][0] + 1;
		else if (cheese[i][0] == 0) countcheese[i][0] = countcheese[i + 1][0];
		else if (cheese[i][0] == 2) countcheese[i][0] = - 10;
	}
	for (j = 1; j < M; j++) {
		if (cheese[N-1][j] == 1) countcheese[N-1][j] = countcheese[N-1][j - 1] + 1;
		else if (cheese[N-1][j] == 0) countcheese[N-1][j] = countcheese[N-1][j - 1];
		else if (cheese[N-1][j] == 2) countcheese[N-1][j] = - 10;
	}
	for (i = N - 2; i >= 0; i--) { // 이제 나머지 칸을 채워가면 된다.
		for (j = 1; j < M; j++) {
			if (cheese[i][j] == 1) { // 해당 자리가 치즈일 경우 아래칸과 왼쪽칸을 비교한 후 더 큰 것을 선택한다.
				if (countcheese[i + 1][j] >= countcheese[i][j - 1]) countcheese[i][j] = countcheese[i + 1][j] + 1;
				else countcheese[i][j] = countcheese[i][j - 1] + 1;
			}
			else if (cheese[i][j] == 0) { // 해당 자리가 아무 것도 없을 경우 그냥 이전 값 중 큰 것을 가져온다.
				if (countcheese[i + 1][j] >= countcheese[i][j - 1]) countcheese[i][j] = countcheese[i + 1][j];
				else countcheese[i][j] = countcheese[i][j - 1];
			}
			else if (cheese[i][j] == 2) countcheese[i][j] = -10; // 해당 자리가 쥐덫일 경우 -10 값으로 변경을 해주었다.
		}
	}
    return countcheese[0][M-1]; // 최종 결과 값을 보내준다.
}

int main() {
    int result1, result2;
    int countcheese1[9][9] = { }; 
    int countcheese2[9][9] = { }; 
    int cheese[9][9] = {
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {1,0,0,0,0,0,0,1,0},
        {0,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0},
        {0,1,0,0,1,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };
    int cheeseWithTrap[9][9] = {
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,2,0},
        {1,0,2,0,0,0,0,1,0},
        {0,0,0,0,1,2,0,0,0},
        {0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,2,1,2,0},
        {0,1,0,0,1,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };
	result1 = cheesenum(cheese, countcheese1);
	cout << "치즈만 있는 경우 : "<<result1<<"를 최대로 먹을 수 있습니다."<< endl;
    result2 = cheesenum(cheeseWithTrap,countcheese2);
    cout << "쥐덫도 있는 경우 : "<<result2<<"를 최대로 먹을 수 있습니다."<<endl;
    cout<<"12171810 정보통신공학과 유지훈 "<<endl;
}

