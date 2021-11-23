#ifndef BINTREE_H
#define BINTREE_H
#include"BinNode.h"
#endif

class BinTree: private BinNode{
    BinNode* _root;
    int _size;

    int removeAt(BinNode* x){
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
    BinNode* root() const {return _root;}

    int clear(){
        int n=0;
        if(_size>0) n=remove(_root);
        return n;
    }
    BinNode* insertRoot(HuffChar const &e){//插入根节点
        _size=1;
        return _root=new BinNode(e);
    }
    BinNode* insertAsLs(BinNode* x, HuffChar const &e){//插入为 x的左儿子
        _size++;
        if(x->ls) remove(x->ls);//保护
        x->ls= new BinNode(e,this);
        return x;
    }
    BinNode* insertAsRs(BinNode* x, HuffChar const &e){//插入为 x的右儿子
        _size++;
        if(x->rs) remove(x->rs);//保护
        x->rs= new BinNode(e,this);
        return x;
    }
    BinNode* attachAsLs(BinNode* x, BinTree* &s){//要求 x->ls==nullptr
        if(x->ls=s->_root) x->ls->pa=x;//接入
        _size+=s->size();
        s->_root=nullptr;
        s->_size=0;
        s->clear();
        s=nullptr;
        return x;
    }
    BinNode* attachAsRs(BinNode* x, BinTree* &s){//要求 x->rs==nullptr
        if(x->rs=s->_root) x->rs->pa=x;//接入
        _size+=s->size();
        s->_root=nullptr;
        s->_size=0;
        s->clear();
        s=nullptr;
        return x;
    }
    int remove(BinNode* x){
        if(x->pa){
            if(x==(x->pa)->ls) (x->pa)->ls=nullptr;
            else (x->pa)->rs=nullptr;
        }//切断来自父节点的指针
        else _root=nullptr;
        int n=removeAt(x);
        _size-=n;
        return n;
    }
};