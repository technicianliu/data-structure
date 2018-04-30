#include <iostream>
using namespace std;
#include "linkstack.h"


template<class T> linkedstack<T>::linkedstack() //建立一个空栈。
{
    top=NULL;
}

template<class T> linkedstack<T>::~linkedstack()
{
    makeempty();
}

template<class T> void linkedstack<T>::makeempty()
{
    linkednode<T> *temp;
    if(top!=NULL)
    {
        while(top)
        {
            temp=top->link;
            delete []top;
            top=temp;
        }
    }
}

template<class T> bool linkedstack<T>::isempty() const
{
    return top==NULL; //这个语句是书上学来的，很简洁。
}

template<class T> bool linkedstack<T>::push(const T &val)
{
    //内存无限大，不用考虑上溢
    linkednode<T> *temp=new linkednode<T>(val,top);
    top=temp;
    /*只要是用new就可以使用构造函数，并不是新定义对象指针时*/
    //top=new linknode<T>(val,top); 书上的这个很简洁
    return true;
}

template<class T> bool linkedstack<T>::pop(T &val)
{
    linkednode<T> *temp;
    if(isempty())
    {
        return false;
    }
    else
    {
        temp=top->link;
        val=top->data;
        delete []top;
        top=temp;
        return true;
    }
}

template<class T> bool linkedstack<T>::gettop( T &val)
{
    if(isempty())
    {
        return false;
    }
    else
    {
        val=top->data;
        return true;
    }
}

template<class T> void linkedstack<T>::show()
{
    linkednode<T> *temp;
    if(isempty())
    {
        return;
    }
    else
    {
        temp=top;
        while(temp)
        {
            cout<<temp->data<<endl;
            temp=temp->link;
        }
    }
    return;
}


