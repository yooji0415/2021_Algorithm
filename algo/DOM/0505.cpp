#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int _next[50];

//kmp 구현 
void InitNext(char *p)
{
	int i, j=0, M = strlen(p);
		
	_next[0] = -1;
	for (i = 0, j = -1; i < M; i++, j++) {
		_next[i] = j; //원래버전
		// _next[i] = (p[i] == p[j]) ? _next[j] : j; //개선된버전
		while ((j >= 0) && (p[i] != p[j]))
			j = _next[j];		
	}
	
}

int KMP(char *p, char *t)
{
	int i, j, M = strlen(p), N = strlen(t);
	InitNext(p);
	for (i = 0, j = 0; j < M && i < N; i++, j++)
		while ((j >= 0) && (t[i] != p[j])) j = _next[j];
	if (j == M) return i - M;
	else return i;
}
//

vector<string> sort(vector<int> key, vector<string> value){
    for(int i=1; i<key.size(); i++){
        int k = key[i];
        string v = value[i];
        int j=i-1;
        while(j > -1 && key[j] > k){
            key[j+1] = key[j];
            value[j+1] = value[j];
            j--;
        }
        key[j+1] = k;
        value[j+1] = v;
    }
    return value;
}

int main(int argc, char const *argv[])
{
    char keyword[10];
    cin>>keyword;

    vector<string> words;
    vector<int> poss;
    while(true){
        char text[256];
        cin>>text;
        if(strcmp(text, "0")==0) break;

        //position 탐색
        int pos = KMP(keyword, text);
        if(pos>strlen(text)-strlen(keyword)) pos=-1;
        
        words.push_back(text);
        poss.push_back(pos);

        // cout<<pos<<endl;
    }
    words = sort(poss, words);
    for(int i=0; i<words.size(); i++){
        cout<<words[i]<<endl;
    }
    return 0;
}