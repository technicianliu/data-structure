#include <iostream>
using namespace std;
template <class T> class Seqstack
{
  private:
      int top;      //topΪջ��Ԫ��λ��ָʾ��,topʼ��ָ��ջ����
      int maxsize;  //˳��ջ����������ռ�
      T *thearray;  //thearrayΪ�����ռ��׵�ַ
  public:
      Seqstack(int sz=20);
      ~Seqstack();
      bool push(const T val);   //ջδ������Ԫ��val��ջ
      bool pop( T &val);    //ջ���գ�����ջ��Ԫ�ظ���val
      bool gettop(T &val) const;
      bool isempty() const;
      bool isfull() const;
      bool traverse() const; //��ջ�׵�ջ���������Ԫ��

};

template <class T> Seqstack<T>::Seqstack(int sz)
{
    maxsize=sz;
    thearray=new T[maxsize];
    top=-1;                    //���top=0Ϊ��ջ��־�����ջʱ���Ȳ���Ԫ�أ�Ȼ��ʹtop��1����ջʱ�Ƚ�top��1��Ȼ���ȡԪ��ֵ��
}

template <class T> Seqstack<T>::~Seqstack()
{
    delete []thearray;
}

template <class T> bool Seqstack<T>::push(const T val)
{
    if(isfull())
    {
        cout<<"ջ���磬����ʧ�ܣ�"<<endl;  //��c�У������������ջ���磬������realoc�����·���ռ�
        return false;
    }
    else
    {
        top++;
        *(thearray+top)=val;
        return true;
    }

}

template <class T> bool Seqstack<T>::pop( T &val)
{
    if(isempty())
    {
        cout<<"ջΪ�գ�����ʧ�ܣ�"<<endl;
        return false;
    }
    else
    {
        val=thearray[top];
        top--;
        return true;
        /*���ﲻ��Ҫ����ջ���Ǹ�ֵɾ����ֻ��Ҫȡ�������ˣ�����ջ��ָʾ����
        �ʹ�����������ջ�ˡ�*/
    }
}

template <class T> bool Seqstack<T>::isfull() const
{
    if(top==maxsize-1)  //�鱾����maxsize
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T> bool Seqstack<T>::isempty() const
{
    return top==-1;
}

template <class T> bool Seqstack<T>::gettop(T &val) const
{
    if(isempty())
    {
        return false;
    }

    val=thearray[top];
    return true;
}

template <class T> bool Seqstack<T>::traverse() const
{
    if(isempty())
    {
        return false;
    }
    int i=top;
    while(i!=-1)  //top����ָ��ջ�����������ﲻ��ֱ��ʹ��top
    {
        cout<<thearray[i--]<<" ";
    }
    return true;
}
