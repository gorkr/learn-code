#include<iostream>
using namespace std;
class area
{
protected:
double height;
double width;
public:
area(double h,double w)
{
height=h;
width=w;
}
virtual double getarea()=0;
};

class Rectangle: public area{
public:
  Rectangle(double h, double w):area(h,w){};
  double getarea();
};
double Rectangle::getarea(){
  return height*width;
}

class Isosceles: public area{
public:
  Isosceles(double h, double w):area(h,w){};
  double getarea();
};
double Isosceles::getarea(){
  return width*height/2;
}

int main(){
  Rectangle * p1;//矩形对象指针
  Isosceles * p2;//三角形对象指针
  Rectangle rec(10.0,5.0);
  Isosceles iso(4.0, 6.0);
  p1=&rec;
  p2=&iso;
  //通过指针访问虚函数：
  cout<<"the area of the Rectangle is "<<p1->getarea()<<endl;
  cout<<"the area of the Isosceles is "<<p2->getarea()<<endl;
}
