#include <iostream>
#include <string>
using namespace std;


struct Node{
    char ch;
    int weight;
    int parent, lchild, rchild;

    // 0判定为空
    explicit Node(char c=NULL, int w=NULL, int p=NULL, int l=NULL, int r=NULL)
            :ch(c),weight(w),parent(p),lchild(l),rchild(r){}

    bool operator < (const Node &P) {
        return this->weight < P.weight;
    }

    ~Node() = default;
};


/* Huffman类:哈夫曼树
 * 接口:
 * MakeEmpty:重置功能，重置哈夫曼树
 * DisSt:展示编码表
 * IsLeaf:判断对应节点是否为叶子节点
 * GetFreq:获取权重数组
 * BuildTree:根据权重数组构建哈夫曼树
 * BuildCode:根据哈夫曼树构建编码表
 * Expend:根据哈夫曼树展开压缩文本
 * Compress:根据编码表压缩原始文本
 */
class Huffman
{
//private:
public:
    int len;  // 权重数组长度
    int *weights; // 权重数组
    char *chars; // 编码表
   // Node *Root; // 哈夫曼树根
    Node *hf_tree;  // 节点数组
    int root;

    // 辅助功能函数
//    void MakeEmpty(Node *);
//    void BuildCode(Node *, char);
    /*
    bool IsLeaf(int i){
        return hf_tree[i].parent==0;
    }
*/

public:
    // 构造函数
    Huffman(int l, int w[], char s[]);
    // 析构函数
 //   ~Huffman();

    // 接口函数
//    void MakeEmpty();
//    void DisSt();

//    bool IsLeaf(Node*);
//    void GetFreq(int);
    void BuildTree();  // initalization
//    void BuildCode();
//    void PrintTree();  // 使用ASCII在终端打印树

//    std::char Expend(std::char);
//    std::char Compress(std::char);


};


/**
void Huffman::BuildTree() {
    // 储存配对堆
    PairHeap<Node> ph;

    // 将所有的字母生成对于的节点存入配对堆中
    for(int c = 0; c < R; c++)
        if (freq[c] > 0) {
            Node *NewNode = new Node();
            NewNode->ch = c;
            NewNode->left = NewNode->right = NULL;
            NewNode->weight = freq[c];
            ph.Insert(*NewNode);
        }

    // 将配对堆中最小的两个节点取出，进行合并，将合并后的节点重新加入配对堆
    // 特别注意:
    //		对于Node，应该处理其拷贝构造函数，因为我们将对其进行深拷贝
    while (ph.size() > 1) {
        Node *x = &ph.Top();
        ph.DeleteMin();
        Node *y = &ph.Top();
        ph.DeleteMin();

        Node *Parent = new Node();
        Parent->ch = '\0';
        Parent->left = x;
        Parent->right = y;
        Parent->weight = x->weight + y->weight;
        ph.Insert(*Parent);
    }

    // 储存根节点同时特殊处理，防止因数据析构而消失
    Root = new Node();
    *Root = ph.Top();
    ph.DeleteMin();
}
*/

Huffman::Huffman(int l, int w[], char s[])
        :len(l),weights(w),chars(s){
    hf_tree = new Node [root];  // 什么时候用this?
    root = 2*len-1;
}

void Huffman::BuildTree(){
   // Node *p = hf_tree;
    // 初始化叶子节点
    for(int i=0;i<len;++i){
        hf_tree[i].ch = chars[i];
        hf_tree[i].weight = weights[i];
    }

    // 构建树
    for(int i=len;i<root;++i){

        // 取得最小两权值的下标
        int min[2] = {0,0};
        int flag0=1, flag1=1;  // 最小值未被初始化
        for(int j=0; j<i; j++){
            if(hf_tree[j].parent==0){
                if(bool(flag0)){
                    min[0]=j;
                    flag0--;
                }else if(bool(flag1)){
                    min[1]=j;
                    flag1--;
                    if(min[0]>min[1]){  // 保证min[0]一定小于min[1]
                        int tmp = min[0]; min[0] = min[1]; min[1] = tmp;
                    }
                }else{
                    if(hf_tree[j] < hf_tree[min[0]])min[0]=j;
                    else if(hf_tree[j] < hf_tree[min[0]])min[1]=j;
                }
            }

        }
        // 根据最小下标 更新parent,lchild和rchild
        hf_tree[min[0]].parent = hf_tree[min[1]].parent = i;
        hf_tree[i].lchild = min[0]; hf_tree[i].rchild = min[1];
        hf_tree[i].weight = hf_tree[min[0]].weight + hf_tree[min[1]].weight;
    }
}

int main(){
    int len;
    cout<<"请输入字符集大小（任意整数，如5）:"<<endl;
    cin>>len;getchar();
    int weights[len];
    char chars[len];
    cout<<"以 字符，权值 方式输入数据,如( ,1 a,2 b,3 c,4 d,5)："<<endl;
    for(int i=0;i<len;i++){
        scanf("%c,%d",&chars[i], &weights[i]);getchar();
    }

    Huffman hf(len, weights, chars);
    hf.BuildTree();
    for(int i=0;i<2*len-1;i++){
        cout<<hf.hf_tree[i].weight<<"   "<<hf.hf_tree[i].parent<<"  "<<endl;
    }
}