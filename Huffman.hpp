#pragma once
#include<queue>

template<class W>
struct HTNode
{
    HTNode(const W& weight)
        : _pLeft(nullptr)
        , _pRight(nullptr)
        , _weight(weight)
    {}

    HTNode *_pLeft;
    HTNode *_pRight;
    HTNode *_pParent;
    W _weight;
};

//仿函数
template<class W>
struct Compare
{
    bool operator()(HTNode<W> *pLeft, HTNode<W> *pRight)  //重载operator()
    {
        if(pLeft-> _weight >= pRight->_weight)
            return true;
        return false;
    }
};

template<class W>
class HuffmanTree
{
    typedef HTNode<W> Node;
    typedef Node *PNode;

    public:
        HuffmanTree()
            : _pRoot(nullptr)
        {}
        ~HuffmanTree()
        {
            Destroy(pRoot);
        }

    //创建 huffmantree
    void CreateHuffmanTree(const vector<W> &v, const W &invalid)
    {
        if(v.empty())
            return;
        //小堆  --创建二叉树森林
        std::priority_queue<PNode, vector<PNode>, Compare<W>> hp;
        for(size_t i = 0; i < v.size(); ++i)
        {
            if(v[i] != invalid)
                hp.push(new Node(v[i]));

        }
        
        while(hp.size() > 1)
        {
            PNode pLeft = hp.top();
            hp.pop();

            PNode pRight = hp.top();
            hp.pop();

            //以pleft和pright权值之和作为新节点的权值
            PNode pParent = new Node(pLeft->_weight + pRight->_weight);
            pParent->_pLeft = pLeft;
            pParent->_pRight = pRight;

            hp.push(pParent);
        }
        _pRoot = hp.top();
    }

    PNode GetRoot()
    {
        return _pRoot;
    }

    private:
    void Destroy(PNode &pRoot)
    {
        if(pRoot)
        {
            Destroy(pRoot->_pLeft);
            Destroy(pRoot->_pRight);
            delete pRoot;
            pRoot = nullptr;
        }
    }

    private:
        PNode pRoot;
};
