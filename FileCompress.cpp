#include"FileCompress.h"
#include<iostream>
#include<assert.h>
using namespace std;

#include"Huffman.hpp"

FileCompress::FileCompress()
{
    _fileInfo.resize(256);
    for(size_t i = 0; i < 256; ++i)
    {
        _fileInfo[i]._ch = i;
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
    ht.CreateHuffmanTree(_fileInfo, CharInfo(0));

    //3.通过Huffman树获取每个字符的编码
    GetHuffmanCode(ht.GetRoot());

    //4.用获取到的Huffman编码来重新改写文件
    char ch = 0;
    char bitCount = 0;
    FILE *fcout = fopen("data.hzp", "w");
    assert(fOut);

    WriteHeadInfo(fOut, strFilePath);
    fseek(fIn, 0, SEEK_SET);
    while(true)
    {
        size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
        if(0 == rdSize)
            break;

        //用编码改写源文件
        for(size_t i = 0; i < rdSize; ++i)
        {
            string &strCode = _fileInfo[pReadBuff[i]].st;
            //AABB
            //A--->100
            //B--->101
            //ch =10010110

            //将每个字符的编码放在ch中
            for(size_t j = 0; j < strCode.size(); ++j)
            {
                ch <<= 1;
                if('1' == strCode[j])
                  ch |= 1;

                bitCount++;
                if(8 == bitCount)
                {
                  // ch写入到压缩文件中
                  fputc(ch, fOut);
                  ch = 0;
                  bitCount = 0;
                }
            }
        }

    }
    //最后一次的ch的8个比特位没有填充满
    if(bitCount > 0 && bitCount < 8)
    {
        ch <<= (8 - bitCount);
        fputc(ch, fOut);
    }

    delete[] pReadBuff;
    fclose(fIn);
    fclose(fOut);
}

void UNCompressFile(const std::string )
{
    string posFix = strFilePath.substr(strFilePath.rfind('.') +1);
      if(postFix != "hzp")
      {
          cout<<"压缩文件格式不对"<<endl;
          return;
      }
      FILE* fIn = fopen(strFilePath.c_str(), "r");
      if(nullptr == fIn)
      {
          cout<<"压缩文件打开失败"<<endl;
          return;
      }
      string strContent;
      GetLine(fIn, strContent);
      fclose(fIn);
}

void FileCompress::GetHuffmanCode(HTNode<CharInfo> *pRoot)
{
    if(nullptr == pRoot)
        return;

    GetHuffmanCode(pRoot->_pLeft);
    GetHuffmanCode(pRoot->_pRight);

    if(nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
    {
        HTNode<CharInfo> *pCur = pRoot;
        HTNode<CharInfo> *pParent = pCur->_pParent;
        string& strCode = _fileInfo[pRoot->_weight._ch]._strCode;
        while(pParent)
        {
            if(pCur == pParent->_pLeft)
              strCode += '0';
            else 
              strCode += '1';

            pCur = pParent;
            pParent = pCur->_pParent;
        }
        reverse(strCode.begin(), strCode.end());
    }
}


void FileCompress::WriteHeadInfo(FILE* pfi, const string& strFileName)
{
    // 源文件后缀
    std::string postFix = strFileName.substr(strFileName.rfind('.')); 
    // 有效编码的行数
    // 有效字符以及其出现的次数
    string strCharCount;
    size_t lineCount = 0;
    char szCount[32] = {0};
    for (size_t i = 0; i < 256; ++i)
    {
        if(0!=_fileInfo[i]._count)
        {
            strCharCount += _fileInfo[i]._ch;
            strCharCount += ',';
            memset(szCount, 0, 32);
            _itoa(_fileInfo[i].count, szCount, 10);
            strCharCount += szCount;
            strCharCount += "\n";
            lineCount++;
        }
    }
    string strHeadInfo;
    strHeadInfo += postFix;
    strHeadInfo += "\n";

    memset(szCount, 0, 32);
    _itoa(lineCount, szCount, 10);
    strHeadInfo += szCount;
    strHeadInfo += "\n";

    strHeadInfo += strCharCount;

    fwrite(strHeadInfo.c_str(), 1, strHeadInfo.size(), pf);
}

void GetLine(FILE* pf, string& strContent)
{
    while(!feof(pf))
    {
        char ch = fgetc(pf);
        if('\n' == ch)
          return;
        strContent += ch;
    }
}
