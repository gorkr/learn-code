#include<iostream>
using namespace std;
const double pi=3.14;
class Container
{
protected:
double radius;
public:
Container(double r):radius(r){};//抽象类Container 的构造函数
virtual double surface_area()=0;//纯虚函数surface_area
virtual double volume()=0;//纯虚函数volume
};

class Sphere:public Container{
public:
  Sphere(double r):Container(r){};
  double surface_area();
  double volume();
};
double Sphere::surface_area(){
  //返回球体面积
  return 4*pi*radius*radius;
}
double Sphere::volume(){
  //返回球体体积
  return 4.0/3.0*pi*radius*radius*radius;
}

class Cylinder:public Container{
public:
  Cylinder(double r, double h):Container(r),height(h){};//构造函数
  double surface_area();
  double volume();
private:
  double height;
};
double Cylinder::surface_area(){
  //返回圆柱体面积
  return 2*pi*radius*radius+2*pi*radius*height;
}
double Cylinder::volume(){
  //返回圆柱体体积
  return pi*radius*radius*height;
}

class Cube:public Container{
public:
  Cube(double r):Container(r){};//构造函数
  double surface_area();
  double volume();
};
double Cube::surface_area(){
  //返回正方体面积
  return 6*radius*radius;
}
double Cube::volume(){
  //返回正方体体积
  return radius*radius*radius;
}

//模板类展示对象的表面积和体积
template<typename T>
void display(T &t){
  cout<<"the area is: "<<t.surface_area()<<" and the volume is "<<t.volume()<<endl;
}

int main(){
  Cube c(6.0); Sphere s(5.0); Cylinder cy(5.0, 6.0);
  display(c);display(s); display(cy);
  return 0;
}
