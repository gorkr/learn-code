// 使用模板
// size_t 下标类型
// std::function
// 如何实现非模板类型动态赋值
// 复习广度深度优先生成树概念。
// 指针变量也和普通变量相同， 在函数内部给指针变量赋值，函数结束，也会丢失改变量

/**
 * 演示连通的无向图上，遍历全部结点的操作。
 * 以邻接多重表为存储结构，实现连通无向图的  深度优先和广度优先遍历。
 * 以用户指定的结点为起点，分别输出每种遍历下的  结点访问序列和相应生成树的边集。
 *
 * 设图的结点不超过30个，每个结点用一个编号表示（如果一个图有n个结点，则它们的编号分别为1，2，…，n）。
 * 通过输入图的全部边输入一个图，每个边为一个数对，可以对边的输入顺序作出某种限制。
 * 注意，生成树的边是有向边，端点顺序不能颠倒。
 */

// 可以写深度优先和广度优先 两种遍历方法， 将vist()函数作为参数，传入两种方法中

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "Queue.h"
#include "Tree.h"


const int MAX_VERTEX_NUM = 31;  // 留个头
enum class VisitIf{unvisited, visited};
struct InData{
    int head;
    int end;
};

// 边
struct EBox{  // edge的缩写吗？
    VisitIf mark;
    int ivex, jvex;
    EBox *ilink, *jlink;
    //int weight;  // 里程
    EBox(int iv,int jv):ivex(iv),jvex(jv),mark(VisitIf::unvisited),ilink(nullptr),jlink(nullptr){}
};

// 顶点
struct VexBox{
    // 顶点data
    VisitIf mark;
    int data;  // 用下标当做data
    //std::string city;
    EBox * firstedge;
};

class OLGraph{
private:
    std::vector<VexBox> adjmulist;
    int vexnum, edgenum;

    int FirstAdjVex(int v);
    int NextAdjvex(int v, int w);
    void DFS(int v, void (*visit)(VexBox n));
    void DFSTreeLoop(int v, Tree<int> * t);

public:

    OLGraph(InData * raw, int vn, int ln);
    void DFSTraverse(void (*visit)(VexBox n));
    void DFSTree(Tree<int> * t);
      // 从第v个定点开始，建立深度优先生成树
    void BFSTraverse(void (*visit)(VexBox n));
    void BFSTree(Tree<int> * &t);


    void SetUnvisit();


    static void PrintVex(VexBox v);

    ~OLGraph()= default;

};

void OLGraph::SetUnvisit() {
    for(auto it=adjmulist.begin(); it!=adjmulist.end();++it){  // 初始化标志位
        it->mark = VisitIf ::unvisited;
    }
}



void OLGraph::DFSTree(Tree<int> *t) {
    SetUnvisit();
    DFSTreeLoop(1,t);
}

void OLGraph::DFSTreeLoop(int v, Tree<int> * t){
    auto q = t;
    adjmulist[v].mark=VisitIf::visited;
    bool first = true;
    for(int w=FirstAdjVex(v); w>0; w=NextAdjvex(v,w)){
        if(adjmulist[w].mark==VisitIf::unvisited){
            auto p = new Tree<int>(w, nullptr, nullptr);
            if(first){
                t->firstchild=p;
                first = false;
            }else{
                while(bool(q->nextsibling))
                    q=q->nextsibling;
                q->nextsibling=p;
            }
            DFSTreeLoop(w,p);
        }
    }
}



void OLGraph::BFSTree(Tree<int> *&t){

    // 为什么  p更新了 t却没有。
     SetUnvisit();
     Queue<Tree<int>*,MAX_VERTEX_NUM> que;
     Tree<int>* p;

     adjmulist[1].mark=VisitIf::visited;
     t =new Tree<int>(adjmulist[1].data, nullptr, nullptr);
            que.EnQueue(t);
            while(!que.empty()){
                auto first = true;
                p = que.DeQueue();
                for(int w = FirstAdjVex(p->data); w>0; w = NextAdjvex(p->data,w)){
                    if(adjmulist[w].mark==VisitIf::unvisited){
                        adjmulist[w].mark=VisitIf::visited;
                        if(first){
                            p->firstchild = new Tree<int>(adjmulist[w].data, nullptr, nullptr);
                            t;

                            first = false;
                            que.EnQueue(p->firstchild);
                        }else{
                            while(bool(p->nextsibling))p=p->nextsibling;
                            p->nextsibling=new Tree<int>(adjmulist[w].data, nullptr, nullptr);
                            que.EnQueue(p->nextsibling);
                        }

                    }

                }
                }


            }


void OLGraph::BFSTraverse(void (*visit)(VexBox n)) {
    SetUnvisit();
    Queue<size_t,MAX_VERTEX_NUM> que;
    for(size_t i=1; i<=vexnum; i++){
        if(adjmulist[i].mark==VisitIf::unvisited){
            adjmulist[i].mark=VisitIf::visited;
            visit(adjmulist[i]);
            que.EnQueue(i);
            while(!que.empty()){
                auto p = que.DeQueue();
                for(int w = FirstAdjVex(p); w>0; w=NextAdjvex(p,w)){
                    if(adjmulist[w].mark==VisitIf::unvisited){
                        adjmulist[w].mark=VisitIf::visited;
                        visit(adjmulist[w]);
                        que.EnQueue(w);
                    }
                }
            }

        }
    }

}

/**
 * @param raw  一个边的数组
 * @param vn  顶点个数  ---------是不是可以没有  // 如果让下标对应存储data，可以用
 */
OLGraph::OLGraph(InData raw[], int vn, int ln):vexnum(vn),edgenum(ln){

    for(int i=0;i<=vn;i++){
        adjmulist.push_back(VexBox{VisitIf::unvisited, i, nullptr});
    }
    // 头插！！
    for(int i=0; i<edgenum; i++){
        // 多用auto关键字，尽量使用更现代化的方式来 new
        auto lin = new EBox(raw[i].head,raw[i].end);
        lin->ilink=adjmulist[lin->ivex].firstedge;
        lin->jlink=adjmulist[lin->jvex].firstedge;
        adjmulist[lin->ivex].firstedge=adjmulist[lin->jvex].firstedge=lin;
    }
}


void OLGraph::PrintVex(VexBox v){
    std::cout << v.data<< ' ';
}

/**
 *下标为v的节点的第一个临接节点
 * @param g 无向图对象
 * @param v 当前节点下标
 * @return  int，第一个相邻节点下标
 */
int OLGraph::FirstAdjVex(int v) {
    if(bool(this->adjmulist[v].firstedge))
    return  this->adjmulist[v].firstedge->ivex==v?this->adjmulist[v].firstedge->jvex:this->adjmulist[v].firstedge->ivex;
    else return 0;

}

/**
 * 下标为v的节点的w节点之后的临街点
 * @param g 无向图对象
 * @param v 在v上找临街点
 * @param w
 * @return int, 下一个临界点下标
 */
int OLGraph::NextAdjvex(int v, int w) {
    EBox *p = this->adjmulist[v].firstedge;
    while(p->ivex!=w&&p->jvex!=w){
        p = p->ivex==v?p->ilink:p->jlink;
    }
    p = p->ivex==v?p->ilink:p->jlink;
    if(bool(p))
        return p->ivex==v?p->jvex:p->ivex;
    else return 0;

}

/**
 * 递归访问一个回路
 * @param g 无向图对象
 * @param v 以v为入口
 * @param visit 访问函数
 */
void OLGraph::DFS(int v, void (*visit)(VexBox n) ){
    this->adjmulist[v].mark = VisitIf::visited;
    visit(this->adjmulist[v]);
    for(int w=FirstAdjVex(v);w > 0; w=NextAdjvex(v,w)){
        if(this->adjmulist[w].mark == VisitIf::unvisited) DFS(w, visit);
    }

}

void OLGraph::DFSTraverse(void (*visit)(VexBox n)) {
    SetUnvisit();

    for(int i=1; i<=this->vexnum; i++){
        if(this->adjmulist[i].mark==VisitIf::unvisited) DFS(i,visit);
    }
}


void test_graph(){
    InData raw[]={{1,2},{1,3},{3,6},{3,7},{6,7},{2,4},{2,5},{5,8},{8,4}};
    int vexnum=8, edgenum=9;
    OLGraph map(raw, vexnum, edgenum);

    std::cout<<"深度优先遍历: ";map.DFSTraverse(OLGraph::PrintVex);
    std::cout<<"\n广度优先遍历: ";map.BFSTraverse(OLGraph::PrintVex);
    std::cout<<std::endl<<"\n深度优先给生成树："<<std::endl;
    auto t = new Tree<int>(1, nullptr, nullptr);
    map.DFSTree(t);
    t->dispTree();



    std::cout<<std::endl<<"广度优先给生成树："<<std::endl;
    //auto b = new Tree<int>(1, nullptr, nullptr);
    Tree<int>* b;
    map.BFSTree(b);
    b->dispTree();


}

void interface(){
    int vexnum, edgenum;
    std::cout << "请输入顶点数量（如：8）：";
    std::cin >> vexnum;
    std::cout << "请输入边数量（如：9）：";
    std::cin  >> edgenum;
    auto raw = new InData [edgenum];
    std::cout << "请以(起-终 起-终)形式输入图数据，如：1-2 1-3 3-6 3-7 6-7 2-4 2-5 5-8 8-4" << std::endl;
    char ch;
    auto p = raw;
    while(true){
        std::scanf("%d-%d%c",&p->head,&p->end, &ch);
        if(ch=='\n')break;
        p++;
    }

    delete(raw);
    OLGraph map(raw, vexnum, edgenum);
    std::cout<<"深度优先遍历: ";map.DFSTraverse(OLGraph::PrintVex);
    std::cout<<"\n广度优先遍历: ";map.BFSTraverse(OLGraph::PrintVex);
}

int main() {

    test_graph();
    //interface();

    return 0;
}

/**
请输入顶点数量（如：25）：25
请输入边数量（如：30）：30
请以(起-终 起-终)形式输入图数据，如：1-3 2-3 3-4 4-5 5-6 6-7 7-8 8-9 3-13 13-12 12-11 11-20 20-18 18-25 18-17 17-19 19-12 17-23 23-24 17-22 17-16 14-16 16-15 14-15 22-16 22-21 13-14 5-12 6-11 7-10
1-3 2-3 3-4 4-5 5-6 6-7 7-8 8-9 3-13 13-12 12-11 11-20 20-18 18-25 18-17 17-19 19-12 17-23 23-24 17-22 17-16 14-16 16-15 14-15 22-16 22-21 13-14 5-12 6-11 7-10
*/