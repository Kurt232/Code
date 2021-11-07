#ifndef BINTREE.H
#define BINTREE.H
#include"BinNode.h"
#endif

class BinTree: public BinNode{
    BinNode* _root;
    int _size;

    static int removeAt(BinNode* x){
        if(!x) return 0;
        int n=1+removeAt(x->ls)+removeAt(x->rs);
        delete x;
        return n;
    }

    public:
    BinTree():_size(0), _root(nullptr){}
    ~BinTree(){
        if(_size>0) remove(_root);
    }
    int size() const{return _size;}
    bool empty() const{return !_root;}
    BinNode* insert(char const& e){
        _size=1;
        return _root=new BinNode(e);
    }
    BinNode* insert(char const& e, BinNode* x){//插入为 x的左儿子
        _size++;
        if(x->ls) remove(x->ls);
        x->ls= new BinNode(e,this);
    }
    BinNode* insert(BinNode* x, char const& e){//插入为 x的右儿子
        _size++;
        if(x->rs) remove(x->rs);
        x->rs= new BinNode(e,this);
    }
    int remove(BinNode* x){
        if(!x->pa){
            if(!((x->pa)->ls)&&x==(x->pa)->ls) (x->pa)->ls=nullptr;
            if(!((x->pa)->rs)&&x==(x->pa)->rs) (x->pa)->rs=nullptr;
        }//切断来自父节点的指针
        int n=removeAt(x);
        _size-=n;
        return n;
    }
};