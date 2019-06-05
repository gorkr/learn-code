//
// Created by gorkr on 19-5-31.
//

#ifndef GRAPH_QUEUE_H
#define GRAPH_QUEUE_H

#endif //GRAPH_QUEUE_H


#include <iostream>
using std::cout;
using std::endl;

template<typename T,int size=30>  // int size 非模板类型参数
class Queue
{
public:
    Queue();
    bool isFull();
    bool empty();
    void EnQueue(T elem);
    T DeQueue();
    T get_back();
    T get_front();

private:
    T _arr[size];
    int _front;
    int _rear;
};

template<typename T,int size>
Queue<T,size>::Queue()
        :_front(0)
        ,_rear(0){}

template<typename T,int size>
bool Queue<T, size>::empty() {
    return  _rear==_front;
}

template<typename T,int size>
bool Queue<T, size>::isFull() {
    return  (_rear + 1) % size == _front;
}

template<typename T,int size>
void Queue<T, size>::EnQueue(T elem) {
    if (!isFull())
        _arr[_rear++] = elem;
    else
        cout << "队列已经满了" << endl;
}
template<typename T,int size>
T Queue<T, size>::DeQueue() {
    if (!empty()) {
        auto p = _front;
        ++_front;
        _front %= size;
        return _arr[p];
    }
    else
        cout << "队列已经空了" << endl;
}
template<typename T,int size>
T Queue<T, size>::get_front() {
    return _arr[_front];
}
template<typename T,int size>
T Queue<T, size>::get_back() {
    return _arr[(_rear - 1 + size) % size];
}