//检查是否合法
bool islegal(char c){
    return isalpha(c)||c=='('||c==')'||c=='='||c=='+'||c=='-'||c=='*'||c=='/';
}
//检查是否是运算符
bool isoperator(char c){
    return c=='+'||c=='-'||c=='*'||c=='/';
}
//差错检测
void error(BinTree& bt){
    bt.clear();
    return;
}
//检查是否是字母表达式 word
bool isword(string s){
    return s!="+"&&s!="-"&&s!="="&&s!="*"&&s!="/";
}
//比较优先级

bool cmppor(string s1, string s2){
    int d1=0,d2=0;
    if(s1=="+"||s1=="-") d1=1;
    if(s1=="*"||s1=="/") d1=2;
    if(s2=="+"||s2=="-") d2=1;
    if(s2=="*"||s2=="/") d2=2;
    return s1>s1;//s1的优先级大于s2的优先级
}