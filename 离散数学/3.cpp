
#include<iostream>
#include<vector>
using namespace std;

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

std::vector<std::vector<int>> input_mat(){
  /**
   * 从标准输入获取矩阵
   * 连续两个回车表示输入结束
   */
  cout<<"input your materix, and end of double return:"<<endl;
  vector<vector<int>> m;
  int flag = 0;
  char c;
  m.push_back(std::vector<int>());
  while((c = getchar()) != '\n' || flag ){
    if(c == '\n'){
      if(flag){
      m.push_back(std::vector<int>());
      flag = 0;
       }
     }else if(c != ' '){
      m.back().push_back(int(c)-48);
      flag = 1;
    }
  }
  return m;
}


class ADJ_MATRIX{
public:
  ADJ_MATRIX(std::vector<std::vector<int>>); //构造函数
  vector<std::vector<int>> involution(int);//矩阵m的m次方
  int get_number(int num_m);//返回两两节点之间长度为m的通路的数目
private:
  vector<vector<int>> m;//原矩阵
  int direct = 0;//是否是有向图，默认0无向图
  int len=m[0].size();
};

ADJ_MATRIX::ADJ_MATRIX(vector<vector<int>> v):m(v){
  for(int i=0; i<len; i++){
    for(int j=0; j<len; j++){
      if(v[i][j] != v[j][i]) direct = 1;
    }
  }
  cout<<"origin matrix:"<<endl;
  display(m);
}

vector <std::vector<int>> ADJ_MATRIX::involution(int num_m){
  //实现矩阵的乘方
  vector<vector<int>> final_v(m); //保存最终结果
  vector<vector<int>> tmp_v(m); //保存中间结果
  int tmp=0;
  for(int m1=1; m1<num_m; m1++){
    for(int i=0; i<len; i++){
      for(int n=0; n<len; n++){
        for(int j=0; j<len; j++){
          tmp+=(tmp_v[i][j]*m[j][n]);
        }
        final_v[i][n] = tmp;
        tmp=0;
      }
    }
    tmp_v = final_v;
  }
  cout<<num_m<<" :"<<endl;
  display(final_v);
  return final_v;
}

int ADJ_MATRIX::get_number(int num_m){
  int sum = 0;
  vector<vector<int>> inv_v = involution(num_m);
  for(int i=0; i<len; i++){
    for(int j=0; j<len; j++){
      sum+=inv_v[i][j];
    }
  }
  if(!direct) {
    sum/=2;
    cout<<"Undirected graph, the number of paths with length "<<num_m<<" between two points is: ";
  //  cout<<"无向图，点两两之间长度为"<<num_m<<"的通路的数目 ：";
}else     cout<<"Directed graph, the number of paths with length "<<num_m<<" between two points is: ";
  cout<<sum<<endl;
  return sum;
}

int main(){
  std::vector<std::vector<int>> mat;
  mat = input_mat();
  ADJ_MATRIX adj_mat(mat);
  adj_mat.get_number(4);
}
