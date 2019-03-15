// 顺序表就地逆置
#include<stdio.h>
#include<stdlib.h>
// 如何判断 malloc函数正确运行
// 指针 详解
// 为什么 将creat 和 init 合并为一步?

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct{
  int * elem;
  int length;  //链表实际长度.
  int listsize;  // 整个链表的最大可拓展长度.
}SqList;

// 初始化一个长度为length的链表
SqList * init_list(int length){
  SqList * l = (SqList *)malloc(sizeof(SqList));
  // 没有给指针 指向的地址,,,  所以才 段错误. 傻逼.
  l->length = length;
  l->listsize = LIST_INIT_SIZE;
  l->elem = (int *)malloc(sizeof(int) * l->listsize);
  if(l->elem == NULL)exit(EXIT_FAILURE);
  for(int i=0; i<length; i++)scanf("%d", &l->elem[i]);
  return l;
}

// 输出链表
void print_list(SqList * l){
  for(int i=0; i<l->length; i++){
    printf(" -> %d", l->elem[i]);
  }
}

int main(){
  SqList * l = init_list(3);
  print_list(l);
  return 0;
}
