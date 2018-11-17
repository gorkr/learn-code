//问题： 只有在以指针在调用派生类的成员函数是， 调用的是基类的同名函数吗？
#include<iostream>
#include<string>
using namespace std;

class Time{
public:
Time(int h,int m, int s){
  hours=h;
  minutes=m;
  seconds=s;
}
void display()
{
  cout<<"出生时间："<<hours<<"时"<<minutes<<"分"<<seconds<<"秒"<<endl;
}
protected:
int hours,minutes,seconds;
};

class Date{
public:
Date(int m,int d,int y)
{
month=m;
day=d;
year=y;
}
void display()
{
  cout<<"出生年月："<<year<<"年"<<month<<"月"<<day<<"日"<<endl;
}
protected:
int month,day,year;
};

class Birthtime: public Time, public Date{
public: Birthtime(int, int, int, int, int, int, string);
void display();

private: string child_name;
};
Birthtime::Birthtime(int t_h, int t_m, int t_s, int d_m, int d_d, int d_y, string c_name):Time(t_h, t_m, t_s), Date(d_m, d_d, d_y), child_name(c_name){}
void Birthtime::display(){

  cout<<"name: "<<child_name<<" was born in "<<year<<"year "<<month<<"month "
  <<day<<"day "<<hours<<':'<<minutes<<':'<<seconds<<endl;
  //Date::display(); //调用日期展示函数
  //Time::display();  //调用时间展示函数
}

int main(){
  Birthtime bob(10, 1, 1, 200, 4, 2, "bob");
  bob.display();
  //Time tom(1,2,3);
  return 0;
}
