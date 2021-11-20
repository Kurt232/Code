#ifndef BINNODE_H
#include<string>
#include<stack>
#define BINNODE_H
#endif
using namespace std;
class BinNode{
    public:
    string data;// ASCII码
    BinNode* ls, *rs, *pa;//ls leftson 左儿子 rs rightson 右儿子 pa parent 父亲
    BinNode(string _data="", BinNode* _ls=nullptr, BinNode* _rs=nullptr, BinNode* _pa=nullptr): data(_data), ls(_ls), rs(_rs), pa(_pa){}
    ~BinNode();
    //前序遍历
    void travPre(string& ss){
        stack<BinNode*> s;//辅助栈
        if(!this) s.push(this);
        while(!s.empty()){
            BinNode* x=s.top();s.pop();
            ss.append(x->data);
            if(x->rs) s.push(x->rs);
            if(x->ls) s.push(x->ls);//左先出去 于是是先序
        }
    }
    //后序遍历
    void travPost(string& ss){
        stack<BinNode*> s;
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
            ss+=x->data;
        }
    }
};