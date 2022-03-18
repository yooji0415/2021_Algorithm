#include <iostream>
#include <string>
using namespace std;

template <typename T>
class List{
public:
    List(){
        this->max_size = 100;
        list = new T[max_size];
        _size=0;
    }
    List(const int &max_size){
        this->max_size = max_size;
        list = new T[max_size];
        _size=0;
    }
    List(const int &max_size, const T &val){
        this->max_size = max_size;
        list = new T[max_size];
        for(int i=0; i<max_size; i++) list[i] = val;
        _size=max_size;
    }
    ~List(){
        delete list;
    }

    void insert(T data){
        list[_size++] = data;
    }
    void remove(){
        _size--;
    }
    int size(){
        return _size;
    }
    bool empty(){
        if(_size==0) return true;
        else return false;
    }

    T& operator[](int idx) { 
        // if (_size <= idx) { 
        //     // cout << "Array index out of bound, exiting"; 
        //     // exit(0); 
            
        // } 
        return list[idx]; 
    } 

private:
    int max_size;
    T *list;
    int _size;
};

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

int main(int argc, char **argv)
{
    int T;
    cin>>T;
    string text;
    string pattern;
    getline(cin, text);
    while(T--){
        getline(cin, pattern);
        getline(cin, text);

        List<int> pos = KMP_all(pattern, text);
        cout<<pos.size()<<"\n";
    }
    return 0;
}