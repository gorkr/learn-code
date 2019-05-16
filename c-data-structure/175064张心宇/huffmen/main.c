/**
 1）I：初始化（Initialization）。
 从终端读入字符集大小n，以及n个字符和n个权值，建立哈夫曼树，并将它存于文件hfmTree中。
（2）E：编码（Encoding）。
 利用以建好的哈夫曼树（如不在内存，则从文件hfmTree中读入），对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。
（3）D：译码（Decoding）。
 利用已经建好的哈夫曼树将文件CodeFile中的代码进行译码，结果存入文件TextFile中。
（4）P：打印代码文件（Print）。
 将文件CodeFile以紧凑格式显示在终端上，每行50个代码，同时将此字符形式的编码写入文件CodePrint中。
（5）T：打印哈夫曼树（Tree printing）。
 将已经在内存中的哈夫曼树以直观的方式（树或凹入表形式）显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中。
 */


/**
 * 在huffman数组里 包含 叶子数，叶子对应的编码 这些属性
 * 但这样内存占用就更多了吧
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



// 字符及其权值表
typedef struct{
    char c;
    unsigned int weight;
}CharNode,* CharMap;

// huffman 数组
typedef struct{
    int len;  // 叶子数
    char c;
    unsigned int weight;
    unsigned int parent, lchild, rchild;
    char * code;  // 叶子对应的编码
}HTNode, * HuffmanTree;

HuffmanTree initalization();  //

/*
// huffman 编码表
typedef struct{
    int len;
    char * value;  // 不能用整型， 因为有以0开头；用字符串存储
    char key;
}DicNode,* Dictionary;
*/

//  将内存中的hftree写入文件hfmTree中
void write_hfmtree(HuffmanTree hf){
    FILE * fp;
    fp = fopen("htmTree.dat", "w");

    if(!fp==NULL){
        fprintf(fp, "hufman数组结构：\n权\t父\t左\t右\n");
        HuffmanTree  p =hf;
        while(p->parent!=0){
            fprintf(fp,"%d\t%d\t%d\t%d\n",p->weight,p->parent,p->lchild,p->rchild);
            p++;
        }
        fprintf(fp,"%d\t%d\t%d\t%d\n",p->weight,p->parent,p->lchild,p->rchild);
    }
    fclose(fp);
    //if(fclose(fp)!=0)printf("Error with closing");
}

// 可以直接存入huffman中， 不必使用字符表
// HuffmanTree * hf
// 还应将生成的树 存储在 hfmTree文件中
HuffmanTree initalization(){
    // 构建字符表
    unsigned int map_len;
    printf("请输入字符集大小（任意整数，如27）:");
    scanf("%d", &map_len);getchar();  // getchar()读取回车
    CharMap map = (CharMap)malloc(map_len*sizeof(CharNode));
    printf("以 字符，权值 方式输入数据( ,1 a,2 b,3 c,4 d,5)：");
    for(int i=0;i<map_len;i++){
        scanf("%c,%d",&map[i].c, &map[i].weight);getchar();
        //printf("%c,%d ",map[i].c, map[i].weight);
    }

    // 创建huffman树
    int m = 2*map_len-1;
    HuffmanTree hf = (HuffmanTree)malloc(m*sizeof(HTNode));
    hf->len = map_len;
    unsigned i=0;HTNode*p=hf;
    for(;i<map_len;++i,++p){  // 赋值叶子节点
        p->c = map[i].c;
        p->weight = map[i].weight;
        p->parent=p->rchild=p->rchild=0;
        p->code = NULL;
    }
    for(;i<m-1;i++,++p){  // 赋值中间节点
        p->c='\0';
        p->weight=p->parent=p->rchild=p->rchild=0;
    }

    for(i=map_len;i<m;++i){  // 建huffman树

        // 取得最小的两个权值的下标
        unsigned int min[2] = {0,0}; // 存储最小的两个权值
        int flag0=1, flag1=1; // 最小值未被初始化
        for(unsigned int j=0;j<i;j++){
            if(hf[j].parent==0){
                if(flag0){min[0]=j;flag0--;}
                else if(flag1){min[1]=j;flag1--;
                    if(min[0]>min[1]){
                        unsigned int tmp = min[0];
                        min[0] = min[1];
                        min[1] = tmp;
                    }
                }
                else {
                    if(hf[j].weight < hf[min[0]].weight)min[0] = j;
                    else if (hf[j].weight < hf[min[1]].weight)min[1] = j;
                }
            }
        }

        hf[min[0]].parent = hf[min[1]].parent = i;
        hf[i].lchild = min[0];
        hf[i].rchild = min[1];
        hf[i].weight = hf[min[0]].weight + hf[min[1]].weight;
    }
    free(map);
    write_hfmtree(hf);
    // 为什么这条语句会影响到encoding 函数的写
    return hf;
}

void encoding(HuffmanTree hf){
    //Dictionary dic = (Dictionary)malloc(hf->len*sizeof(DicNode));
    // 字符对应编码
    char * code = (char *)malloc(hf->len*sizeof(char));
    if(!code)exit(-1);

    for(int i=0;i<hf->len;++i){  // 从叶子节点，向上回溯
        int start = hf->len-1;
        // ~~code字符串为什么无法更改字符~~, 不是无法更改,是前面是空白,认定为空字符串,无法输出,也无法执行其他操作
        code[hf->len]='\0';
        int j =i;
        for(int p=hf[j].parent; p!=0;j=p,p=hf[p].parent){
            if(hf[p].lchild==j){
                code[--start] = '0';
                }
            else {code[--start] = '1';
                }
        }
        hf[i].code = (char*)malloc((hf->len-start)*sizeof(char));

        //strcpy(hf[i].code, code);  这样只会把空串复制过去
        for(int k=0;start<hf->len;start++,k++){
            hf[i].code[k]=code[start];
        }
        //puts(hf[i].code);
    }
    free(code);

    // 读取文件，并进行编码
    FILE * fp_r, * fp_w;
    fp_r = fopen("ToBeTran.txt", "r");
    fp_w = fopen("CodeFile.dat", "w");
    int ch;
    ch = getc(fp_r);
    while(ch != EOF){
        HuffmanTree p = hf;
        for(int i = 0; i<hf->len; i++,p++){
            if(p->c==ch)break;
        }
        ch = getc(fp_r);
        fputs(p->code, fp_w);
    }
    fclose(fp_r);fclose(fp_w);
}

void decoding(HuffmanTree hf){
    FILE * fp_r, * fp_w;
    fp_r = fopen("CodeFile.dat", "r");
    fp_w = fopen("TextFile.txt", "w");
    HTNode root = hf[2*hf->len-2];  // 根节点
    HTNode p =root;
    int ch;
    ch = getc(fp_r);
    while(ch!=EOF){
        if(p.code==NULL){
            // p节点不是叶子节点
            if(ch=='0')p=hf[p.lchild];
            else p=hf[p.rchild];
            ch = getc(fp_r);
        }else{
            // p节点是叶子 节点
            fputc(p.c, fp_w);
            p = root;
        }

    }
    fputc(p.c, fp_w);
}



int main(){

    HuffmanTree hf = initalization();
    //encoding(hf);
    //decoding(hf);
    return 0;

}