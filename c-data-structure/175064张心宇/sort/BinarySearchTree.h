// 二叉搜索树
// Created by gorkr on 19-6-5.
//

#ifndef SORT_BINARYSEARCHTREE_H
#define SORT_BINARYSEARCHTREE_H

#endif //SORT_BINARYSEARCHTREE_H


#include <iostream>
#include <vector>
#include <stack>

template <typename T>
class BinarySearchTreeNode{
    typedef BinarySearchTreeNode Node;
public:
    T data;
    Node * lchild;
    Node * rchild;
public:

    //friend bool operator!=(const BinarySearchTreeNode<T>*&, const BinarySearchTreeNode<T>*&)= default;
    BinarySearchTreeNode(T data):data(data),lchild(nullptr),rchild(nullptr){};
    ~BinarySearchTreeNode(){
        delete(lchild);
        delete(rchild);
    }
    // BinarySearchTreeNode<T> &operator=(const BinarySearchTreeNode<T> &);
    // 从当前节点向下搜索  _hot变量记录被搜索到节点的父节点
    BinarySearchTreeNode<T>* search(T key,BinarySearchTreeNode<T> *&_hot);  // 引用作为返回值，可以放在等号左边  // 指针的引用
    BinarySearchTreeNode<T>* search(T key);
    // 从当前节点向下插入；
    void insert(T key);
    // 从当前节点向下删除
    bool del(T key);
    void traverseInOrder(void (*visit)(T& e));
    // 从当前节点向下打印二叉树
    void dispTree();

};


template <typename T>
class BinarySearchTree{
private:
    BinarySearchTreeNode<T>* root;
public:
    BinarySearchTree():root(nullptr){}
    void insert(T key){
        if (root) root->insert(key);
        else
            root = new BinarySearchTreeNode<T>(key);
    }
    bool search(T key){
        if(root) root->search(key);
        else return false;
    }
    void del(T key){
        if(root) root->del(key);
    }
    void dispTree(){
        if(root) root->dispTree();
    }
    void findIt(T key){
        auto p = search(key);
        if(p==nullptr)std::cout<<"没有找到元素"<<key<<std::endl;
        else std::cout<<"找到元素"<<key<<std::endl;
    }
};



template <typename T>
void BinarySearchTreeNode<T>::dispTree() {
    std::stack<BinarySearchTreeNode<T>*> s;
    std::stack<int> level;
    std::stack<std::string> type;
    int width =  4;
    int above_width=0;
    BinarySearchTreeNode<T> *p;
    p=this;

    // 先将根入栈
    s.push(p);
    level.push(width);
    type.push("根");

    while(s.size()){
        p=s.top();s.pop();
        above_width = level.top(); level.pop();

        for(int i=1; i<=above_width; i++){
            std::cout<<"-";
        }
        std::cout<<p->data<<"("<<type.top()<<")"<<std::endl;
        type.pop();

        if(p->lchild!= nullptr){
            s.push(p->lchild);
            level.push(above_width+width);
            type.push("左");
        }
        if(p->rchild!= nullptr){
            s.push(p->rchild);
            level.push(above_width+width);
            type.push("右");
        }

    }

}


template <typename T>
void BinarySearchTreeNode<T>::traverseInOrder(void (*visit)(T & e)){
    if(this->lchild) this->lchild->traverseInOrder(visit);
    visit(data);
    if(this->rchild) this->rchild->traverseInOrder(visit);
}

template <typename T>
BinarySearchTreeNode<T>* BinarySearchTreeNode<T>::search(T key,BinarySearchTreeNode<T> * &_hot) {
    if(this->data==key)return(this);
    else if(key<this->data){
        if(lchild){
            _hot = this;
            return(this->lchild->search(key, _hot));
        }
        else
            return nullptr;
    }
    else {
        if(rchild){
            _hot = this;
            return(this->rchild->search(key, _hot));
        }
        else
            return nullptr;
    }

}

template <typename T>
BinarySearchTreeNode<T>* BinarySearchTreeNode<T>::search(T key){
    if(this->data==key)return(this);
    else if(key<this->data){
        if(lchild)
            return(this->lchild->search(key));
        else
            return nullptr;
    }
    else {
        if(rchild){
            return(this->rchild->search(key));
        }
        else
            return nullptr;
    }
}


template <typename T>
void BinarySearchTreeNode<T>::insert(T key) {
    if(key<data){
        if(lchild)
            lchild->insert(key);
        else
            lchild = new BinarySearchTreeNode<T>(key);
    }else if(key>data){
        if(rchild)
            rchild->insert(key);
        else
            rchild = new BinarySearchTreeNode<T>(key);
    }
}

template <typename T>
bool BinarySearchTreeNode<T>::del(T key){
    //BinarySearchTreeNode<T>* parent = nullptr;
    BinarySearchTreeNode<T>* succ = nullptr;  // 实际删除节点的阶梯这
    BinarySearchTreeNode<T>* d = search(key);
    if(!d) return false;

    if(d->lchild== nullptr){
        succ = d->rchild;
        if(succ){
            *d = *succ;
            delete(succ);
        }else{
            delete(d);
        }


    }

    else if (d->rchild== nullptr){
        succ = d->lchild;
        if(succ){
            *d = *succ;
            delete(succ);
        }else{
            delete(d);
        }
    }
    else{
        BinarySearchTreeNode<T>* exchnge=d->lchild; // 记录d节点的直接前驱节点， 左转
        BinarySearchTreeNode<T>* p = d; // 记录交换节点的父节点
        while(exchnge->rchild){
            p = exchnge;
            exchnge = exchnge->rchild;
        }
        d->data = exchnge->data;
        ((p!=d)?p->rchild:p->lchild) = exchnge->lchild;
        delete(exchnge);
    }
}

