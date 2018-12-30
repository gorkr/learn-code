
//thi\]\898s is a strange /* way */
//返回值类型是引用， 这个引用是全局变量， 再将返回值作为右值时， 其实这个右值是这个全局变量。
//并不是将引用赋值给了引用
/*
#include<iostream>
using namespace std;
int &f(int &i){
  i+=10;
  return i;
}
int main(){
  int k = 0;
  int &m=f(k);//相当于 int &m = i;
  cout<<k<<endl;
  m=20;
  cout<<k<<endl;
  return 0;
}
*/


//所以 mian函数永远在程序最后调用
/*
#include<iostream>
using namespace std;
class Test{
public:
  Test(){
    cout<<"creat"<<endl;
  }
  ~Test(){
    cout<<"co"<<endl;
  }
};

int main(){
  cout<<"1"<<endl;
  return 0;
}
Test a;
*/

// 虚基类  跟static 一样吗
#include<iostream>
using namespace std;
class Base{
public:
  Base(){
    a=5;
  }
  int a;
};
class Base1: virtual public Base{
public:
  Base1(){
    a+=15;
  }
};
class Base2: virtual public Base{
public:
  Base2(){
    a+=10;
  }
  void dis(){cout<<a<<endl;}
};
class C:public Base1, public Base2{
public:
  C(){
    cout<<a<<endl;ii

  }
};
int main(){
  C c;
  c.dis();
}
