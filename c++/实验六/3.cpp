//如何在文件读取的同时修改
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
  //将两个文件链接
  char ch;
  ifstream fin1("file1.dat");//打开文件1
  ifstream fin2("file2.dat");//打开文件2
  ofstream fout("all.dat");//连接后，输出的文件
  while(((ch=fin1.get())!=EOF)||((ch=fin2.get())!=EOF)){
    fout.put(ch);
  }
  fin1.close(); fin2.close(); fout.close();//这里关闭fout之后，就不能再在后面使用fout了吗

  //将all中数据大写并打印
  string buffer="";//作为缓冲
  ifstream fin("all.dat");
  while((ch=fin.get())!=EOF){
    if(ch>='a'&&ch<='z')ch-=32;
    cout<<ch;
    buffer = buffer + ch;
  }
  fin.close();
  ofstream fout1("all.dat");
  fout1<<buffer;
  fout1.close();

/*
  fstream f("all.dat");
  while((ch=f.get())!=EOF){
    if(ch>='a'&&ch<='z')ch-=32;
    f.put(ch);
  }
  f.close();
*/
}
