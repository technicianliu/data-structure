/*����������ó�Ϊ��һ����������Ԫ��
�������ʹ�����ѶȽ��Ͳ��٣��������������
���Խ���������������������һ��ʹ�ã�����
������ֻҪ������ָ�������*/
#include <iostream>
#include "node.h"
using namespace std;
/*����Ϊ�յĳ�Ҫ������front=rear=NULL*/
template<class T> class linkquene
{
     private:
         linknode<T> *front,*rear;  //������ָ��������ʵ�ֶ��в�����
     public:
         linkquene();
         ~linkquene();
         bool isempty() const;
         void enquene(T val);  //��Ҫ����ֵ����Ϊ���в��������
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
       front=rear=new linknode<T>(val);  //�Ѿ�����Ĭ�ϲ���������ֻ��һ��������ȥ
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
        if(!front)  //����Ѷ���ɾ�գ���Ҫ����rear
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
