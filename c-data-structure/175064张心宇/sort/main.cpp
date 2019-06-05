// 引用作为函数参数，直接影响参数变量
// 形参可以和属性命名相同
// 模板类外定义函数
// 必须先判定对象不是null  然后在调用方法 不然就会 段错误
// 当我们把一个指针做为参数传一个方法时，其实是把指针的复本传递给了方法，也可以说传递指针是指针的值传递。

/**
 * 查找表是数据处理的重要操作， 试建立有100个结点的   二叉排序树进行查找，然后用原数据建立AVL树， 并比较两者的平均查找长度。
 *
 (1）以链表作为存储结构，实现二叉排序树的建立、查找和删除。
（2）根据给定的数据建立平衡二叉树。
（3）比较二叉排序树和平衡二叉树的平均查找长度。
【测试数据】
随机生成。
【实现提示】
（1）初始，二叉排序树和平衡二叉树都为空树，操作界面给出查找、插入和删除三种操作供选择。每种操作均要提示输入关键字。每次插入或删除一个结点后，应更新平衡二叉树或二叉排序树的显示。
（2）平衡二叉树或二叉排序树的显示可以采用凹入表形式，也可以采用图形界面画出树形。
 */


#include <iostream>
#include <vector>
#include <stack>
#include <string>

template <typename T>
class BinarySearchTreeNode{
    typedef BinarySearchTreeNode Node;
public:
    T data;
    Node * lchild;
    Node * rchild;
public:
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


/*  什么是 nonstatic member function
template <typename T>
BinarySearchTreeNode<T> &operator=(const BinarySearchTreeNode<T> &p){
    if(this==&p)return *this;
    //auto ptr = new BinarySearchTreeNode
    this->lchild=p.lchild;
    this->rchild=p.rchild;
}
 */


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
};




void test(){
    std::vector<int> raw{45,12,53,3,37,100,24,61,90,78};
    /*
    BinarySearchTreeNode<int> t(1);
    for(int i =2 ; i<=100; i++){
        t.insert(i);
    }
    BinarySearchTreeNode<int> *p;
    std::cout<<bool(t.search(3, p))<<std::endl;
    std::cout<<bool(t.search(500))<<std::endl;
    t.del(3);
    std::cout<<bool(t.search(3, p))<<std::endl;
     */

    BinarySearchTree<int> tree;
    for(int i=0; i<10; i++){
        tree.insert(raw[i]);
    }
    tree.dispTree();
   // std::cout<<tree.search(45)<<std::endl;

    std::cout<<"\n\n删除节点45:"<<std::endl;
    tree.del(45);
    // std::cout<<tree.search(45)<<std::endl;
    tree.dispTree();
 }
int main(){
    test();
}
















