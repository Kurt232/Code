#ifndef BINNODE_H
#include<stack>
#include"HuffChar.h"
#define BINNODE_H
#endif

class BinNode{
    public:
    HuffChar ch;
    BinNode* ls, *rs, *pa;//ls leftson 左儿子 rs rightson 右儿子 pa parent 父亲
    BinNode(): ls(nullptr), rs(nullptr), pa(nullptr){}
    BinNode(HuffChar c, BinNode* _ls=nullptr, BinNode* _rs=nullptr, BinNode* _pa=nullptr): ch(c), ls(_ls), rs(_rs), pa(_pa){}
    //~BinNode();
    //前序遍历
    void travPre(char& ss){
        std::stack<BinNode*> s;//辅助栈
        if(!this) s.push(this);
        while(!s.empty()){
            BinNode* x=s.top();s.pop();
            //待改
            if(x->rs) s.push(x->rs);
            if(x->ls) s.push(x->ls);//左先出去 于是是先序
        }
    }
    //后序遍历
    void travPost(char& ss){
        std::stack<BinNode*> s;
        BinNode* x=this;
        if(x) s.push(x);
        while(!s.empty()){
            if(s.top()!=x->pa){
                while(BinNode* y=s.top()){
                    if(y->ls){
                        if(y->rs) s.push(y->rs);
                        s.push(y->ls);
                    }
                    else{
                        s.push(y->rs);//如果右子树没有 压入nullptr 使while退出
                    }
                }
                s.pop();//最后栈顶有个一个nullptr
            }
            x=s.top();s.pop();
            //待改
        }
    }
};