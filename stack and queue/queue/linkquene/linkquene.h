/*将这个类设置成为另一个结点类的友元类
，本身就使操作难度降低不少，而且在这个类中
可以将结点类像基本的数据类型一样使用，所以
本类中只要有两个指针就行了*/
#include <iostream>
#include "node.h"
using namespace std;
/*队列为空的充要条件是front=rear=NULL*/
template<class T> class linkquene
{
     private:
         linknode<T> *front,*rear;  //这两个指针是用来实现队列操作的
     public:
         linkquene();
         ~linkquene();
         bool isempty() const;
         void enquene(T val);  //不要返回值是因为队列不可能溢出
         bool dequene(T &val);
         bool getfront(T &val) const;
         bool show() const;
         void makeempty();
         int length() const;

};

template<class T> linkquene<T>::linkquene()
{
    front=NULL;
    rear=NULL;
}

template<class T> linkquene<T>::~linkquene()
{
    makeempty();
}

template<class T> bool linkquene<T>::isempty() const
{
    return front==NULL;
}

template<class T> void linkquene<T>::enquene(T val)
{
   if(front==NULL)
   {
       front=rear=new linknode<T>(val);  //已经有了默认参数，可以只传一个参数进去
   }
   else
   {
       rear->link=new linknode<T>(val);
       rear=rear->link;
   }
}

template<class T> bool linkquene<T>::dequene(T &val)
{
    linknode<T> *temp;
    if(isempty())
    {
        return false;
    }
    else
    {
        temp=front;
        val=temp->data;
        front=front->link;
        delete []temp;
        if(!front)  //如果把队列删空，就要重置rear
        {
            rear=front;
        }
        return true;
    }
}


template<class T> void linkquene<T>::makeempty()
{
    linknode<T> *temp;
    if(isempty())
    {
        return;
    }
    else
    {
        while(front!=NULL)
        {
            temp=front;
            front=front->link;
            delete []temp;
        }
        rear=front;
    }
}

template<class T> bool linkquene<T>::getfront(T &val) const
{
    if(front==NULL)
        return false;
    val=front->data;
    return true;
}


template<class T> int linkquene<T>::length() const
{
    int i=0;
    linknode<T> *temp=front;
    while(temp!=NULL)
    {
        i++;
        temp=temp->link;
    }
    return i;
}

template<class T> bool linkquene<T>::show() const
{
    linknode<T> *temp=front;
    if(temp==NULL)
    {
        return false;
    }
    while(temp!=NULL)
    {
        cout<<temp->data<<"  ";
        temp=temp->link;
    }

    cout<<endl;
    return true;
}
