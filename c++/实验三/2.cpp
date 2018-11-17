//如何在派生类中 与基类同名的函数中 拓展与基类同名函数的功能
//静态变量如何继承
//sting 的使用
#include<iostream>
#include<string>
using namespace std;

class Person{
public:
  Person(int i, string n, char m, int a):id(i), name(n), male(m), age(a){}
  void display(){
    cout<<"id："<<id<<" name: "<<name<<" male:"<<male<<" age: "<<age<<endl;
  }
protected:
  int id;
  string name;
  char male; //性别 f代表女性， m代表女性
  int age;
};

class Student: public Person{
public:
  Student(int i, string n, char m, int a, string s_m, double s_s):Person(i,n,m,a),major(s_m),score(s_s){};
  void display();
protected:
  string major;//系别
  double score;
};
void Student::display(){
  Person::display();
  cout<<"\r major: "<<major<<" score: "<<score<<endl;
}

class Teacher: public Person{
public:
  Teacher(int i, string n, char m, int a, string t_p, string t_d):Person(i,n,m,a),position(t_p),department(t_d){};
  void display();
protected:
  string position;//职位
  string department;//部门
};
void Teacher::display(){
  Person::display();
  cout<<"\r position: "<<position<<" department: "<<department<<endl;
}

int main(){
  Teacher bob(1,"bob",'m',25,"cs","cs");
  bob.display();
  return 0;
}
