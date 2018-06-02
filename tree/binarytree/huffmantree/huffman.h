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
        huff_node():weight(0),parent(0),left(0),right(0) {} //����Ĺ��캯����new���ٵĶ�̬�ռ���Ҳ����ʹ��
};

typedef char** HuffmanCode;  //�����ַ������飻

template<class T> class HuffmanTree
{
     private:
        huff_node<T> *HT;  //�������
        int Size,maxsize;  //�����������ռ�
        int Min(int i) const; //����СȨֵ������ź���
        void Select(int k,int &s1,int &s2); //ѡ�����������Ȩֵ��С��������������
     public:
        HuffmanTree(int sz=100); //Huffman����ʼ��
        ~HuffmanTree() {delete []HT;} //����һ��Huffman��
        void CreatHuffmanTree(T *d,unsigned *w,int n); //����һ��Huffman��
        void PrintHuffmanTree(HuffmanCode &HC,int n) const;  //���Huffman��
        void HuffmanCoding(HuffmanCode &HC,int n); //Huffman����
        void HuffmanUncoding(HuffmanCode &HC,int n,char *cd);

};


template<class T> int HuffmanTree<T>::Min(int i) const  //��ǰȨֵ���е���СȨֵ,��Huffman����ĳ�Ա��������˿���ֱ��ʹ��HT
{
    //Ҫ��һ����������С����ȴ��û��ʲô��׼����������������С����ʱ
    //����С����ʱ��ʼ��һ���ܴ��������������ʱ��ʼ��һ����С����
    //���߽�k��ʼ��Ϊ�����е�һ������
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
    HT[flag].parent=1;  //��ֹ�ý���ٴα��Ƚϡ���Ϊ��Ҫ������������СȨֵ�ĳ������С�
    return flag;
}

template<class T> HuffmanTree<T>::HuffmanTree(int sz)
{
    Size=0;
    maxsize=sz;
    HT=new huff_node<T>[sz];   //�����Ѿ��Ը���Ȩֵ��ָʾ����ʼ�����ˣ���Ĭ�ϲ�����
}

template<class T> void HuffmanTree<T>::CreatHuffmanTree(T *d,unsigned *w,int n)
//����һ��n��Ҷ�ӽ��(��Ȩ���)��Huffman�������У���Ȩ�����������������d�ṩ��Ȩֵ������w�ṩ
{
    int i,m,s1,s2;
    huff_node<T> *p;

    if(n<1) {return;}
    m=2*n-1; //m����������
    if(maxsize<m+1)
    {
        delete []HT;
        HT=new huff_node<T>[m+1]; //0�ŵ�Ԫ����
        maxsize=m+1;
    }

    for(p=HT+1,i=1,d=d+1,w=w+1;i<n+1;i++,++p,++w,++d) //���0�ŵ�Ԫ���ã�pӦ��ָ���1����Ԫ��ʼ
    {         //��һ��Ҳ���Լ��޸ĵģ��α��϶��Ǵ�ġ�
        p->data=*d;
        p->weight=*w;
    }

    for(i=n+1;i<=m;i++)  //�����Ȩֵ��С�������ϲ���һ��������
    {
        Select(i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].left=s1;
        HT[i].right=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    Size=m;  //����Huffman����������

}

template<class T> void HuffmanTree<T>::Select(int k,int &s1,int &s2)
{
    s1=Min(k);
    s2=Min(k);  //���ڱ�ǣ�s1!=s2;������С�����������
}

template<class T> void HuffmanTree<T>::PrintHuffmanTree(HuffmanCode &HC,int n) const  //HC����������Ƿϵ�
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


//��Ϊ����
//��һ��������Huffman��
//�ڶ����Ǵ���Huffman���õ�����

template<class T> void HuffmanTree<T>::HuffmanCoding(HuffmanCode &HC,int n)
{
     int i,start;
     unsigned c,f;
     char *cd;
     HC=new char*[n+1];//����һ��Huffman�����0�ŵ�Ԫ�����á�
     cd=new char[n];
     cd[n-1]='\0'; //������ʱ��ſռ䣬����ÿ������Ľ�����
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

//��ѹ����������ļ�������������Huffman����
//(1),���ζ����ļ��еĶ������룬��Huffman���ĸ�������������ǰ����0��������
// ���ӣ����������Һ��ӡ�
//(2)һ������ĳһҶ��ʱ�������Ӧ���ַ���Ȼ�����´Ӹ��������������룬ֱ���ļ�������


//emmm,����������Լ�������д������ ��������

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
