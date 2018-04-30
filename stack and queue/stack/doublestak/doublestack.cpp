#include "doublestack.h"
#include <iostream>
using namespace std;

template<class T> doublestack<T>::doublestack(int size)
{
    vector=new T[size]; //����֣���˳��ջ�Ŀռ䶼���Լ��ڶ������ٵģ�������ֱ�Ӵ���һ������
    maxsize=size;
    bottom[0]=-1;  //���������-1������Ҫ�������Ҳ���ԣ�ֻ����������ܷ��㡣
    bottom[1]=maxsize;
    top[0]=-1;
    top[1]=maxsize;
}

template<class T> bool doublestack<T>::isempty(int i) const
{
    if(i<1||i>2)
    {
        return false;
    }
    else
    {
        if(top[i-1]==bottom[i-1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //���ϴ����ǣ�return top[i-1]==bottom[i-1];
}

template<class T> bool doublestack<T>::isfull() const
{
    /*���ﲻҪ֪���ǵڼ���ջ���ˣ���Ϊһ�����ˣ���һ��һ��Ҳ����
     top[0]+1==top[1]��ջ��������*/


         return top[0]+1==top[1];//������жϱ��ʽ���з���ֵ�ģ�����Ĭ��top[0]�����ջ��ָ�뿪ʼ
}

template<class T> bool doublestack<T>::push(int i,T elem)
{
    /*��ջʱ����ջ�����������м����죬ֱ������ջ��ָ��������
    */
    if(isfull())
    {
        return false;
    }
    else
    {
        if(i-1==0)
        {
            top[0]++;
            vector[top[0]]=elem;
        }
        else
        {
            top[1]--;
            vector[top[1]]=elem;
        }
    }
    return true;

}

template<class T> bool doublestack<T>::pop(int i,T &elem)
{
    if(isempty(i))
    {
        return false;
    }
    else
    {
        if(i==1)
        {
            elem=vector[top[0]];
            top[0]--;
        }
        else
        {
            elem=vector[top[1]];
            top[1]++;
        }
        return true;
    }
}

template<class T> bool doublestack<T>::gettop(int i,T &elem) const
{
    if(!isempty(i))
    {
        elem=vector[top[i-1]];
        return true;
    }
    return false;
}

template<class T> void doublestack<T>::traverse() const
{
    //��ͷ��β�������ջ�е�Ԫ��
    int i;
        i=bottom[0]+1;
        cout<<"the first stack:"<<endl;
        while(i<=top[0])
            {
                cout<<vector[i]<<"  ";
                i++;
            }

        i=top[1];
        cout<<"the second stack:"<<endl;
        while(i<bottom[1])
           {
               cout<<vector[i]<<"  ";
               i++;
           }
          cout<<endl;

}
