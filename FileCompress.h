#pragma once
#include<string>
#include<vector>
#include"Huffman.hpp"

typedef unsigned char UCH;
struct CharInfo
{
    CharInfo(unsigned long long count = 0)
      :_count(count)
    {}

    UCH _ch;
    unsigned long long _count;
    std::string _strCode;  //获取字符的编码

    CharInfo operator+(const CharInfo &info)
    {
        return CharInfo(_count + info._count);
    }

    bool operator>(const CharInfo &info)
    {
        return _count > info._count;
    }
    bool operator!=(const CharInfo &info)const
    {
        return _count != info._count;
    }
    
};


class FileCompress
{
    public:
        FileCompress();
        void CompressFile(const std::string &strFilePath);
        void UNCompressFile(const std::string &strFilePath);
    private:
        void GetHuffmanCode(HTNode<CharInfo> *_pRoot);
        void WriteHeadInfo(FILE* pf, const std::string& strFileName);
        void GetLine(FILE* pf, std::string& strContent);
    private:
        std::vector<CharInfo> _fileInfo;
};

