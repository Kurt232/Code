#define N_CHAR (0x80-0x20)//仅可打印字符

struct HuffChar{ //huffman char
    char ch;
    int weight;
    HuffChar(char c='^', int w=0): ch(c), weight(w){}
    bool operator< (HuffChar const& x){
        return weight<x.weight;
    }
    bool operator==(HuffChar const& x){
        return weight==x.weight;
    }
    bool operator<=(HuffChar const& x){
        return *this<x||*this==x;
    }
    bool operator>(HuffChar const& x){
        return !(*this<=x);
    }
    bool operator>=(HuffChar const& x){
        return !(*this<x);
    }
};
