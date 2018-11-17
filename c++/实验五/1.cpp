#include<iostream>
using namespace std;
template<class T>
T min(T x, T y, T z){
  if(x>y){
    if(y>z)return z;
    else return y;
  }else{
    if(x>z)return z;
    else return x;
  }
}

int main()
{
cout<<min(10,5,3)<<endl;
cout<<min(10.2,5.6,3.8)<<endl;
cout<<min('a','b','c')<<endl;
return 0;
}
