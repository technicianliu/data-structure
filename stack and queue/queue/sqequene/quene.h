/*简单的顺序队列会产生假溢出现象，因此要使用循环队列，
即将队列的数据区看作是头尾相连的循环结构，
循环队列要解决两个问题：
1、如何区分队列和满两个状态？
少用一个空间可以解决这个问题，当front==rear时，队列空；
而当(rear+1)%maxsize==front时队列满。除此之外，还可以
通过设置标志来来区分队列空和满两种状态
2、队尾和队首两个指示器如何从序号最大的空间顺义到序号
最小的空间？
利用模运算解决，即front=(front+1)%maxsize,或rear=(rear+1)%maxsize*/
#include <iostream>
using namespace std;

template<class T> class seqquene
{
   private:
       int front,rear;
       T *thearray;
       int maxsize;

   public:
       seqquene(int size=20);
       ~seqquene() {delete []thearray;}
       bool enquene(const T val);
       bool dequene(T &val);
       bool getfront(T &val) const;
       bool isempty() const {return front==rear;}
       bool isfull() const {return (rear+1)%maxsize==front;}
       int length() const {return (rear-front+maxsize)%maxsize;}
       bool show();
};


template<class T> seqquene<T>::seqquene(int size)
{
    front=0;rear=0;
    maxsize=size;
    thearray=new T[size];
}

template<class T> bool seqquene<T>::enquene(const T val)
{
    if(isfull())
    {
        return false;
    }
    else
    {
        thearray[rear]=val;
        rear=(rear+1)%maxsize;
        return true;
    }
}

template<class T> bool seqquene<T>::dequene(T &val)
{
    if(isempty())
    {
        return false;
    }
    else
    {
        val=thearray[front];
        front=(front+1)%maxsize;
        return true;
    }
}

template<class T> bool seqquene<T>::getfront(T &val) const
{
    if(isempty())
    {
        return false;
    }
    else
    {
        val=thearray[front];
        return true;
    }
}

template<class T> bool seqquene<T>::show()
{
    int i;
    i=front;
    for(;i<10;i++)
        cout<<thearray[i]<<"   ";
    return true;
}
