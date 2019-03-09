#include"FileCompress.h"

int main()
{
    FileCompress fc;
    fc.CompressFile("data.txt");
    fc.UNCompressFile("data.hzp");
    return 0;
}
