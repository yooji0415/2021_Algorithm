#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector> 
using namespace std; 

// pattern�� i���� ��ġ���� ��,
// i+1���� ��ġ���� �ʰų� pattern�� ������ ��ġ�� ��
// ���� Ž�� ������ġ pi[i]�� ��Ƴ��� pi���͸� get�ϴ� �Լ�
vector<int> getPi(string p){ 
	
	int m = p.size();
	int j = 0;
	vector<int> pi(m, 0); 

	for(int i = 1; i< m ; i++){ 
		while(j > 0 && p[i] != p[j]) j = pi[j-1]; 
		if(p[i] == p[j]) pi[i] = ++j;
	} 
	return pi; 
} 

vector<int> kmp(string s, string p){ 
	
	vector<int> ans; // Ž���Ϸ�� ���ڿ��� ���� ��ġ�� �����ϴ� ans���� ����
	vector<int> Pi = getPi(p); // p�� pi���͸� getPi�Լ��� ���� ���� Pi���ͷ� ����

	int n = s.size();
	int m = p.size();
	int j = 0;

	for(int i = 0 ; i < n ; i++){ 
		while (j > 0 && s[i] != p[j]) j = Pi[j - 1];
		if(s[i] == p[j]){   
			if(j == m - 1){ //pattern�� ������ ��ġ�� �� 
				ans.push_back(i - m + 1); //�˻��� pattern�� ������ġ�� ans���Ϳ� push
				j = Pi[j]; // ���� Ž�� ��ġ�� ����
			}
			else{ //pattern�� ������ ��ġ���� ���� ��
				j++; //pattern�� ���� ��ġ�� text�� ��
			} 
		} 
	} 
	return ans; //ans���� ��ȯ
}

int main() {
	cout << " 12181793 �ɱ�ȯ HW#2\n\n";

	string pattern;
	string text;

	cout << " Pattern�� �Է����ּ���\n ";
	cin >> pattern;
	cout << endl;	
	
	ifstream readFile;
	readFile.open("RFC2616_modified.txt"); //�ؽ�Ʈ ���� open
	
	if (readFile.is_open()) //���� file�� ������
	{
		while (!readFile.eof()) { //������ ������ ���� 
			string tmp;
			getline(readFile, tmp); //getline �ؽ�Ʈ ���� ���پ� tmp�� ���� 
			text = text + tmp + "\n"; // text�ڿ� tmp�� ����
		} //while�� ������ string text�� �ؽ�Ʈ ���� ���� �Ϸ�
		readFile.close(); //�ؽ�Ʈ ���� close
	}

	vector<int> location = kmp(text, pattern); 
	//Ž���� ��ġ�� �����ϴ� vector�� kmp�� ���� ��ȯ�� ans�� ����

	cout << " RFC2616_modified.txt���� Ž���Ϸ�� Ƚ��" << endl;
	cout << " " << location.size() << endl; //Ž���Ϸ�� Ƚ��(vector�� ������)�� ���
	cout << endl;

	cout << " RFC2616_modified.txt���� Ž���Ϸ�� "<<pattern<<"�� ���� ��ġ" << endl;
	for (int i = 0; i < location.size(); i++) {
		if (i != 0 && i % 10 == 0) cout << endl;
		cout << " " << location[i] << " "; //Ž���Ϸ�� ���ڿ��� ���� ��ġ��(vector�� ����� ����)�� ���
	}
	cout << endl;

	return 0;
}
