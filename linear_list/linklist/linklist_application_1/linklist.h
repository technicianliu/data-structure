#include <iostream>
#include "node.h"
using namespace std;


template<class T> class linklist
{
    private:
        node<T> *first;
        node<T> *pcurrent;
    public:
        linklist(){first=new node<T>;pcurrent=first;node<T>::length++;}
        linklist(linklist<T> &list);
        ~linklist(){makeempty();}
        void makeempty();
        void  showlist();
        void creatlist();
        void listplus(const linklist<T> &list1,linklist<T> &list2);
};


template<class T> linklist<T>::linklist(linklist<T> &list)
{

    node<T> *temp=list.first->link,*pt;
    first=new node<T>; node<int>::length++;
    pt=first;
    while(temp!=NULL)
    {
        pt->link=new node<T>(temp->data1,temp->data2,NULL);
        pt=pt->link;
        temp=temp->link;
        node<int>::length++;
    }

}

template<class T> void linklist<T>::makeempty()
{
    node<T> *temp=first->link,*pt=NULL;
    if(temp==NULL)
        return;
    while(temp!=NULL)
    {
        pt=temp->link;
        delete []temp;
        temp=pt;
        node<int>::length--;
    }
    first->link=NULL;
    pcurrent=first;

}


template<class T> void linklist<T>::creatlist()
{
    T m,n;
    node<T> *pt1,*pt2;
    cin>>m>>n;
    while(n!=-1)
    {
        pt2=new node<T>(m,n,NULL);
        if(first->link==NULL)
        {
            first->link=pt2;
            pt1=pt2;
            node<T>::length++;
        }
        else
        {
            pt1->link=pt2;
            pt1=pt2;
            node<T>::length++;
        }
        cin>>m>>n;
    }
}

template<class T> void linklist<T>::showlist()
{
    node<T> *temp=first->link;
    if(temp==NULL)
    {
        return;
    }
    while(temp!=NULL)
    {
        if(temp->data2==0)
        {
            if(temp->data1>0)
            {
               cout<<"+"<<temp->data1;
               temp=temp->link;
            }
            else if(temp->data1<0)
            {
               cout<<"-"<<temp->data1;
               temp=temp->link;
            }
            else
               continue;
        }
        else
        {
            if(temp->data1>0)
            {
               cout<<"+"<<temp->data1<<"x"<<temp->data2;
               temp=temp->link;
            }
            else if(temp->data1<0)
            {
               cout<<"-"<<temp->data1<<"x"<<temp->data2;
               temp=temp->link;
            }
            else
               continue;
        }

    }


    cout<<endl;
}

template<class T> void linklist<T>::listplus(const linklist<T> &list1,linklist<T> &list2)
{ //这个程序处理的多项式系数是顺序增大的，如果系数比较乱，先将其排序就行
    node<T> *pt1,*pt2,*pt3=list2.first;
    pt1=first->link;
    pt2=list1.first->link;

    if(pt1==NULL||pt2==NULL)
        return;

    while(pt1!=NULL&&pt2!=NULL)
    {
        if(pt1->data2==pt2->data2)
        {
            pt3->link=new node<T>(pt1->data1+pt2->data1,pt1->data2,NULL);
            pt1=pt1->link;
            pt2=pt2->link;
            pt3=pt3->link;
        }
        else if(pt1->data2<pt2->data2)
        {
            pt3->link=new node<T>(pt1->data1,pt1->data2,NULL);
            pt1=pt1->link;
            pt3=pt3->link;
        }
        else
        {
            pt3->link=new node<T>(pt2->data1,pt2->data2,NULL);
            pt2=pt2->link;
            pt3=pt3->link;
        }
    }
    while(pt1!=NULL)
    {
        pt3->link=new node<T>(pt1->data1,pt1->data2,NULL);
        pt1=pt1->link;
        pt3=pt3->link;
    }
    while(pt2!=NULL)
    {
        pt3->link=new node<T>(pt2->data1,pt2->data2,NULL);
        pt2=pt2->link;
        pt3=pt3->link;
    }

}

