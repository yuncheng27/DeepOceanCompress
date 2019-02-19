#pragma once
#include<string>
#include<vector>

struct CharInfo
{
    char _ch;
    unsigned long long _count;
    std::string _strCode;  //获取字符的编码

    CharInfo operator+(const CharInfo &info)
    {
        return CharInfo(_count + info._count);
    }

    bool operator>=(const CharInfo &info)
    {
        return _count >= info._count;
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
        void CompressFile(const string &strFilePath);
        void UNCompressFile(const std::string &strFilePath);
    private:
        void GetHuffmanCode(HTNode<CharInfo> *_pRoot);
    private:
        std::vector<CharInfo> _fileInfo;
};
