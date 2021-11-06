#include "textEditor.h"

int main(){
    cout<<"请输入命令 输入H/h/'?'查询命令列表"<<endl;
    char c;
    string s,s1;
    int num;
    textEditor T;
    while(1){
        cin>>c;
        switch (c){
        case 'R':
        case 'r':
            cout<<"请输入读取文档的绝对路径"<<endl;
            cin>>s;
            T.ReadText(s);
            break;
        case 'W':
        case 'w':
            cout<<"请输出读取文档的绝对路径"<<endl;
            T.WriteText(s);
            break;
        case 'I':
        case 'i':
            cout<<"插入到前一行 先输入内容 换行后输入行号"<<endl;
            //cin>>s;
            getchar();
            getline(cin,s);
            cin>>num;
            T.InsertLine(s, num);
            break;
        case 'D':
        case 'd':
            T.DeleteLine();
            break;
        case 'F':
        case 'f':
            cout<<"输入'0'从第一行开始, 输入'1'对从当前行开始, 在下一行输入文本s"<<endl;
            cin>>num;
            cin>>s;
            T.FindLine(s, num);
            break;
        case 'C':
        case 'c':
            cout<<"输入'0'对当前行使用, 输入'1'对全局使用"<<endl;
            cin>>num;
            cout<<"在第二行输入查找文本"<<endl;
            cin>>s;
            cout<<"在第三行输入替换文本"<<endl;
            cin>>s1;
            T.ChangeText(s,s1,num);
            break;
        case 'Q':
        case 'q':
            if(T.Quit()){
                exit(0);
            }
            break;
        case 'H':
        case 'h':
        case '?':
            T.Help();
            break;
        case 'N':
        case 'n':
            T.NextLine();
            break;
        case 'P':
        case 'p':
            T.PrevLine();
            break;
        case 'B':
        case 'b':
            T.BeginLine();
            break;
        case 'E':
        case 'e':
            T.EndLine();
            break;
        case 'G':
        case 'g':
            cin>>num;
            T.GotoLine(num);
            break;
        case 'V':
        case 'v':
            T.ViewText();
            break;
        default:
            cout<<"命令有误"<<endl;
            break;
        }
    }
}