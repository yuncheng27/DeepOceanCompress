#include"FileCompress.h"
#include<iostream>
using namespace std;

#include"Huffman.hpp"

FileCompress::FileCompress()
{
    _fileInfo.resize(256);
    for(size_t i = 0; i < 256; ++i)
    {
        _fileInfo[i].ch = i;
        _fileInfo[i]._count = 0;
    }
}

void FileCompress::CompressFile(const std::string &strFilePath)
{
    //1.统计源文件中每个字符出现的次数
    FILE *fIn = fopen(strFilePath.c_str(), "r");
    if(nullptr == fIn)
    {
        cout << "打开文件失败" << endl;
        return;
    }

    char *pReadBuff = new char[1024];

    while(true)
    {
        size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
        if( 0 == rdSize)
        {
            break;
        }
        for(size_t i = 0; i < 1024; ++i)
            _fileInfo[pReadBuff[i]]._count++;
    }
    //2.以每个字符出现的次数为权值创建Huffman树
    HuffmanTree<CharInfo> ht;
    ht.CreateHuffmanTree(_fileInfo(0), CharInfo(0));

    //3.通过Huffman树获取每个字符的编码
    GetHuffmanCode(ht.GetRoot());

    //4.用获取到的Huffman编码来重新改写文件
    char ch = 0;
    char bitCount = 0;
    FILE *fcout = fope("data.hzp", "w");
    assert(fOut);

    fseek(fIn, 0, SEEK_SET);
    while(true)
    {
        size_t rdSize = fread(pReadBuff, 1, 1024, );
        if(0 == rdSize)
            break;

        //用编码改写源文件
        for(size_t i = 0; i < rdSize; ++i)
        {
            string &strCode = fileInfo[pReadBuff[i]].st;
            //AABB
            //A--->100
            //B--->101
            //ch =10010110

            //将每个字符的编码放在ch中
            for(size_t j = 0; j < strCode.size(); ++i)
            {
                ch <<= 1;
            }
        }

    }
}


void FileCompress::GetHuffmanCode(HTNode<CharInfo> *pRoot)
{
    if(nullptr == pRoot)
        return;

    GetHuffmanCode(pRoot->_pLeft);
    GetHuffmanCode(pRoot->_pRight);

    if(pRoot->_pLeft && pRoot->_pRight)
    {
        HTNode<CharInfo> *pCur = pRoot;
    }
}
