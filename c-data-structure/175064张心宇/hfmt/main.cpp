#include <iostream>
#include <string>
using namespace std;


class Node{
    // 储存元素
    char ch;
    int weigth;
    Node *Left;
    Node *Right;

    Node(){
        ch = NULL;  // 这样子占用的内存 和 ch = 'c'; 相同吗？
        weigth = NULL;
        Left = nullptr;
        Right = nullptr;
    }

    Node(const Node &P){
        ch = P.ch;
        weigth = P.weigth;
        if (P.Left == nullptr)
            Left = nullptr;
        else {
            Left = new Node();
            *Left = *(P.Left);
        }
        if (P.Right == nullptr)
            Right = nullptr;
        else {
            Right = new Node();
            *Right = *(P.Right);
        }
    }

    bool operator <= (const Node &P) {
        return this->weigth <= P.weigth;
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
public:
    // 构造函数
    Huffman();
    // 析构函数
    ~Huffman();

    // 接口函数
    void MakeEmpty();
    void DisSt();

    bool IsLeaf(Node*);
    void GetFreq(int);
    void BuildTree();  // initalization
    void BuildCode();

    std::string Expend(std::string);
    std::string Compress(std::string);

private:
    // 辅助功能函数
    void MakeEmpty(Node *);
    void BuildCode(Node *, string);

    // 数据成员
    int len;  // 数组长度
    int *freq; // 权重数组
    string *st; // 编码表
    Node *Root; // 哈夫曼树根
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
            NewNode->Left = NewNode->Right = NULL;
            NewNode->weigth = freq[c];
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
        Parent->Left = x;
        Parent->Right = y;
        Parent->weigth = x->weigth + y->weigth;
        ph.Insert(*Parent);
    }

    // 储存根节点同时特殊处理，防止因数据析构而消失
    Root = new Node();
    *Root = ph.Top();
    ph.DeleteMin();
}
*/

void Huffman::BuildTree() {

}


Huffman::Huffman(){
    cout<<"请输入字符集大小（任意整数，如5）:"<<endl;
    cin>>len;
    cout<<"以 字符，权值 方式输入数据,如( ,1 a,2 b,3 c,4 d,5)："<<endl;
    freq = new int [len];
    st = new string [len];
    for(int i=0; i<len; i++){
        scanf("%s,%d",&st[i], &freq[i]);getchar();
    }
}