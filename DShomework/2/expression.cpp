#include<iostream>
#include"BinNode.h"
#include"BinTree.h"
#include"Check.h"
#include<string>
#include<cctype>
using namespace std;
//处理输入
void in(string&s){
    printf("请输入下一行输入表达式\n");
    getline(cin,s);
    s.push_back('#');//结尾标记
}
//将表达式转化成二叉树
void execute(BinTree& bt, string s){
    bt.insert("");//插入根节点
    BinNode* p=bt.root();//当前位置
    string word="";//临时的 字母表示
    for(int i=0; i<s.size(); i++){
        char& c=s[i];
        if(islegal(c)||i==s.size()-1){//检查是否合法
            if(isalpha(c)){
                word.push_back(c);
            }
            else if(!isalpha(c)){
                if(c=='#'){//处理最后一个
                    if(!word.empty()) bt.insert(p,word);//一定在右儿子
                    else continue;
                }
                //优先级的变化
                if(c=='('&&p->por==0){
                    p->por=1;
                }
                else if(c==')'&&p->por==1&&p->ls&&!p->rs) bt.insert(p,word);//插入到右儿子
                else{
                    //差错检测
                    error(bt);
                    return;
                }
                //插入字母表达式
                if(isoperator(c)){
                    if(!p->ls&&p->data.empty()){
                        bt.insert(word,p);//只有第一次左儿子会是空的
                        word.clear();
                    }
                    if(isword(p->ls->data)&&p->data.empty()){
                        word.push_back(c);
                        p->data=word;
                        word.clear();
                    }
                    //插入算术运算符
                    if(!p->data.empty()&&!p->rs){
                        word.push_back(c);
                        if(p->por||cmppor(p->data,word)){//c的优先级更高
                            bt.insert()
                        }
                        else{//平级或更低

                        }
                        word.clear();
                    }
                    //p的位置移动
                    if(p->ls&&p->rs){
                        BinNode* t=p;
                        bt.insert("");
                        p=bt.root();
                        p->ls=t;
                    }
                }
                word.clear();
            }
        }
        else{
            error(bt);
            return;
        }
    }
}
//打印生成后的表达式
void out(BinTree& bt){
    if(bt.empty()) cout<<"输入字符串不是一个合法的表达式"<<endl;
    string s;//储存表达式
    cout<<s<<endl;
}
int main(){
    BinTree expr;
    string s;//暂存输入表达式
    in(s);//读入
    execute(expr, s);//将表达式转化成二叉树
    out(expr);//通过中序遍历将二叉树转换成表达式
}