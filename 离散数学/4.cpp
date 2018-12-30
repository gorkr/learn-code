/**
 *  实验4、最优树的构造：从键盘输入一组权值，构造出对应的最优树，列出构造过程。
 *
 * (1)根据给定的n个权值wl，w2，…，wn构成n棵二叉树的森林F={T1，T2，…，Tn}，其中每棵二叉树Ti中都只有一个权值为wi的根结点，其左右子树均空。
 * (2)在森林F中选出两棵根结点权值最小的树(当这样的树不止两棵树时，可以从中任选两棵)，
 *    将这两棵树合并成一棵新树，为了保证新树仍是二叉树，需 要增加一个新结点作为新树的根，
 *    并将所选的两棵树的根分别作为新根的左右孩子(谁左，谁右无关紧要)，将这两个孩子的权值之和作为新树根的权值。
 * (3)对新的森林F重复(2)，直到森林F中只剩下一棵树为止。这棵树便是哈夫曼树。 
 *
 * 分析：n个叶子的哈夫曼树要经过n-1次合并，产生n-1个新结点。最终求得的哈夫曼树中共有2n-1个结点。
 */
#include<iostream>
#include <iomanip>
using namespace std;

//二叉树结构
struct element{
  int weight; //权值
  int lchild, rchild, parent;//左叶，右叶，根结点
};


/**
 * 选区权值最小的两个节点
 * @param a  权值数组
 * @param n  数组长度
 * @param s1 权值最小的下标
 * @param s2 权值次小的下标
 */
void select_min(element a[], int n, int &s1, int &s2){
  for(int i=0; i<n; i++){
    if(a[i].parent == -1){
      s1 = i;
      break;
    }//??????????????????
  }
  for(int i=0; i<n; i++){
    //寻找最小权值的小标
    if(a[i].parent == -1 && a[s1].weight > a[i].weight)s1=i;
  }
  for(int j=0; j<n; j++){
    if(a[j].parent == -1 && j!=s1){
      s2 = j;
      break;
    }
  }
  for(int j=0; j<n; j++){
    //寻找权值次小的下标
    if(a[j].parent == -1 && a[s2].weight > a[j].weight && j!=s1)s2=j;
  }
}

/**
 * 最优二叉树算法(哈夫曼算法)
 * @param huftree [description]
 * @param w       权值数组
 * @param n       权值数组长度
 */
 void HuffmanTree(element huftree[], int w[], int n){
   for(int i=0; i<2*n-1; i++){
     //初始化
     huftree[i].parent = -1;
     huftree[i].lchild = -1;
     huftree[i].rchild = -1;
   }
   for(int i=0; i<n; i++){
     huftree[i].weight = w[i];
   }
   for(int k=n; k<2*n-1; k++){ //n-1次合并
     int i1,i2;
     select_min(huftree, k, i1, i2);
     huftree[i1].parent = k;
     huftree[i2].parent = k;
     huftree[k].lchild = i1;
     huftree[k].rchild = i2;
     huftree[k].weight = huftree[i1].weight + huftree[i2].weight;
   }
 }

void print(element hT[], int n){
   cout << "index weight parent lChild rChild" << endl;
   cout << left;    // 左对齐输出
   for (int i = 0; i < n; ++i)
   {
       cout << setw(5) << i << " ";
       cout << setw(6) << hT[i].weight << " ";
       cout << setw(6) << hT[i].parent << " ";
       cout << setw(6) << hT[i].lchild << " ";
       cout << setw(6) << hT[i].rchild << endl;
   }
}
int main()
{
    int x[] = { 2,3,5,7,8 };        // 权值集合
    element *hufftree=new element[2*8-1];    // 动态创建数组
    HuffmanTree(hufftree, x, 8);
    print(hufftree,15);
    system("pause");
    return 0;
}
