#include "node.h"
#include <iostream>
using namespace std;

/*������ĵ���������⣬ÿһ������ָ��������һ������
��ַ*/
template <class T> class linkedstack
{
    private:
       linkednode<T> *top;   //��ջ�������������һ����Ա���ݾ͹���
    public:
       linkedstack();
       ~linkedstack();
       //bool isfull() const;  ����������࣬���ﲻ������������
       bool isempty() const;
       bool push(const T val);
       bool pop(T &val);
       bool gettop(T &val);
       void makeempty();
       void show();

};

template<class T> linkedstack<T>::linkedstack() //����һ����ջ��
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
    return top==NULL; //������������ѧ���ģ��ܼ�ࡣ
}

template<class T> bool linkedstack<T>::push(const T val)
{
    //�ڴ����޴󣬲��ÿ�������
    //linkednode<T> *temp=new linkednode<T>(val,top);
    //top=temp;
    /*ֻҪ����new�Ϳ���ʹ�ù��캯�����������¶������ָ��ʱ*/
    top=new linkednode<T>(val,top); //���ϵ�����ܼ��
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
            cout<<temp->data;  //��д���Ǹ�ģ��ֱ���������ˣ���������Ҫ�޸�һ�£����Ҫ�ĳ�������
            temp=temp->link;
        }
        cout<<endl;
    }
    return;
}
