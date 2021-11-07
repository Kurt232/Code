#ifndef BINNODE.H
#include<string>
#define BINNODE.H
#endif

class BinNode{
    public:
    string data;// ASCII码
    bool por;
    BinNode* ls, *rs, *pa;//ls leftson 左儿子 rs rightson 右儿子 pa parent 父亲

    BinNode(string _data="", BinNode* _ls=nullptr, BinNode* _rs=nullptr, BinNode* _pa=nullptr, bool f=0): data(_data), ls(_ls), rs(_rs), pa(_pa), por(f){}
    ~BinNode();
};