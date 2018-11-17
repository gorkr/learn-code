#include<stdio.h>
int main(){
  char ch;
  while((ch=getchar())!='\n'){
    if((ch>='a'&&ch<'z')||(ch>='A'&&ch<'Z')){
      ch+=1;
    }else if(ch=='z'||ch=='Z'){
      ch-=25;
    }
    putchar(ch);
  }
}
