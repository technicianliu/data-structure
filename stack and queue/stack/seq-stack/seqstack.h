#include <iostream>
using namespace std;
template <class T> class Seqstack
{
  private:
      int top;      //top为栈顶元素位置指示器,top始终指向栈顶。
      int maxsize;  //顺序栈所允许的最大空间
      T *thearray;  //thearray为连续空间首地址
  public:
      Seqstack(int sz=20);
      ~Seqstack();
      bool push(const T val);   //栈未满，将元素val进栈
      bool pop( T &val);    //栈不空，弹出栈顶元素赋予val
      bool gettop(T &val) const;
      bool isempty() const;
      bool isfull() const;
      bool traverse() const; //自栈底到栈顶输出所有元素

};

template <class T> Seqstack<T>::Seqstack(int sz)
{
    maxsize=sz;
    thearray=new T[maxsize];
    top=-1;                    //如果top=0为空栈标志，则进栈时，先插入元素，然后使top加1，出栈时先将top减1，然后获取元素值。
}

template <class T> Seqstack<T>::~Seqstack()
{
    delete []thearray;
}

template <class T> bool Seqstack<T>::push(const T val)
{
    if(isfull())
    {
        cout<<"栈上溢，操作失败！"<<endl;  //在c中，这里如果遇到栈上溢，可以用realoc来重新分配空间
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
        cout<<"栈为空，操作失败！"<<endl;
        return false;
    }
    else
    {
        val=thearray[top];
        top--;
        return true;
        /*这里不需要将出栈的那个值删掉，只需要取出就行了，下移栈顶指示器，
        就代表将该数据退栈了。*/
    }
}

template <class T> bool Seqstack<T>::isfull() const
{
    if(top==maxsize-1)  //书本上是maxsize
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
    while(i!=-1)  //top必须指向栈顶，所以这里不能直接使用top
    {
        cout<<thearray[i--]<<" ";
    }
    return true;
}
