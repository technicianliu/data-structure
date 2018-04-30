/*�򵥵�˳����л����������������Ҫʹ��ѭ�����У�
�������е�������������ͷβ������ѭ���ṹ��
ѭ������Ҫ����������⣺
1��������ֶ��к�������״̬��
����һ���ռ���Խ��������⣬��front==rearʱ�����пգ�
����(rear+1)%maxsize==frontʱ������������֮�⣬������
ͨ�����ñ�־�������ֶ��пպ�������״̬
2����β�Ͷ�������ָʾ����δ�������Ŀռ�˳�嵽���
��С�Ŀռ䣿
����ģ����������front=(front+1)%maxsize,��rear=(rear+1)%maxsize*/
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
