#include<stdio.h>
#include<malloc.h>

typedef enum{NUM, ADD, SUB, MUL, DIV} Type;  // 枚举类型

typedef struct NodeTag{
  union {
    double number;  // 数只能是叶子节点， 使用union节省空间
    struct NodeTag *children[2];
  }u;
  Type type;
}Node;


int isspace(char** s){
  if(**s==' ')return 1;
  return 0;
}
int isdigit(char** s){
  if(**s>=0&&**s<=9)return 1;
  return 0;
}

Node* parse(char** s){  // char **s 是一个字符串数组
  while(isspace(**s))(*s)++;
  if(**s == '\0')return NULL;
  else{
    Node* n = (Node*)calloc(1, sizeof(Node));  // 与malloc完全相同

  }
}
