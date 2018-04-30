#include "doublestack.h"
#include <iostream>
using namespace std;

template<class T> doublestack<T>::doublestack(int size)
{
    vector=new T[size]; //很奇怪，连顺序栈的空间都是自己在堆区开辟的，并不是直接创建一个数组
    maxsize=size;
    bottom[0]=-1;  //这里如果用-1，而不要这个变量也可以，只不过这样会很方便。
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
    //书上代码是：return top[i-1]==bottom[i-1];
}

template<class T> bool doublestack<T>::isfull() const
{
    /*这里不要知道是第几个栈满了，因为一个满了，另一个一定也满了
     top[0]+1==top[1]是栈满的条件*/


         return top[0]+1==top[1];//这里的判断表达式是有返回值的，这里默认top[0]代表的栈从指针开始
}

template<class T> bool doublestack<T>::push(int i,T elem)
{
    /*进栈时两个栈均从两端向中间延伸，直到两个栈顶指针相遇，
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
    //从头到尾输出共享栈中的元素
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
