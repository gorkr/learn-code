// 平衡二叉树
// Created by gorkr on 19-6-5.
// 多看书，多思考。
// 代码参考 【https://www.cnblogs.com/skywang12345/p/3577360.html】

// 体会 height 仅是高度，并不代表层次

#ifndef SORT_AVLTREE_H
#define SORT_AVLTREE_H

#endif //SORT_AVLTREE_H

#include <iostream>
#include <stack>
//#include "BinarySearchTree.h"



// AVL树节点
template <typename T>
class AVLNode : public BinarySearchTreeNode<T>{
public:
    int height;
    AVLNode * lchild,* rchild;
    AVLNode(T data):
            BinarySearchTreeNode<T>(data),height(0),lchild(nullptr),rchild(nullptr){}
    AVLNode(T data, AVLNode* l, AVLNode* r):
            BinarySearchTreeNode<T>(data),height(0),lchild(l),rchild(r){}
    ~AVLNode()= default;

    AVLNode<T>* leftLeftRotation(AVLNode<T>* n2);
    AVLNode<T>* rightRightRotation(AVLNode<T>* n1);
    AVLNode<T>* leftRightRotation(AVLNode<T>* n3);
    AVLNode<T>* rightLeftRotation(AVLNode<T>* n1);
    void dispTree();

    int getHight(AVLNode<T>* t);
    int setHight(AVLNode<T>* &t);

    AVLNode<T>*& insert(AVLNode<T>* &t, T key);
};

template <typename T>
void AVLNode<T>::dispTree() {
    std::stack<AVLNode<T>*> s;
    std::stack<int> level;
    std::stack<std::string> type;
    int width =  4;
    int above_width=0;
    AVLNode<T> *p;
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
int AVLNode<T>::getHight(AVLNode<T> *t) {
    if(t!= nullptr)return t->height;
    return 0;
}

template <typename T>
int AVLNode<T>::setHight(AVLNode<T> *&t) {
   return t->height = (getHight(t->lchild)>getHight(t->rchild)?getHight(t->lchild):getHight(t->rchild))+1;
}


/**
 *
 * @tparam T
 * @param n2 失衡节点
 * @return 平衡后的根节点
 */
template <typename T>
AVLNode<T>* AVLNode<T>::leftLeftRotation(AVLNode<T> *n2) {
    AVLNode<T>* n1 = n2->lchild;
    n2->lchild = n1->rchild;
    n1->rchild = n2;

    // 次序不能乱
    setHight(n2);
    setHight(n1);
    return n1;
}



template <typename T>
AVLNode<T>* AVLNode<T>::rightRightRotation(AVLNode<T> *n1) {
    AVLNode<T>* n2;
    n2 = n1->rchild;

    n1->rchild = n2->lchild;
    n2->lchild = n1;

    // 次序不能乱
    setHight(n1);
    setHight(n2);
    return n2;
}


template <typename T>
AVLNode<T>* AVLNode<T>::leftRightRotation(AVLNode<T> *n3) {
    n3->lchild = rightRightRotation(n3->lchild);
    return leftLeftRotation(n3);
}

template <typename T>
AVLNode<T>* AVLNode<T>::rightLeftRotation(AVLNode<T> *n1) {
    n1->rchild = leftLeftRotation(n1->rchild);
    return rightRightRotation(n1);
}



/**
 *将节点插入t节点以下，并返回根节点
 * @tparam T
 * @param t
 * @param key
 * @return 根节点
 */
template <class T>
AVLNode<T>*& AVLNode<T>::insert(AVLNode<T>* &t, T key)
{
    if (t == nullptr)  // 这是第一个节点
        t = new AVLNode<T>(key);
    else if (key < t->data) // 应该将key插入到"tree的左子树"的情况
    {
        t->lchild = insert(t->lchild, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHight(t->lchild) - getHight(t->rchild) == 2)
        {
            if (key < t->lchild->data)
                t = leftLeftRotation(t);
            else
                t = leftRightRotation(t);
        }
    }
    else if (key > t->data) // 应该将key插入到"tree的右子树"的情况
    {
        t->rchild = insert(t->rchild, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHight(t->rchild) - getHight(t->lchild) == 2)
        {
            if (key > t->rchild->data)
                t = rightRightRotation(t);
            else
                t = rightLeftRotation(t);
        }
    }

    setHight(t);
    return t;
}

