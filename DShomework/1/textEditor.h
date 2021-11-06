#ifndef TEXTEDITOR.H
#include<iostream>
#include<fstream>
#include<string>
#include"List.h"
#include"matchString.h"
#define TEXTEDITOR.H
#endif
using namespace std;
class textEditor{
	List<string> textBuff;//缓冲区
	int curNo;//当前行号
	ListNodePosi<string> cur;//当前行
	bool f;//判断是否输入了文本

	public:
	textEditor(){
		List<string> textBuff;
		curNo=0;
		cur=nullptr;
		f=1;
	}
	~textEditor(){}

	void ReadText(string s){
		ifstream istrm(s,std::ios::binary);
		if(!istrm.is_open()){
			cout<<"未成功打开"<<endl;
			return;
		}
		if(!textBuff.empty()){
			cout<<"已有文本 是否重新读入？"<<endl;
			cout<<"是 输入 1 否输入 0"<<endl;
			int op;
			cin>>op;
			if(!op) return;
		}
		string str;
		while(getline(istrm,str)){
			textBuff.insertAsLast(str);
		}
		f=0;
		cur=textBuff.first();
		cout<<"成功打开"<<endl;
	}
	void WriteText(string s){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		ofstream ostrm(s, std::ios::binary);
		ListNodePosi<string> p=textBuff.first();
		while(!textBuff.empty()){
			ostrm<<p->data<<"\n";
			p=p->succ;
			textBuff.remove(p->pred);
		}
	}
	void InsertLine(string s, int num){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		ListNodePosi<string> p=cur;
		int n=num-curNo,step=1;
		if(n>0) step=-1;
		while(n){
			if(step==-1) p=p->succ;
			else p=p->pred;
			n+=step;
			if(!textBuff.valid(p)) break;
		}
		if(n) cout<<"错误的行号"<<endl;
		else{
			p->insertAsPred(s);
		}
	}
	void DeleteLine(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		textBuff.remove(cur);
	}
	void FindLine(string s, int num){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		ListNodePosi<string> p=cur;
		int no=curNo;
		if(!num){ p=textBuff.first(); no=0;}
		if(num!=0&&num!=1){
			cout<<"输入错误"<<endl;
			return;
		}
		bool f1=0;
		for(;textBuff.valid(p);p=p->succ){
			if(match(s,p->data)<(p->data).length()){f1=1; break;}
			no++;
		}
		if(f1) cout<<no<<endl;
		else cout<<"未找到"<<endl;
	}

	void ChangeText(string s, string s1, int num){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		ListNodePosi<string> p=cur;
		int no=0;
		if(num){
			p=textBuff.first();
			for(;textBuff.valid(p);p=p->succ){
				int i=0;
				while(1){
					string text(p->data,i);
					i+=match(s,text);
					int j=0;
					for(; j<s.length()||j<s1.length(); j++){
						if(j<s.length()&&j<s1.length()){
							(p->data)[i+j]=s1[j];
						}
						else if(s.length()<=j&&j<s1.length()){
							(p->data).insert((p->data).begin()+i+j,s1[j]);
						}
						else if(j<s.length()&&s1.length()<=j){
							(p->data).erase(s1.length()+i+j);
						}
					}
					i+=j+1;
					if((p->data).length()<=i) break;
					else no++;
				}
			}
		}
		else{
			int i=0;
			while(1){
				string text(p->data,i);
				i+=match(s,text);
				int j=0;
				for(; j<s.length()||j<s1.length(); j++){
					if(j<s.length()&&j<s1.length()){
						(p->data)[i+j]=s1[j];
					}
					else if(s.length()<=j&&j<s1.length()){
						(p->data).insert((p->data).begin()+i+j,s1[j]);
					}
					else if(j<s.length()&&s1.length()<=j){
						(p->data).erase(s1.length()+i+j);
					}
				}
				i+=j+1;
				no++;
				if((p->data).length()<=i) break;
				else no++;
			}
		}
		if(no) cout<<"替换了"<<no<<"处"<<endl;
		else cout<<"未找到"<<endl;
	}
	int Quit(){
		return 1;
	}
	void Help(){
		cout<<"基本命令 大小写字母都可以输入\n";
    	cout<<"R:读取文本文件\n";
    	cout<<"W:将缓冲区的内容都写入文本\n";
    	cout<<"I:插入单个新行 输入新行和行号\n";
    	cout<<"D:删除该行并移动到下一行\n";
    	cout<<"F:查找目标串的第一行\n";
    	cout<<"C:将目标字符串修改为对应字符串\n";
    	cout<<"Q:退出编辑器立即结束\n";
    	cout<<"H:显示所有命令的帮助消息 '?'程序也能接受\n";
    	cout<<"N:当前行移动到下一行\n";
    	cout<<"P:当前行移动到上一行\n";
    	cout<<"B:当前行移动到首一行\n";
    	cout<<"E:当前行移动到尾一行\n";
    	cout<<"G:当前行移动到指定行号\n";
    	cout<<"V:查看缓冲区的全部内容\n";
		cout<<endl;
	}
	void NextLine(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		if(!textBuff.valid(cur->succ)){
			cout<<"已经到最后一行了"<<endl;
			return;
		}
		curNo+=1;
		cur=cur->succ;
	}
	void PrevLine(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		if(!textBuff.valid(cur->pred)){
			cout<<"已经到最前一行了"<<endl;
			return;
		}
		curNo+=-1;
		cur=cur->pred;
	}
	void BeginLine(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		curNo=0;
		cur=textBuff.first();
	}
	void EndLine(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		curNo=textBuff.size()-1;
		cur=textBuff.last();
	}
	void GotoLine(int num){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		if(num<0||num>=textBuff.size()){
			cout<<"错误的行数"<<endl;
			return;
		}
		ListNodePosi<string> p=textBuff.first();
		for(int i=0; i<=num; i++){
			p=p->succ;
		}
		cur=p;
		curNo=num;
	}
	void ViewText(){
		if(f){
			cout<<"未读入文本"<<endl;
			return;
		}
		for(ListNodePosi<string> p=textBuff.first(); textBuff.valid(p); p=p->succ){
			cout<<p->data<<endl;
		}
	}
};

