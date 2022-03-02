#include <iostream>
#include <string>
using namespace std;

int main(){
    int cnt=0;
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        string check=s.substr(0, 1);
        bool f=false;
        for(int i=1; i<s.size(); i++){
            if(s[i-1] != s[i]){
                for(int j=0; j<check.size(); j++){
                    if(check[j]==s[i]) {
                        f=true;
                        break;
                    }
                }
                if(f) break;
                check.append(s.substr(i, 1));
            }
        }
        if(f) continue;
        cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}