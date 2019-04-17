// 打印满二叉树
// 两个循环 一个迭代深度，一个迭代每层的节点

#include<stdio.h>

int main(){
  int i, j, k, depth = 4;
  for(j=0; j<depth; j++){
    int w = 1<<(depth-j+2); // 控制间隔， 只需要让下一层是上一层的1/2就可以;
                            //  w是这一行第一个元素 与左边距的距离
    if(j==0)printf("%*c\n",w,'_');
    else{
      for(i=0; i<1<<(j-1); i++){  // 1<<j等价于2^j，将1向左移动j位   ， 第二行循环一次  实现  _______/\_______  效果
        printf("%*c", w+1, ' ');  //  控制左边应有的空格
        for(k=0; k<w-3; k++)printf("_");  // w-3 是怎么决定的？？？
        printf("/ \\");  // 实现 左右分差效果：
        for(k=0; k<w-3; k++)printf("_");
        printf("%*c", w+2, ' ');
      }
      printf("\n");

      for(i=0;i<1<<(j-1); i++){
        printf("%*c/%*c_%*c", w, '_', w*2-2, '\\', w, ' ' );  // 实现两边的 _/  和  \_
      }
      printf("\n");
    }

    for(i=0;i<1<<j; i++){
      //printf("%*c_)%*c", w-1, '(', w-1, ' ');
      printf("%*c o %*c", w-2, ' ', w-1, ' ');
    }
    printf("\n");
  }
  return 0;
}
