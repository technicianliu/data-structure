/*��װ˫��������ʵ�֣�����˫������ͷ����ǰ��ָ��β���
β����ǰ��ָ��ͷ��㣬����˫�������б�յ�������һ��
˫����ȵ�����򵥣����Բ���ʵ����ô������*/
#include <iostream>
#include "node.h"
using namespace std;

template<class T> class linklist
{
    private:
        node<T> *first;
        int len=0;
        void creatlist(istream &in);
    public:
        linklist() {first=new node<T>;first->prior=first;first->next=first;len++;}
        linklist(const linklist<T> &list1);
        ~linklist() {makeempty();}
        void makeempty();
        bool isempty() {return first->next==first;}
        bool Find(int k,T &val) const;//val���������е�i�����
        bool Insert(int k,const T val); //�ڵ�i���ڵ�ǰ����һ�����
        bool Remove(int k,T &val);//ɾ����i�����
        void output() const; //������������н��
        friend istream& operator >>(istream &in,linklist<T> &list1)
        {
            list1.creatlist(in);
            return in;
        }
};

template<class T> void linklist<T>::creatlist(istream &in)
{
    T val;
    //int i=1,n;
    //cout<<"�����������"<<endl;
    //in>>n;
    node<T> *temp=NULL;
    cout<<"���������ݣ�"<<endl;
    while(in>>val)
    {
        //in>>val;
        if(first->next==first)
        {
            first->next=new node<T>(val,first,NULL);
            len++;
        }
        else
        {
            temp=new node<T>(val,first,first->next);
            first->next=temp;
            temp->next->prior=temp;
            len++;
        }
        //++i;
    }

}

template<class T> linklist<T>::linklist(const linklist<T> &list1)
{

    node<T> *temp=list1.first->next,*pt1,*pt2=NULL;
    if(temp==NULL)
       return;
    first=new node<T>;
    /*������һ��Ҫע��ĵ㣬���������,�������캯���͹��캯��
    ֻ�����һ�����������������ôfirst������һ��ָ��*/
    pt2=new node<T>(temp->data,first,NULL);
    pt1=pt2;
    first->next=pt1;
    temp=temp->next;
    len=len+1;
    while(temp!=NULL)
    {


            pt2=new node<T>(temp->data,pt1,NULL);
            pt1->next=pt2;
            pt1=pt2;
            temp=temp->next;
            len++;

    }

}

template<class T> void linklist<T>::makeempty()
{
    node<T> *temp=first->next,*pt;
    while(temp!=NULL)
    {
        pt=temp->next;
        delete []temp;
        temp=pt;
    }
    len=1;
}

template<class T> bool linklist<T>::Find(int k,T &val) const
{
    node<T> *temp=first;
    int i;
    if(k<=0||k>len)
        return false;
    for(i=0;i<k;i++)
    {
        temp=temp->next;
    }
    val=temp->data;
    return true;
}

template<class T> bool linklist<T>::Insert(int k,T val)
{
    node<T> *temp=first,*pt;
    int i;
    if(k<=0||k>len)
        return false;
    for(i=0;i<k-1;i++)
    {
        temp=temp->next;
    }
    pt=new node<T>(val,temp,temp->next);
    temp->next=pt;
    pt->next->prior=pt;
    len++;
    return true;
}

template<class T> bool linklist<T>::Remove(int k,T &val)
{
    int i;
    node<T> *temp=first,*pt;
    if(k<=0||k>len)
        return false;

        for(i=0;i<k;i++)
        {
           temp=temp->next;
        }
        pt=temp->prior;
        val=temp->data;
        pt->next=temp->next;
        if(k<len)
        {
            temp->next->prior=pt;
        }
        delete []temp;
        len--;
        return  true;
}

template<class T> void linklist<T>::output() const
{
    node<T> *temp=first->next;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
