#include <iostream>
#include <string>
using namespace std;

void initNext(const string &pattern, int *ret) {
    int p_length = pattern.size();
	int i, j;
	
	for (i=0, j=-1; i < p_length; i++, j++) {
		ret[i] = j; //원래버전
        // next[i] = (p[i] == p[j]) ? next[j] : j; //개선된버전
		while ((j >= 0) && (pattern[i] != pattern[j]))
			j = ret[j];
	}
}

int KMP(const string &pattern, const string &text) {
    int p_length = pattern.size();
    int t_length = text.size();
    int *next = new int[p_length];
    initNext(pattern, next);
	int i, j;
	for (i=0, j=0; i < t_length && j < p_length; i++, j++)
		while ((j >= 0) && (text[i] != pattern[j])) j = next[j];
	if (j == p_length) return i-p_length;
	else return i;
}

vector<int> KMP_all(string pattern, string text){
    vector<int> poss;
	int pos, cnt=0;
	while (1) {
		pos = KMP(pattern, text.substr(cnt, text.size()-cnt));
		pos += cnt;
		if (pos + pattern.size() <= text.size()) poss.push_back(pos);
		else break;
        cnt++;
	}
    return poss;
}

// int main(int argc, char **argv)
// {
//     string p = "10100111";
	
//     vector<int> next = initNext(p);
	
// 	for (int i = 0; i < next.size(); i++)
// 		printf("%d ", next[i]);
// 	printf("\n");

//     return 0;
// }

int main(int argc, char **argv)
{
	//char text[100] = "1001110100101000101001110";
	//char pattern[50] = "10100111";


	//char text[100] = "ababababcababababcaabbabababcaab";
	//char pattern[50] = "abababca";

	// string text = "AABAAbabcababAABAAaabbabAABAAaab";
	// string pattern = "AABAA";

	string text = "aaaaa";
	string pattern = "aa";

    vector<int> poss = KMP_all(pattern, text);
    for(int i=0; i<poss.size(); i++)
        printf("패턴이 발생한 위치 : %d\n", poss[i]);
	printf("스트링 탐색 종료.\n");
    
    return 0;
}