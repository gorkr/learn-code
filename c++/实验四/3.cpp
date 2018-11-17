//友元重载双目运算符，不加命名空间
//返回值是引用时，不能直接对引用调用方法，返回的引用会在函数返回会，结束恒明周期而被释放。要先将返回的引用存储在另一个对象中。
#include<iostream>
using namespace std;
class Point{
public:
  //三个构造函数
  Point();
  Point(double, double);
  Point(const Point &);
  //两个重载成员函数, 实现偏移
  void offert(int, int); //参数是偏移量
  void offert(Point &);// 点对象是偏移量
  //六个重载函数
  bool operator ==(Point &); //判断两个点对象是否相等；
  void operator +=(Point &);//将两个点对象相加；
  void operator ++();//将当前对象自增1（前缀）；
  void operator ++(int );//将当前对象自增1（后缀）；
  friend Point& operator +(Point &, Point &);
  friend Point& operator -(Point &, Point &);
  //访问私有数据
  int GetX();
  int GetY();
  //输出数据成员
  void Display();
private:
  int x;//横坐标
  int y;//纵坐标
};

//构造函数
Point::Point():x(0),y(0){};
Point::Point(double x, double y):x(x),y(y){};
Point::Point(const Point &p){
  x= p.x; y=p.y;
}

//重载成员函数
void Point::offert(int right, int bottom){
  //默认向右下偏移为正方向
  x+=right;
  y+=bottom;
}
void Point::offert(Point &p){
  x+=p.x;
  y+=p.y;
}

//重载运算符
bool Point::operator ==(Point &p){
  return (x==p.x&&y==p.y);
}
void Point::operator +=(Point &p){
  x+=p.x;y+=p.y;
}
void Point::operator ++(){
  x++;y++;
}
void Point::operator ++(int){
  x++;y++;
}

Point& operator +(Point& p1, Point& p2){
  Point q;
  Point &p=q;
  p.x=p1.x+p2.x; p.y=p1.y+p2.y;
  //p.Display();
  return p;
}
Point& operator -(Point& p1, Point& p2){
  Point q;
  Point &p=q;
  p.x=p1.x-p2.x; p.y=p1.y-p2.y;
  //p.Display();
  return p;
}

//存取器
int Point::GetX(){
  return x;
}
int Point::GetY(){
  return y;
}

void Point::Display(){
  cout<<"x is "<<GetX()<<" and y is "<<GetY()<<endl;
  //cout<<"x is "<<x<<" and y is "<<y<<endl;
}

int main(){
  Point p1, p2(1,2);
  p1.Display();
  p2.Display();
  p1++;
  p1.Display();

  Point p3=p1+p2,p4=p1-p2; //p3存取和的值，p4存取差的值
  p3.Display();
  p4.Display();
  if(p1==p2) cout<<"ture"<<endl;
  else cout<<"false"<<endl;
  return 0;
}
