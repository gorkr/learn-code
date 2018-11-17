#include<iostream>
using namespace std;
class Time{
public:
  Time(){};
  Time(int, int, int);
  Time(const Time &);
  Time add(Time &);
  friend Time operator +(Time &, Time &);//重载+
  void display();//输出对象的数据成员
private:
  int hour;
  int minute;
  int second;
};
Time::Time(int h, int m, int s){
  hour = h;
  minute = m;
  second = s;
}
Time::Time(const Time &p){
  hour = p.hour;
  minute = p.minute;
  second = p.second;
}
Time Time::add(Time &p){
  Time value;int add_minute=0;int add_hour=0;//记录进位
  value.second = this->second+p.second;
  if(value.second>60){ //实现进位机制
    value.second -= 60;
    add_minute = 1;
  }
  value.minute = this->minute+p.minute+add_minute;
  if(value.minute>60){
    value.minute -= 60;
    add_hour = 1;
  }
  value.hour = this->hour + p.hour + add_hour;
  return value;
}
Time operator +(Time &p1, Time &p2){
  return p1.add(p2);
}
void Time::display(){
  std::cout<<"the time is "<<hour<<':'<<minute<<':'<<second<<endl;
}
int main(){
  Time t1(11, 45, 55), t2(2, 23, 5),t3;
  t1.display();t2.display();
  t3=t1+t2;
  t3.display();
  return 0;
}
