# 实验3 Huffman编码(二叉树应用)

## 实验的目的和要求

### 目的

    要求对文件进行Huffman编码的算法,以及对已编码文件进行解码的算法。
    熟练掌握二叉树的应用;

### 要求

    用户输入1.源文件名2.压缩后文件名3.解压后文件名  
    先统计源文件中各字符出现的频率，以字符出现的频率建立哈夫曼树，再将源文件大小和各字符出现的频率写入压缩文件。（要保留字符相关信息）。  
    然后从压缩文件名读取源文件大小以及各字符出现的频率，以字符出现的频率建立哈夫曼权，然后对压缩文件各字符进行解码，然后将解码后的字符写入目标文件中。

## 实现过程

    最小冗余码/哈夫曼码
    
    要求用户输入源文件和目标文件名，然后统计源文件中各字符出现的频率，以字符出现的频率建立哈夫曼树，再将源文件大小和各字符出现的频率写入目标文件，最后对源文件中各字节进行哈夫曼编码，将编码以比特为单位写入到目标文件

### 源代码解释

```
    Huffman.h 引用了这四个我写的数据结构
    BinNode.h BinTree.h Bitmap.h HuffChar.h
    其中HuffChar.h 中定义了编码的字符0x32-0x80，定义了权重weight
    其中BinNode.h 定义了BinNode类 为二叉树节点 其储存数据为HuffChar
    其中BinTree.h 定义了BinTree类 定义了二叉树的行为
    其中Bitmap.h 定义了数据结构 Bitmap 用二进制方式储存数据 进一步实现压缩 其定了一系列函数 读入二进制文件 翻译成string 等

    除此之外还用到了 queue 中的优先队列priority_queue 进行Huffman编码树的合并
    map 将代编码文本中的 char 和 01字符串对应
    string cstring更方便地处理字符串
    iostream fstream cstdio 处理输入输出
```

以下函数均在 Huffman.h头文件中：

### 读入文本文件并统计字符出现频率

```
    int* statistics(char* text_file);//统计字符出现频率 返回为数组形式
    从text_file文件中读取字符并统计
```

### 构造Huffman树

```
    HuffForest* initForest( int* freq)
    首先对每个频率对应字符char都建立一个二叉树 放到 priority_queue中

    BinTree* generateTree(HuffForest* forest)
    不断从HuffmanForest(priority_queue) 中pop出BinTree, 由于重新定义了结构体 struct cmp, priority_queue每次pop得到的都是最小频率，实现了huffman编码的实现
    再将每次pop的两个BinTree 合并为一个树
```

### 生成Huffman编码表

```
    void generateCharTable(Bitmap* code, int len, HuffTable* table, BinNode* x)
    递归地不断读取 bitmap的值，在Huffman树中 确定对应字符的编码
    HuffTable* generateTable(BinTree* tree)
    生成编码表
```

### 确定Huffman编码

```
    int encode(HuffTable* table, Bitmap* code, std::string s)
    不断从s中读取字符 借由table翻译成对应01字符串，再转存到code中
    由于期间没有控制字符，只有在书写主程序的时候维护控制字符
```

### 对源文件进行Huffman编码,写入目标文件

```
    void decode(BinTree* tree, Bitmap* code, int len, std::string& s)
    从code中去读文件 len确定长度 tree为Huffman编码树
    s为解码后的字符串
```

### 主函数解释 Huffman.cpp

```
    int *frequency=statistics(text_file);//统计字符出现频率
    HuffForest* forest=initForest(frequency);//构建HuffmanForest
    BinTree* encodeTree=generateTree(forest);//构建HuffmanEncodeTree
    HuffTable* table=generateTable(encodeTree);//构建编码表
    //依次执行
伪代码：
	建立缓冲 vector<string> buff;
	while(每行读取string到buff);
	for(对应buff中的每一行string){
		对string编码成code;
		code输入到text_encode文件;
	}
	for(从text_encode按行读入code){
		将code解码到string中;
		string输出到text_decode.txt;    int *frequency=statistics(text_file);//统计字符出现频率
    HuffForest* forest=initForest(frequency);//构建HuffmanForest
    BinTree* encodeTree=generateTree(forest);//构建HuffmanEncodeTree
    HuffTable* table=generateTable(encodeTree);//构建编码表
	}
```



