#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> initNext(const string &pattern) {
    int p_length = pattern.size();
    vector<int> next;
	int i, j;
	
	for (i=0, j=-1; i < p_length; i++, j++) {
		// next[i] = j; //원래버전
        next.push_back(j);
		// next.push_back((pattern[i] == pattern[j]) ? next[j] : j); //개선된버전
		while ((j >= 0) && (pattern[i] != pattern[j]))
			j = next[j];
	}
	return next;
}

int KMP(const string &pattern, const string &text) {
    int p_length = pattern.size();
    int t_length = text.size();
    vector<int> next = initNext(pattern);
	int i, j;
	for (i=0, j=0; i < t_length && j < p_length; i++, j++)
		while ((j >= 0) && (text[i] != pattern[j])) j = next[j];
	if (j == p_length) return i-p_length;
	else return i;
}

// vector<int> KMP_all(const string &pattern, const string &text) {
//     int p_length = pattern.size();
//     int t_length = text.size();
//     vector<int> next = initNext(pattern);
//     vector<int> poss;
// 	int i, j;
// 	for (i=0, j=0; i < t_length && j < p_length; i++, j++){
// 		while ((j >= 0) && (text[i] != pattern[j])) j = next[j];
// 		if (j == p_length-1 && text[i] == pattern[j]){
// 			poss.push_back(i-p_length+1);
// 			j = next[j];
// 		}
// 	}
//     return poss;
// }

vector<int> KMP_all(const string &pattern, const string &text){
    int p_length = pattern.size();
    int t_length = text.size();
    vector<int> pos;
	int cnt=0;
	while (1) {
		int p = KMP(pattern, text.substr(cnt, t_length-cnt));
		p += cnt;
		if (p + p_length <= t_length) pos.push_back(p);
		else break;
        cnt = p+1;
	}
    return pos;
}


int main(int argc, char **argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string text;
	string pattern;
    getline(cin, text);
    getline(cin, pattern);

    vector<int> pos = KMP_all(pattern, text);
    for(int i=0; i<pos.size(); i++)
        cout<<pos[i]+1<<" ";
    cout<<"\n";
    
    return 0;
}