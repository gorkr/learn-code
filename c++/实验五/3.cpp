#include<iostream>
#include<math.h>
using namespace std;
double sqr(double x){
  //求平方根函数
  if(x<0)throw x;
  return sqrt(x);
}
int main(){
  double num;
  cout<<"input a number";
  cin>>num;
  try{
    cout<<sqr(num);
  }catch (double){
    cout<<"there is a error. Don't input negative number, try again, please."<<endl;
  }
  return 0;
}
