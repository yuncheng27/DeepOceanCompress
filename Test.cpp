#include"FileCompress.h"

int main()
{
    char* pstr = "hh";
    FileCompress fc;
    fc.CompressFile("data.txt");
    fc.UNCompressFile("data.hzp");
    return 0;
}
