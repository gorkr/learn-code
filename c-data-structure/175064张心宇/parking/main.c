//
// Created by gorkr on 19-3-25.
//
/**
【实验学时】5学时
【实验目的】
（1）深入了解栈和队列的特性，掌握栈和队列的存储方法。
（2）掌握栈和队列的基本操作，如初始化、入栈（队列）、出栈（队列）等，并能在实际问题背景下灵活运用。
【问题描述】
设停车场是一个可以停放n辆汽车的狭长通道，且只有一个大门可供汽车进出。汽车在停车场内按车辆到达时间的先后顺序，依次由北向南排列（大门在最南端，最先到达的第一辆车停放在车场的最北端），
 若车场内已经停满n辆汽车，则后来的汽车只能在门外的便道上等候，一旦有车开走，则排在便道上的第一辆车即可开入；当停车场内某辆车要离开时，在它之后进入的车辆必须先退出场为它让路，
 待该辆车开出大门外，其他车辆再按次序进入车场，

 每辆停放在车场的车在它离开停车场时必须按它停留的时间长短交纳费用，试为停车场编制按上述要求进行管理的模拟程序。？？？？

【基本要求】
以栈模拟停车场，以队列模拟车场外的便道，按照从终端读入的输入数据序列进行模拟管理。每一组输入数据包括三个数据项：汽车“到达”或“离去”信息、汽车牌照号码以及到达或离去的时刻。
 对一组输入数据进行操作后的输出信息为：若是车辆到达，则输出汽车在停车场内或便道上的停车位置；若是车辆离去，则输出汽车在停车场内停留的时间和应交纳的费用（在便道上停留的时间不收费）。
 栈以顺序结构实现。队列以链表结构实现。
【测试数据】
设n=2，输入数据为：（‘A’，1，5）， （‘A’，2，10）， （‘D’，1，5）， （‘A’，3，20）， （‘A’，4，25）， （‘A’，5，30）， （‘D’，2，35）， （‘D’，4，40）， （‘E’，0，0）。
 其中：‘A’表示到达（Arrival），‘D’表示离去（Departure），‘E’表示输入结束（End）。
【实现提示】
需另设一个栈，临时停放为给要离去的汽车让路而从停车场退出来的汽车，也用顺序存储结构实现。输入数据按到达或离去的时刻有序。栈中每个元素表示一辆汽车，包含两个数据项：汽车的牌照号码和进入停车场的时刻。
【选作内容】
（1）两个栈共享空间，思考应开辟数组的空间是多少？
（2）汽车可以有不同种类，则他们的占地面积不同，收费标准也不同，如1辆客车和1。5辆小汽车的占地面积相同，1辆十轮卡车占地面积相当于3辆小汽车的占地面积。
（3）汽车可以直接从便道上开走，此时排在它前面的汽车要先开走让路，然后再依次排到队尾。
（4）停放在便道上的汽车业收费，收费标准比停放在停车场的车低，请思考如何修改结构以满足这种要求。
 */

/*
#include<stdio.h>
#include<stdlib.h>

//车辆信息
typedef struct{
    int id;
    int time;  // 车辆入库时间
}Car;


//两个共享空间的栈
typedef struct{
    Car * base_park;  // 停车场底
    //car * base_tmp;  // 离车时暂存底
    Car * top_park;
    //car * top_tmp;
    int size;
    int car_num;  // 已停放车数量
}* ParkStack;

// 创建车辆信息
int creatCar(Car * car, int id, int t){
    car->id = id;
    car->time = t;
    return 0;
}


// 构造一个长度为n的停车stack。
int initParkStack(ParkStack park_stack, int n){
    park_stack->base_park = (Car *)malloc(n * sizeof(Car));
    if(park_stack->base_park == NULL)exit(EXIT_FAILURE);
    park_stack->top_park = park_stack->base_park;
    //park_stack->base_tmp = &park_stack->base_park[n-1];  // base_tmp指向数组顶部
    //park_stack->top_tmp = park_stack->base_tmp;
    park_stack->size = n;
    park_stack->car_num = 0;
    return 0;
}


// return 0 通道未满， 1 通道已满。
int parkFull(ParkStack park_stack){
    //if(park_stack->top_park - park_stack->base_park >= park_stack->size)return 1;
    //return 0;
    if(park_stack->car_num==park_stack->size) return 1;
    return 0;
}


// return 0 通道未空， 1 通道已空。
int parkEmpty(ParkStack park_stack){
    //if(park_stack->base_park == park_stack->top_park) return 1;
    //return 0;
    if(park_stack->car_num==0) return 1;
    return 0;
}


// 车进通道
int pushPark(ParkStack park_stack, Car car){  // t: 进库时间
    if(parkFull(park_stack))exit(-1);  // 通道已满， 报错
    //park_stack->top_park->time = t;
    //park_stack->top_park->id = id;
    *park_stack->top_park++ = car;
    //park_stack->top_park++;
    park_stack->car_num++;
    return 0;
}

// 车出通道
Car popPark(ParkStack park_stack){  // t: 离库时间
    if(parkEmpty(park_stack))exit(-1);
    Car c = *--park_stack->top_park;
    return c;
}

// 中间车出库
int outPark(ParkStack park_stack){

}

int main(){
    ParkStack p;
    initParkStack(p,2);
    return 0;
}
*/

#include<stdio.h>
#include<stdlib.h>

// 汽车信息
typedef struct{
    char status;  // 记录车'A' 或 ‘D'.
    int id;
    int time;
}Car;

// 栈结构
typedef struct{
    int capacity;
    int top;
    Car * array;
}Stack;

/*
// 队列结构
typedef struct{
    int capacity;
    int front;
    int rear;
    int size;
    Car * array;
}Queue;
*/

// 队列节点
typedef struct node{
    Car car;
    struct node * next;
}node;

// 队列结构
typedef struct {
    node * front;
    node * rear;
    int num;  // 记录队列长度
}Queue;


// 初始化车辆信息
Car* create_car(char s,int id, int time){
    Car * car = (Car *)malloc(sizeof(Car));
    car->id = id;
    car->time = time;
    car->status = s;
    return car;
}


Stack* create_stack(int n){
    Stack * s = (Stack*)malloc(sizeof(Stack));
    if(!s)exit(-1);
    s->array = (Car*)malloc(sizeof(Car) * n);
    if(!s->array)exit(-1);
    s->capacity = n;
    s->top = 1;
    return s;
}

/*
// 创建队列
Queue* create_queue(int n){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    if(!q)exit(-1);
    q->array = (Car*)malloc(sizeof(Car) * n);
    if(!q->array)exit(-1);
    q->capacity = n;
    q->size = 0;
    q->front = 1;
    q->rear = 0;

}
*/

// 初始化呆头结点的队列
Queue* create_queue(){
    Queue * q = (Queue*)malloc(sizeof(Queue));
    if(!q)exit(-1);
    q->front=q->rear=(node*)malloc(sizeof(node));  // 创建头结点
    if(!q->front)exit(-1);
    q->front->next = NULL;
    q->num = 0;
    return q;
}


// 1 空， 0 非空
int stack_is_empty(Stack *s){
    if(s->top==1)return 1;
    return 0;
}
int queue_is_empty(Queue *q){
    return q->front->next==NULL;
}

// 1 满， 0 不满
int stack_is_full(Stack *s){
    if(s->top==s->capacity+1)return 1;
    return 0;
}

int push(Car *c, Stack *s){
    //if(stack_is_full(s))exit(-1);
    s->array[s->top++] = *c;
    return 0;
}

Car* pop(Stack *s){
    //if(stack_is_empty(s))exit(-1);
    s->top--;
    return &s->array[s->top];
}

// 入队
int enqueue(Queue *q, Car *c){
    node * p = (node*)malloc(sizeof(node));
    if(!p)exit(-1);
    p->car=*c;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    q->num++;
    return 0;
}

// 出队
Car dequeue(Queue *q){
    if(queue_is_empty(q))exit(-1);  // 如果保证操作队列绝对不空， 这条语句必要吗？
    Car c = q->front->next->car;  // 如果这里使用指针，free以后会不会丢失内存
    node * p = q->front;
    q->front=q->front->next;
    free(p);
    q->num--;
    return c;  // 如果是返回指针， 函数调用后， 指针所指向的内存释放。
}

// 车辆离开车库
Car out_car(Car *c, Stack *s, Stack *tmp){
    Car * car, result;
    while((car=pop(s))->id!=c->id){
        push(car, tmp);
    }
    result = *car;
    while(!stack_is_empty(tmp)){
        push(pop(tmp), s);
    }
    return result;
}

// 停车时间
int parking_time(Car a, Car*d){
    return (d->time)-(a.time);
}

// 收费, n:每分钟费用
int charge(int parking_time, int n){
    return n*parking_time;
}

// 停车场函数
int parking(){
    // 初始化两个栈
    int n;  // 停车场大小
    printf("请输入停车场大小：");
    scanf("%d", &n);
    Stack * park = create_stack(n);  // 停车场栈
    Stack * tmp = create_stack(n-1);  // 倒车时的暂存栈

    // 初始化便道
    Queue * road = create_queue();

    //Car * moved_car = NULL;
    Car * car = NULL;
    int flag = 1;  // 控制循环
    int i = 1;
    while(flag){
        // 初始化车辆信息

        if(!car){
            char status;
            int id;
            int time;
            printf("请输入车辆%d信息：", i);
            i++;
            scanf(" %c,%d,%d", &status, &id, &time);

            car = create_car(status, id, time);
        }

        switch(car->status){
            case 'A': if(!stack_is_full(park)){
                    push(car, park);
                    printf("%d号车辆位于停车场的%d号位。\n", car->id, park->top-1);  // 这样是不是破坏了封装性
                }else{
                    enqueue(road, car);
                    printf("%d号车辆位于便道的%d号位\n", car->id, road->num);  // 长整型
                }
                    car = NULL; break;
            case 'D': if(!queue_is_empty(road)){
                    //car = dequeue(road).time;
                    Car c = dequeue(road);
                    //Car * outed_car = out_car(car, park, tmp);
                    c.status = 'A';
                    c.time = car->time;
                    int time = parking_time(out_car(car, park, tmp), car);
                    int money = charge(time, 1);
                    printf("%d号车在车场内停车%d分钟，应交费%d元。\n", car->id, time, money);
                    car = &c;
                }else{
                    int time = parking_time(out_car(car, park, tmp), car);
                    int money = charge(time, 1);
                    printf("%d号车在车场内停车%d分钟，应交费%d元。\n", car->id, time, money);
                    car = NULL;

                }
                    break;
            case 'E': flag = 0; break;  // 结束停车场函数循
        }
//（‘A’，1，5）， （‘A’，2，10）， （‘D’，1，5）， （‘A’，3，20）， （‘A’，4，25）， （‘A’，5，30）， （‘D’，2，35）， （‘D’，4，40）， （‘E’，0，0）。
    }

}

int main(){
    parking();
    return 0;
}


struct a{
    int a;
;

struct a b;