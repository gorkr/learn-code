//1、下面是一个计算器类的定义，请完成该类成员函数的实现。
#include<iostream>
using namespace std;
class Counter
{
public:
Counter(int number);
void increment(); //给原值加1
void decrement(); //给原值减1
int getValue(); //取得计数器值
int print(); //显示计数
private:
int value;
};
Counter::Counter(int number):value(number){}
void Counter::increment(){
  value++;
}
void Counter::decrement(){
  value--;
}
int Counter::getValue(){
  return value;
}
int Counter::print(){
  cout<<"value: "<<getValue()<<endl;
  return 0;
}
int main(){ //main写成了mian()
  Counter num(4);
  num.increment();
  num.print();
  return 0;
}
