#include <iostream>
using namespace std;

template<class T> class linkedstack; //要想在下面把linkstack设置为友元函数，就必须在这里声明这个类
template <class T> class linkednode
{
    private:
       T data;
       linkednode<T> *link;
    public:
        linkednode(linkednode<T> *ptr=NULL);
        linkednode(const T &item,linkednode<T> *ptr=NULL);
        friend class linkedstack<T>;
};

template<class T> linkednode<T>::linkednode(linkednode<T> *ptr)
{
    link=ptr;
}

template<class T> linkednode<T>::linkednode(const T &item,linkednode<T> *ptr)
{
    data=item;
    link=ptr;
}


