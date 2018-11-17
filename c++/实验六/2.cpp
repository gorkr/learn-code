#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
  int in;
  double dou;
  string str;
  ofstream fout("date.dat");
  if(!fout){
    cout<<"can't open the file.";
    return 1;
  }
  cin>>in>>dou>>str;//键盘输入
  fout<<"integer: "<<in<<"\ndouble: "<<dou<<"\nstring: "<<str<<endl;
  fout.close();
  return 0;
}
