#include <iostream>
using namespace std;

template<class T> class linkquene;

template<class T> class linknode
{
    friend class linkquene<T>;  //这样做的好处是不用在结点类中声明大量函数，而且结点类使用起来也十分方便
    private:
        linknode<T> *link;  //这里这个指针就是链接结点
        T data;
    public:
        linknode(linknode<T> *ptr=NULL);
        linknode(const T item,linknode<T> *ptr=NULL);

};


template<class T> linknode<T>::linknode(linknode<T> *ptr)
{
    link=ptr;
}

template<class T> linknode<T>::linknode(const T item,linknode<T> *ptr):data(item),link(ptr)
{

}
