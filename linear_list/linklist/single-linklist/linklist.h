/*这里写一个带有头结点的单链表
头结点作用：
1、链表始终有一个头结点，使空表和非空表同一；且对
一个元素来说都有一个唯一的前驱结点。
2、使算法处理结点一致，即对链表中任意元素结点的操作
，都不会改变头结点的值。当链表中最后一个结点的指针域
指向头结点，则是环形链表，则从链表任意结点出发均可找
到链表中的其他结点，单项循环链表和单项链表操作基本一致
，区别在于算法中循环语言的判断条件是不是结点的地址为
空或结点的指针域为空，而是结点的指针域是否指向头结点。
*/
/*上面是重点知识，复制到github的笔记中去*/

/*vector和list实现的都是线性表的操作*/


#include <iostream>
#include "node.h"
using namespace std;


template<class T> class linklist
{
    private:
        node<T> *first;
        node<T> *pcurrent; //这个指针专门指向链表中特定的结点，在这个特定的结点处做一些操作
        int len;//某个对象中结点个数，自己在这个程序中用结点类静态成员数据代替了

        void creatlist(istream &in); //建立一个链表 这两个私有成员函数只能用来帮助实现别的函数，不可以在类外被调用
        void showlist(ostream &out); //输出一个链表 这里显然是为了给下面的两个友元使用。
    public:
        linklist(){first=new node<T>;pcurrent=first;node<T>::length++;} //构造函数初始化一个带头结点的空表
        linklist(linklist<T> &list);   //拷贝构造函数

        ~linklist(){makeempty();}
        void makeempty();

        bool isempty() const {return first->link==NULL;}
        int length() const {return node<T>::length;}

        void locate(const T val); //返回链表中第一个与val值相同的元素地址
        void locateelem(int k);  //返回链表中第k个结点的地址，k越界返回空 ,自己用pcurrent来直接指向结点，不再返回

        T getelem(node<T> *ptr) {return ptr->data;} //获取指定结点的数据值

        bool insert(int k,T val);  //在链表的第k个结点前插入一个值为val的结点
        void insert(const T val);//这个插入实在当前结点后插入,需要先根据要求定位

        bool listdelete(int k,T &val); //删除链表中第k个结点，并将值返回给val
        bool listdelete(T val); //按照给出的关键字把相应结点删除,删除所有与val相同的结点

        void  showlist();

        void creatlist();

        friend istream& operator>>(istream &in,linklist<T> &list) //建立一个链表
        {//重载输入流，用下面函数创建一个新的链表
           list.creatlist(in);
           return in;
        }

        friend ostream& operator<<(ostream &out,linklist<T> &list) //输出所有结点值
        {//这里和上面都有一个问题，为什么不把函数中的内容直接写在这里呢
           list.showlist(out);
           return out;
        }

};


template<class T> linklist<T>::linklist(linklist<T> &list)
{
    /*这里用到了链表类对象的林引用，同一个类之间的对象可以
    直接使用另一个对象的数据与函数。因为封装是针对类内外而言的，
    而且这里进行深拷贝*/
    node<T> *temp=list.first->link,*pt;
    first=new node<T>; node<int>::length++;
    pt=first;
    while(temp!=NULL)
    {
        pt->link=new node<T>(temp->data,NULL);
        pt=pt->link;
        temp=temp->link;
        node<int>::length++;
    }

}

template<class T> void linklist<T>::makeempty()
{
    node<T> *temp=first->link,*pt=NULL;
    if(temp==NULL)
        return;
    while(temp!=NULL)
    {
        pt=temp->link;
        delete []temp;
        temp=pt;
        node<int>::length--;
    }
    first->link=NULL;
    pcurrent=first;
    /*
        node<T> *p;       //答案的这种删除方法更清楚简洁
        while(first->link)
        {
            p=first-link;
            first->link=p->link;
            delete []p;
        }
    */
}

template<class T> void linklist<T>::locate(const T val)
{
    node<T> *temp=first->link;
    while(temp!=NULL)
    {
        if(val==temp->data)
            {
                pcurrent=temp;
                return;
            }
        temp=temp->link;
    }
    return;

    /*node<T> *temp=first->link;
    while(temp!=NULL)
    {
        if(val==temp->data)
            {
                return temp;
            }
        temp=temp->link;
    }
    return NULL;*/ //这段书上源码是把找到的指针返回
}

template<class T> void linklist<T>::locateelem(int k)
{
    node<T> *temp=first->link;
    int i;
    if(k<=0||k>node<T>::length||first->link==NULL)
        return;
    for(i=2;i<=k;i++)
    {
        temp=temp->link;
    }
    pcurrent=temp;
    return;

    /*书本上的实现方式：
    node<T> *p=first->link;
    int i=1;
    while(p&&i<k)
    {
        p=p->link;
        i++;
    }
    return p;*/

}

template<class T> bool linklist<T>::insert(int k,T val)
{
    /*这里要注意因为是单链，所以访问起来不是很方便
    因此指针定位到第k-1个元素比较好处理，这是已知结点
    序号的情况，若是根据结点内容访问，则用需要两个指针
    同时遍历链表，虽然麻烦但却是时间复杂度最小的，当然也可
    以先利用上面的根据内容定位的函数，先把相应指针定位，然后
    再找其前驱结点，比较方便，但时间复杂度就高了。*/
    node<T> *temp=first,*pt;
    int i=0; //自己的程序虽然和书上不一样，但是考虑不周全，看了书上之后才改过来

    if(k<=0||k>node<T>::length+1)
    /*把length加1，因为可能在最后结点的最后插入，书本
    把这个函数处理的比较好，自己的可能比较复杂,书本上的
    可以在空表插入*/
    {
        return false;
    }

    for(i=0;i<k-1;i++)  //i的起始值也很关键
    {
        temp=temp->link;
    }

    pt=new node<T>(val,temp->link);
    temp->link=pt;
    node<T>::length++;  //这个静态成员数据并不是自己增加和减少的，需要人为改动。

    return true;
    /*
    node<T> *p=first,*temp;
    int j=0;
    while(j<k-1)
    {
        p=p->link;
        ++j; //这里不要忘了
    }
    temp=new node<T>(val,p-link);
    p->link=temp;
    return true;
    */
}
/*可以用上面插入结点的函数实现链表的创建*/

template<class T> bool linklist<T>::listdelete(int k,T &val)
{//事实上可以借助定位函数更简单的实现这个函数
    node<T> *pt1=first,*pt2;
    int i;
    if(k<=0||k>node<T>::length)
    {
        return false;
    }
    if(first->link==NULL)
    {
        return false;
    }
    for(i=0;i<k-1;i++)
    {
        pt1=pt1->link;
    }
    pt2=pt1->link;
    val=pt2->data;
    pt1->link=pt2->link;
    delete []pt2;
    node<T>::length--;
    return true;
}

template<class T> void linklist<T>::creatlist(istream &in)
//这个按照书上来写，竟然把输入流类的一个对象拿来用了,流对象应该在内存中有一部分分配的空间
{
      node<T> *p;
      T val;
      int i=1,n;
      cout<<"输入链表结点个数："<<endl;
      in>>n;  //这里是输入结点的个数
      cout<<"输入链表内容："<<endl;
      while(i<=n)
      {
          in>>val;
          p=new node<T>(val); //将新结点始终插入在头结点之后，这种算法不用定位，建表最快捷。
          p->link=first->link;
          first->link=p;
          ++i;
      }
      node<T>::length+=n;
}

template<class T> void linklist<T>::showlist()
{
    node<T> *temp=first->link;
    if(temp==NULL)
    {
        return;
    }
    while(temp!=NULL)
    {
        cout<<temp->data<<"  ";
        temp=temp->link;
    }
    cout<<endl;
}

template<class T> void linklist<T>::showlist(ostream &out)
{  /*我觉得书上这里的重载还是有缺陷，因为似乎
    重载后链表中数据域只能是基本的数据类型*/
    node<T> *p=first->link;
    if(p==NULL)
    {
        return;
    }

    while(p!=NULL)
    {
        out<<p->data<<"  ";
        p=p->link;
    }
    out<<endl;
}

template<class T> bool linklist<T>::listdelete(T val)
{
    node<T> *temp=first->link,*pt=first;
    if(temp==NULL)
        return false;

    while(temp!=NULL)
    {
        if(temp->data==val)
        {
            pt->link=temp->link;
            delete []temp;
            temp=pt->link;
        }
        temp=temp->link;
        pt=pt->link;
    }
    return true;

}

template<class T> void linklist<T>::creatlist()
{ //这个创建函数结点时按插入顺序排列的
    T val;
    node<T> *pt1,*pt2;
    while(cin>>val) //这里在输入时模拟文件的结束
    {
        pt2=new node<T>(val,NULL);
        if(first->link==NULL)
        {
            first->link=pt2;
            pt1=pt2;
            node<T>::length++;
        }
        else
        {
            pt1->link=pt2;
            pt1=pt2;
            node<T>::length++;
        }
    }
}

template<class T> void linklist<T>::insert(const T val)
{ //这函数也可以用来生成链表
    node<T> *temp=new node<T>(val,pcurrent->link);
    pcurrent->link=temp;
}
/*学到了这里对输入流输出流类的理解深一些了
，cin、cout这两个对象是系统创建的与终端分别
有其相对应的关系。而真正输入输出的是两个
操作符，所以重载是对两个操作符的重载。而且cin和
cout都是实参，自己在重载的时候应该用的是形参
，如同重载函数的调用一样，操作符也是根据参数的不
同来决定选择个重载*/
