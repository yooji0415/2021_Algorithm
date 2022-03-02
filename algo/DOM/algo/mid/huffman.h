#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include <iostream>
#include <string>
#include "list.h"
using namespace std;

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
                if(list[p]->frequency > list[p/2]->frequency) break;
                swap(list[p], list[p/2]);
                p/=2;
            }
        }
    };

    Heap heap;
};

void show(node *r, string s){
    if(r->left==NULL && r->right==NULL) cout<<r->symbol<<" "<<r->frequency<<" "<<s<<endl;
    else {
        if(r->left != NULL)
            show(r->left, s.append("0"));
        s = s.substr(0, s.size()-1);
        if(r->right != NULL)
            show(r->right, s.append("1"));
    }
}

// int main(int argc, char const *argv[])
// {
//     string s;
//     getline(cin, s);
    
//     Huffman hm;
//     hm.setString(s);
//     node *r = hm.build();
//     show(r, "");

//     return 0;
// }
// aaaaaaaaaaaaaaa                           bbbbbbbbbbbbcccccccccdddddeeeeeeeeeefffffffffff
#endif