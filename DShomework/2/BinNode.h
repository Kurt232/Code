#ifndef BINNODE.H
#define BINNODE.H
#endif

struct BinNode{
    char data;// ASCII码
    BinNode* ls, *rs, *pa;//ls leftson 左儿子 rs rightson 右儿子 pa parent 父亲

    BinNode(char _data=0, BinNode* _ls=nullptr, BinNode* _rs=nullptr, BinNode* _pa=nullptr): data(_data), ls(_ls), rs(_rs), pa(_pa){}
    ~BinNode();
};