#ifndef __HEAP_H__
#define __HEAP_H__
#include "list.h"

template <typename K, typename V>
class Heap{
public:
    Heap(){
        key.insert(NULL);
        value.insert(NULL);
        _size = 0;
    }

    void insert(const K &key, const V &value){
        this->key.insert(key);
        this->value.insert(value);
        heapify(_size++);
    }

    V top_value(){
        return value[1];
    }
    K top_key(){
        return key[1];
    }

    V pop(){
        V result = value[1];
        swap(key[1], key[_size]);
        swap(value[1], value[_size]);
        key.remove();
        value.remove();
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
    List<K> key;
    List<V> value;
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
            if(key[p] > key[p/2]) break;
            swap(key[p], key[p/2]);
            swap(value[p], value[p/2]);
            p/=2;
        }
    }
};

#endif