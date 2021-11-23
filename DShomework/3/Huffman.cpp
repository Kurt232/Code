#include"Huffman.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

int main(){
    char text_file[]="C:\\Users\\Karl\\Desktop\\Code\\DShomework\\3\\test_in.txt";
    char text_encode[]="C:\\Users\\Karl\\Desktop\\Code\\DShomework\\3\\text_encode.txt";
    char text_decode[]="C:\\Users\\Karl\\Desktop\\Code\\DShomework\\3\\text_decode.txt";
    int *frequency=statistics(text_file);//统计字符出现频率
    HuffForest* forest=initForest(frequency);//构建HuffmanForest
    BinTree* encodeTree=generateTree(forest);//构建HuffmanEncodeTree
    HuffTable* table=generateTable(encodeTree);//构建编码表
    
    //编码
    int size=-1;
    FILE* fp=fopen(text_file,"r");
    if(fp!=nullptr){
        fseek(fp,0,SEEK_END);
        size=ftell(fp);//返回的是偏移地址
    }
    fclose(fp);
    if(size==-1){
        std::cout<<"文件打开失败"<<std::endl;
        return 0;
    }
    int maxn=size;
    char* s=new char [maxn];
    FILE* fin=fopen(text_file,"r");
    fgets(s,maxn,fin);
    fclose(fin);
    Bitmap codeString(size);
    int length=encode(table, &codeString, s);
    codeString.dump(text_encode);
    //进行解码
    std::fstream out(text_decode, std::ios::out);
    std::string ss;
    Bitmap code(text_encode, length);
    decode(encodeTree, &code, length, ss);
    out<<ss;
    out.close();

    //2021.11.23 很奇怪 遇到换行符就终止了 可能是 encode 函数的问题



    //建立缓冲
    // std::ifstream in(text_file,std::ios::in);
    // if(in.is_open()) std::cout<<"good";
    // std::vector<std::string> buff;
    // std::string s;
    // while(getline(in,s)){
    //     buff.push_back(s);
    // }
    // //进行编码 并导出编码结果;
    // int length=0;
    // for(int i=0; i<buff.size(); i++){
    //     Bitmap codeString(buff[i].size());
    //     length=encode(table, &codeString, buff[i]);
    //     FILE* fout=fopen(text_encode,"a+");
    //     fprintf(fout, "%d ", length);
    //     fclose(fout);
    //     codeString.dump(text_encode);//导出
    // }
    // //进行解码
    // FILE* fin=fopen(text_encode, "r");
    // int len=0,num=0;
    // std::ofstream out(text_decode, std::ios::out);
    // while(!feof(fin)){
    //     fseek(fin, len, SEEK_SET);
    //     fscanf(fin,"%d", &num);
    //     getchar();
    //     Bitmap encodeString(fin, num);
    //     std::string ss;//解码文本
    //     decode(encodeTree, &encodeString, num, ss);
    //     len+=(num+7)/8+sizeof(int)+sizeof(char);
    //     out<<ss<<"\n";
    // }
    // fclose(fin);
    // out.close();
}