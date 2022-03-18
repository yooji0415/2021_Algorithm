#include<iostream>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<cmath>
#include<ctime>
using namespace std;

#define chromosomenum 60       //����ü �� = population size
#define crossoverprob 85       //���� Ȯ��
#define mutationprob 1        //�������� Ȯ��
#define generationnum 300      //���� ��
#define max_item 16            //���濡 �־��� item max ����
#define random_num (rand()%100)+1  // ������
#define elite 0                //����Ʈ���ǰ� ����� ��� 2 ������� ���� ��� 0�Դϴ�.

int num, fullweight;
int max1 = 0, max2 = 0;
int chromosome[chromosomenum][max_item]; // population���� item������ �������迭�� ������־����ϴ�.
int fit[chromosomenum]; // ���յ� ���� �־��ֱ� ���� population����ŭ ������־����ϴ�.
int map[101][1001];    // DP�� ����ϱ� ���� ������ �迭�� ����� �־����ϴ�.

class item { // knapsack�� ���� item Ŭ���� �Դϴ�.
private:
	int price = 0;
	int weight = 0;
public:
	friend class knapsackGA;
	friend class knapsackDP;
	item(int p, int w) { //������ p�� w�� �޾��־����ϴ�.
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

void knapsackGA::binaryEncoding() { // population���� item������ŭ 0,1�� ĭ�� ä���ݴϴ�.
	int i, j;
	for (i = 0; i < chromosomenum; i++) {
		for (j = 1; j <= num; j++) {
			chromosome[i][j] = rand() % 2;
		} // rand�Լ��� �̿��Ͽ� �������� �������迭�� ���� �־��־����ϴ�.
	}
}

void knapsackGA::fitness(vector<item> &v) { //���յ��� ���ϴ� �Լ��Դϴ�.
	int i, j;
	int totalp = 0, totalw = 0;
	int totalfit;
	for (i = 0; i < chromosomenum; i++) {
		for (j = 1; j <= num; j++) {
			item k = v.at(j); //vector�� �ִ� item�� k�� �������ݴϴ�.
			if (chromosome[i][j] == 1) { // ����ü �ȿ� ���� 1�� ���, ������ ���� �� ������ �����ݴϴ�.
				totalp = totalp + k.price;
				totalw = totalw + k.weight;
			}
		}
		if (totalw <= fullweight) { // fullweight���� �� ���԰� �������
			fit[i] = totalp; // ���� �� ���� fit �迭�� �־��ݴϴ�.
		}
		else { // fulweight�� ���Ը� �ʰ��� ��� 
			fit[i] = 0; // fit�� 0�� �־��ݴϴ�.
		}
		totalp = 0; totalw = 0; // �� �յ��� �ٽ� 0���� �ʱ�ȭ ���ݴϴ�.
	}
}

int knapsackGA::rouletteselection() { // �귿���� ����Դϴ�.
	int i, j;
	int fitsum = 0;
	int a = 0, b = 1;
	for (i = 0; i < chromosomenum; i++) { // ���յ��� �� ���� ���մϴ�.
		fitsum = fitsum + fit[i];
	}
	int *fitprob = new int[fitsum]; // ���յ��� �� ���� ũ�⸸ŭ �迭�� ������ݴϴ�.
	for (i = 0; i < chromosomenum; i++) {
		a = fit[i]; 
		for (j = b; j < a + b; j++) { // 1���� ���յ��� ũ�⸸ŭ �迭�� ����ü index�� �־��ݴϴ�.
			fitprob[j] = i; 
		}
		b = b + a; // �Ŀ� b ���� a�� ���� �迭�� �߰������� ������ �� �ֵ��� ������־����ϴ�.
	}
	int arrow = (rand() % fitsum) + 1; // fitsum�� ũ�⸸ŭ rand�Լ��� �����־����ϴ�.
	return fitprob[arrow]; // arrow�� �̿��Ͽ�, fitprob�� �ִ� ���� return ���־����ϴ�.
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
void knapsackGA::twopointcrossover() { //�ΰ��� ������ ������ �����ϴ� ����Դϴ�.
	int i, j;
	int coprob, fitarrow1, fitarrow2;
	int temparr1[max_item], temparr2[max_item]; // �귿�� ���ÿ� ����� temparr 2�� ����
	int copychromosome[chromosomenum][max_item]; // ����ü�� ���� �� ���� �迭�Դϴ�.
	for (i = 0; i < elite; i++) {   //����Ʈ���ǰ� ���Ǿ��� ��� ���� �ܰ��� ���� ���� ���յ� �ΰ���
		for (j = 1; j < max_item; j++) { // copychromosome�� �̸� ���縦 �صӴϴ�.
			copychromosome[i][j] = chromosome[max1][j];
			copychromosome[i][j] = chromosome[max2][j];
		}
	}
	
	for (i = elite; i < chromosomenum; i++) {  // ����Ʈ ���Ǹ� ����Ͽ��� ��� i�� ���������� �ٲ�����ϴ�.
		for (j = 1; j < max_item; j++) {
			copychromosome[i][j] = chromosome[i][j];
		}
	} // ����ü�� �����س����ϴ�.
	for (i = elite; i < chromosomenum; i=i+2) { 
		coprob = random_num; // random���� �־� Ȯ���� Ȯ���մϴ�.
		fitarrow1 = rouletteselection(); // ù��° �귿�� ���� ����ü �����մϴ�.
		for (;;) {
			fitarrow2 = rouletteselection(); // �ι�° �귿�� ���� ����ü �����մϴ�.
			if (fitarrow1 != fitarrow2)break; //���� ��� ���� ����ü�� ����ǹǷ�, �ٸ� ����ü�� �� ��� break
		}
		if (crossoverprob >= coprob) { // ����Ȯ���� ������ coprob�� ���� ��� �����մϴ�.
			for (j = 1; j < max_item; j++) {
				temparr1[j] = chromosome[fitarrow1][j]; // temparr1�� ����
				temparr2[j] = chromosome[fitarrow2][j]; // temparr2�� ����
			}
			for (j = 1; j < max_item; j++) { //������ temparr���� chromosome�� ����
				copychromosome[i][j] = temparr1[j];
				copychromosome[i + 1][j] = temparr2[j];
			}
			int p1 = (rand()%num)+1, p2 = (rand()%num)+1; //p1�� p2�� rand�Լ��� �̿��Ͽ� ���� �ݴϴ�.
			if (p1 > p2) { //p1 �� p2���� Ŭ��� swap�մϴ�.
				int temp = p1;
				p1 = p2;
				p2 = temp;
			}
			for (j = p1; j <= p2; j++) {  // p1�� p2������ ���� �ٲ��ݴϴ�.
				copychromosome[i][j] = temparr2[j];
				copychromosome[i + 1][j] = temparr1[j];
			}
		}
	}
	for (i = 0; i < chromosomenum; i++) { //���� ����ü �迭�� copy�� ������ �ٽ� �������ݴϴ�.
		for (j = 1; j < max_item; j++) {
			chromosome[i][j] = copychromosome[i][j];
		}
	} 
}


void knapsackGA::mutation() { //���������Դϴ�.
	int i,j;
	int p1, p2;
	int muprob;
	for (i = 0; i < chromosomenum; i++) {
		muprob = random_num; 
		if (mutationprob >= muprob) { // ���������� Ȯ������ ���� ���� ���ð�� �������̸� �����ݴϴ�.
			p1 = (rand()%num)+1; p2 = (rand()%num)+1; // ������ �� �ΰ��� �����մϴ�.
			if (p1 > p2) { //p1�� p2���� Ŭ ��� swap�մϴ�.
				int temp = p1;
				p1 = p2;
				p2 = temp;
			}
			for (j = p1; j <= p2; j++) { // p1���� p2���� ������ ������ bit�� ��ȯ�����ݴϴ�.
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


int knapsackGA::print(int cnt) { // ���յ��� ����ϱ� ���� print �Դϴ�.
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

void knapsackGA::generation(vector<item> &v) { //�� ���븦 ����־����ϴ�.
	int i,value;
	int cnt = 0; // ���� ���� �����ϱ� ���� count
	binaryEncoding(); // encoding�� �����մϴ�.
	for (i = 1; i <= generationnum; i++) {
		cnt++;
		fitness(v); // ���յ��� �ο��մϴ�.
		value=print(cnt); // max���յ��� �� fit�� ���յ����� ����մϴ�.
		/*if (value == optimalvalue)break;*/
		twopointcrossover(); // ���踦 ��ŵ�ϴ�.
		mutation(); // �������̸� �����մϴ�.
	}
	cout << "GA PRICE = " << value << endl;
}


class knapsackDP { //dp �� ������ knapsack�Դϴ�.
public:
	friend class item;
	void knapsackProblem(vector<item> &v);
	int getMax(int x, int y);
};
int knapsackDP::getMax(int x, int y) { // �� ���� �� �� ū ���� return ���ݴϴ�.
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
		item k = v.at(i); // vector�� i��° ���� item k�� �����մϴ�.
		for (j = 1; j <= fullweight; j++) {
			if (k.weight <= j) { // k.weight�� j ���� ������� �Ʒ� ���� ��������ݴϴ�.
				map[i][j] = getMax(map[i - 1][j], k.price + map[i - 1][j - k.weight]);
			}
			else { //�ƴҰ�� ���� ���� �״�� ������ �ݴϴ�.
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
	srand(time(NULL)); //rand���� ������ �����ϱ� ���� ������־����ϴ�.
	cout << "������ ���� : ";
	cin >> num; // item�� ������ �� ���԰��� �־��ݴϴ�.
	cout << "�� ���� : ";
	cin >> fullweight;
	knapsackDP a; // knapsackDP Ŭ����
	knapsackGA b; // knapsackGA Ŭ����
	vector<item> v;
	item k(0, 0); // �ε����� 1���� ����ϱ⿡ (0,0)���� �־��־����ϴ�.
	v.push_back(k);
	int p, w;
	cout << "������ ���� �Է� : (���� / ����) " << endl;
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


//1��° data set
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

//2��° data set
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

//3��° data set
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


//4��° data set
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