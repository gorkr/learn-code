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


/**
 * 二叉查找树给我们带来了很多方便，但是由于其在有序序列插入时就会退化成单链表（时间复杂度退化成 O(n)），AVL-tree就克服了上述困难。
 */

#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"






void testBST(){
    std::vector<int> raw{45,12,53,3,37,100,24,61,90,78};

    std::cout<<"二叉排序树："<<std::endl;
    BinarySearchTree<int> tree;
    for(int i=0; i<10; i++){
        tree.insert(raw[i]);
    }


    tree.dispTree();
    //auto p = tree.search(45);
    //std::cout<<bool(tree.search(45))<<std::endl;


    std::cout<<"\n\n删除节点45的二叉排序树:"<<std::endl;
    tree.del(45);
    tree.dispTree();
 }

void testAVL(){
    std::vector<int> raw{45,12,53,3,37,100,24,61,90,78};

    std::cout<<"平衡二叉树："<<std::endl;
    AVLNode<int>* tree= nullptr;
    for(int i=0; i<10; i++){
        tree->insert(tree, raw[i]);
    }
    tree->dispTree();
}

int main(){
    testBST();
    std::cout<<std::endl;
    testAVL();
}
