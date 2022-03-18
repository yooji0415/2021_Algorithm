#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int A, B;
    cin>>A>>B;
    getchar();
    vector<int> *k_eng = new vector<int>[A];
    for(int i=0; i<A; i++){
        for(int j=0; j<B; j++){
            k_eng[i].push_back((int)(getchar()-'0'));
        }
        getchar();
    }
    int *count = new int[B];
    for(int i=0; i<B; i++) count[i]=0;
    for(int i=0; i<A-1; i++){
        for(int j=i+1; j<A; j++){
            int cnt=0;
            for(int k=0; k<B; k++){
                if(k_eng[i].at(k)==1 || k_eng[j].at(k)==1) cnt++;
            }
            count[cnt-1]++;
        }
    }
    for(int i=B-1; i>=0; i--) {
        if(count[i]!=0){
            cout<<i+1<<endl;
            cout<<count[i];
            break;
        }
    }
    return 0;
}
