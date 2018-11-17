
#include<iostream>
using namespace std;
class Time
{
public:
Time(int h,int m,int s);//构造函数
Time operator+(Time &);//运算符重载函数，实现两个时间的相加
void disptime();//显示时间函数
private:
int hours,minutes,seconds;
};

Time::Time(int h=0, int m=0, int s=0):hours(h),minutes(m),seconds(s){}

Time Time::operator +(Time &t){
  int all_seconds = (t.hours+hours)*3600+(t.minutes+minutes)*60+t.seconds+seconds; //将时间换算成秒后的总时间
  Time value; //相加结果
  value.hours=all_seconds/3600;
  value.minutes=all_seconds%3600/60;
  value.seconds=all_seconds%3600%60;
  return value;
}

void Time::disptime(){
  cout<<"the time is: "<<hours<<" hours, "<<minutes<<" minutes, "<<seconds<<" seconds."<<endl;
}

int main(){
  Time t1(1,1,1), t2(2,59,59);
  t1.disptime();t2.disptime();

  cout<<"all of ";
  (t1+t2).disptime();
}
