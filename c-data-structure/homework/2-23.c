// 实现链表逆序输出.
#include<stdio.h>
#include<stdlib.h>
// -> 究竟是用在什么情况下.
// malloc 函数详解
// typedef 详解
// 注意指针变为NULL结束的位置


// 节点结构.
typedef struct LNode{
  int data;
  struct LNode * next;
}LinkList;
//这样不会发生递归吗?

// 创建列表,长度为length.
LinkList * init_list(int length){
  LinkList *head, *node, *p;  // p负责向后移动
  head = (LinkList *)malloc(sizeof(LinkList));  // head被指向LinkList类型的指针.

  //head = (LinkList *)malloc(sizeof(int));  // malloc 函数详解.  // 这句话为什么没有报错.
    //因为你分配的内存很小，所以你之前分配的节点的内存其实不够
    //他用了后面本来不属于他的内存
    //但是因为其实那块内存别人没有用到，也没有改变

  p = head;
  for(int i=0; i<length; i++){
    node = (LinkList *)malloc(sizeof(LinkList));
    scanf("%d", &node->data);
    p->next = node;
    p = node;
  }
  p->next = NULL;
  return head;
}

// 输出链表
void print_list(LinkList * head){
  LinkList * p = head;
  while(p->next){
    printf(" %d ->", p->next->data);
    p = p->next;
  }
}

// 逆序链表
void reverse_list(LinkList * head, int length){
  LinkList * pre, *p, *nx_p;
  pre = head->next;  // 保持head不动.
  p = pre->next;  // 保持pre始终在p前,方便实现插入操作.
  pre->next = NULL;
  for(int i=0; i<length-1; i++){
    //pre->next = p->next;
    nx_p = p->next;
    p->next = pre;
    head->next = p;  // 实现向前插入.
    pre = p;
    p = nx_p;
  }
}

// 逆序链表,方法2
// 每次向前插入节点,都更换头结点的next域是没必要的. 据此改进算法.
void reverse_list2(LinkList * head){
  LinkList *p1, *p2, *p3; // p1第一个节点...
  p1 = head->next;
  p2 = p1->next;
  p1->next = NULL;
  while(p2){  // 指针变为NULL时结束
    p3=p2->next;
    p2->next=p1;
    p1=p2;
    p2=p3;
  }
  head->next = p1;
}

int main(){
  LinkList * list = init_list(3);
  //print_list(list);
  reverse_list2(list);
  print_list(list);
  return 0;
}
