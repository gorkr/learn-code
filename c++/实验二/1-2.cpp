//2、根据注释语句的提示，实现类Date 的成员函数。
#include<iostream>
using namespace std;
class Date
{
public:
void printDate();//显示日期
void setDay(int d);//设置日的值
void setMonth(int m);//设置月的值
void setYear(int y);//设置年的值
private:
int day,month,year;
};
void Date::printDate(){
  cout<<year<<'.'<<month<<'.'<<day<<endl;
}
void Date::setDay(int d){
  day = d;
}
void Date::setMonth(int m){
  month = m;
}
void Date::setYear(int y){
  year = y;
}
int main()
{
Date testDay;
testDay.setDay(5);
testDay.setMonth(10);
testDay.setYear(2014);
testDay.printDate();
return 0;
}
