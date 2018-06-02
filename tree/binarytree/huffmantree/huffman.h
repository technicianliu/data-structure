#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

template<class T> class HuffmanTree;

template<class T> class huff_node
{
     friend class HuffmanTree<T>;
     private:
        T data;
        unsigned weight;
        unsigned parent,left,right;
        huff_node():weight(0),parent(0),left(0),right(0) {} //这里的构造函数在new开辟的动态空间中也可以使用
};

typedef char** HuffmanCode;  //定义字符串数组；

template<class T> class HuffmanTree
{
     private:
        huff_node<T> *HT;  //结点向量
        int Size,maxsize;  //结点个数和最大空间
        int Min(int i) const; //求最小权值结点的序号函数
        void Select(int k,int &s1,int &s2); //选择两个根结点权值最小的子树构造新树
     public:
        HuffmanTree(int sz=100); //Huffman树初始化
        ~HuffmanTree() {delete []HT;} //销毁一棵Huffman树
        void CreatHuffmanTree(T *d,unsigned *w,int n); //建立一棵Huffman树
        void PrintHuffmanTree(HuffmanCode &HC,int n) const;  //输出Huffman树
        void HuffmanCoding(HuffmanCode &HC,int n); //Huffman编码
        void HuffmanUncoding(HuffmanCode &HC,int n,char *cd);

};


template<class T> int HuffmanTree<T>::Min(int i) const  //求当前权值当中的最小权值,是Huffman树类的成员函数，因此可以直接使用HT
{
    //要在一个数组找最小的数却又没有什么标准，常见做法是找最小的数时
    //找最小的数时初始化一个很大的数，找最大的树时初始化一个很小的树
    //或者将k初始化为数组中第一个数。
    int j,flag;
    unsigned k=65535;
    for(j=1;j<=i;j++)
    {
        if(HT[j].weight<k&&HT[j].parent==0)
        {
            k=HT[j].weight;
            flag=j;
        }
    }
    HT[flag].parent=1;  //防止该结点再次被比较。因为需要连续找两个最小权值的出来才行。
    return flag;
}

template<class T> HuffmanTree<T>::HuffmanTree(int sz)
{
    Size=0;
    maxsize=sz;
    HT=new huff_node<T>[sz];   //这里已经对各个权值和指示器初始化过了，有默认参数。
}

template<class T> void HuffmanTree<T>::CreatHuffmanTree(T *d,unsigned *w,int n)
//建立一有n个叶子结点(带权结点)的Huffman树，其中，带权结点自身数据由数组d提供，权值由数组w提供
{
    int i,m,s1,s2;
    huff_node<T> *p;

    if(n<1) {return;}
    m=2*n-1; //m代表结点总数
    if(maxsize<m+1)
    {
        delete []HT;
        HT=new huff_node<T>[m+1]; //0号单元不用
        maxsize=m+1;
    }

    for(p=HT+1,i=1,d=d+1,w=w+1;i<n+1;i++,++p,++w,++d) //如果0号单元不用，p应该指向第1个单元开始
    {         //这一点也是自己修改的，课本上都是错的。
        p->data=*d;
        p->weight=*w;
    }

    for(i=n+1;i<=m;i++)  //根结点权值最小的子树合并成一棵新树。
    {
        Select(i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].left=s1;
        HT[i].right=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    Size=m;  //设置Huffman树结点个数。

}

template<class T> void HuffmanTree<T>::Select(int k,int &s1,int &s2)
{
    s1=Min(k);
    s2=Min(k);  //由于标记，s1!=s2;，是最小的两个根结点
}

template<class T> void HuffmanTree<T>::PrintHuffmanTree(HuffmanCode &HC,int n) const  //HC这个参数就是废的
{
    int i,j;
     for(i=1;i<=Size;i++)
     {
         cout<<i<<" "<<HT[i].data<<setw(5)<<HT[i].weight<<setw(5)<<HT[i].left<<setw(5)<<HT[i].right<<setw(5)<<HT[i].parent<<endl;
     }

     cout<<"the result of coding is:"<<endl;
     for(j=1;j<=n;j++)
     {
         cout<<HT[j].data<<"---"<<HC[j]<<endl;

     }
     return;
}


//分为两步
//第一步是生成Huffman树
//第二步是处理Huffman树得到编码

template<class T> void HuffmanTree<T>::HuffmanCoding(HuffmanCode &HC,int n)
{
     int i,start;
     unsigned c,f;
     char *cd;
     HC=new char*[n+1];//开辟一个Huffman编码表，0号单元不可用。
     cd=new char[n];
     cd[n-1]='\0'; //编码临时存放空间，设置每个编码的结束符
     for(i=1;i<=n;i++)
     {
         start=n-1;
         for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
         {
             if(HT[f].left==c)
             {
                 cd[--start]='0';
             }
             else
             {
                 cd[--start]='1';
             }
         }
         HC[i]=new char[n-start];
         strcpy(HC[i],&cd[start]);
     }
     delete cd;
}

//对压缩后的数据文件解码必须借助于Huffman树，
//(1),依次读入文件中的二进制码，从Huffman树的根结点出发，若当前读入0，则走向
// 左孩子，否则走向右孩子。
//(2)一旦到达某一叶子时便译出相应的字符，然后重新从根结点出发继续编码，直到文件结束。


//emmm,这个解码是自己不看书写出来的 厉害厉害

template<class T> void HuffmanTree<T>::HuffmanUncoding(HuffmanCode &HC,int n,char *cd)
{
    char temp[10];
    int i;
    for(i=1;i<=n;i++)
    {
        int m=2*n-1;
        strcpy(temp,HC[i]);
        for(int j=0;temp[j]!='\0';j++)
        {
            if(m<=n)
                break;
            if(temp[j]=='0')
                m=HT[m].left;
            else
                m=HT[m].right;
        }
        cd[i]=HT[m].data;
    }
}
