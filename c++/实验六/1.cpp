#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
int i,j;
const int wd = 5; //位宽
cout<<"*";
for(i=1;i<=9;i++)
{
  cout.width(wd);
cout<<i;
}
cout<<endl;
for(i=1;i<=9;i++)
{

cout<<i;
for(j=1;j<=i;j++){
    cout.width(wd);
    cout<<i*j;
}

cout<<'\n';
}

return 0;
}
