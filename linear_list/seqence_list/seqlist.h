#include <iostream>
using namespace std;

template<class T> class seqlist
{
   private:
       T *first;
       int len;
       int maxsize;

       void creatlist(istream &in);
   public:
       seqlist(int size=100);   //创建空表
       seqlist(const seqlist<T> &List);//拷贝构造寒素
       ~seqlist() {delete []first;}
       int length() const {return len;}
       bool getelem(int k,T &val) const;//找出第k个元素，如越界返回false
       bool isempty() const {return length==0;}
       int locateelem(const T val) const;//返回第一个与val相同的元素位置，查找失败则返回0
       bool insertelem(int k,const T val); //在第k个元素前插入元素
       bool listdelete(int k,T &val);
       void mergelist(const seqlist<T> &La,const seqlist<T> &Lb);//有序顺序表的合并
       void Union(const seqlist<T> &List);//实现顺序表的并集操作

       friend istream& operator>>(istream &in,seqlist<T> &List)  //这个函数的定义只能放在这里，或者在类外的时候自己弄一个模板参数
       {
            List.creatlist(in);
            return in;
       }

       friend ostream& operator<<(ostream &out,seqlist<T> &List)
       {
           out<<"顺序表中的数据为："<<endl;
           T temp;
           int i=1;
           while(i<=List.len)
           {
               List.getelem(i,temp);
               out<<temp<<" ";
               i++;
           }
           out<<endl;
           return out;
       }

};

template<class T> seqlist<T>::seqlist(int size)
{
    first=new T[size];
    len=0;
    maxsize=size;
}

template<class T> seqlist<T>::seqlist(const seqlist<T> &List)
{
    int i;
    maxsize=List.maxsize;
    len=List.len;
    first=new T[maxsize];
    for(i=0;i<List.length;i++)
    {
        first[i]=List.first[i];
    }
}

template<class T> bool seqlist<T>::getelem(int k,T &val) const
{
    if(k>=len+1||k<0)
        return false;
    else
    {
        val=first[k-1];
    }
    return true;
}

template<class T> int seqlist<T>::locateelem(const T val) const
{
    int i;
    for(i=0;i<len;i++)
    {
        if(first[i]==val)
            return i+1;
    }
    return 0;
}

template<class T> bool seqlist<T>::insertelem(int k,const T val)
{
    int i;
    if(k<=0||k>len+1||len==maxsize)
        return false;
    else if(k==len+1)
    {
        first[len]=val;
        len++;
    }
    else
    {
        for(i=len-1;i>=k-1;i--)
        {
            first[i+1]=first[i];
        }
        first[k-1]=val;
        len++;
    }
    return true;
}

template<class T> bool seqlist<T>::listdelete(int k,T &val)
{
    int i;
    if(k<=0||k>len||len==0)
        return false;
    else
    {
        val=first[k-1];
        for(i=k-1;i<len-1;i++)
        {
            first[i]=first[i+1];
        }
        len--;
    }
    return true;
}

template<class T> void seqlist<T>::mergelist(const seqlist<T> &La,const seqlist<T> &Lb)
{  //这里假设两个顺序表元素排序是非递减的
    T tempa,tempb;

    int i=1,j=1,k=0;
    int len_a,len_b;

    len_a=La.length();
    len_b=Lb.length();

    while(i<=len_a&&j<=len_b)
    {
        La.getelem(i,tempa);
        Lb.getelem(j,tempb);

       if(tempa>=tempb)
        {
            first[k++]=tempa;
            i++;
        }
        else
        {
            first[k++]=tempb;
            j++;
        }
    }

    while(i<=len_a)
    {
        getelem(i,tempa);
        first[k++]=tempa;
        i++;
    }
    while(j<=len_b)
    {
        getelem(j,tempb);
        first[k++]=tempb;
        j++;
    }
    len=k; //因为这个k多调试多长时间，
}

template<class T> void seqlist<T>::Union(const seqlist<T> &List)
{
    T temp;
    int len_l=List.len,i;

    for(i=0;i<len_l;i++)
    {
        getelem(i,temp);
        for(i=0;i<len;i++)
        {
            if(first[i]==temp)
                break;
        }
        if(i==len)
        {
            first[len]=temp;
            len++;
        }
    }
}

template<class T> void seqlist<T>::creatlist(istream &in)
{
           T temp;
           int i=0,n;
           cout<<"请输入建立顺序表的数据个数:"<<endl;
           in>>n;
           len=n;
           cout<<"输入相应数据："<<endl;
           while(i<n)
           {
               in>>temp;
               if(len!=maxsize)
               {
                   first[i]=temp;
               }
               else
               {
                   cout<<"顺序表已满!"<<endl;
                   break;
               }
               i++;
           }
}
