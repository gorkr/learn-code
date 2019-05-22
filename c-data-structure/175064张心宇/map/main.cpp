
// 复习广度深度优先生成树概念。

/**
 * 演示连通的无向图上，遍历全部结点的操作。
 * 以邻接多重表为存储结构，实现连通无向图的  深度优先和广度优先遍历。
 * 以用户指定的结点为起点，分别输出每种遍历下的  结点访问序列和相应生成树的边集。
 *
 * 设图的结点不超过30个，每个结点用一个编号表示（如果一个图有n个结点，则它们的编号分别为1，2，…，n）。
 * 通过输入图的全部边输入一个图，每个边为一个数对，可以对边的输入顺序作出某种限制。
 * 注意，生成树的边是有向边，端点顺序不能颠倒。
 */

#include <iostream>
#include <string>

const int MAX_VERTEX_NUM = 31;  // 留个头
typedef enum{unvisited, visited} VisitIf;
typedef struct InData{
    int start;
    int end;
}InData;

// 边
typedef struct EBox{  // edge的缩写吗？
    VisitIf mark;
    int ivex, jvex;
    struct EBox *ilink, *jlink;
    //int weight;  // 里程
}EBox;

// 顶点
typedef struct VexBox{
    // 顶点data
    //int data;  // 用下标当做data
    std::string city;
    EBox * firstdege;
}VexBox;

class OLGraph{
private:
    VexBox adjmulist[MAX_VERTEX_NUM];  // 选择动态生成， 还是静态？
    int vexnum, edgenum;
public:
    OLGraph(InData *, int);

};
OLGraph::OLGraph(InData raw[], int vn):vexnum(vn){
    //?

    /*
    int i=0;
    for(; bool(&raw[i]); i++){
        adjmulist[raw[i].start].data=raw[i].start;

    }
     */
}





int main() {

    InData raw[MAX_VERTEX_NUM];
    std::cout << "请以(起-终 起-终)形式输入图数据，如：1-3 2-3 3-4 4-5 5-6 6-7 7-8 8-9 3-13 13-12 12-11 11-20 20-18 18-25 18-17 17-19 19-12 17-23 23-24 17-22 17-16 14-16 16-15 14-15 22-16 22-21 13-14 5-12 6-11 7-10" << std::endl;
    //std::scanf("");
    char ch;
    InData * p = raw;
    while(true){
        std::scanf("%d-%d%c",&p->start,&p->end, &ch);
        if(ch=='\n')break;
        p++;
    }


    //delete(raw);



    return 0;
}