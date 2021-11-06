// du wj.2021.9.18 dsacpp Deng J.H THU
#ifndef LIST.H
#define LiST.H
#endif

using Rank = int; //秩
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; //列表节点位置
template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
// 成员
    T data; ListNodePosi<T> pred; ListNodePosi<T> succ; //数值、前驱、后继
// 构造函数
    ListNode() {} //针对header和trailer的构造
    ListNode ( T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL )
       : data ( e ), pred ( p ), succ ( s ) {} //默认构造器
// 操作接口
    ListNodePosi<T> insertAsPred ( T const& e ); //紧靠当前节点之前插入新节点
    ListNodePosi<T> insertAsSucc ( T const& e ); //紧随当前节点之后插入新节点
};

template <typename T> 
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e){
    ListNodePosi<T> x=new ListNode(e, pred, this);
    pred->succ=x;pred=x;
    return x;
}
template <typename T> 
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e){
    ListNodePosi<T> x=new ListNode(e, this, succ);
    succ->pred=x;succ=x;
    return x;
}

template <typename T> class List { //列表模板类
private:
    int _size; ListNodePosi<T> header; ListNodePosi<T> trailer; //规模、头哨兵、尾哨兵
protected:
    void init(){//列表创建时的初始化
        header=new ListNode<T>;
        trailer=new ListNode<T>;
        header->succ=trailer; header->pred=nullptr;
        trailer->pred=header; trailer->succ=nullptr;
        _size=0;
    }
    int clear(){//清除所有节点
        int oldSize=_size;
        while(0<_size) remove(header->succ);
        return oldSize;
    }
    void copyNodes ( ListNodePosi<T> p, int n){//复制列表中自位置p起的n项
        init();
        while(n--){
            insertAsLast(p->data);
            p=p->succ;
        }
    }
    ListNodePosi<T> merge ( ListNodePosi<T> p, int n, List<T> &L, ListNodePosi<T> q, int m){//归并
        ListNodePosi<T> pp=p->succ;
        while((0<m)&&(q!=p))
            if((0<n)&&(p->data)<=q->data){
                p=p->succ;
            }
            else{
                insert(L.remove((q=q->succ)->pred), p);
                m--;
            }
        return pp->succ;
    }
    void mergeSort ( ListNodePosi<T> &p, int n){//对从p开始连续的n个节点归并排序
        if(n<2) return;
        int m=n>>1;
        ListNodePosi<T> q=p;
        for(int i=0; i<m; i++) q=q->succ;
        mergeSort(p,m);
        mergeSort(q, n-m);
        p=merge(p, m, *this, q, n-m);
    }
    //void selectionSort ( ListNodePosi<T>, int ); //对从p开始连续的n个节点选择排序
    //void insertionSort ( ListNodePosi<T>, int ); //对从p开始连续的n个节点插入排序
    //void radixSort(ListNodePosi<T>, int); //对从p开始连续的n个节点基数排序
public:
// 构造函数
    List() { init(); } //默认
    List ( List<T> const& L ){//整体复制列表L
        copyNodes(L.first(), L.size());
    }
    List ( List<T> const& L, Rank r, int n ){//复制列表L中自第r项起的n项
        ListNodePosi<T> p=L.first();
        while(0<r--) p=p->succ;
        copyNodes(p,n);
    }
    List ( ListNodePosi<T> p, int n ){//复制列表中自位置p起的n项
        copyNodes(p,n);
    }
// 析构函数
    ~List(){//释放（包含头、尾哨兵在内的）所有节点
        clear();
        delete header;
        delete trailer;
    }
// 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    //T& operator[] ( Rank r ) const;//重载，支持循秩访问（效率低）
    ListNodePosi<T> first() const { return header->succ; } //首节点位置
    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置
    bool valid ( ListNodePosi<T> p ){//判断位置p是否对外合法
        return p && ( trailer != p ) && ( header != p );
    } //将头、尾节点等同于NULL
    ListNodePosi<T> find ( T const& e ) const //无序列表查找
    { return find ( e, _size, trailer ); }
    ListNodePosi<T> find ( T const& e, int n, ListNodePosi<T> p ) const{//无序区间查找
        while(n--)
            if(e==(p=p->pred)->data) return p;
        return nullptr;
    }
    ListNodePosi<T> search ( T const& e ) const //有序列表查找
    { return search ( e, _size, trailer ); }
    ListNodePosi<T> search ( T const& e, int n, ListNodePosi<T> p ) const{//有序区间查找
        //assert: 0<=n<=rank(p)<_size()
        do{
            p=p->pred;
            n--;
        } while((-1<n)&&(e<p->data));
        return p;
    }
    ListNodePosi<T> selectMax ( ListNodePosi<T> p, int n ){//在p及其n-1个后继中选出最大者
        ListNodePosi<T> max=p;
        for(ListNodePosi<T> cur=p; 1<n; n--)
            if((cur=cur->succ)->data<max->data) max=cur;
        return max;
    }
    ListNodePosi<T> selectMax() { return selectMax ( header->succ, _size ); } //整体最大者
// 可写访问接口
    ListNodePosi<T> insertAsFirst ( T const& e ){//将e当作首节点插入
        _size++;
        return header->insertAsSucc(e);
    }
    ListNodePosi<T> insertAsLast ( T const& e ){//将e当作末节点插入
        _size++;
        return trailer->insertAsPred(e);
    }
    ListNodePosi<T> insert ( ListNodePosi<T> p, T const& e ){//将e当作p的后继插入
        _size++;
        return p->insertAsSucc(e);
    }
    ListNodePosi<T> insert ( T const& e, ListNodePosi<T> p ){//将e当作p的前驱插入
        _size++;
        return p->insertAsPred(e);
    }
    T remove ( ListNodePosi<T> p ){//删除合法位置p处的节点,返回被删除节点
        T e=p->data;
        p->pred->succ=p->succ;
        p->succ->pred=p->pred;
        delete p;
        _size--;
        return e;
    }
    void merge ( List<T> & L ) { merge ( header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
    void sort ( ListNodePosi<T> p, int n ){//列表区间排序
        mergeSort(p,n);
    }
    void sort() { sort ( first(), _size ); } //列表整体排序
    int deduplicate(){//无序去重
        int oldSize=_size;
        ListNodePosi<T> p=first();
        for(Rank r=0; p!=trailer; p=p->succ)
            if(ListNodePosi<T> q=find(p->data, r, p))
                remove(q);
            else r++;
        return oldSize-_size;
    }
    int uniquify(){//有序去重
        if(_size<2) return 0;
        int oldSize=_size;
        ListNodePosi<T> p=first();
        ListNodePosi<T> q;
        while((q=p->succ)!=trailer)
            if(p->data!=q->data) p=q;
            else remove(q);
        return oldSize-_size;
    }
    //void reverse(); //前后倒置
// 遍历
    void traverse ( void (*visit ) ( T& ) ){//遍历，依次实施visit操作（函数指针，只读或局部性修改）
        for(ListNodePosi<T> p=header.succ; p!=trailer; p=p->succ)
            visit(p->data);
    }
    template <typename VST> //操作器
    void traverse ( VST& visit ){//遍历，依次实施visit操作（函数对象，可全局性修改）
        for(ListNodePosi<T> p=header.succ; p!=trailer; p=p->succ)
            visit(p->data);
    }
}; //List