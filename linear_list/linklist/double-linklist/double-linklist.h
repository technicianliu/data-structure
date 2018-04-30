/*环装双向链表不再实现，就是双向链表头结点的前驱指向尾结点
尾结点的前驱指向头结点，就是双向链表，判表空的条件可一样
双链表比单链表简单，所以不再实现那么多内容*/
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
        bool Find(int k,T &val) const;//val带回链表中第i个结点
        bool Insert(int k,const T val); //在第i各节点前插入一个结点
        bool Remove(int k,T &val);//删除第i个结点
        void output() const; //输出链表中所有结点
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
    //cout<<"输入结点个数："<<endl;
    //in>>n;
    node<T> *temp=NULL;
    cout<<"输入结点内容："<<endl;
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
    /*这里是一个要注意的点，必须有这个,拷贝构造函数和构造函数
    只会调用一个，如果不这样，那么first仅仅是一个指针*/
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
