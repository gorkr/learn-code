//3、考课本例子，建立一个源程序文件，在此文件中建立一个新的类，将新
//建的类命名为Rect。
#include<iostream>
using namespace std;
class Rect
{
public:
  int Area_int();
  double Area_double();
  //---2. 重载构造函数
  Rect(double length,double width);
  Rect(int length,int width);
  ~Rect();
private:
  int nLength;
  int nWidth;
  double dLength;
  double dWidth;
};

//---1.计算面积
int Rect::Area_int(){
  return nLength*nWidth;
}
double Rect::Area_double(){
  return dLength*dWidth;
}

//---3。跟踪构造和析构
Rect::Rect(double length, double width):dLength(length),dWidth(width){
  cout<<"i'm the double constructor!"<<endl;//---3
}
Rect::Rect(int length, int width):nLength(length),nWidth(width){
  cout<<"i'm the int constructor!"<<endl;//---3
}
Rect::~Rect(){
  cout<<"i'm the destructor!"<<endl;
}
//---4
int main(){
  Rect r1(2,1);
  //另一个对象用指针实现(利用关键字new，给指针分配内存空间)   掌握动态内存分配。
  Rect *r2;
  r2 = new Rect(2.0, 1.0);
  delete r2;
  //析构函数什么时候调用， 为什么只运行醒一次析构函数， 所有对象难道是在共用一个类的资源？....因为没有delete
//  r2->Area_int();
  return 0;
}
