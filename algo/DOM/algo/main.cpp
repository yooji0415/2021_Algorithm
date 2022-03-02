#include <iostream>
using namespace std;
#include "kmp.h"
#include "heap.h"
#include "list.h"

int main(int argc, char const *argv[])
{
	// string text;
	// string pattern;
    // getline(cin, text);
    // getline(cin, pattern);

    // List<int> pos = KMP_all(pattern, text);
    // cout<<pos.size()<<"\n";
    // for(int i=0; i<pos.size(); i++)
    //     cout<<pos[i]+1<<" ";
    // cout<<"\n";
    

    Heap<int, char> h;
    h.insert(3, 'c');
    h.insert(4, 'a');
    h.insert(1, 's');
    h.insert(10, 'z');
    h.insert(9, 'q');
    while(!h.empty()) {
        cout<<h.pop()<<endl;
    }
   
    return 0;
}
