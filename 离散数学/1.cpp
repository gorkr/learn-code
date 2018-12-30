#include<iostream>
#include<iomanip>
using namespace std;
void draw(int, int);//画真值表函数
void conjon(int p, int q){
  //合取
  cout.width(5);
  cout<<int(p&&q);
}
void disjon(int p, int q){
  //析取
  cout.width(5);
  cout<<int(p||q);
}
void condi(int p, int q){
  //条件
  cout.width(5);
  cout<<int(p&&!q);
}
void doub_condi(int p, int q){
  //双条件
  if(p==q){
    cout.width(5);
    cout<<1;
  }
  else{
    cout.width(5);
    cout<<0;}
}

void draw(int p, int q){
  //param:: p,q 1为true,0为false
  cout<<"--------------------------"<<'\n';
  cout<<setw(8)<<" con | "<<"dis |"<<"condi| "<<"dou"<<endl;
  cout<<"--------------------------"<<'\n';
  conjon(p,q);cout<<" |";disjon(p,q);cout<<'|';condi(p,q);cout<<'|';doub_condi(p,q);
}

int main(){
  draw(1,0);
  return 0;
}
