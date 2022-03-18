#include "stdc++.h"
#include <limits.h>
using namespace std;

#define START 0 // 시작 노드 위치를 정해줍니다.
#define POP_SIZE 10 // 초기상태에 얼마의 유전자를 만들지 정해줍니다.
#define TRY 14
// #define V 5
// #define V 10
#define V 15 // 도시의 수를 정해줍니다

bool visited[20]; // DP를 위한 visted 어레이
int lowCost = INT_MAX; // DP 최소값을 담기 위한 변수

void tspDP(int node, int costSum, int count, int map[V][V]) {  // DP를 이용해서 최적값을 찾는 함수
    visited[node] = true;  // 시작 노드를 우선 방문했다고 처리해준다.
    if (count == V) {  // 한바퀴를 다 돈 경우를 고려해서 카운트 값과 비교를 해준다. 
        lowCost = min(lowCost, costSum); // 다 돈 경우에는 해당 경우가 이때까지의 최소값과 같은지를 판단하고 교환을 해준다.
        visited[node] = false;
        return;
    }
 
    for(int i=0;i<V;i++){  //만약 카운트가 다 안찼다는 것은 한바퀴를 못 돈 것이기 때문에 
        if(!visited[i] && map[node][i] != 0){ // 해당위치가 동일 위치(0) 이고 방문을 하지 않았다면
            if (costSum + map[node][i] < lowCost) { // 지금까지 더했던 값과 다음 노드를 방문해서 더해질 값을 고려해 해당 값이 지금까지의 가장 작은 결과값보다 작다면 
                tspDP(i, costSum + map[node][i], count + 1, map); // 그 위치를 기준으로 값을 바꿔서 tspDP를 다시 실행해줍니다.
            }
        }
    }
    visited[node] = false;
}

// 상단은 DP함수 하단은 GA함수로 구분된다.

struct singleData { // 유전자의 구조로
	string gnome;   // 경로는 스트링 구조
	int length;    // 경로의 값은 정수 구조
};

int rand_num(int start, int end)    // 랜덤한 수를 생성하는 함수
{
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}

bool repeat(string s, char ch)
{
	for (int i = 0; i < s.size(); i++) {  // 동일한 노드가 겹치면 
		if (s[i] == ch)                   // tsp 구조가 아니기 때문에 
			return true;                  // 이를 검사해주기 위한 함수이다.
	}
	return false;
}

string mutatedGene(string gnome) // 랜덤하게 스트링 구조를 바꾸어준다.
{
	while (true) {
		int r1 = rand_num(1, V);   // 한 유전자 안에서 위치를 바꿔주는 방식을 채택하였다.
		int r2 = rand_num(1, V);  // tsp 구조에서는 두 유전자를 선택해서 바꾸는 것 보다
		if (r2 != r1) {            // 한 스트링 안에서 경로 위치만 바꾸어 주는 것이 효율적이라 판단했기 때문이다.
			char temp = gnome[r1];
			gnome[r1] = gnome[r2];
			gnome[r2] = temp;
			break;
		}
	}
	return gnome;
}

string create_gnome()       // 유전자 풀을 랜덤하게 만들어주기 위해서 만들어진 함수로
{                           // 동일한 문자가 섞이지 않게 설정을 해준다. 
	string gnome = "0";
	while (true) {
		if (gnome.size() == V) {
			gnome += gnome[0];
			break;
		}
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48)))
			gnome += (char)(temp + 48);
	}
	return gnome;
}

int cal_length(string gnome, int map[V][V])    // 해당 경로에 해당하는 값을 출력해주는 함수이다.
{
	int total = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {               // 끊겨있는 경우를 제외한 경우에 
		if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)  // 경로에 존재하는 값을 다 다헌 값을 리턴해준다.
			return INT_MAX;
		total += map[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return total;
}

int cooldown(int temp)                // tsp 구조에서 반복문을 위한 장치가 두개가 마련이 되어있다.
                                      // 하나는 설정해준 반복 횟수이고 다른 하나는 최적화를 위해서 설정한 
                                      // temp 변수인데 이를 점점 줄이기 위해서 해당 함수를 넣게 되었다.
{
	return (90 * temp) / 100;
}

bool lessthan(struct singleData t1,
			struct singleData t2)     // 두 유전자를 비교하기 위해 만든 함수
{
	return t1.length < t2.length;   // 단순하게 두 유전자의 결과 거리를 비교해준다.
}

void tspGA(int map[V][V])
{
	int gen = 1; // 초기에는 1세대기 때문에 처리를 해준다.
	int generationTry = TRY; // 몇 번의 세대를 만들어서 시도할 지 정해준다.

	vector<struct singleData> population; // 벡터로 유전자 풀을 만들어준다.
	struct singleData temp;

	for (int i = 0; i < POP_SIZE; i++) {  // 초기에 설정해둔 값 만큼 유전자 풀을 채워준다.
		temp.gnome = create_gnome();
		temp.length = cal_length(temp.gnome, map);
		population.push_back(temp);
	}

	cout << "\n초기 유전자 풀 : " << endl   // 초기 유전자 풀의 값을 출력해준다.
		<< "각 유전자의 총 거리는 다음과 같다.\n";
	for (int i = 0; i < POP_SIZE; i++)
		cout << "경로 : "<< population[i].gnome << " "
			<< "값 : " << population[i].length << endl;

	bool found = false;
	int temperature = 10000;

	while (temperature > 1000 && gen <= generationTry) {
		sort(population.begin(), population.end(), lessthan);  // 유전자를 총 거리를 비교해서 정렬을 해준다.
		cout << "현 temp의 값 : " << temperature << "\n";
		vector<struct singleData> new_population;              // 새로운 유전자 풀을 형성하기 위해서 벡터를 만들어준다.

		for (int i = 0; i < POP_SIZE; i++) {                   
			struct singleData p1 = population[i];

			while (true) {
				string new_g = mutatedGene(p1.gnome);          // 유전자 변이를 일으켜준 스트링 값을 받아온다.
				struct singleData new_gnome;                   // 해당 스트링 값을 기반으로 새로운 유전자를 형성해준다.
				new_gnome.gnome = new_g;
				new_gnome.length = cal_length(new_gnome.gnome, map);

				if (new_gnome.length <= population[i].length) {    // 만약 새로 변형한 유전자가 이전의 유전자보다 좋은 성능을 보이면 
					new_population.push_back(new_gnome);             // 새로운 유전자를 넣어준다.
					break;
				}
				else {
					float prob = pow(2.7,                                    // 새롭게 생성된 유전자가 더 좋은 성능이 아닌 경우에는 
									-1 * ((float)(new_gnome.length          // 현 temp값에 비례해서 성능 비교를 해서 상대 성능을 확인한 후에
												- population[i].length)     // 임의로 설정해준 최소 성능을 넘는 경우에는 넣어준다.
										/ temperature));                     // 새로운 유전자가 성능이 좋은 것 만 넣을 경우에는 
					if (prob > 0.5) {                                        // 원하는 최소가 아닌 다른 최소가 나올 수 있기 때문이다.
						new_population.push_back(new_gnome);
						break;
					}
				}
			}
		}

		temperature = cooldown(temperature);   // 최적화를 너무 많이 하는 것을 방지하기 위해서 설정한 쿨다운 함수를 실행시킨다.
		population = new_population;           // 새로운 유전자 풀을 기존 유전자 풀 정보에 넣어준다.
		cout << "\n세대 : " << gen << " \n";
		cout << "각 유전자의 총 거리는 다음과 같다.\n";

		for (int i = 0; i < POP_SIZE; i++)
			cout << "경로 : "<< population[i].gnome << " "
			<< "값 : " << population[i].length << endl;
		gen++;
	}
}

int main()
{
    clock_t start, end; // 시간측정을 위한 변수 생성한다

	/*int map[V][V] = { { 0, 2, 7, 12, 5 },
					  { 2, 0, 4, 8, 32 },
					  { 21, 4, 0, 3, 3 },
					  { 12, 8, 3, 0, 10 },
					  { 5, 18, 3, 10, 0 } };*/
    /*int map[V][V] = { { 0, 2, 7, 12, 5, 10, 4, 9, 32, 16 },
					    { 2, 0, 4, 8, 32, 11, 6, 13, 15, 17 },
					    { 21, 4, 0, 3, 3, 3, 9, 5, 22, 13 },
					    { 12, 8, 3, 0, 10, 18, 4, 20, 33, 7 },
					    { 5, 18, 3, 10, 0, 32, 4, 5, 6, 8}, 
                        { 10, 4, 9, 10, 31, 0, 4, 2, 0, 4},
                        { 7, 2, 12, 32, 12, 33, 0, 4, 16, 18},
                        { 1, 3, 42, 18, 22, 88, 2, 0, 3, 4},
                        { 8, 9, 10, 33, 2, 4, 8, 1, 0, 13},
                        { 7, 9, 12, 1, 3, 13, 8, 1, 9, 0}};*/
    int map[V][V] = { {0, 1, 7, 8, 19, 2, 1, 31, 8, 1, 6, 32, 6, 18, 9},
                        {3, 0, 9, 8, 15, 21, 33, 7, 13, 4, 9, 8, 11, 23, 4}, 
                        {21, 19, 0, 9, 8, 2, 11, 31, 23, 14, 22, 3, 4, 5, 22}, 
                        {23, 12, 14, 0, 14, 32, 17, 18, 22, 11, 14, 45, 26, 28, 19}, 
                        {7, 11, 12, 14, 0, 34, 18, 21, 23, 24, 28, 11, 32, 32, 41}, 
                        {16, 25, 21, 3, 33, 0, 11, 23, 26, 12, 12, 33, 14, 5, 12}, 
                        {18, 22, 12, 31, 13, 34, 0, 4, 4, 29, 2, 14, 3, 6, 5}, 
                        {7, 6, 24, 23, 8, 9, 17, 0, 31, 23, 9, 7, 16, 32, 21}, 
                        {9, 17, 23, 11, 3, 12, 31, 10, 0, 10, 9, 8, 32, 13, 31}, 
                        {8, 10, 20, 10, 20, 11, 2, 12, 23, 0, 21, 12, 23, 26, 25}, 
                        {4, 4, 19, 12, 11, 23, 16, 15, 25, 10, 0, 21, 12, 11, 32}, 
                        {8, 27, 26, 22, 5, 23, 4, 6, 12, 28, 6, 0, 18, 10, 4}, 
                        {9, 8, 11, 22, 31, 23, 14, 11, 3, 22, 41, 23, 22, 21, 14}, 
                        {6, 15, 2, 21, 33, 4, 8, 7, 6, 12, 21, 13, 14, 0, 12}, 
                        {12, 9, 8, 9, 8, 2, 21, 21, 33, 15, 12, 31, 11, 31, 0}};

    cout<<"------------------GA결과를 출력합니다------------------"<<endl;
    start = clock();
	tspGA(map);
    end = clock();
    cout<<TRY<<"세대까지의 GA 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.

    cout<<endl<<"------------------DP결과를 출력합니다------------------"<<endl;
    start = clock();
    for (int i = 0; i < V; i++)
        tspDP(i, 0, 1, map);
    end = clock();
    cout<<"DP의 최소값 결과 : "<<lowCost<<endl;
    cout<<"DP 소요시간 : "<<double(end-start)<<"ns"<<endl; // 소요시간을 출력해준다.
    cout<<"12171810 정보통신공학과 유지훈"<<endl;
    return 0;
}