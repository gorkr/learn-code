// 顺序表实现joesh环
#include<stdio.h>
#include<stdlib.h>

// 个人节点结构
typedef struct {
    int seceret;
    int pos;  // 初始位置
}Node;

// 顺序表
#define LIST_INIT_SIZE  30
typedef struct {
    Node *array;
    int length;  // 当前元素含量
}List;


/**
 * 初始化长度为num的顺序表
 * @param num 线性表长度
 * @return 顺序表指针
 */
List* init_List(int num){
    // 创造一个空线性表
    List * l = (List*)malloc(sizeof(List));
    if(!l)exit(-1);
    l->array = (Node*)malloc(sizeof(Node)*LIST_INIT_SIZE);
    l->length = 0;

    // 线性表插入元素
    int seceret;
    for(int i=1; i<=num; i++){
        printf("请输入第%d个元素的密码: ", i);
        scanf("%d", &seceret);
        l->array[i-1].seceret = seceret;
        l->array[i-1].pos = i;
        l->length++;
    }
    return l;
}


/**
 * 删除顺序表中下标为i的节点
 * @param l 被操作线性表
 * @param i 删除节点下标
 * @return 被删除节点
 */
Node del_node_sq(List * l, int i){
    if((i<0)||(i>=l->length))exit(-1);
    Node deled_node = l->array[i];
    l->length--;
    for(i;i<l->length;i++){
        l->array[i]=l->array[i+1];
    }
    return deled_node;
}

/**
 * joseph循环
 * @param num 参与游戏人数
 * @param m 游戏初始密码
 * @return 0,游戏顺利执行
 */
int game(int num, int m){
    int result[num], del=0;
    List * josph_circle = init_List(num);
    for(int i=0; i<num; i++){

        // 找到要删除的节点
        while((m-1)%josph_circle->length ){
            del++;
            del=del%josph_circle->length;
            m--;
        }
        del=del%josph_circle->length;  // 防止(m-1)=length的情况， 以至越界。

        m = josph_circle->array[del].seceret;
        result[i]=josph_circle->array[del].pos;
        del_node_sq(josph_circle, del);
    }
    for(int i=0; i<num; i++){
        printf("%d,  ", result[i]);
    }
    return 0;

}

int main(){
    int num, init_sec;
    printf("请输入游戏参与人数n,(n<30): ");
    scanf("%d", &num);

    while(1){
        if(0<num&&num<=30){break;}
        printf("输入错误,请重新输入: ");
        scanf("%d", &num);
    }

    printf("请输入初始密码: ");
    scanf("%d", &init_sec);

    game(num, init_sec);
    return 0;
}





















