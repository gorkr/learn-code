//
// Created by gorkr on 19-5-31.
//

#ifndef GRAPH_TREE_H
#define GRAPH_TREE_H

#endif //GRAPH_TREE_H
#include <iostream>
#include <stack>

template <typename T>
class Tree{
public:
    T data;
    Tree * firstchild, * nextsibling;

    Tree(T d, Tree *fc, Tree *nb):data(d),firstchild(fc),nextsibling(nb){};
    Tree():data(NULL),firstchild(nullptr),nextsibling(nullptr){};
    // 从当前节点向下打印二叉树
    void dispTree();
};


template <typename T>
void Tree<T>::dispTree() {
    std::stack<Tree<T>*> s;
    std::stack<int> level;
    std::stack<std::string> type;
    int width =  4;
    int above_width=0;
    Tree<T> *p;
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

        if(p->firstchild!= nullptr){
            s.push(p->firstchild);
            level.push(above_width+width);
            type.push("孩子");
        }
        if(p->nextsibling!= nullptr){
            s.push(p->nextsibling);
            level.push(above_width+width);
            type.push("兄弟");
        }

    }

}