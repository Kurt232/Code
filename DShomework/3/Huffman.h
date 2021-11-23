#include<queue>
#include<map>
#include<string>
#include<cstring>
#include"BinTree.h"
#include"Bitmap.h"
#pragma region 

struct cmp{
    bool operator()(BinTree* x, BinTree* y){
        return x->root()->ch<y->root()->ch;//方便优先队列
    }
};

typedef std::priority_queue<BinTree*, std::vector<BinTree*>, cmp > HuffForest;
typedef std::map<char, char* > HuffTable;//char 算是整型 用其二进制数的表示 来记录编码
int* statistics(char* text_file){//统计字符出现频率 返回为数组形式
    int *freq=new int[N_CHAR];
    memset(freq,0,sizeof(int)*N_CHAR);//clear
    FILE* fp=fopen(text_file,"r");
    for(char ch; 0<fscanf(fp,"%c", &ch);)
        if(ch>=0x20) freq[ch-0x20]++;
    fclose(fp);
    return freq;
}

HuffForest* initForest( int* freq){
    HuffForest* forest=new HuffForest;
    for(int i=0; i<N_CHAR; i++){
        BinTree* x=new BinTree();
        x->insertRoot(HuffChar(0x20+i, freq[i]));
        forest->push(x);
    }
    return forest;
}

BinTree* generateTree(HuffForest* forest){
    while(1<forest->size()){
        BinTree* x=forest->top();forest->pop();
        BinTree* y=forest->top();forest->pop();
        BinTree* s=new BinTree();
        s->insertRoot(HuffChar('^', x->root()->ch.weight+y->root()->ch.weight));//完成huffman编码树的构建
        s->attachAsLs(s->root(), x);
        s->attachAsRs(s->root(), y);
        forest->push(s);
    }
    BinTree *s=forest->top();forest->pop();
    return s;
}

//O(nlogn)

//生成Huffman编码表
//递归前序遍历
void generateCharTable(Bitmap* code, int len, HuffTable* table, BinNode* x){
    if(!x->ls&&!x->rs){
        (*table)[x->ch.ch]=code->bits2string(len);
        return;
    }
    if(x->ls){
        code->clear(len);//向左儿子走 置位0
        generateCharTable(code, len+1, table, x->ls);
    }
    if(x->rs){
        code->set(len);//向右儿子走 置1
        generateCharTable(code, len+1, table, x->rs);
    }
}

HuffTable* generateTable(BinTree* tree){
    HuffTable* table=new HuffTable;
    Bitmap* code=new Bitmap;
    generateCharTable(code,0,table, tree->root());
    delete code;
    return table;
}

//编码 encode
int encode(HuffTable* table, Bitmap* code, std::string s){// s为目标文段 code 为编码后文段
    int len=0;//编码后长度
    int m=s.size();
    for(int i=0; i<m; i++){
        char* pCharCode=(*table)[s[i]];
        //判空
        if(!pCharCode) pCharCode=(*table)[s[i]+'A'-'a'];//只有大写字母
        if(!pCharCode) pCharCode=(*table)[' '];
        int n=strlen(pCharCode);
        for(int j=0; j<n; j++)
            '1'==pCharCode[j]? code->set(len++):code->clear(len++);
    }
    return len; //s编码后长度
}

//解码 decode
void decode(BinTree* tree, Bitmap* code, int len, std::string& s){// len 为 code长度
    BinNode* x=tree->root();
    for(int i=0; i<len; i++){
        x=code->test(i)? x->rs: x->ls;
        if(!x->ls&&!x->rs){
            s.push_back(x->ch.ch);
            x=tree->root();
        }
    }
    return;
}



