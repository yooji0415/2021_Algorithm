#ifndef __KMP_H__
#define __KMP_H__
#include <string>
#include "list.h"
using std::string;

// List<int> initNext(const string &pattern) {
//     int p_length = pattern.size();
//     List<int> next(p_length);
// 	int i, j;
	
// 	for (i=0, j=-1; i < p_length; i++, j++) {
// 		// next[i] = j; //원래버전
//         next.insert(j);
// 		// next[i] = (p[i] == p[j]) ? next[j] : j; //개선된버전
// 		while ((j >= 0) && (pattern[i] != pattern[j]))
// 			j = next[j];
// 	}
// 	return next;
// }

// int KMP(const string &pattern, const string &text) {
//     int p_length = pattern.size();
//     int t_length = text.size();
//     List<int> next = initNext(pattern);
// 	int i, j;
// 	for (i=0, j=0; i < t_length && j < p_length; i++, j++)
// 		while ((j >= 0) && (text[i] != pattern[j])) j = next[j];
// 	if (j == p_length) return i-p_length;
// 	else return i;
// }

// List<int> KMP_all(const string &pattern, const string &text){
//     int p_length = pattern.size();
//     int t_length = text.size();
//     List<int> poss(t_length);
// 	int pos, cnt=0;
// 	while (1) {
// 		pos = KMP(pattern, text.substr(cnt, t_length-cnt));
// 		pos += cnt;
// 		if (pos + p_length <= t_length) poss.insert(pos);
// 		else break;
//         cnt = pos+1;
// 	}
//     return poss;
// }

List<int> initNext(const string &pattern) {
    int p_length = pattern.length();
    List<int> next(p_length, 0);
	int j=0;
	for (int i=1; i<p_length; i++) {
		while ((j > 0) && (pattern[i] != pattern[j]))
			j = next[j-1];
        if(pattern[i]==pattern[j])
            next[i] = ++j;
	}
	return next;
}

List<int> KMP_all(const string &pattern, const string &text){
    int p_length = pattern.length();
    int t_length = text.length();
    List<int> next = initNext(pattern);
    List<int> pos(t_length);
	int j=0;
	for (int i=0; i<t_length; i++){
		while ((j > 0) && (text[i] != pattern[j])) j = next[j-1];
        if(text[i] == pattern[j]){
            if (j == p_length-1){
                pos.insert(i-p_length+1);
                j = next[j];
            } else j++;
        }
	    
    }
    return pos;
}

// int main(int argc, char const *argv[])
// {
// 	string text;
// 	string pattern;
//     getline(cin, text);
//     getline(cin, pattern);

//     List<int> pos = KMP_all(pattern, text);
//     cout<<pos.size()<<"\n";
//     for(int i=0; i<pos.size(); i++)
//         cout<<pos[i]+1<<" ";
//     cout<<"\n";
//     return 0;
// }

#endif