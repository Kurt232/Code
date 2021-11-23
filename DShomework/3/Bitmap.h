#pragma once

#include <cstdio>
#include <cstdlib>
#include <memory.h>

class Bitmap
{
private:
  char *M;
  int N; //比特图所存放的空间M[]，容量为N*sizeof(char)*8比特
protected:
  void init(int n)
  {
    M = new char[N = (n + 7) / 8];
    memset(M, 0, N);
  }

public:
  Bitmap(int n = 1000) { init(n); } // 开大一点

  Bitmap(char *file, int n = 1000) //从文件中读取
  {
    init(n);
    FILE *fp = fopen(file, "r");
    fread(M, sizeof(char), N, fp);
    fclose(fp);
  }

  Bitmap(FILE* fp, int n=1000){
    init(n);
    fread(M, sizeof(char), N, fp);
  }

  ~Bitmap()
  {
    delete[] M;
    M = NULL;
  }

  void set(int k)
  {
    expand(k);
    M[k >> 3] |= (0x80 >> (k & 0x07));
  }
  void clear(int k)
  {
    expand(k);
    M[k >> 3] &= ~(0x80 >> (k & 0x07));
  }
  bool test(int k)
  {
    expand(k);
    return M[k >> 3] & (0x80 >> (k & 0x07));
  }

  void dump(char *file) //将位图整体导出至指定的文件，以便对此后的新位图批量初始化
  {
    FILE *fp = fopen(file, "a+");
    fwrite(M, sizeof(char), N, fp);
    fclose(fp);
  }

  char *bits2string(int n)
  {                //将前n位转换为字符串——
    expand(n - 1); //此时可能被访问的最高位为bitmap[n - 1]
    char *s = new char[n + 1];
    s[n] = '\0';
    for (int i = 0; i < n; i++)
      s[i] = test(i) ? '1' : '0';
    return s; //返回字符串
  }

  void expand(int k)
  { //若被访问的Bitmap[k]已出界，则需扩容
    if (k < 8 * N)
      return;
    int oldN = N;
    char *oldM = M;
    init(2 * k);
    memcpy_s(M, N, oldM, oldN);
    delete[] oldM;
  }
  void print(int n) //测试
  {
    expand(n);
    for (int i = 0; i < n; i++)
      printf(test(i) ? "1" : "0");
  }
};