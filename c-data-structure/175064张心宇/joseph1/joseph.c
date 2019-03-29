// 用链表实现joseph环
/**思路描述:
 * 1. 一个节点,要同时保存他的 原始位置, 和 密码.
 *    head节点的密码属性存储表长度, 并随删除而变化.
 * 2. 每次出列, 都从环中删除出列节点. 并 记录出列元素位置信息.
 *    链表中仅剩一个节点, 可不删除.
 * 3. 循环次数是确定的, 使用for循环即可.
 * 4. 删除head->next节点时,注意head丢失.
 */
/**保留问题:
 * 1. 带头节点的单链表有 几种结构.
 */


#include<stdio.h>
#include<stdlib.h>

// 节点结构.
typedef struct LNode{
    int seceret;  // 存储密码
    int pos;  // 初始位置
    struct LNode * next;
}LinkList;




/**
 * 创建带头结点的单向循环链表,长度为length. 头结点不参与循环.
 * @param  length 循环链表中节点个数(不含头结点)
 * @return        头结点指针
 */
LinkList * init_circle(int length){
    LinkList *head, *node, *p;  // p负责向后移动

    head = (LinkList *)malloc(sizeof(LinkList));
    if(!head)exit(EXIT_FAILURE);
    head->seceret = length;  // 记录循环链表中节点个数.
    head->pos = 0;

    p = head;
    for(int i=1; i<=length; i++){
        node = (LinkList *)malloc(sizeof(LinkList));
        if(!node)exit(EXIT_FAILURE);
        printf("请输入第%d个元素的密码: ", i);
        scanf("%d", &node->seceret);
        node->pos = i;
        p->next = node;
        p = node;
    }
    p->next = head->next;  // 闭合循环.
    return head;
}


/* 输出链表
int print_circle(LinkList * head){
    LinkList * p = head->next;
    for(int i=0; i<head->seceret; i++){
        printf("%d  ", p->pos);
        p = p->next;
    }
    return 0;
}
*/

/**
 * 删除now节点
 * @param  head 循环链表头结点
 * @param  now  要删除的节点
 * @return      0 删除, 1 不需要执行删除.
 */
int del_node(LinkList * head, LinkList * now){
    if(head->seceret<=1)return 1;  // 如果除头结点外只剩一个节点, 返回1.

    if(now==head->next){head->next=now->next;}  // 如果删除的节点恰好是head的next节点,让head指向下一节点
    // 给我找崩溃了.......这个错.

    LinkList * p;
    p = head;
    while(p->next!=now){  // 找到now节点的前一个节点.
        p=p->next;
    }

    p->next=now->next;
    free(now);
    head->seceret--;


    return 0;
}


/**
 * 实现joseh游戏
 * @param num  参与joseph人数(节点数量)
 * @param m   初始密码
 * @return   0: 成功执行
 */
int game(int num, int m){
    int result[num];
    LinkList *p, *q, *joseph_circle = init_circle(num);
    p = joseph_circle->next;
    for(int i=0; i<num-1; i++){

        //找到要删除的节点
        while((m-1)%joseph_circle->seceret){
            p = p->next;
            m--;
        }
        m = p->seceret;
        q = p->next;  // 记录下一个节点位置
        result[i] = p->pos;  // 记录位置
        del_node(joseph_circle, p);
        p = q;
    }
    result[num-1] = joseph_circle->next->pos;
    printf("游戏结果为: ");
    for(int i=0; i<num; i++){
        printf("%d,  ", result[i]);
    }
}


int main(){
    int num , init_sec;  // num:游戏人数, init_sec:初始密码

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

}
