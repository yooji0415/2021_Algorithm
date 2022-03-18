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
class KMP { // KMPŬ����
private:
	int *next = new int[patternsize]; //�ܾ��� ������ Ȯ���ϱ� ���� ����.
public:
	void InitNext(char p[]); //����Ȯ���� ���� �Լ�
	int kmp(char p[], char t[], int num); // Buf���� �ܾ��� �ε����� return
	void Loopkmp(vector<int> &kmparray,char p[], char t[]); 
	//kmp�� �ݺ��Ͽ� �ܾ��� ����Ȯ��.
};
void KMP::InitNext(char p[]) {
	int i, j;
	int psize = strlen(p);
	next[0] = -1;
	for (i = 0, j = -1; i < psize; i++, j++) {
		if (p[i] == p[j])  //������ ������ġ�� ����Ͽ����ϴ�.
			next[i] = next[j];
		else
			next[i] = j;
		while (j >= 0 && p[i] != p[j]) {
			j = next[j]; // �ܾ �̵���Ű�� ��ġ���� Ȯ���Ͽ� ��ġ �� ��� j�� ����
		}                // ��Ű�� ������ ã�´�.
	}
}
int KMP::kmp(char p[], char t[], int num) {
	int i, j;
	int psize = strlen(p), tsize = strlen(t);
	InitNext(p);
	for (i = num, j = 0; j < psize&&i < tsize; i++, j++) {
		while (j >= 0 && t[i] != p[j]) {
			j = next[j];  // i�� �ؽ�Ʈ�� ��ġ�� �ű�� ���� ���̴�. ���� �ܾ ã������
		} // i�� �Ű������� �޾ƿ�����, ������ġ�� �ٲ����ν� ���� �ܾ ã���� �Ͽ����ϴ�.
	}
	if (j == psize) { // j�� ���� psize�� ������� �ܾ ã�����̴�.
		return i - psize; // �ܾ��� ù��° �ε����� return
	}
	else {
		return -1; // ã�� ��ġ�� buf�� ũ�⸦ �Ѿ��� -1�� return
	}
}
void KMP::Loopkmp(vector<int> &kmparray,char p[],char t[]) {
	int index;
	int start = 0; //buf �˻���ġ�� 0���� ����.
	int psize = strlen(p);
	for (;;) {
		index = kmp(p, t, start); // �ε����� ���
		if (index == -1)break; // buf�� �Ѿ ��� ����.
		kmparray.push_back(index); // vector�� �ε����� ����
		start = index + psize;  // ��˻� ��ġ�� index+psize
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
		skip[i] = psize; // 128ĭ�� psize�� ����
	}
	for (i = 0; i < psize; i++) {
		skip[(int)p[i]] = psize - i - 1; //�ܾ� �������� �迭�� ��ȣ�� ����
	}
}

int Boyer_Moore::BoyerMoore(char p[], char t[], int num) {
	int i, j, k;
	int psize = strlen(p), tsize = strlen(t);
	InitSkip(p);

	for (i = num + psize - 1, j = psize - 1; j >= 0; i--, j--) {
		while (t[i] != p[j]) { 
			k = skip[(int)t[i]]; //�ܾ ��ġ�Ұ�� k�� �ܾ��� �ε����� �ش�.
			if (psize - j > k) { // psize-j>k�ϰ��  psize-j�� ���Ͽ� �̵������ش�.
				i = i + psize - j;
			}
			else { // �װ� �ƴ� ��� i + k�� ���ش�. 
				i = i + k;
			}
			if (i >= tsize)return -1; // �ؽ�Ʈ ����� �Ѿ ��� -1 return���ش�.
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
		index = BoyerMoore(p, t, start); // boyermoore�� �̿��Ͽ� index ����
		if (index == -1)break; // -1�� ���ϵǾ��� ��� ����
		bmarray.push_back(index); //bmarray�� index�� ����
		start = index + psize; // ����� ��ġ�� index+psize
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
	FILE *p;  //�ؽ�Ʈ ������ �����ϱ� ���� ����
	int tmp;
	int i = 0;
	p = fopen("C:\\Users\\����\\Desktop\\����2\\����.txt", "r");
	while (true) {
		tmp = fgetc(p);
		if (tmp == -1) {
			buf[i] = '\0';
			break;
		}
		buf[i] = (char)tmp;
		i = i + 1;
	}

	cout << "�̸�: �����   �й�: 12141668" << endl;
	cout << "Word �Է� : ";
	cin >> pattern;

	start1 = clock();
	k.Loopkmp(KMParray, pattern, buf);
	end1 = clock();
	duration1 = (double)(end1 - start1) / CLOCKS_PER_SEC;


	cout << "KMP�� ���ڿ� �˻�" << endl;
	for (int i = 0; i < (int)KMParray.size(); i++) {
		cout << i + 1 << " : " << KMParray[i] << endl;
	}
	cout << endl;

	start2 = clock();
	b.LoopBM(BMarray, pattern, buf);
	end2 = clock();
	duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

	
	cout << "Boyer_Moore�� ���ڿ� �˻�" << endl;
	for (int i = 0; i < (int)BMarray.size(); i++) {
		cout << i + 1 << " : " << BMarray[i] << endl;
	}
	cout << endl;
	cout << "KMP�˰������� ã�� Word�� �� ���� : " << KMParray.size() << endl;
	cout << "KMP�� ����ð� : " << duration1 << endl;
	cout << endl;
	cout << "Boyer_Moore�˰������� ã�� Word�� �� ���� : " << BMarray.size() << endl;
	cout << "Boyer_Moore�� ����ð� : " << duration2 << endl;
	cout << endl;
	delete[]buf;
	delete[]pattern;
}