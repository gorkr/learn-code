#include<iostream>
using namespace std;
class Student{
public:
  void account(double);//设置分数，累计成绩，累计学生
  static double sum();//学生成绩和
  static double average();//全班平群成绩
private:
  double score;  //个人你成绩
  static double total_score; //总成绩
  static int count; //人数
};
void Student::account(double s){
  score = s;
  total_score += score;
  count++;
}
double Student::sum(){ //静态成员函数可以在类内定义吗
  return total_score;
}
double Student::average(){
  return total_score/count;
}
//初始化静态数据成员
double Student::total_score = 0.0;
int Student::count = 0;

int main(){
  Student s1,s2,s3;
  s1.account(99.9);
  s2.account(88.8);
  s3.account(77.7);
  cout<<"total score: "<<Student::sum()<<endl
      <<"average score: "<<Student::average()<<endl;
  return 0;
}
