#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Hash {
public:
    Hash(int size=11){
        this->size=size;
        hash = new vector<string>[size];
    }

    void insert(string s){
        hash[hashing(s)].push_back(s);
    }

    bool find(string s){
        int idx = hashing(s);
        for(int i=0; i<hash[idx].size(); i++){
            if(s == hash[idx][i]) return true;
        }
        return false;
    }
    
    int hashing(string s) {
        int mul = 1;
        int x = 0;
        for (int i = 0; s[i] != 0; i++) {
            x = ((s[i] * mul) + x) % size;
            mul *= 7;
        }
        if (x < 0)x = -x;
        return x%size;
    }   
private:
    int size;
    vector<string> *hash;
};

int main(int argc, char const *argv[])
{
    Hash h(1999);
    int W, P;
    cin>>W>> P;
    string word;
    while(W--){
        cin>>word;
        h.insert(word);
    }
    bool find_flag=true;
    while(P--){
        cin>>word;
        if(!h.find(word)){
            find_flag = false;
            break;
        }
    }
    cout<<find_flag<<endl;
    return 0;
}

