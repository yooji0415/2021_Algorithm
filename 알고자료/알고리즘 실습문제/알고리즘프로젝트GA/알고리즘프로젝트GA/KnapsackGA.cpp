#include<iostream>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<cmath>
#include<ctime>
using namespace std;

#define chromosomenum 60       //염색체 수 = population size
#define crossoverprob 85       //교배 확률
#define mutationprob 1        //돌연변이 확률
#define generationnum 300      //세대 수
#define max_item 16            //가방에 넣어질 item max 갯수
#define random_num (rand()%100)+1  // 랜덤수
#define elite 0                //엘리트주의가 실행될 경우 2 실행되지 않을 경우 0입니다.

int num, fullweight;
int max1 = 0, max2 = 0;
int chromosome[chromosomenum][max_item]; // population수와 item갯수로 이차원배열을 만들어주었습니다.
int fit[chromosomenum]; // 적합도 값을 넣어주기 위해 population수만큼 만들어주었습니다.
int map[101][1001];    // DP를 사용하기 위해 이차원 배열을 만들어 주었습니다.

class item { // knapsack에 넣을 item 클래스 입니다.
private:
	int price = 0;
	int weight = 0;
public:
	friend class knapsackGA;
	friend class knapsackDP;
	item(int p, int w) { //생성자 p와 w를 받아주었습니다.
		price = p;
		weight = w;
	}
};

class knapsackGA {
public:
	friend class item;
	void binaryEncoding();
	void generation(vector<item> &v);
	void fitness(vector<item> &v);
	int rouletteselection();
	void twopointcrossover();
	void mutation();
	void findtwomax();
	int print(int cnt);
};

void knapsackGA::binaryEncoding() { // population수와 item갯수만큼 0,1로 칸을 채워줍니다.
	int i, j;
	for (i = 0; i < chromosomenum; i++) {
		for (j = 1; j <= num; j++) {
			chromosome[i][j] = rand() % 2;
		} // rand함수를 이용하여 무작위로 이차원배열에 값을 넣어주었습니다.
	}
}

void knapsackGA::fitness(vector<item> &v) { //적합도를 구하는 함수입니다.
	int i, j;
	int totalp = 0, totalw = 0;
	int totalfit;
	for (i = 0; i < chromosomenum; i++) {
		for (j = 1; j <= num; j++) {
			item k = v.at(j); //vector에 있는 item을 k에 저장해줍니다.
			if (chromosome[i][j] == 1) { // 염색체 안에 값이 1일 경우, 값들을 더해 총 값들을 구해줍니다.
				totalp = totalp + k.price;
				totalw = totalw + k.weight;
			}
		}
		if (totalw <= fullweight) { // fullweight보다 총 무게가 적을경우
			fit[i] = totalp; // 값의 총 합을 fit 배열에 넣어줍니다.
		}
		else { // fulweight의 무게를 초과할 경우 
			fit[i] = 0; // fit에 0을 넣어줍니다.
		}
		totalp = 0; totalw = 0; // 총 합들을 다시 0으로 초기화 해줍니다.
	}
}

int knapsackGA::rouletteselection() { // 룰렛선택 방식입니다.
	int i, j;
	int fitsum = 0;
	int a = 0, b = 1;
	for (i = 0; i < chromosomenum; i++) { // 적합도의 총 합을 구합니다.
		fitsum = fitsum + fit[i];
	}
	int *fitprob = new int[fitsum]; // 적합도의 총 합의 크기만큼 배열을 만들어줍니다.
	for (i = 0; i < chromosomenum; i++) {
		a = fit[i]; 
		for (j = b; j < a + b; j++) { // 1부터 적합도의 크기만큼 배열에 염색체 index를 넣어줍니다.
			fitprob[j] = i; 
		}
		b = b + a; // 후에 b 값에 a를 더해 배열에 추가적으로 더해질 수 있도록 만들어주었습니다.
	}
	int arrow = (rand() % fitsum) + 1; // fitsum의 크기만큼 rand함수를 돌려주었습니다.
	return fitprob[arrow]; // arrow를 이용하여, fitprob에 있는 값을 return 해주었습니다.
}

void knapsackGA::findtwomax() {
	int i, j;
	for (i = 0; i < chromosomenum; i++) {
		if (fit[i] > max1) {
			max2 = max1;
			max1 = i;
		}
		else if (fit[i] > max2&&fit[i] <= max1) {
			max2 = i;
		}
	}
}
void knapsackGA::twopointcrossover() { //두개의 지점을 선택후 교차하는 방법입니다.
	int i, j;
	int coprob, fitarrow1, fitarrow2;
	int temparr1[max_item], temparr2[max_item]; // 룰렛의 선택에 저장될 temparr 2개 생성
	int copychromosome[chromosomenum][max_item]; // 염색체를 복사 해 놓을 배열입니다.
	for (i = 0; i < elite; i++) {   //엘리트주의가 사용되었을 경우 이전 단계의 가장 높은 적합도 두개를
		for (j = 1; j < max_item; j++) { // copychromosome에 미리 복사를 해둡니다.
			copychromosome[i][j] = chromosome[max1][j];
			copychromosome[i][j] = chromosome[max2][j];
		}
	}
	
	for (i = elite; i < chromosomenum; i++) {  // 엘리트 주의를 사용하였을 경우 i의 시작지점이 바뀌어집니다.
		for (j = 1; j < max_item; j++) {
			copychromosome[i][j] = chromosome[i][j];
		}
	} // 염색체를 복사해놓습니다.
	for (i = elite; i < chromosomenum; i=i+2) { 
		coprob = random_num; // random값을 주어 확률을 확인합니다.
		fitarrow1 = rouletteselection(); // 첫번째 룰렛을 통해 염색체 선택합니다.
		for (;;) {
			fitarrow2 = rouletteselection(); // 두번째 룰렛을 통해 염색체 선택합니다.
			if (fitarrow1 != fitarrow2)break; //같은 경우 같은 염색체가 복사되므로, 다른 염색체가 될 경우 break
		}
		if (crossoverprob >= coprob) { // 교배확률의 값보다 coprob가 낮을 경우 실행합니다.
			for (j = 1; j < max_item; j++) {
				temparr1[j] = chromosome[fitarrow1][j]; // temparr1에 복사
				temparr2[j] = chromosome[fitarrow2][j]; // temparr2에 복사
			}
			for (j = 1; j < max_item; j++) { //각각의 temparr들을 chromosome에 복사
				copychromosome[i][j] = temparr1[j];
				copychromosome[i + 1][j] = temparr2[j];
			}
			int p1 = (rand()%num)+1, p2 = (rand()%num)+1; //p1과 p2에 rand함수를 이용하여 값을 줍니다.
			if (p1 > p2) { //p1 이 p2보다 클경우 swap합니다.
				int temp = p1;
				p1 = p2;
				p2 = temp;
			}
			for (j = p1; j <= p2; j++) {  // p1과 p2사이의 값을 바꿔줍니다.
				copychromosome[i][j] = temparr2[j];
				copychromosome[i + 1][j] = temparr1[j];
			}
		}
	}
	for (i = 0; i < chromosomenum; i++) { //원래 염색체 배열에 copy된 값들을 다시 복사해줍니다.
		for (j = 1; j < max_item; j++) {
			chromosome[i][j] = copychromosome[i][j];
		}
	} 
}


void knapsackGA::mutation() { //돌연변이입니다.
	int i,j;
	int p1, p2;
	int muprob;
	for (i = 0; i < chromosomenum; i++) {
		muprob = random_num; 
		if (mutationprob >= muprob) { // 돌연변이의 확률보다 낮은 값이 나올경우 돌연변이를 시켜줍니다.
			p1 = (rand()%num)+1; p2 = (rand()%num)+1; // 임의의 값 두개를 선정합니다.
			if (p1 > p2) { //p1이 p2보다 클 경우 swap합니다.
				int temp = p1;
				p1 = p2;
				p2 = temp;
			}
			for (j = p1; j <= p2; j++) { // p1부터 p2구간 사이의 값들의 bit를 변환시켜줍니다.
				if (chromosome[i][j]==0) {
					chromosome[i][j] = 1;
				}
				else {
					chromosome[i][j] = 0;
				}
			}
		}
		else {
			continue;
		}
	}
}


int knapsackGA::print(int cnt) { // 적합도를 출력하기 위한 print 입니다.
	int i, j;
	double max = 0;
	cout << "generation : " << cnt << endl;
	for (i = 0; i < chromosomenum; i++) {
		cout <<fit[i] << " ";
		if (fit[i] > max) {
			max = fit[i];
		}
	}
	cout << endl;
	cout << max <<endl;
	return max;
}

void knapsackGA::generation(vector<item> &v) { //한 세대를 모아주었습니다.
	int i,value;
	int cnt = 0; // 세대 수를 측정하기 위한 count
	binaryEncoding(); // encoding을 실행합니다.
	for (i = 1; i <= generationnum; i++) {
		cnt++;
		fitness(v); // 적합도를 부여합니다.
		value=print(cnt); // max적합도와 각 fit의 적합도들을 출력합니다.
		/*if (value == optimalvalue)break;*/
		twopointcrossover(); // 교배를 시킵니다.
		mutation(); // 돌연변이를 실행합니다.
	}
	cout << "GA PRICE = " << value << endl;
}


class knapsackDP { //dp 로 구현한 knapsack입니다.
public:
	friend class item;
	void knapsackProblem(vector<item> &v);
	int getMax(int x, int y);
};
int knapsackDP::getMax(int x, int y) { // 두 개의 값 중 큰 값을 return 해줍니다.
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}
void knapsackDP::knapsackProblem(vector<item> &v) {
	int i, j;
	for (i = 0; i <= 100; i++) {
		for (j = 0; j <= 1000; j++) {
			map[i][j] = 0;
		}
	}
	for (i = 1; i <= num; i++) {
		item k = v.at(i); // vector에 i번째 값을 item k에 저장합니다.
		for (j = 1; j <= fullweight; j++) {
			if (k.weight <= j) { // k.weight이 j 보다 작을경우 아래 식을 실행시켜줍니다.
				map[i][j] = getMax(map[i - 1][j], k.price + map[i - 1][j - k.weight]);
			}
			else { //아닐경우 이전 값을 그대로 가져와 줍니다.
				map[i][j] = map[i - 1][j];
			}
		}
	}
	cout <<"DP PRICE = "<< map[num][fullweight] << endl;
}

int main() {
	int i, j;
	clock_t start1, end1, start2, end2;
	double duration1, duration2;
	srand(time(NULL)); //rand값의 난수를 조절하기 위해 사용해주었습니다.
	cout << "아이템 갯수 : ";
	cin >> num; // item의 갯수와 총 무게값을 넣어줍니다.
	cout << "총 무게 : ";
	cin >> fullweight;
	knapsackDP a; // knapsackDP 클래스
	knapsackGA b; // knapsackGA 클래스
	vector<item> v;
	item k(0, 0); // 인덱스는 1부터 사용하기에 (0,0)값을 넣어주었습니다.
	v.push_back(k);
	int p, w;
	cout << "아이템 정보 입력 : (가격 / 무게) " << endl;
	for (i = 0; i < num; i++) {
		cin >> p >> w;
		item k(p, w);
		v.push_back(k);
	}
	start1 = clock();
	a.knapsackProblem(v);
	end1 = clock();
	duration1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
	cout << "DP clock = " << duration1<<endl;
	start2 = clock();
	b.generation(v);
	end2 = clock();
	duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	cout << "GA clock = " << duration2<<endl;
	cout <<"Generation = "<< generationnum << endl;
	cout << "Population = " << chromosomenum << endl;
	cout << "Crossover = " << crossoverprob << endl;
	cout << "Mutation = " << mutationprob << endl;
}


//1번째 data set
//10 101
//24 19
//7 16
//6 3
//10 7
//8 12
//17 20
//10 25
//9 10
//27 30
//8 6

//2번째 data set
//15 150
//20 15
//16 10
//22 19
//7 8
//22 24
//4 7
//17 16
//12 9
//31 22
//26 11
//37 19
//11 8
//6 1
//19 14
//27 22

//3번째 data set
//30 600
//12 6
//19 9
//40 22
//23 16
//10 8
//74 35
//16 11
//11 4
//24 14
//26 16
//31 20
//20 11
//24 19
//7 16
//6 3
//10 7
//8 12
//17 20
//10 25
//9 10
//27 30
//8 6
//14 9
//17 14
//15 16
//27 13
//14 17
//11 7
//8 6
//7 2


//4번째 data set
//20 250
//15 4
//22 23
//17 9
//33 18
//24 16
//31 20
//21 16
//13 10
//24 20
//17 11
//60 36
//48 23
//42 19
//38 20
//40 32
//13 10
//21 16
//14 7
//36 18
//12 7

//20 400
//13 35
//50 60
//15 60
//68 45
//27 60
//39 40
//23 30
//52 10
//11 70
//32 30
//24 15
//48 10
//73 40
//42 70
//43 75
//22 80
//7 20
//18 12
//4 50
//30 10