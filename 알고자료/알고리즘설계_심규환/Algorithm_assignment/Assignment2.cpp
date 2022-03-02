#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector> 
using namespace std; 

// pattern이 i까지 일치했을 때,
// i+1에서 일치하지 않거나 pattern이 완전히 일치할 때
// 다음 탐색 시작위치 pi[i]를 담아놓는 pi벡터를 get하는 함수
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
	
	vector<int> ans; // 탐색완료된 문자열의 시작 위치를 저장하는 ans벡터 생성
	vector<int> Pi = getPi(p); // p의 pi벡터를 getPi함수로 얻은 다음 Pi벡터로 복사

	int n = s.size();
	int m = p.size();
	int j = 0;

	for(int i = 0 ; i < n ; i++){ 
		while (j > 0 && s[i] != p[j]) j = Pi[j - 1];
		if(s[i] == p[j]){   
			if(j == m - 1){ //pattern이 완전히 일치할 때 
				ans.push_back(i - m + 1); //검색된 pattern의 시작위치를 ans벡터에 push
				j = Pi[j]; // 다음 탐색 위치를 설정
			}
			else{ //pattern이 완전히 일치하지 않을 때
				j++; //pattern의 다음 위치와 text를 비교
			} 
		} 
	} 
	return ans; //ans벡터 반환
}

int main() {
	cout << " 12181793 심규환 HW#2\n\n";

	string pattern;
	string text;

	cout << " Pattern을 입력해주세요\n ";
	cin >> pattern;
	cout << endl;	
	
	ifstream readFile;
	readFile.open("RFC2616_modified.txt"); //텍스트 파일 open
	
	if (readFile.is_open()) //만약 file이 열리면
	{
		while (!readFile.eof()) { //파일이 끝날때 까지 
			string tmp;
			getline(readFile, tmp); //getline 텍스트 파일 한줄씩 tmp에 저장 
			text = text + tmp + "\n"; // text뒤에 tmp를 붙임
		} //while이 끝나면 string text에 텍스트 파일 복사 완료
		readFile.close(); //텍스트 파일 close
	}

	vector<int> location = kmp(text, pattern); 
	//탐색된 위치를 저장하는 vector에 kmp를 통해 반환된 ans를 복사

	cout << " RFC2616_modified.txt에서 탐색완료된 횟수" << endl;
	cout << " " << location.size() << endl; //탐색완료된 횟수(vector의 사이즈)를 출력
	cout << endl;

	cout << " RFC2616_modified.txt에서 탐색완료된 "<<pattern<<"의 시작 위치" << endl;
	for (int i = 0; i < location.size(); i++) {
		if (i != 0 && i % 10 == 0) cout << endl;
		cout << " " << location[i] << " "; //탐색완료된 문자열의 시작 위치들(vector에 저장된 값들)을 출력
	}
	cout << endl;

	return 0;
}
