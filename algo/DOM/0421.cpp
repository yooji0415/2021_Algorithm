#include <iostream>
#include <vector>
using namespace std;

class BST {
public:
	BST() {
        for(int i=0; i<max_size; i++) tree[i]=0;
	}
	~BST(){
	}
    void insert(int n){
        if(n>0) {
            int i=1;
            while(tree[i]!=0){
                if(n<tree[i]) i*=2;
                else i=i*2+1;
            }
            tree[i]=n;
        } else if(n<0){
            int i = serch(-n);
            if(i==0) printf("0\n");
            else {
                printf("%d\n", tree[i]);
                delete_(i);
            }
        } else {
            print();
        }   
    }
    int serch(int n){
        int i=1;
        while(tree[i]!=0){
            if(n==tree[i]) return i;
            if(n<tree[i]) i*=2;
            else i=i*2+1;
        }
        return 0;
    }
    void delete_(int i){
        deletor(i/2, i);
    }
    void deletor(int p_i, int i){
        tree[i]=0;
        if(i*2>max_size) return ;
        if(tree[i*2]!=0 && tree[i*2+1]!=0){
            int p;
            if(tree[i*2]<tree[p_i])
                p=p_i*2;
            else
                p=p_i*2+1;  
            tree[p]=tree[i*2];
            deletor(p, i*2);

            if(tree[i*2+1]<tree[p_i])
                p=p_i*2;
            else
                p=p_i*2+1;  
            tree[p]=tree[i*2+1];
            deletor(p, i*2+1);
        } else if(tree[i*2]!=0) {
            int p;
            if(tree[i*2]<tree[p_i])
                p=p_i*2;
            else
                p=p_i*2+1;  
            tree[p]=tree[i*2];
            deletor(p, i*2);
        } else if(tree[i*2+1]!=0){
            int p;
            if(tree[i*2+1]<tree[p_i])
                p=p_i*2;
            else
                p=p_i*2+1;  
            tree[p]=tree[i*2+1];
            deletor(p, i*2+1);
        } else return ;    
    }
    void print(){
        for(int i=1; i<max_size; i++){
            if(tree[i]!=0) printf("%d ", tree[i]);
        }
        printf("\n");
    }

private:
    int max_size=256;
	int tree[256];
};

int main(int argc, char const *argv[])
{
    BST bst;
    while(true){
        int N;
        cin>>N;
        bst.insert(N);
        if(!N) break;
    }
   
    return 0;
}
