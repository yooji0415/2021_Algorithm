#ifndef __LIST_H__
#define __LIST_H__

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
            cout << "Array index out of bound, exiting"; 
            exit(0); 
        } 
        return list[idx]; 
    } 

protected:
    int max_size;
    T *list;
    int _size;
};

template <typename T>
class Stack : public List<T>{
    using List<T>::_size;
    using List<T>::list;

public:
    Stack() : List<T>(){
    }
    Stack(const int &max_size) : List<T>(max_size){
    }
    Stack(const int &max_size, const T &val) : List<T>(max_size, val){
    }
    ~Stack(){
    }

    const T& top(){
        return list[_size-1];
    }
};

template <typename T>
class Queue : public List<T>{
    using List<T>::_size;
    using List<T>::list;

public:
    Queue() : List<T>(){
    }
    Queue(const int &max_size) : List<T>(max_size){
    }
    Queue(const int &max_size, const T &val) : List<T>(max_size, val){
    }
    ~Queue(){
        delete list;
    }

    const T& front(){
        return list[0];
    }
    void remove(){
        _size--;
        for(int i=0; i<_size; i++){
            list[i] = list[i+1];
        }
    }
};

#endif