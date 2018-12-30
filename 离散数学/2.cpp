#include<iostream>
#include<vector>
using namespace std;
/**
 * 一个类， 实现基本的闭包运算
 * vector对象不能使用下标添加元素。
 */

void display(vector<vector<int>> v){
  //输出矩阵
  int len=v[0].size();
  for(int i=0;i<len;i++){
    for(int j=0;j<len;j++){
      cout.width(3);
      cout<<v[i][j];
    }
      cout<<'\n';
  }
  cout<<'\n';
}

class RELATION_MATRIX{
public:
  RELATION_MATRIX(vector<vector<int>>);
  vector<vector<int>> get_mr();//返回自反闭包
  vector<vector<int>> get_ms();//返回对称闭包
  vector<vector<int>> get_mt();//返回传递闭包
private:
  vector<vector<int>> m;//原矩阵
  vector<vector<int>> mc;//逆矩阵
  int len=m[0].size();
};

RELATION_MATRIX::RELATION_MATRIX(vector<vector<int>> v):m(v){
vector<vector<int>> p_mc(len,vector<int>(len));//初始化逆矩阵
vector<vector<int>> p_ix(len,vector<int>(len));//初始化单位矩阵
for(int i=0;i<len;i++){
  for(int j=0;j<len;j++){
      p_mc[j][i]= m[i][j];
  }
}
mc=p_mc;
cout<<"origin matrix:"<<endl;
display(m);
};

vector<vector<int>> RELATION_MATRIX::get_mr(){
  //自反闭包运算
  vector<vector<int>> mr(m);
  for(int i=0;i<len;i++){
    for(int j=0;j<len;j++){
      if(i==j)mr[i][j]=1;
    }
  }
  cout<<"Mr:"<<endl;
    display(mr);
    return mr;
}

vector<vector<int>> RELATION_MATRIX::get_ms(){
  //对称闭包
vector<vector<int>> ms(len,vector<int>());
  for(int i=0;i<len;i++){
    for(int j=0;j<len;j++){
      if(m[i][j]==1||mc[i][j]==1){
        ms[i].push_back(1);
      }else {
        ms[i].push_back(0);
      }
    }
  }
  cout<<"Ms:"<<endl;
    display(ms);
    return ms;
}

vector<vector<int>> RELATION_MATRIX::get_mt(){
  //washall算法得传递闭包
vector<vector<int>> mt(m);
  for(int i=0;i<len;i++){//i 代表列
    for(int j=0;j<len;j++){
      if(mt[j][i]){
        for(int k=0;k<len;k++){
          mt[j][k] = mt[j][k]||mt[i][k];
          }
        }
      }
  }
  cout<<"Mt:"<<endl;
    display(mt);
    return mt;
}


int main(){
  //使用了书上p124给出的矩阵
  vector<vector<int>> v={{1,1,0,0,0,0,0},
                         {0,0,0,1,0,0,0},
                         {0,0,0,0,1,0,0},
                         {0,1,0,0,0,0,0},
                         {0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0}};
  RELATION_MATRIX mat(v);
  mat.get_mr();
  mat.get_ms();
  mat.get_mt();
  return 0;
}
