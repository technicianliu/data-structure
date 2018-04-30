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
       seqlist(int size=100);   //�����ձ�
       seqlist(const seqlist<T> &List);//�������캮��
       ~seqlist() {delete []first;}
       int length() const {return len;}
       bool getelem(int k,T &val) const;//�ҳ���k��Ԫ�أ���Խ�緵��false
       bool isempty() const {return length==0;}
       int locateelem(const T val) const;//���ص�һ����val��ͬ��Ԫ��λ�ã�����ʧ���򷵻�0
       bool insertelem(int k,const T val); //�ڵ�k��Ԫ��ǰ����Ԫ��
       bool listdelete(int k,T &val);
       void mergelist(const seqlist<T> &La,const seqlist<T> &Lb);//����˳���ĺϲ�
       void Union(const seqlist<T> &List);//ʵ��˳���Ĳ�������

       friend istream& operator>>(istream &in,seqlist<T> &List)  //��������Ķ���ֻ�ܷ�����������������ʱ���Լ�Ūһ��ģ�����
       {
            List.creatlist(in);
            return in;
       }

       friend ostream& operator<<(ostream &out,seqlist<T> &List)
       {
           out<<"˳����е�����Ϊ��"<<endl;
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
{  //�����������˳���Ԫ�������Ƿǵݼ���
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
    len=k; //��Ϊ���k����Զ೤ʱ�䣬
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
           cout<<"�����뽨��˳�������ݸ���:"<<endl;
           in>>n;
           len=n;
           cout<<"������Ӧ���ݣ�"<<endl;
           while(i<n)
           {
               in>>temp;
               if(len!=maxsize)
               {
                   first[i]=temp;
               }
               else
               {
                   cout<<"˳�������!"<<endl;
                   break;
               }
               i++;
           }
}
