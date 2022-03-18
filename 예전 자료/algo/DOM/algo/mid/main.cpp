#include <iostream>
using namespace std;

template <typename T>
class List{
public:
    List(){
        this->max_size = 64;
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
        if(_size==max_size){
            T *temp = new T[max_size];
            for(int i=0; i<_size; i++) temp[i]=list[i];
            max_size*=2;
            delete list;
            list = new T[max_size];
            for(int i=0; i<_size; i++) list[i]=temp[i];
        }
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
        if (_size <= idx) { 
            // cout << "Array index out of bound, exiting"; 
            exit(0); 
        } 
        return list[idx]; 
    } 

private:
    int max_size;
    T *list;
    int _size;
};

struct node{
    char symbol;
    int frequency;
    node *left=NULL;
    node *right=NULL;
};
    
class Huffman{
public:
    Huffman(){

    }

    void setString(string s){
        List<int> freqs(128, 0);
        for(int i=0; i<s.size(); i++){
            freqs[s[i]]++;
        }
        for(int i=0; i<freqs.size(); i++){
            if(freqs[i]!=0){
                node *n = new node;
                n->frequency = freqs[i];
                n->symbol = i;
                heap.insert(n);
            }
        }
    }

    node *build(){
        while(heap.size()!=1){
            node *n = new node;

            node *l = heap.pop();
            n->left = l;

            node *r = heap.pop();
            n->right = r;
            
            n->frequency = l->frequency + r->frequency;
            heap.insert(n);
        }
        return heap.pop();
    }
private:
    class Heap{
    public:
        Heap(){
            list.insert(NULL);
            _size = 0;
        }

        void insert(node *data){
            list.insert(data);
            heapify(_size++);
        }

        node *top(){
            return list[1];
        }

        node *pop(){
            node *result = list[1];
            swap(list[1], list[_size]);
            list.remove();
            _size--;
            for(int i=0; i<_size; i++) heapify(i);
            return result;
        }

        int size(){
            return _size;
        }
        bool empty(){
            if(_size==0) return true;
            else return false;
        }
    private:
        List<node*> list;
        int _size;

        template <typename T>
        void swap(T &a, T &b){
            T t=a;
            a=b;
            b=t;
        }

        void heapify(int location){
            int p=location+1;
            while(true){
                if(p==1) break;
                if(list[p]->frequency >= list[p/2]->frequency) break;
                swap(list[p], list[p/2]);
                p/=2;
            }
        }
    };

    Heap heap;
};

int total = 0;

void count(node *r, int bit){
    if(r->left==NULL && r->right==NULL) {
        cout<<r->symbol<<" "<<r->frequency<<" "<<bit<<endl;
        total += bit*r->frequency;
    } else {
        if(r->left != NULL)
            count(r->left, bit+1);
        if(r->right != NULL)
            count(r->right, bit+1);
    }
}

// void show(node *r, string s){
//     if(r->left==NULL && r->right==NULL) cout<<r->symbol<<" "<<r->frequency<<" "<<s<<endl;
//     else {
//         if(r->left != NULL)
//             show(r->left, s.append("0"));
//         s = s.substr(0, s.size()-1);
//         if(r->right != NULL)
//             show(r->right, s.append("1"));
//     }
// }

int main(int argc, char const *argv[])
{
    string s;
    cin>>s;

    Huffman h;
    h.setString(s);
    node *r = h.build();
    count(r, 0);

    cout<<total<<"\n";
   
    return 0;
}
