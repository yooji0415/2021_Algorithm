#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;
int patternsize = 10;
int bufsize = 1000000;
class KMP { // KMP클래스
private:
	int *next = new int[patternsize]; //단어의 패턴을 확인하기 위해 설정.
public:
	void InitNext(char p[]); //패턴확인을 위한 함수
	int kmp(char p[], char t[], int num); // Buf에서 단어의 인덱스를 return
	void Loopkmp(vector<int> &kmparray,char p[], char t[]); 
	//kmp를 반복하여 단어의 갯수확인.
};
void KMP::InitNext(char p[]) {
	int i, j;
	int psize = strlen(p);
	next[0] = -1;
	for (i = 0, j = -1; i < psize; i++, j++) {
		if (p[i] == p[j])  //개선된 유한장치를 사용하였습니다.
			next[i] = next[j];
		else
			next[i] = j;
		while (j >= 0 && p[i] != p[j]) {
			j = next[j]; // 단어를 이동시키며 일치함을 확인하여 일치 할 경우 j를 증가
		}                // 시키며 패턴을 찾는다.
	}
}
int KMP::kmp(char p[], char t[], int num) {
	int i, j;
	int psize = strlen(p), tsize = strlen(t);
	InitNext(p);
	for (i = num, j = 0; j < psize&&i < tsize; i++, j++) {
		while (j >= 0 && t[i] != p[j]) {
			j = next[j];  // i는 텍스트의 위치를 옮기기 위한 것이다. 여러 단어를 찾기위해
		} // i를 매개변수로 받아왔으며, 시작위치를 바꿈으로써 여러 단어를 찾도록 하였습니다.
	}
	if (j == psize) { // j의 값이 psize랑 같을경우 단어를 찾은것이다.
		return i - psize; // 단어의 첫번째 인덱스를 return
	}
	else {
		return -1; // 찾는 위치가 buf의 크기를 넘어갈경우 -1을 return
	}
}
void KMP::Loopkmp(vector<int> &kmparray,char p[],char t[]) {
	int index;
	int start = 0; //buf 검색위치는 0부터 시작.
	int psize = strlen(p);
	for (;;) {
		index = kmp(p, t, start); // 인덱스를 출력
		if (index == -1)break; // buf를 넘어갈 경우 중지.
		kmparray.push_back(index); // vector에 인덱스를 저장
		start = index + psize;  // 재검색 위치는 index+psize
	}
}

class Boyer_Moore {
private:
	int skip[128];
public:
	void InitSkip(char p[]);
	int BoyerMoore(char p[], char t[], int num);
	void LoopBM(vector<int> &bmarray, char p[], char t[]);
};

void Boyer_Moore::InitSkip(char p[]) {
	int i;
	int psize = strlen(p);
	for (i = 0; i < 128; i++) {
		skip[i] = psize; // 128칸을 psize로 선언
	}
	for (i = 0; i < psize; i++) {
		skip[(int)p[i]] = psize - i - 1; //단어 역순으로 배열의 번호를 설정
	}
}

int Boyer_Moore::BoyerMoore(char p[], char t[], int num) {
	int i, j, k;
	int psize = strlen(p), tsize = strlen(t);
	InitSkip(p);

	for (i = num + psize - 1, j = psize - 1; j >= 0; i--, j--) {
		while (t[i] != p[j]) { 
			k = skip[(int)t[i]]; //단어가 일치할경우 k는 단어의 인덱스를 준다.
			if (psize - j > k) { // psize-j>k일경우  psize-j를 더하여 이동시켜준다.
				i = i + psize - j;
			}
			else { // 그게 아닐 경우 i + k를 해준다. 
				i = i + k;
			}
			if (i >= tsize)return -1; // 텍스트 사이즈를 넘어갈 경우 -1 return해준다.
			j = psize - 1;
		}
	}
	return i + 1;
}
void Boyer_Moore::LoopBM(vector<int> &bmarray, char p[], char t[]) {
	int start = 0;
	int index;
	int psize = strlen(p);
	for (;;) {
		index = BoyerMoore(p, t, start); // boyermoore를 이용하여 index 저장
		if (index == -1)break; // -1이 리턴되었을 경우 중지
		bmarray.push_back(index); //bmarray에 index를 저장
		start = index + psize; // 재시작 위치는 index+psize
	}
}




int main() {
	clock_t start1, end1,start2,end2; 
	double duration1,duration2;
	KMP k;
	Boyer_Moore b;
	vector<int>KMParray;
	vector<int>BMarray;
	char *pattern = new char[patternsize];
	char *buf = new char[bufsize];
	FILE *p;  //텍스트 파일을 오픈하기 위해 선언
	int tmp;
	int i = 0;
	p = fopen("C:\\Users\\권중\\Desktop\\과제2\\연습.txt", "r");
	while (true) {
		tmp = fgetc(p);
		if (tmp == -1) {
			buf[i] = '\0';
			break;
		}
		buf[i] = (char)tmp;
		i = i + 1;
	}

	cout << "이름: 김권중   학번: 12141668" << endl;
	cout << "Word 입력 : ";
	cin >> pattern;

	start1 = clock();
	k.Loopkmp(KMParray, pattern, buf);
	end1 = clock();
	duration1 = (double)(end1 - start1) / CLOCKS_PER_SEC;


	cout << "KMP로 문자열 검색" << endl;
	for (int i = 0; i < (int)KMParray.size(); i++) {
		cout << i + 1 << " : " << KMParray[i] << endl;
	}
	cout << endl;

	start2 = clock();
	b.LoopBM(BMarray, pattern, buf);
	end2 = clock();
	duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

	
	cout << "Boyer_Moore로 문자열 검색" << endl;
	for (int i = 0; i < (int)BMarray.size(); i++) {
		cout << i + 1 << " : " << BMarray[i] << endl;
	}
	cout << endl;
	cout << "KMP알고리즘으로 찾은 Word의 총 갯수 : " << KMParray.size() << endl;
	cout << "KMP의 실행시간 : " << duration1 << endl;
	cout << endl;
	cout << "Boyer_Moore알고리즘으로 찾은 Word의 총 갯수 : " << BMarray.size() << endl;
	cout << "Boyer_Moore의 실행시간 : " << duration2 << endl;
	cout << endl;
	delete[]buf;
	delete[]pattern;
}