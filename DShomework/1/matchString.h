#ifndef MATCHSTRING.H
#include<string>
#define MATCHSTRING.H
#endif
using namespace std;

//KMP字符串匹配
int* buildNext (string P){ //构造模式串P的next
    size_t m=P.length(), j = 0; //文本串
    int* N=new int[m]; //next表
    int t=N[0]=-1; //模式串
    while (j < m - 1)
        if (0 > t||P[j] == P[t]) { //匹配
            N[j] =( P[++j] != P[++t] ? t : N[t] );
        }else //失配
        t=N[t];
    return N;
}
int match (string P, string T){  //KMP算法
    int* next = buildNext ( P ); //构造next表
    int n=T.length(), i = 0; //文本串指针
    int m=P.length(), j = 0; //模式串指针
    while ( j<m&&i<n ) //自左向右逐个比对字符
        if ( 0>j||T[i] == P[j]){//若匹配，或P已移出最左侧
            i++;
            j++;
        } //则转到下一字符
    else //否则
        j=next[j]; //模式串右移
    delete []next; //释放
    return i-j;
}