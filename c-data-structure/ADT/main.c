// static的问题，有什么方法 不用额外传参， 不用全局变量 解决这个问题。
// 使用指针的指针实现？？？

// 二叉树的链表实现
#include <stdio.h>
#include <malloc.h>

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct Queue{
    BiTNode * array;
    int front, rear, length;
}Queue;



// 创建二叉树， #代表空， 先序遍历。
BiTree create_bitree(){
    BiTree t;
    static char ch;
    ch = getchar();
    if(ch=='#')t=NULL;
    else{
        t = (BiTNode*)malloc(sizeof(BiTNode));
        t->data = ch;
        t->lchild = create_bitree();
        t->rchild = create_bitree();
    }

    return t;
}


/*
// 创建二叉树， #代表空， 先序遍历。
BiTree create_bitree(BiTree t){

    static char ch;
    ch = getchar();
    if(ch=='#')t=NULL;
    else{
        t = (BiTNode*)malloc(sizeof(BiTNode));
        t->data = ch;
        t->lchild = create_bitree(t);
        t->rchild = create_bitree(t);
    }

    return t;
}
*/


// 打印二叉树, 先序
void print_bitree(BiTree t){
    if(t){
        printf("%c ", t->data);
        print_bitree(t->lchild);
        print_bitree(t->rchild);
    }else printf("# ");
}


// 先序迭代二叉树, (返回节点总数？）
int pre_order(BiTree t){
    static int num = 0;
    if(t){
        num++;
        if(t->lchild)pre_order(t->lchild);
        if(t->rchild)pre_order(t->rchild);
    }

    return num;
}


// 先序列迭代，返回叶子节点总数
int sum_leaves(BiTree t){
    static int num = 0;
    if(!t->lchild&&!t->rchild)num++;
    else{
        if(t->lchild)sum_leaves(t->lchild);
        if(t->rchild)sum_leaves(t->rchild);
    }

    return num;
}

// 交换左右子树木, 后序
void mirror(BiTree t){
    static BiTNode * tmp;
    if(t){
        if(t->lchild)mirror(t->lchild);
        if(t->rchild)mirror(t->rchild);
        tmp = t->lchild;
        t->lchild = t->rchild;
        t->rchild = tmp;
    }
}



/*
// 层次遍历
void trav_level(BiTree t){

}
*/

// 数深度, 先序
// 每次调用函数的时候都是前往左子树或者右子树，这个时候所前往的结点的深度都会增加一个，
// 而当函数调用完成的时候会退出函数栈在此函数中的结点深度就会减少一个。
int bitree_depth(BiTree t){
    static int depth = 0, max = 0;  // depth代表每个节点的深度
    depth++;
    printf("%d", depth);
    if(t){
        if(max<depth)max=depth;  // 最后回调的是 max0
        bitree_depth(t->lchild);
        bitree_depth(t->rchild);
    }
    depth--;
    return max;
}

// x节点为根的子数的深度
int sontree_depth(BiTree  t, char x){
    static int num=0;
    if(t){
        if(t->data == x)num = bitree_depth(t);
        else{
            sontree_depth(t->lchild, x);
            sontree_depth(t->rchild, x);
        }
    }
    return num;
}


int main() {
    printf("先序创建二叉树（ABC##DE#G##F###）：\n");
    //BiTree t = (BiTree )(sizeof(BiTNode));
    //create_bitree(t);
    BiTree  t = create_bitree();
    printf("二叉树创建结束。\n\n");

    printf("节点数为%d\n", pre_order(t));
    printf("叶子节点数为%d\n", sum_leaves(t));

    print_bitree(t);printf("\n");
    mirror(t);
    print_bitree(t);printf("\n");
    //printf("数的深度%d\n", bitree_depth(t));

    printf("以C为根的子数的深度%d\n", sontree_depth(t, 'B'));


    return 0;
}